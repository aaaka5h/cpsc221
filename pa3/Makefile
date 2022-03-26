EXEPTree = testPTree
OBJS  = PNG.o HSLAPixel.o lodepng.o hue_utils.o testPTree.o ptree.o

CXX = clang++
CXXFLAGS = -stdlib=libc++ -std=c++1y -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -stdlib=libc++ -std=c++1y -lc++abi -lpthread -lm

all : testPTree

$(EXEPTree) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXEPTree)

testPTree.o : testPTree.cpp ptree.h ptree-private.h cs221util/PNG.h cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) testPTree.cpp

ptree.o : ptree.cpp ptree.h ptree-private.h hue_utils.h
	$(CXX) $(CXXFLAGS) -Wfloat-conversion ptree.cpp

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

HSLAPixel.o : cs221util/HSLAPixel.cpp cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/HSLAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

hue_utils.o : hue_utils.cpp hue_utils.h
	$(CXX) $(CXXFLAGS) hue_utils.cpp

clean :
	-rm -f *.o $(EXEPTree)
