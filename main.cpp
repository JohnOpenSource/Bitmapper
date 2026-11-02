#include "image.h"

int main()
{
    const int width = 1224;
    const int height = 2720;

    // Image image(width, height);
    //
    // for (int y = 0; y < height; y++)
    // {
    //     for (int x = 0; x < width; x++)
    //     {
    //         // image.setColor(Color((float)x / (float)width, 1.0f - ((float)x / (float)width), (float)y / (float)height), x, y);
    //         // image.setColor(Color((float)x*4, (float)y*4, (float)x+y / 2), x, y);
    //         // image.setColor(Color((float)x,(float)y,(float)x/y), x, y);
    //         // image.setColor(Color((float)x*width, 1.0f - (float)y*height, width*height), x, y);
    //         // image.setColor(Color(144,(float)x*y,144), x, y); // this is cool
    //         // image.setColor(Color(144, 144, (float)x*y), x, y);
    //         image.setColor(Color((float)x*height, (float)y*height, (float)width/height), x, y);
    //     }
    // }
    //
    // image.Export("bmpImage11.bmp");

    Image copy;

    copy.Read("wallhaven-gp6p5l.bmp");
    for (int y = 500; y < 2000; y++)
    {
        for (int x = 50; x < 200; x++)
        {
            copy.setColor(Color(133.0, 155.0, 255.0), x, y);
        }
    }


    copy.Export("bmpImageCopy.bmp");
}