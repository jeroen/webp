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
  SEXP image = allocVector(RAWSXP, picture);
  SEXP dim = allocVector(INTSXP, 3);
  INTEGER(dim)[0] = 4;
  INTEGER(dim)[1] = width;
  INTEGER(dim)[2] = height;
  setAttrib(image, mkString("dim"), dim);
  memcpy(RAW(image), rgba, picture);
  free(rgba);
  return image;
}

SEXP R_webp_encode(SEXP img, SEXP quality){
  int *dim = INTEGER(getAttrib(img, mkString("dim")));
  int channel = dim[0];
  int width = dim[1];
  int height = dim[2];
  uint8_t *buf;
  size_t len;
  if(channel == 3){
    len = WebPEncodeRGB(RAW(img), width, height, width * channel, asInteger(quality), &buf);
  } else {
    len = WebPEncodeRGBA(RAW(img), width, height, width * channel, asInteger(quality), &buf);
  }
  SEXP out = allocVector(RAWSXP, len);
  memcpy(RAW(out), buf, len);
  free(buf);
  return out;
}
