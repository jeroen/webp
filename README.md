# webp

##### *A New Format for Lossless and Lossy Image Compression*

[![Build Status](https://travis-ci.org/jeroen/webp.svg?branch=master)](https://travis-ci.org/jeroen/webp)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/jeroen/webp?branch=master&svg=true)](https://ci.appveyor.com/project/jeroen/webp)
[![Coverage Status](https://codecov.io/github/jeroen/webp/coverage.svg?branch=master)](https://codecov.io/github/jeroen/webp?branch=master)
[![CRAN_Status_Badge](http://www.r-pkg.org/badges/version/webp)](https://cran.r-project.org/package=webp)
[![CRAN RStudio mirror downloads](http://cranlogs.r-pkg.org/badges/webp)](https://cran.r-project.org/package=webp)

> Lossless webp images are 26% smaller in size compared to PNG. Lossy
  webp images are 25-34% smaller in size compared to JPEG. This package reads
  and writes webp images into a 3 (rgb) or 4 (rgba) channel bitmap array using
  conventions from the 'jpeg' and 'png' packages.

## Hello World

```r
# Convert to webp
library(png)
img <- readPNG(system.file("img", "Rlogo.png", package="png"))
write_webp(img, "rlogo.webp")
browseURL("rlogo.webp")
rm(img)

# Convert from webp
library(jpeg)
img <- read_webp("rlogo.webp")
writeJPEG(img, "rlogo.jpeg")
browseURL("rlogo.jpeg")
```

## Installation

Binary packages for __OS-X__ or __Windows__ can be installed directly from CRAN:

```r
install.packages("webp")
```

Installation from source on Linux or OSX requires [`libwebp`](https://developers.google.com/speed/webp/). On __Debian__ or __Ubuntu__ install [libwebp-dev](https://packages.debian.org/testing/libwebp-dev):

```
sudo apt-get install -y libwebp-dev
```

On __Fedora__ we need [libwebp-devel](https://apps.fedoraproject.org/packages/libwebp-devel):

```
sudo yum install libwebp-devel
````

On __CentOS / RHEL__ we install [libwebp-devel](https://apps.fedoraproject.org/packages/libwebp-devel) via EPEL:

```
sudo yum install epel-release
sudo yum install libwebp-devel
```

On __OS-X__ use [webp](https://github.com/Homebrew/homebrew-core/blob/master/Formula/webp.rb) from Homebrew:

```
brew install webp
```
