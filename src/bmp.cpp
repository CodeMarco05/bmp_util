#include "../headers/bmp.h"

#include <fstream>

namespace BMP {

  bool Generator::generate(const std::string &filename, uint32_t width,
                           uint32_t height, const std::vector<Pixel> *pixelData) {
    // Calculate the size of the pixel data
    const uint32_t dataSize = width * height * 3; // 3 bytes per pixel (RGB)

    // Create pixel data (RGB format)
    // std::vector<uint8_t> pixelData(dataSize, 255); // Initialize with white
    // pixels (RGB: 255, 255, 255

    // Create the BMP header
    BMPHeader header;
    header.fileSize = sizeof(BMPHeader) + dataSize;
    header.offset = sizeof(BMPHeader);
    header.width = width;
    header.height = height;
    header.dataSize = dataSize;

    // Open the output file
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
      std::cerr << "Error: Unable to open file." << '\n';
      return false;
    }

    // Write the BMP header to the file
    outFile.write(reinterpret_cast<const char *>(&header), sizeof(BMPHeader));

    // Write the pixel data to the file
    outFile.write(reinterpret_cast<const char *>(pixelData->data()), dataSize);

    // Close the output file
    outFile.close();

    return true;
  }

  std::vector<uint8_t> Reader::readBytes(const std::string& fileName) {
    std::vector<uint8_t> data;

    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open()) {
      std::cerr << "Unanble to open file: " << fileName << '\n';
      return data;
    }

    uint8_t byte;

    while (file.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {
      data.push_back(byte);
    }
    file.close();

    return data;
  }

  void Reader::completeRead(const std::string& filename,
                            std::vector<Pixel> *pixels, BMPHeader *header) {

    std::vector<uint8_t> data = readBytes(filename);

    header->fileType[0] = (char) data[0];
    header->fileType[1] = (char) data[1];
    data.erase(data.begin(), data.begin() + 2);

    std::vector<uint8_t> subvector(data.begin(), data.begin() + 4);
    int num = calculateNumberInBytes(subvector);

    std::cout << num << '\n';

    // iterate over the elements given and 2^0 if 1 2^1 if 1 and so on. add all
    // together
  }

  int Reader::calculateNumberInBytes(std::vector<uint8_t> nums) {
    int sum = 0;
    for (int i = 0; i < nums.size(); ++i) {
      sum += (nums[i] << (8 * i));
    }
    return sum;
  }
} // namespace BMP
