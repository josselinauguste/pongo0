#!/bin/bash

cd src/
make
cd ..
./build_linux/pongo $1 $2