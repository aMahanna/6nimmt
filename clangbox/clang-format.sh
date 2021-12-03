#!/bin/sh
cd ${PWD}/clangbox
docker build -t clangbox .
cd ..
docker run -v ${PWD}:/6nimmt -ti clangbox:latest