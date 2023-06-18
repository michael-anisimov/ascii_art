#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#include "image.hpp"
#include <string>
#include <vector>

/**
 * @brief A class representing a Bitmap (BMP) image.
 *
 * This class inherits from the base Image class and provides functionality
 * to load and process BMP image files.
 */
class BmpImage : public Image
{
public:
    /**
     * @brief Load a BMP image from a file.
     * @param filename The name of the BMP image file to load.
     * @return True if the image is loaded successfully, false otherwise.
     *
     * This function overrides the loadImage function from the base Image class.
     * It is responsible for loading the BMP image data from the specified file.
     */
    bool loadImage(const std::string &filename) override;

    /**
     * @brief Destructor.
     *
     * This is the destructor for the BmpImage class.
     */
    ~BmpImage() {}
};

#endif
