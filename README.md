# yaQThreadPool

Yet another Qt thread pool.

## Purpose

This is a Qt library to extend Qt capabilities about threads pool.

Why another thread pool? Qt allows to create pool of threads of objects
that run once and then stop.
This is ok for a lot of scenarios, but if you want your objects to live
more time that a single shot, this is your library.

## Prerequisites

You can build your self, in this case you need:

* cmake
* Qt

If you have docker, you're done.

## Build & run tests

### Manual way

```bash
mkdir build
cd build
cmake ..
make -j
GTEST_COLOR=1 ./tests/test-yatp
```

### Docker way

Just run this to build & run tests:

```bash
./build.sh
```

This will use docker image
[docker-qt-builder](https://hub.docker.com/r/ociotec/docker-qt-builder/) ([GitHub](https://github.com/ociotec/docker-qt-builder))
as builder.
