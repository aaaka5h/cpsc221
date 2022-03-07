#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"
#include <limits.h>
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "filler.h"
#include "solidColorPicker.h"
#include "imageTileColorPicker.h"
#include "negativeColorPicker.h"
#include "censorColorPicker.h"
#include "rainbowColorPicker.h"

using namespace std;
using namespace cs221util;

#define IMAGEDIR "images/"
#define SOLNIMGDIR "soln_images/"

#define FUNCTORTESTHEIGHT 150
#define FUNCTORTESTWIDTH 150
#define FUNCTORTESTFREQ 10
#define FUNCTORTESTX 40
#define FUNCTORTESTY 10
#define FUNCTORTESTRADIUS 45

#define SOLIDX 80
#define SOLIDY 80
#define SOLIDTOLERANCE 0.01
#define SOLIDTESTIMAGE "originals/Canada.png"
#define SOLIDFRAMEFREQ 100

#define NEGATIVEX 80
#define NEGATIVEY 80
#define NEGATIVETOLERANCE 0.01
#define NEGATIVETESTIMAGE "originals/Canada.png"
#define NEGATIVEFRAMEFREQ 100

#define IMGTILEX 120
#define IMGTILEY 75
#define IMGTILETOLERANCE 0.008
#define IMGTILETESTIMAGE "originals/mooncake.png"
#define IMGTILEOTHERIMAGE "originals/strawberry.png"
#define IMGTILEFRAMEFREQ 250

#define CENSORX 50
#define CENSORY 50
#define CENSORTESTIMAGE "originals/leaf.png"
#define CENSORFRAMEFREQ 250
#define CENSORTOLERANCE 0.08
#define CENSORRADIUS 70
#define CENSORWIDTH 10

#define RAINFREQ 1.0/1000.0
#define RAINTOLERANCE 0.01
#define RAINX 75
#define RAINY 75
#define RAINTESTIMAGE "originals/leaf.png"
#define RAINFRAMEFREQ 150 

PNG testColorPicker(ColorPicker& picker)
{
    PNG img;
    img.resize(FUNCTORTESTWIDTH, FUNCTORTESTHEIGHT);
    HSLAPixel px;

/*
    for (int x = 1; x < FUNCTORTESTWIDTH; x = x + x) {
        for (int y = 1; y < FUNCTORTESTHEIGHT; y = y + y) {
            px = picker(PixelPoint(x, y, HSLAPixel()));
            cout << "\toperator()(" << x << ", " << y << ") = {"
                << (int)px.h << ", "
                << (int)px.s << ", "
                << (int)px.l << "}" << endl;
        }
    }
*/

    for (int x = 0; x < FUNCTORTESTWIDTH; x++){
        for (int y = 0; y < FUNCTORTESTHEIGHT; y++){
            HSLAPixel * p = img.getPixel(x,y);
            PixelPoint pp(x, y, *p);
            *p = picker(pp);
        }
    }

    return img;
}

TEST_CASE("colorPicker::basic solid","[weight=1][part=colorPicker]"){

    HSLAPixel px;
    px.h = 0; px.s = 1.0; px.l = 0.5; // red
    SolidColorPicker solidPicker(px);

    PNG result = testColorPicker(solidPicker);
    result.writeToFile("images/solidColorPickerTest.png");
    PNG expected; expected.readFromFile("soln_images/solidColorPickerTest.png");
    REQUIRE(result == expected);
    
}

TEST_CASE("colorPicker::basic image tile","[weight=1][part=colorPicker]"){
    
    PNG imgtest, imgother;
    imgtest.readFromFile(IMGTILETESTIMAGE);
    imgother.readFromFile(IMGTILEOTHERIMAGE);

    ImageTileColorPicker imgtilePicker(imgother);

    PNG result = testColorPicker(imgtilePicker);
    result.writeToFile("images/imageTileColorPickerTest.png");
    PNG expected; expected.readFromFile("soln_images/imageTileColorPickerTest.png");
    REQUIRE(result == expected);
}

