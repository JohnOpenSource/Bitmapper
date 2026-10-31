//
// Created by Muneeb on 30/10/2026.
//
#include <iostream>
#include<fstream>

#include "image.h"

Color::Color() : r(0), g(0), b(0) {}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color::~Color() {}

Image::Image(int width, int height) : m_width(width), m_height(height), m_colors(std::vector<Color>(width * height)) {}

Image::~Image() {}

Color Image::getColor(int x, int y) const
{
    return m_colors[y * m_width + x];     // converting from 2D coordinates to 1D
}

void Image::setColor(Color const& color, int x, int y)     // setting the color for each channel
{
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

void Image::Export(const char *path) const
{
    std::fstream f;
    f.open(path, std::ios::out | std::ios::binary);     // writing in binary

    if (!f.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    unsigned char BMPpadding[3] = {0,0,0};      // an unsigned char array to hold the padding value in bytes. Max size is 3 because per row, you can only have 3 bytes and because the padding must be a multiple of 4
    const int paddingAmount  = ((4 - (m_width * 3) % 4) % 4);    // (4-(m_width*3)%4) gives us the padding we need. the second modulo is when we don't need any padding. so the first part becomes (4 - 0)%4, that is 0 and 4%4 is 0.

    const int fileHeaderSize = 14;  // the file header can only be 14 bytes max
    const int informationHeaderSize = 40;  // the info header can only be 40 bytes max
    const int fileSize = fileHeaderSize + informationHeaderSize + m_width*m_height*3 + paddingAmount * m_height;  // total file size

    unsigned char BMPfileHeader[fileHeaderSize];

    //File type
    BMPfileHeader[0] = 'B';
    BMPfileHeader[1] = 'M';

    // File size
    BMPfileHeader[2] = fileSize;        // stores the least significant byte, discards the rest by right shifting
    BMPfileHeader[3] = fileSize >> 8;   // stores the next least significant byte, discards the rest by right shifting
    BMPfileHeader[4] = fileSize >> 16;  // stores the next least significant byte, discards the rest by right shifting
    BMPfileHeader[5] = fileSize >> 24;  // stores the last byte

    // Reserved 1 (not used)
    BMPfileHeader[6] = 0;
    BMPfileHeader[7] = 0;

    // Reserved 2
    BMPfileHeader[8] = 0;
    BMPfileHeader[9] = 0;

    // Pixel data offset. Will not exceed 255
    BMPfileHeader[10] = fileHeaderSize + informationHeaderSize;
    BMPfileHeader[11] = 0;
    BMPfileHeader[12] = 0;
    BMPfileHeader[13] = 0;

    unsigned char informationHeader[informationHeaderSize];

    // Header size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;

    // Image width
    informationHeader[4] = m_width;         // stores the least significant byte, discards the rest by right-shifting
    informationHeader[5] = m_width >> 8;    // stores the next least significant byte, discards the rest by right shifting
    informationHeader[6] = m_width >> 16;   // stores the next least significant byte, discards the rest by right shifting
    informationHeader[7] = m_width >> 24;   // stores the last byte

    // Image height
    informationHeader[8] = m_height;            // stores the least significant byte, discards the rest by right shifting
    informationHeader[9] = m_height >> 8;       // stores the next least significant byte, discards the rest by right shifting
    informationHeader[10] = m_height >> 16;     // stores the next least significant byte, discards the rest by right shifting
    informationHeader[11] = m_height >> 24;     // stores the last byte

    // Planes
    informationHeader[12] = 1;
    informationHeader[13] = 0;

    // bits per pixel (RGB)
    informationHeader[14] = 24;
    informationHeader[15] = 0;

    // compression (no compression)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;

    // image size (no compression)
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;

    // x pixels per meter (not specified)
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;

    // y pixels per meter (not specified)
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;

    // total colors (color palette not used)
    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;

    // important colors (generally ignored)
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    f.write(reinterpret_cast<char*>(BMPfileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            unsigned char r = static_cast<unsigned char>(getColor(x, y).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(getColor(x, y).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(getColor(x, y).b * 255.0f);

            unsigned char color[] = {b, g, r};  // bitmap processes Blue, then Green, and then Red channel.

            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(BMPpadding), paddingAmount);
    }

    f.close();
    std::cout << "Done! File created!" << std::endl;
}