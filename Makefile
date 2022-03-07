TEST_PR = testPriority
TEST_SQ = testStackQueue
TEST_FILLS = testFills

OBJS_COLORPICKERS = imageTileColorPicker.o negativeColorPicker.o censorColorPicker.o solidColorPicker.o rainbowColorPicker.o
OBJS_MAIN = main.o
OBJS_TEST_PR = testPriority.o priority.o
OBJS_TEST_FILLS = testFills.o priority.o
OBJS_TEST_SQ = testStackQueue.o
OBJS_UTILS  = animation.o lodepng.o HSLAPixel.o PNG.o

INCLUDE_PR = pixelpoint.h priority.h
INCLUDE_SQ = stack.h queue.h stack.cpp queue.cpp
INCLUDE_FILLS = pixelpoint.h priority.h filler.h filler.cpp imageTileColorPicker.h negativeColorPicker.h censorColorPicker.h solidColorPicker.h rainbowColorPicker.o
INCLUDE_UTILS = cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm

all: $(TEST_FILLS) $(TEST_SQ) $(TEST_PR)

$(TEST_PR) : $(OBJS_TEST_PR) lodepng.o HSLAPixel.o PNG.o
	$(LD) $^ $(LDFLAGS) -o $@

$(TEST_SQ) : $(OBJS_TEST_SQ)
	$(LD) $^ $(LDFLAGS) -o $@

$(TEST_FILLS) : $(OBJS_COLORPICKERS) $(OBJS_TEST_FILLS) $(OBJS_UTILS)
	$(LD) $^ $(LDFLAGS) -o $@

testPriority.o : testPriority.cpp $(INCLUDE_PR)
	$(CXX) $(CXXFLAGS) $< -o $@

testStackQueue.o : testStackQueue.cpp $(INCLUDE_SQ)
	$(CXX) $(CXXFLAGS) $< -o $@

testFills.o : testFills.cpp $(INCLUDE_FILLS) $(INCLUDE_PR) $(INCLUDE_SQ) $(INCLUDE_UTILS)
	$(CXX) $(CXXFLAGS) $< -o $@

# Pattern rules for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

PNG.o : cs221util/PNG.cpp $(INCLUDE_UTILS)
	$(CXX) $(CXXFLAGS) $< -o $@

HSLAPixel.o : cs221util/HSLAPixel.cpp $(INCLUDE_UTILS)
	$(CXX) $(CXXFLAGS) $< -o $@

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(TEST_PR) $(TEST_SQ) $(TEST_FILLS) $(OBJS_DIR) *.o
