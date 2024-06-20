#include "../headers/bmp.h"
#include <iostream>
#include <vector>
#include <cstdint>


int main(int argc, char **argv) {
  // Format for BMP bgr
  const uint32_t width = 16;
  const uint32_t height = 16;

  //cmd::arguments args = cmd::getCommandLineArguments(&argc, argv);


  std::vector<BMP::Pixel> pixelData(width * height, {0xFF, 0xFF, 0xFF});

  pixelData[136].green = 0;
  pixelData[136].blue = 0;

  pixelData[0].blue = 0;

  BMP::ImageData data = BMP::Generator::generate(width, height, pixelData);

  BMP::Generator::writeToFileSystem("../output/out.bmp", data);

  BMP::ImageData image = BMP::Reader::completeRead("../output/out.bmp");

  return 0;
}




