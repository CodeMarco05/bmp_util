#include "../headers/bmp.h"

#include <fstream>
#include <memory>
#include <cstdint>

namespace BMP {

  std::ostream &operator<<(std::ostream &os, const BMPHeader &header) {
    os << "BMPHeader {\n"
       << "  fileType: " << header.fileType[0] << header.fileType[1] << "\n"
       << "  fileSize: " << header.fileSize << "\n"
       << "  offset: " << header.offset << "\n"
       << "  headerSize: " << header.headerSize << "\n"
       << "  width: " << header.width << "\n"
       << "  height: " << header.height << "\n"
       << "  planes: " << header.planes << "\n"
       << "  bitsPerPixel: " << header.bitsPerPixel << "\n"
       << "  compression: " << header.compression << "\n"
       << "  dataSize: " << header.dataSize << "\n"
       << "  horizontalResolution: " << header.horizontalResolution << "\n"
       << "  verticalResolution: " << header.verticalResolution << "\n"
       << "  colorsUsed: " << header.colorsUsed << "\n"
       << "  importantColors: " << header.importantColors << "\n"
       << "}";
    return os;
  }

  std::ostream &operator<<(std::ostream &os, const Pixel &pixel) {
    os << "Pixel { "
       << "blue: " << static_cast<int>(pixel.blue) << ", "
       << "green: " << static_cast<int>(pixel.green) << ", "
       << "red: " << static_cast<int>(pixel.red)
       << " }";
    return os;
  }

  std::ostream &operator<<(std::ostream &os, const std::vector<Pixel> &pixels) {
    os << "{ ";
    for (Pixel pixel: pixels) {
      os << pixel << ", ";
    }
    os << "}";
    return os;
  }

  ImageData Generator::generate(uint32_t width,
                                uint32_t height, const std::vector<Pixel> &pixelData) {
    bool check = checkPixelDimensions(width, height, pixelData);
    if (!check) {
      return ImageData();
    }

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


    ImageData data(pixelData, header);
    return data;

    /*// Open the output file
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
    outFile.close();*/
  }

  bool Generator::checkPixelDimensions(uint32_t width, uint32_t height, const std::vector<Pixel> &pixelData) {
    if (width * height == pixelData.size()) {
      return true;
    }
    return false;
  }

  ImageData
  Generator::generate(uint32_t width, uint32_t height, const std::vector<Pixel> &pixelData, const BMPHeader header) {
    return ImageData(pixelData, header);
  }

  void Generator::writeToFileSystem(const std::string &path, ImageData &data) {
    std::ofstream outFile(path, std::ios::binary);
    if (!outFile.is_open()) {
      std::cerr << "Error: Unable to open file." << '\n';
      exit(1);
    }

    // Write the BMP header to the file
    outFile.write(reinterpret_cast<const char *>(&data.header), sizeof(BMPHeader));

    // Write the pixel data to the file
    for (const Pixel &pixel: data.pixels) {
      outFile.write(reinterpret_cast<const char *>(&pixel), sizeof(Pixel));
    }

    // Close the output file
    outFile.close();
  }


  std::vector<uint8_t> Reader::readBytes(const std::string &fileName) {
    std::vector<uint8_t> data;

    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open()) {
      std::cerr << "Unanble to open file: " << fileName << '\n';
      exit(1);
    }

    uint8_t byte;

    while (file.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {
      data.push_back(byte);
    }
    file.close();

    return data;
  }

