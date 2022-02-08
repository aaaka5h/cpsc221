// File:        testimglist.cpp
// Date:        2022-01-24 11:35
// Description: Contains basic tests for ImgList class
//              for CPSC 221 2021W2 PA1
//              You may add your own additional tests

#include "imglist.h"

#include <iostream>

using namespace std;
using namespace cs221util;

// test function definitions
void TestConstructorRender();
void TestCarveMode0();
void testClear();
void TestRenderMode2();

int main(void) {

  // call the various test functions
  // you may comment and uncomment these as needed
  TestConstructorRender();
  //testClear();
  TestCarveMode0();
  TestRenderMode2();

  return 0;
}

// void testClear() {
//   PNG inimg;
//   inimg.readFromFile("input-images/5x6.png");

//   ImgList list5x6(inimg);
//     cout << "done." << endl;
//     cout << "Attempting to clear list... ";
//     list5x6.Clear();
//     cout << "done." << endl;
// }

void TestConstructorRender() {
  cout << "Entered TestConstructorRender function" << endl;

  PNG inimg;
  inimg.readFromFile("input-images/3x4.png");

  if (inimg.height() == 4 && inimg.width() == 3) {
    cout << "Input PNG 3x4.png successfully read." << endl;
    cout << "Creating ImgList object using input PNG... ";
    ImgList list3x4(inimg);
    cout << "done." << endl;

    cout << "Attempting to render unmodified list data to output PNG... ";
    PNG outputimg = list3x4.Render(false, 0);
    cout << "done." << endl;

    cout << "Writing output PNG to 3x4-0-0.png... ";
    outputimg.writeToFile("output-images/3x4-0-0.png");
    cout << "done." << endl;

    cout << "Exiting TestConstructorRender function" << endl;
  }
  else {
    cout << "Input PNG image not read. Exiting..." << endl;
  }
}

void TestCarveMode0() {
  cout << "Entered TestCarveMode0 function" << endl;

  PNG inimg;
  inimg.readFromFile("input-images/5x6.png");

  if (inimg.height() == 6 && inimg.width() == 5) {
    cout << "Input PNG 3x4.png successfully read." << endl;
    cout << "Creating ImgList object using input PNG... ";
    ImgList list5x6(inimg);
    cout << "done." << endl;

    cout << "Attempting to carve list using selection mode 0... ";
    list5x6.Carve(1, 0);
    cout << "done." << endl;

    cout << "Determining physical node dimensions of carved image... ";
    unsigned int postcarvex = list5x6.GetDimensionX();
    unsigned int postcarvey = list5x6.GetDimensionY();
    cout << "done." << endl;

    cout << "Expected horizontal dimension: 4" << endl;
    cout << "Your horizontal dimension: " << postcarvex << endl;

    cout << "Rendering carved image using rendermode 0... ";
    PNG outputimg1 = list5x6.Render(false, 0);
    cout << "done." << endl;

    cout << "Writing output PNG to 5x6-0-0.png... ";
    outputimg1.writeToFile("output-images/5x6-0-0.png");
    cout << "done." << endl;

    cout << "Rendering carved image using rendermode 1 and fillmode 0... ";
    PNG outputimg2 = list5x6.Render(true, 0);
    cout << "done." << endl;

    cout << "Writing output PNG to 5x6-1-0.png... ";
    outputimg2.writeToFile("output-images/5x6-1-0.png");
    cout << "done." << endl;

    cout << "Rendering carved image using rendermode 1 and fillmode 1... ";
    PNG outputimg3 = list5x6.Render(true, 1);
    cout << "done." << endl;

    cout << "Writing output PNG to 5x6-1-1.png... ";
    outputimg3.writeToFile("output-images/5x6-1-1.png");
    cout << "done." << endl;

    cout << "Carving a second pixel from image... ";
    list5x6.Carve(1, 0);
    cout << "done." << endl;

    cout << "Determining physical node dimensions of carved image... ";
    postcarvex = list5x6.GetDimensionX();
    postcarvey = list5x6.GetDimensionY();
    cout << "done." << endl;

    cout << "Expected horizontal dimension: 3" << endl;
    cout << "Your horizontal dimension: " << postcarvex << endl;

    cout << "Rendering carved image using rendermode 0... ";
    PNG outputimg4 = list5x6.Render(false, 0);
    cout << "done." << endl;

    cout << "Writing output PNG to 5x6-0-0.png... ";
    outputimg4.writeToFile("output-images/5x6-0-0-c2.png");
    cout << "done." << endl;

    cout << "Rendering carved image using rendermode 1 and fillmode 2... ";
    PNG outputimg5 = list5x6.Render(true, 2);
    cout << "done." << endl;

    cout << "Writing output PNG to 5x6-1-2.png... ";
    outputimg5.writeToFile("output-images/5x6-1-2.png");
    cout << "done." << endl;

    cout << "Exiting TestCarveMode0 function" << endl;
  }
  else {
    cout << "Input PNG image not read. Exiting..." << endl;
  }
}

void TestRenderMode2() {
  cout << "Entered TestRenderMode2 function" << endl;

  PNG inimg;
  inimg.readFromFile("input-images/6x6grad.png");

  if (inimg.height() == 6 && inimg.width() == 6) {
    cout << "Input PNG 6x6.png successfully read." << endl;
    cout << "Creating ImgList object using input PNG... ";
    ImgList list6x6(inimg);
    cout << "done." << endl;

    cout << "Attempting to carve more pixels than allowable in mode 0... ";
    list6x6.Carve(12, 0);
    cout << "done." << endl;

    cout << "Determining physical node dimensions of carved image... ";
    unsigned int postcarvex = list6x6.GetDimensionX();
    unsigned int postcarvey = list6x6.GetDimensionY();
    cout << "done." << endl;

    cout << "Expected horizontal dimension: 2" << endl;
    cout << "Your horizontal dimension: " << postcarvex << endl;

    cout << "Rendering carved image using rendermode 0... ";
    PNG outputimg1 = list6x6.Render(false, 0);
    cout << "done." << endl;

    cout << "Writing output PNG to 6x6-0-0.png... ";
    outputimg1.writeToFile("output-images/6x6-0-0.png");
    cout << "done." << endl;

    cout << "Rendering carved image using rendermode 1 and fillmode 2... ";
    PNG outputimg2 = list6x6.Render(true, 2);
    cout << "done." << endl;

    cout << "Writing output PNG to 6x6-1-2.png... ";
    outputimg2.writeToFile("output-images/6x6-1-2.png");
    cout << "done." << endl;

    cout << "Exiting TestRenderMode2 function" << endl;
  }
  else {
    cout << "Input PNG image not read. Exiting..." << endl;
  }
}