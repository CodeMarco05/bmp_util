#pragma once

#include <fstream>
#include <iostream>
#include <vector>

namespace BMP {
// Define the BMP header structure
#pragma pack(push, 2)
struct BMPHeader {
  char fileType[2] = {'B', 'M'};
  uint32_t fileSize;
  uint32_t reserved = 0;
  uint32_t offset;           // Offset to pixel data
  uint32_t headerSize = 40;  // Size of header
  uint32_t width;
  uint32_t height;
  uint16_t planes = 1;
  uint16_t bitsPerPixel = 24;            // 24-bit color depth (RGB)
  uint32_t compression = 0;              // No compression
  uint32_t dataSize;                     // Size of pixel data
  uint32_t horizontalResolution = 2835;  // 72 DPI
  uint32_t verticalResolution = 2835;    // 72 DPI
  uint32_t colorsUsed = 0;               // Number of colors in palette
  uint32_t importantColors = 0;          // Number of important colors
};
#pragma pack(pop)

struct Pixel {
  uint8_t blue;
  uint8_t green;
  uint8_t red;

  Pixel(uint8_t blue_val, uint8_t green_val, uint8_t red_val)
      : blue(blue_val), green(green_val), red(red_val) {}
};

class Generator {
 public:
  static bool generate(const std::string& filename, uint32_t width,
                       uint32_t height, const std::vector<Pixel>* pixelData);
};

class Reader{
  public:
  static std::vector<uint8_t> readBytes(const std::string& filename);
  static void completeRead(const std::string& filename, std::vector<Pixel> *pixels, BMPHeader *header);

  private:
  static int calculateNumberInBytes(std::vector<uint8_t> nums);
};
}  // namespace BMP