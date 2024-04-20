#include "../headers/bmp.h"
#include "../headers/commadline.h"
#include <iostream>
#include <vector>




int main(int argc, char** argv) {
  // Format for BMP bgr
  const uint32_t width = 16;
  const uint32_t height = 16;

  cmd::arguments args = cmd::getCommandLineArguments(&argc, argv);


  std::vector<BMP::Pixel> pixelData(width * height, {0xFF, 0xFF, 0xFF});

  pixelData[136].green = 0;
  pixelData[136].blue = 0;

  bool success = BMP::Generator::generate(args.outputDir, width, height,
                                          &pixelData);

  if(success){
    std::cout << "File generated." << '\n';
  }else{
    exit(1);
  }

  BMP::BMPHeader header;
  std::vector<BMP::Pixel> dataRead;
  //BMP::Reader::completeRead(args.inputDir, &dataRead, &header);

  return 0;
}




