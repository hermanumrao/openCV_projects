LIB_DIR=/usr/lib/x86_64-linux-gnu/


# Generate linker flags for all OpenCV libraries
LIBS=$(ls $LIB_DIR/libopencv*.so| grep -v 'lib3d\.so' | sed -E 's/.*\/lib([^\/]+)\.so$/-l\1/' | tr '\n' ' ')


g++ -Wall -std=c++11 $1 -I/usr/include/opencv4 -L/  -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_core