TEST_CASE("colorPicker::basic negative","[weight=1][part=colorPicker]"){

    PNG imgtest;
    imgtest.readFromFile(NEGATIVETESTIMAGE);

    NegativeColorPicker negativePicker(imgtest);

    PNG result = testColorPicker(negativePicker);
    result.writeToFile("images/negativeColorPickerTest.png");
    PNG expected; expected.readFromFile("soln_images/negativeColorPickerTest.png");
    REQUIRE(result == expected);
}

TEST_CASE("colorPicker::basic censor", "[weight=1][part=colorPicker]") {
  
  PNG imgtest;
  imgtest.readFromFile(CENSORTESTIMAGE);

  CensorColorPicker censorPicker(CENSORWIDTH, PixelPoint(CENSORX, CENSORY, HSLAPixel()), CENSORRADIUS, imgtest);

  PNG result = testColorPicker(censorPicker);
  result.writeToFile("images/censorColorPickerTest.png");
  PNG expected; expected.readFromFile("soln_images/censorColorPickerTest.png");
  REQUIRE(result == expected);
}

TEST_CASE("colorPicker::basic rainbow","[weight=1][part=colorPicker]"){
    RainbowColorPicker rainPicker(1.0/1000.0);

    PNG result = testColorPicker(rainPicker);
    result.writeToFile("images/rainColorPickerTest.png");
    PNG expected; expected.readFromFile("soln_images/rainColorPickerTest.png");
    REQUIRE(result == expected);
}


TEST_CASE("fill::basic solid dfs","[weight=1][part=fill]"){
    
    HSLAPixel px(100., 1.0, 0.5);
    SolidColorPicker solidPicker(px);

    filler::FillerConfig solidconfig;
    solidconfig.img.readFromFile(SOLIDTESTIMAGE);
    solidconfig.frameFreq = SOLIDFRAMEFREQ;
    solidconfig.tolerance = SOLIDTOLERANCE;
    solidconfig.seedpoint = PixelPoint(SOLIDX, SOLIDY, *solidconfig.img.getPixel(SOLIDX,SOLIDY));
    solidconfig.picker = &solidPicker;

    animation anim;
    anim = filler::FillDFS(solidconfig);
    PNG result = anim.write("images/dfssolid.gif"); 
    result.writeToFile("images/dfssolid.png");

    PNG expected; expected.readFromFile("soln_images/dfssolid.png");
    REQUIRE(result==expected);

}


TEST_CASE("fill::basic solid bfs","[weight=1][part=fill]"){
    
    HSLAPixel px(100., 1.0, 0.5);
    SolidColorPicker solidPicker(px);

    filler::FillerConfig solidconfig;
    solidconfig.img.readFromFile(SOLIDTESTIMAGE);
    solidconfig.frameFreq = SOLIDFRAMEFREQ;
    solidconfig.tolerance = SOLIDTOLERANCE;
    solidconfig.seedpoint = PixelPoint(SOLIDX, SOLIDY, *solidconfig.img.getPixel(SOLIDX, SOLIDY));
    solidconfig.picker = &solidPicker;

    animation anim;
    anim = filler::FillBFS(solidconfig);
    PNG result = anim.write("images/bfssolid.gif");
    result.writeToFile("images/bfssolid.png");

    PNG expected; expected.readFromFile("soln_images/bfssolid.png");
    REQUIRE(result==expected);
}


