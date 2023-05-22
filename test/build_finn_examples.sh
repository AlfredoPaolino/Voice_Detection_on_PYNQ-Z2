#!/bin/bash

#script for building finn examples
FINN_EXAMPLES=/home/alessio/Desktop/Ingegneria/Torino/Courses/SoC/finn-examples

# cd into finn submodule
cd $FINN_EXAMPLES/build/finn

# launch the build on the bnn-pynq folder
bash run-docker.sh build_custom $FINN_EXAMPLES/build/kws
