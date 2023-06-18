#ifndef JPEGIMAGE_H
#define JPEGIMAGE_H

#include "image.hpp"
#include <csetjmp>

extern "C"
{
#include <jpeglib.h>
}

/**
 * @class JpegImage
 * @brief Represents a JPEG image object.
 *
 * This class extends the base Image class and provides functionality for loading and processing JPEG images.
 */
class JpegImage : public Image
{
    struct jpegErrorManager
    {
        jpeg_error_mgr manager; /**< The JPEG error manager. */
        jmp_buf jumpBuffer;     /**< The jump buffer to return to the caller on error. */
    };

protected:
    unsigned char *image; /**< The image data buffer. */
    int width;            /**< The width of the image. */
    int height;           /**< The height of the image. */

public:
    /**
     * @brief Load a JPEG image from a file.
     * @param filename The name of the JPEG image file to load.
     * @return True if the image is loaded successfully, false otherwise.
     *
     * This function overrides the loadImage function from the base Image class.
     * It is responsible for loading the JPEG image data from the specified file.
     */
    bool loadImage(const std::string &filename) override;

    /**
     * @brief Virtual destructor for the JpegImage class.
     */
    ~JpegImage() override = default;

    /**
     * @brief JPEG decompression error handler.
     * @param cinfo The pointer to the JPEG decompression structure.
     *
     * This function is used as the error handler for the JPEG decompression library.
     * It is called when an error occurs during JPEG decompression.
     */
    static void jpegDecompressErrorHandler(j_common_ptr cinfo);
};

#endif
