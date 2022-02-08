#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "sketchify.h"
#include "cs221util/PNG.h"

using namespace cs221util;

/**
 * Simple testing macro
 * @param src   path to source image to sketchify
 * @param dst   destination path
 * @param exp   path to expected output image
 */
#define TEST_SKETCH(src, dst, exp) { \
	sketchify(src, dst);         \
	PNG expIm, outIm;            \
	expIm.readFromFile(exp);     \
	outIm.readFromFile(dst);     \
	REQUIRE(outIm==expIm);       \
}

TEST_CASE("basic::sketchify","[weight=0][part=basic]"){
	TEST_SKETCH("given_imgs/in_0.png", "out0.png", "given_imgs/out_0.png");
	TEST_SKETCH("given_imgs/in_1.png", "out1.png", "given_imgs/out_1.png");
	TEST_SKETCH("given_imgs/in_2.png", "out2.png", "given_imgs/out_2.png");
	TEST_SKETCH("given_imgs/in_3.png", "out3.png", "given_imgs/out_3.png");
}
