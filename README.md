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

    -h, --help            show this help message and exit

Basic options
    -s, --source=<str>    file path
    -d, --detect=<int>    edge detect; default: 80
    -c, --count=<int>     point max num; default: 5000
    -b, --blur=<int>      blur size; default: 2
    -e, --edge=<int>      edge size; default: 6
    -p, --pixel=<int>     pixel limit; default: 8000000
```
