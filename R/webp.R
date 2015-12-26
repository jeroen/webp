#' Webp image format
#'
#' Read and write webp images into a raw bitmap array.
#'
#' @export
#' @useDynLib webp R_webp_decode
webp_read <- function(buf) {
  if(is.character(buf))
    buf <- readBin(buf[1], raw(), file.info(buf)$size)
  stopifnot(is.raw(buf))
  out <- .Call(R_webp_decode, buf)
  class(out) <- c("rawimg", class(out))
  out
}

#' @export
#' @useDynLib webp R_webp_encode
webp_write <- function(img, file = NULL, quality = 100) {
  channels = dim(img)[1]
  stopifnot(channels == 3 || channels == 4)
  buf <- .Call(R_webp_encode, img, quality)
  if(is.character(file))
    writeBin(buf, file)
  else
    structure(buf, class = "webp")
}

#' @useDynLib webp R_webp_get_info
webp_dims <- function(buf) {
  stopifnot(is.raw(buf))
  .Call(R_webp_get_info, buf)
}

#' @export
print.rawimg <- function(x, ...){
  dims <- dim(x)
  cat(sprintf("raw image (%d x %d) with %d channels\n", dims[2], dims[3], dims[1]))
  invisible()
}

#' @export
print.webp <- function(x, ...){
  dims <- webp_dims(x)
  cat(sprintf("webp buffer (%d x %d)\n", dims[1], dims[2]))
  invisible()
}
