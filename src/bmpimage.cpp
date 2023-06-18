#include "bmpimage.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>

bool BmpImage::loadImage(const std::string &filename)
{
    /**
     * @brief Load a BMP image from a file.
     * @param filename The name of the BMP image file to load.
     * @return True if the image is loaded successfully, false otherwise.
     *
     * This function loads the BMP image data from the specified file.
     * It reads the BMP header information and pixel data, and stores them in the `m_raw_image` member variable.
     * The function returns true if the image is loaded successfully, and false otherwise.
     * If the file does not exist or if the image format is not supported, an error message is displayed.
     */

    std::ifstream file(filename, std::ios::binary);

    if (!file)
    {
        std::cout << "There is no such image" << std::endl;
        return false;
    }

    char header[54];
    file.read(header, 54);

    m_width = *(int *)&header[18];
    m_height = *(int *)&header[22];

    int bpp = *(short *)&header[28];

    if (bpp != 24)
    {
        std::cout << "No format" << std::endl;
        return false;
    }

    m_raw_image.resize(m_height, std::vector<Pixel>(m_width));

    for (int y = m_height - 1; y >= 0; --y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            unsigned char pixel[3];
            file.read(reinterpret_cast<char *>(pixel), 3);

            m_raw_image[y][x].red = pixel[2];
            m_raw_image[y][x].green = pixel[1];
            m_raw_image[y][x].blue = pixel[0];

            // int brightness = (pixel[0] + pixel[1] + pixel[2]) / 3;
            // m_image[y][x] = brightness;
        }
    }

    return true;
}
