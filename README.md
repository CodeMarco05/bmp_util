# BMP Util 📷

# Explanation

BMP_UTIL is a tool which helps to generate images 📷 in bmp format.
It is also possible to read in data from bitmap formatted files.
<br>
Possibilities

- Generate bmp file code
- Export bmp file
- Read bmp file

# Table of Contents

- [Getting started](#getting-started)
  - [Writing](#getting_started_writing)
  - [Reading](#getting_started_reading)
- [Usage](#usage)
  - [Writing](#usage_writing)
  - [Reading](#usage_reading)
- [Standard header format](#standard-header-format)

---

# Getting started

---

<h2 id="getting_started_writing">Writing</h2>

For writing files to the internal filesystem, the util es generating
a header with the provided pixel-data. Providing a filepath is necessary
for a correct output of the .bmp file. Standard is provided in [standard header format](#standard-header-format).
For a custom header, you need to provide a header customized to your liking.
Keep in mind, that a custom header may not work, when specified incorrect.
When providing the standard pixel-vector, there shouldn't be any errors.
<br>
<br>
❗️The File is getting written from the bottom left corner to the 
top right corner according to the index of the vector list.❗️

<h2 id="getting_started_reading">Reading</h2>
For reading you need to provide the filepath. The output will be saved into a given
reference from the user about the vector for the pixels and the header. 
When the method is done, you can use the two datastructures.

# Usage

---

<h2 id="usage_writing">Writing</h2>
For writing simple Pixels without any adaptation of the header.
```c++
//Give the width and height for the image
const uint32_t width = 16;
const uint32_t height = 16;

//Generate a vector of pixels. The Pixel is rgb values
std::vector<BMP::Pixel> pixelData(width * height, {0xFF, 0xFF, 0xFF});

//For a red dot in the picture
pixelData[136].green = 0;
pixelData[136].blue = 0;

//Then call the method for generating the image data
BMP::ImageData data = BMP::Generator::generate(width, height, pixelData);

//For outputting the data call
```
//TODO write 


<h2 id="usage_reading">Reading</h2>


# Standard header format

---

This is the standard header format, when you just provide the pixel vector
and the filepath. Every `-` is generated based on the vector pass to the generator.

| Element               | Byte Length |           Values            |
|-----------------------|:-----------:|:---------------------------:|
| File Type             |      2      |          'B', 'M'           |
| File Size             |      4      |              -              |
| Reserved              |      4      |              0              |
| Data Offset           |      4      |              -              |
| Header Size           |      4      |  Size of Header (54 Bytes)  |
| Image Width           |      4      |              -              |
| Image Height          |      4      |              -              |
| Planes                |      2      |              1              |
| Bits per pixel        |      2      |             24              |
| Compression           |      4      |              0              |
| Data Size             |      4      |              -              |
| Horizontal Resolution |      4      |        2835 (72 DPI)        |
| Vertical Resolution   |      4      |        2835 (72 DPI)        |
| Colors used           |      4      |              0              |
| Important Colors      |      4      |              0              |