  ImageData Reader::completeRead(const std::string filename) {
    std::vector<uint8_t> data = readBytes(filename);

    std::vector<uint8_t> numsToCalculate;

    ImageData imageData;

    //erased the filetype chars
    data.erase(data.begin(), data.begin() + 2);

    //fileSize
    numsToCalculate.push_back(data[0]);
    numsToCalculate.push_back(data[1]);
    numsToCalculate.push_back(data[2]);
    numsToCalculate.push_back(data[3]);
    data.erase(data.begin(), data.begin() + 4);

    //reserved get deleted
    data.erase(data.begin(), data.begin() + 4);

    imageData.header.fileSize = calculateNumberInBytes(numsToCalculate);
    numsToCalculate.clear();

    //offset
    numsToCalculate.push_back(data[0]);
    numsToCalculate.push_back(data[1]);
    numsToCalculate.push_back(data[2]);
    numsToCalculate.push_back(data[3]);
    data.erase(data.begin(), data.begin() + 4);

    imageData.header.offset = calculateNumberInBytes(numsToCalculate);
    numsToCalculate.clear();

    //headersize
    numsToCalculate.push_back(data[0]);
    numsToCalculate.push_back(data[1]);
    numsToCalculate.push_back(data[2]);
    numsToCalculate.push_back(data[3]);
    data.erase(data.begin(), data.begin() + 4);

    imageData.header.headerSize = calculateNumberInBytes(numsToCalculate);
    numsToCalculate.clear();


    //width
    numsToCalculate.push_back(data[0]);
    numsToCalculate.push_back(data[1]);
    numsToCalculate.push_back(data[2]);
    numsToCalculate.push_back(data[3]);
    data.erase(data.begin(), data.begin() + 4);

    imageData.header.width = calculateNumberInBytes(numsToCalculate);
    numsToCalculate.clear();

    //height
    numsToCalculate.push_back(data[0]);
    numsToCalculate.push_back(data[1]);
    numsToCalculate.push_back(data[2]);
    numsToCalculate.push_back(data[3]);
    data.erase(data.begin(), data.begin() + 4);

    imageData.header.height = calculateNumberInBytes(numsToCalculate);
    numsToCalculate.clear();

    //planes
    numsToCalculate.push_back(data[0]);
    numsToCalculate.push_back(data[1]);
    data.erase(data.begin(), data.begin() + 2);

    imageData.header.planes = calculateNumberInBytes(numsToCalculate);
    numsToCalculate.clear();

    // bits per pixel
    data.erase(data.begin(), data.begin() + 2);

    //compression
    numsToCalculate.push_back(data[0]);
    numsToCalculate.push_back(data[1]);
    numsToCalculate.push_back(data[2]);
    numsToCalculate.push_back(data[3]);
    data.erase(data.begin(), data.begin() + 4);

    imageData.header.compression = calculateNumberInBytes(numsToCalculate);
    numsToCalculate.clear();

    //data size
    numsToCalculate.push_back(data[0]);
    numsToCalculate.push_back(data[1]);
    numsToCalculate.push_back(data[2]);
    numsToCalculate.push_back(data[3]);
    data.erase(data.begin(), data.begin() + 4);

    imageData.header.dataSize = calculateNumberInBytes(numsToCalculate);
    numsToCalculate.clear();


    //horizontal resolution
    numsToCalculate.push_back(data[0]);
    numsToCalculate.push_back(data[1]);
    numsToCalculate.push_back(data[2]);
    numsToCalculate.push_back(data[3]);
    data.erase(data.begin(), data.begin() + 4);

    imageData.header.horizontalResolution = calculateNumberInBytes(numsToCalculate);
    numsToCalculate.clear();

    //vertical resolution
    numsToCalculate.push_back(data[0]);
    numsToCalculate.push_back(data[1]);
    numsToCalculate.push_back(data[2]);
    numsToCalculate.push_back(data[3]);
    data.erase(data.begin(), data.begin() + 4);

    imageData.header.verticalResolution = calculateNumberInBytes(numsToCalculate);
    numsToCalculate.clear();

    //color used
    numsToCalculate.push_back(data[0]);
    numsToCalculate.push_back(data[1]);
    numsToCalculate.push_back(data[2]);
    numsToCalculate.push_back(data[3]);
    data.erase(data.begin(), data.begin() + 4);

    imageData.header.colorsUsed = calculateNumberInBytes(numsToCalculate);
    numsToCalculate.clear();

    //important colors
    numsToCalculate.push_back(data[0]);
    numsToCalculate.push_back(data[1]);
    numsToCalculate.push_back(data[2]);
    numsToCalculate.push_back(data[3]);
    data.erase(data.begin(), data.begin() + 4);

    imageData.header.importantColors = calculateNumberInBytes(numsToCalculate);
    numsToCalculate.clear();

    //print(data);

    //print
    std::cout << "Read header: " << imageData.header << '\n';

    return imageData;
  }

  void Reader::print(std::vector<uint8_t> &data) {
    for (uint8_t a: data) {
      Reader::printBinary(a);
      std::cout << " ";
    }
    std::cout << '\n';
  }

  void Reader::printBinary(uint8_t num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; --i) {
      std::cout << ((num >> i) & 1);
    }
  }

  /*void Reader::completeRead(const std::string& filename,
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
  }*/

  int Reader::calculateNumberInBytes(std::vector<uint8_t> nums) {
    //this method should calculate the result number from index 0 lsb to msb
    int result = 0;

    for (int i = 0; i < nums.size(); i++) {
      result += nums[i] << i * 8;
    }
    return result;
  }

} // namespace BMP
