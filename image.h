//
// Created by Muneeb on 30/10/2026.
//
#include <vector>

#pragma once

struct Color
{
    float r, g, b;
    Color();
    Color(float r, float g, float b);
    ~Color();
};

class Image
{
    int m_width;
    int m_height;
    std::vector<Color> m_colors;
    
    public:
    Image();
    Image(int width, int height);
    ~Image();

    Color getColor(int x, int y) const;
    void setColor(const Color& color, int x, int y);

    void Read(const char* filename);
    void Export(const char* filename) const;
};