TEST_CASE("fill::basic image tile dfs","[weight=1][part=fill]"){
    
    PNG tiletest;
    PNG tileother;
    tiletest.readFromFile(IMGTILETESTIMAGE);
    tileother.readFromFile(IMGTILEOTHERIMAGE);
    ImageTileColorPicker tilePicker(tileother);

    filler::FillerConfig tileconfig;
    tileconfig.img = tiletest;
    tileconfig.frameFreq = IMGTILEFRAMEFREQ;
    tileconfig.tolerance = IMGTILETOLERANCE;
    tileconfig.seedpoint = PixelPoint(IMGTILEX, IMGTILEY, *tileconfig.img.getPixel(IMGTILEX, IMGTILEY));
    tileconfig.picker = &tilePicker;

    animation anim;
    anim = filler::FillDFS(tileconfig);
    PNG result = anim.write("images/dfsimgtile.gif");
    result.writeToFile("images/dfsimgtile.png");

    PNG expected; expected.readFromFile("soln_images/dfsimgtile.png");
    REQUIRE(result==expected);
}

TEST_CASE("fill::basic image tile bfs","[weight=1][part=fill]"){
    
    PNG tiletest;
    PNG tileother;
    tiletest.readFromFile(IMGTILETESTIMAGE);
    tileother.readFromFile(IMGTILEOTHERIMAGE);
    ImageTileColorPicker tilePicker(tileother);

    filler::FillerConfig tileconfig;
    tileconfig.img = tiletest;
    tileconfig.frameFreq = IMGTILEFRAMEFREQ;
    tileconfig.tolerance = IMGTILETOLERANCE;
    tileconfig.seedpoint = PixelPoint(IMGTILEX, IMGTILEY, *tileconfig.img.getPixel(IMGTILEX, IMGTILEY));
    tileconfig.picker = &tilePicker;

    animation anim;
    anim = filler::FillBFS(tileconfig);
    PNG result = anim.write("images/bfsimgtile.gif");
    result.writeToFile("images/bfsimgtile.png");

    PNG expected; expected.readFromFile("soln_images/bfsimgtile.png");
    REQUIRE(result==expected);
}

TEST_CASE("fill::basic negative dfs", "[weight=1][part=fill]") {
    PNG negativetest;
    negativetest.readFromFile(NEGATIVETESTIMAGE);
    NegativeColorPicker negativePicker(negativetest);

    filler::FillerConfig negativeconfig;
    negativeconfig.img = negativetest;
    negativeconfig.frameFreq = NEGATIVEFRAMEFREQ;
    negativeconfig.tolerance = NEGATIVETOLERANCE;
    negativeconfig.seedpoint = PixelPoint(NEGATIVEX, NEGATIVEY, *negativeconfig.img.getPixel(NEGATIVEX, NEGATIVEY));
    negativeconfig.picker = &negativePicker;

    animation anim;
    anim = filler::FillDFS(negativeconfig);
    PNG result = anim.write("images/dfsnegative.gif");
    result.writeToFile("images/dfsnegative.png");

    PNG expected; expected.readFromFile("soln_images/dfsnegative.png");
    REQUIRE(result == expected);
}

TEST_CASE("fill::basic negative bfs", "[weight=1][part=fill]") {
    PNG negativetest;
    negativetest.readFromFile(NEGATIVETESTIMAGE);
    NegativeColorPicker negativePicker(negativetest);

    filler::FillerConfig negativeconfig;
    negativeconfig.img = negativetest;
    negativeconfig.frameFreq = NEGATIVEFRAMEFREQ;
    negativeconfig.tolerance = NEGATIVETOLERANCE;
    negativeconfig.seedpoint = PixelPoint(NEGATIVEX, NEGATIVEY, *negativeconfig.img.getPixel(NEGATIVEX, NEGATIVEY));
    negativeconfig.picker = &negativePicker;

    animation anim;
    anim = filler::FillBFS(negativeconfig);
    PNG result = anim.write("images/bfsnegative.gif");
    result.writeToFile("images/bfsnegative.png");

    PNG expected; expected.readFromFile("soln_images/bfsnegative.png");
    REQUIRE(result == expected);
}

