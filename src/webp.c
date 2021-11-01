#include <Rinternals.h>
#include <webp/decode.h>
#include <webp/encode.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

SEXP R_webp_get_info(SEXP buf){
  SEXP out = allocVector(INTSXP, 2);
  if (!WebPGetInfo(RAW(buf), LENGTH(buf), &INTEGER(out)[0], &INTEGER(out)[1]))
    Rf_error("Failed to read buffer webp image");
  return out;
}

SEXP R_webp_decode(SEXP buf){
  int width;
  int height;
  uint8_t *rgba = WebPDecodeRGBA(RAW(buf), LENGTH(buf), &width, &height);
  if(!rgba)
    Rf_error("Failed to read buffer webp image");
  int picture = width * height * 4;
  SEXP image = PROTECT(allocVector(RAWSXP, picture));
  SEXP dim = PROTECT(allocVector(INTSXP, 3));
  INTEGER(dim)[0] = 4;
  INTEGER(dim)[1] = width;
  INTEGER(dim)[2] = height;
  setAttrib(image, R_DimSymbol, dim);
  memcpy(RAW(image), rgba, picture);
  free(rgba);
  UNPROTECT(2);
  return image;
}

SEXP R_webp_encode(SEXP img, SEXP quality){
  int *dim = INTEGER(getAttrib(img, R_DimSymbol));
  int qual = asInteger(quality);
  int channel = dim[0];
  int width = dim[1];
  int height = dim[2];
  uint8_t *buf;
  size_t len;
  if(channel == 3){
    len = (qual == NA_INTEGER) ?
      WebPEncodeLosslessRGB(RAW(img), width, height, width * channel, &buf) :
      WebPEncodeRGB(RAW(img), width, height, width * channel, qual, &buf);
  } else {
    len = (qual == NA_INTEGER) ?
      WebPEncodeLosslessRGBA(RAW(img), width, height, width * channel, &buf) :
      WebPEncodeRGBA(RAW(img), width, height, width * channel, qual, &buf);
  }
  SEXP out = allocVector(RAWSXP, len);
  memcpy(RAW(out), buf, len);
  free(buf);
  return out;
}
