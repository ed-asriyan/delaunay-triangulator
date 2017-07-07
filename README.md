# Delaunay triangulator
## Dependencies
* [OpenCv](http://opencv.org/)
  
  Installation on Debian/Ubuntu:
  ```bash
  sudo apt install libopencv-dev 
  ```
* [Delaunay](https://github.com/eloraiby/delaunay) as git module
* [Argparse](https://github.com/cofyc/argparse) as git module

## Build
```bash
cmake CMakeLists.txt
make
```
It download git modules and build the executable.

## Usage
```
Usage: delaunay_triangulator [options] [[--] args]
   or: delaunay_triangulator [options]

    -h, --help                show this help message and exit

Basic options
    -s, --source=<str>        [ camera ] or file path; default: "camera"
    -c, --count=<int>         points number; default: 5000
    -g, --generator=<str>     [ rand, canny, edges ] points generator; default: "rand"
    -d, --drawer=<str>        [ filled, edges, edges_thick ] drawer method; default: "filled"

Generator canny options
    --th1=<int>               threshold1; default: 10
    --th2=<int>               threshold2; default: 50

Generator edges options
    --edge_value=<int>        edge detect value; default: 8
```

## Point generator algorithms
* `rand` - random points
* `canny` - use OpenCv canny algorithm to detect edges on the image
* `edges` - algorithm to detect edges on the image used on [this repo](https://github.com/timbennett/delaunay/blob/master/index.js#L331)

## Drawing algorithm
* `filled` - draw filled triangles
* `edges` - draw only triangles edges
* `edges_thick` - draw only triangles edges, the larger the triangle, the thicker the side