TEST_CASE("fill::basic censor dfs","[weight=1][part=fill]"){
    PNG imgtest;
    imgtest.readFromFile(CENSORTESTIMAGE);
    CensorColorPicker censorPicker(CENSORWIDTH, PixelPoint(CENSORX, CENSORY, HSLAPixel()), CENSORRADIUS, imgtest);

    filler::FillerConfig censorconfig;
    censorconfig.img = imgtest;
    censorconfig.frameFreq = CENSORFRAMEFREQ;
    censorconfig.tolerance = CENSORTOLERANCE;
    censorconfig.seedpoint = PixelPoint(CENSORX, CENSORY, *censorconfig.img.getPixel(CENSORX, CENSORY));
    censorconfig.picker = &censorPicker;

    animation anim;
    anim = filler::FillDFS(censorconfig);
    PNG result = anim.write("images/dfscensor.gif");
    result.writeToFile("images/dfscensor.png");

    PNG expected; expected.readFromFile("soln_images/dfscensor.png");
    REQUIRE(result==expected);
}

TEST_CASE("fill::basic censor bfs","[weight=1][part=fill]"){
    PNG imgtest;
    imgtest.readFromFile(CENSORTESTIMAGE);
    CensorColorPicker censorPicker(CENSORWIDTH, PixelPoint(CENSORX, CENSORY, HSLAPixel()), CENSORRADIUS, imgtest);

    filler::FillerConfig censorconfig;
    censorconfig.img = imgtest;
    censorconfig.frameFreq = CENSORFRAMEFREQ;
    censorconfig.tolerance = CENSORTOLERANCE;
    censorconfig.seedpoint = PixelPoint(CENSORX, CENSORY, *censorconfig.img.getPixel(CENSORX, CENSORY));
    censorconfig.picker = &censorPicker;

    animation anim;
    anim = filler::FillBFS(censorconfig);
    PNG result = anim.write("images/bfscensor.gif");
    result.writeToFile("images/bfscensor.png");

    PNG expected; expected.readFromFile("soln_images/bfscensor.png");
    REQUIRE(result==expected);
}

TEST_CASE("fill::basic rainbow dfs","[weight=1][part=fill]"){

    PNG imgtest;
    imgtest.readFromFile(RAINTESTIMAGE);
    RainbowColorPicker rainPicker(RAINFREQ);

    filler::FillerConfig rainbowconfig;
    rainbowconfig.img = imgtest;
    rainbowconfig.frameFreq = RAINFRAMEFREQ;
    rainbowconfig.tolerance = RAINTOLERANCE;
    rainbowconfig.seedpoint = PixelPoint(RAINX, RAINY, *rainbowconfig.img.getPixel(RAINX, RAINY));
    rainbowconfig.picker = &rainPicker;

    animation anim;
    anim = filler::FillDFS(rainbowconfig);
    PNG result = anim.write("images/dfsrain.gif");
    result.writeToFile("images/dfsrain.png");

    PNG expected; expected.readFromFile("soln_images/dfsrain.png");
    REQUIRE(result==expected);
}

TEST_CASE("fill::basic rainbow bfs","[weight=1][part=fill]"){

    PNG imgtest;
    imgtest.readFromFile(RAINTESTIMAGE);
    RainbowColorPicker rainPicker(RAINFREQ);

    filler::FillerConfig rainbowconfig;
    rainbowconfig.img = imgtest;
    rainbowconfig.frameFreq = RAINFRAMEFREQ;
    rainbowconfig.tolerance = RAINTOLERANCE;
    rainbowconfig.seedpoint = PixelPoint(RAINX, RAINY, *rainbowconfig.img.getPixel(RAINX, RAINY));
    rainbowconfig.picker = &rainPicker;

    animation anim;
    anim = filler::FillBFS(rainbowconfig);
    PNG result = anim.write("images/bfsrain.gif");
    result.writeToFile("images/bfsrain.png");

    PNG expected; expected.readFromFile("soln_images/bfsrain.png");
    REQUIRE(result==expected);

}

