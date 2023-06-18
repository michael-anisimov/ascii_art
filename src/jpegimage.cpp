#include "jpegimage.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <csetjmp>

/**
 * @brief Load a JPEG image from a file.
 * @param filename The name of the JPEG image file to load.
 * @return True if the image is loaded successfully, false otherwise.
 *
 * This function overrides the loadImage function from the base Image class.
 * It is responsible for loading the JPEG image data from the specified file.
 * The JPEG image is decompressed using the libjpeg library.
 */

// Important note! I was inspired and used this source code to implement loading of jpeg images:
// https://github.com/menshiva/ascii-art-terminal/blob/master/src/image/format/JPEGImage.cpp
// Because it is a library stuff

bool JpegImage::loadImage(const std::string &filename)
{
    jpeg_decompress_struct decompressInfo{};
    /*
     * We use our private extension JPEG error handler.
     * Note that this struct must live as long as the main JPEG parameter
     * struct, to avoid dangling-pointer problems.
     */
    jpegErrorManager errorManager{};

    // Convert filename to const char*
    const char *filenameC = filename.c_str();

    FILE *file = fopen(filenameC, "rb");
    if (!file)
    {
        std::cout << "There is no such image" << std::endl;
        return false;
    }
    decompressInfo.err = jpeg_std_error(&errorManager.manager);
    errorManager.manager.error_exit = jpegDecompressErrorHandler;

    // if decompress traces an error, then jpegDecompressErrorHandler calls this part of code
    if (setjmp(errorManager.jumpBuffer))
    {

        jpeg_destroy_decompress(&decompressInfo);
        fclose(file);
        return false;
    }

    jpeg_create_decompress(&decompressInfo);
    jpeg_stdio_src(&decompressInfo, file);

    // read metadata
    jpeg_read_header(&decompressInfo, true);
    jpeg_start_decompress(&decompressInfo);

    // color components (RGB, YCbCr, CMYK, etc.)
    auto components = static_cast<size_t>(decompressInfo.num_components);
    m_height = decompressInfo.output_height;
    m_width = decompressInfo.output_width;

    if (!m_height || !m_width || !components || components > 3)
        return false;

    size_t lineWidth = components * m_width;
    std::vector<unsigned char> data(m_height * lineWidth);
    while (decompressInfo.output_scanline < decompressInfo.output_height)
    {
        // pointer to data + current line * lineWidth
        unsigned char *rowptr = data.data() + decompressInfo.output_scanline * lineWidth;
        // read 1 line to rowptr
        jpeg_read_scanlines(&decompressInfo, &rowptr, 1);
    }

    jpeg_finish_decompress(&decompressInfo);
    jpeg_destroy_decompress(&decompressInfo);

    m_raw_image.resize(m_height, std::vector<Pixel>(m_width));

    // convert components data to pixels data
    size_t row = 0, col = 0;
    for (size_t dataI = 0; dataI < data.size(); dataI += components)
    {
        m_raw_image[row][col].red = data[dataI];
        if (components == 1)
        {
            // if jpeg is grayscaled then all color components should be the same
            m_raw_image[row][col].green = data[dataI];
            m_raw_image[row][col].blue = data[dataI];
        }
        else
        {
            m_raw_image[row][col].green = data[dataI + 1];
            m_raw_image[row][col].blue = data[dataI + 2];
        }
        if (++col >= static_cast<size_t>(m_width))
        {
            col = 0;
            ++row;
        }
    }

    return true;
}

/**
 * @brief Custom error handler for JPEG decompression.
 * @param cinfo The pointer to the JPEG decompression structure.
 *
 * This function is used as the error handler for the libjpeg library.
 * It is called when an error occurs during JPEG decompression.
 * The function performs a long jump to return control to the setjmp point in the loadImage function.
 */
void JpegImage::jpegDecompressErrorHandler(j_common_ptr cinfo)
{
    // jump to setjmp in loadImage (return control to the setjmp point)
    longjmp(((jpegErrorManager *)cinfo->err)->jumpBuffer, 1);
}
