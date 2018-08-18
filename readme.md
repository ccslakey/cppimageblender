compile with clang from a command line (bash or the like):

$ g++ $(pkg-config --cflags --libs opencv) blendImgs.cpp -o blender
