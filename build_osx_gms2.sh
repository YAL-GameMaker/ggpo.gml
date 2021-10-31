#!/bin/sh
echo ========================================================================================
g++ -m64\
  -std=c++17 \
  ggpo_gml/*.cpp \
  src/lib/ggpo/backends/*.cpp \
  src/lib/ggpo/network/*.cpp \
  src/lib/ggpo/*.cpp \
  -Wl,-rpath,assets/ -fPIC \
  -DGML_SOCKETS \
  -Isrc/include \
  -Isrc/lib/ggpo \
  -shared -o ggpo_gml_23/extensions/ggpo_gml/ggpo_gml.dylib
