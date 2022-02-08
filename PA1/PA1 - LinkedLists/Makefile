EXEImglist = testimglist
OBJS  = PNG.o HSLAPixel.o lodepng.o testimglist.o imglist.o

CXX = clang++
CXXFLAGS = -stdlib=libc++ -std=c++1y -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -stdlib=libc++ -std=c++1y -lc++abi -lpthread -lm

all : testimglist

$(EXEImglist) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXEImglist)

testimglist.o : testimglist.cpp imglist.h cs221util/PNG.h cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) testimglist.cpp

imglist.o : imglist.cpp imglist.h
	$(CXX) $(CXXFLAGS) -Wfloat-conversion imglist.cpp

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

HSLAPixel.o : cs221util/HSLAPixel.cpp cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/HSLAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

clean :
	-rm -f *.o $(EXEImglist)
