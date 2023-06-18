#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>
#include <cmath>
#include <iostream>

/**
 * @class Image
 * @brief Represents an image object.
 *
 * This class provides functionality for loading, processing, and manipulating images.
 */
class Image
{
protected:
    /**
     * @struct Pixel
     * @brief Represents a pixel in the image.
     *
     * Each pixel has red, green, and blue color components.
     */
    struct Pixel
    {
        unsigned char red;   /**< The red color component of the pixel. */
        unsigned char green; /**< The green color component of the pixel. */
        unsigned char blue;  /**< The blue color component of the pixel. */

        /**
         * @brief Get the grayscale value of the pixel.
         * @return The grayscale value of the pixel.
         *
         * The grayscale value is calculated based on the gamma-compressed components of the pixel.
         */
        unsigned char getGrey();
    };

    int m_width;  /**< The width of the image. */
    int m_height; /**< The height of the image. */

    std::vector<std::vector<Pixel>> m_raw_image;          /**< The raw image data. */
    std::vector<std::vector<unsigned char>> m_grey_image; /**< The grayscale image data. */
    std::vector<std::vector<char>> m_ascii_image;         /**< The ASCII representation of the image. */
    std::vector<std::vector<char>> m_scaled_ascii_image;  /**< The scaled ASCII representation of the image. */

    /**< The transition string used for ASCII conversion. */
    std::string m_transition = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    std::string m_path; /**< The path to the image file. */

public:
    /**
     * @brief Load an image from a file.
     * @param filename The name of the image file to load.
     * @return True if the image is loaded successfully, false otherwise.
     *
     * This is a pure virtual function that needs to be implemented by derived classes.
     * It is responsible for loading the image data from the specified file.
     */
    virtual bool loadImage(const std::string &filename) = 0;

    /**
     * @brief Set the transition string for ASCII conversion.
     * @param transition The new transition string to set.
     *
     * The transition string is used to map grayscale values to ASCII characters during ASCII conversion.
     */
    void setTransition(const std::string &transition);

    /**
     * @brief Set the path to the image file.
     * @param path The new path to set.
     */
    void setPath(std::string &path);

    /**
     * @brief Get the path to the image file.
     * @return The path to the image file.
     */
    std::string &getPath();

    /**
     * @brief Convert the image to grayscale.
     *
     * Each pixel in the image is converted to its grayscale equivalent.
     */
    void toGreyScale();

    /**
     * @brief Convert the grayscale image to ASCII representation.
     *
     * Each grayscale pixel is mapped to an ASCII character based on the transition string.
     */
    void convertGreyToAscii();

    /**
     * @brief Convert a grayscale value to an ASCII symbol.
     * @param brightness The brightness value of the grayscale pixel.
     * @return The corresponding ASCII symbol.
     */
    char greyToAsciiSymbol(int brightness);

    /**
     * @brief Resize the ASCII representation of the image.
     *
     * The ASCII image is resized to match the dimensions of the original image.
     */
    void resizeAsciiImage();

    /**
     * @brief Negate the colors of the image.
     *
     * Each pixel's color components are negated.
     */
    void negateImage();

    /**
     * @brief Mirror the image horizontally.
     *
     * The image is flipped horizontally.
     */
    void mirrorImage();

    /**
     * @brief Change the brightness of the image.
     * @param delta The amount to change the brightness by.
     *
     * The brightness of each pixel is adjusted by the specified delta value.
     */
    void changeBrigtness(int delta);

    /**
     * @brief Print the ASCII representation of the image.
     *
     * The ASCII art is printed to the standard output.
     */
    void printAsciiArt();

    /**
     * @brief Virtual destructor for the Image class.
     */
    virtual ~Image() {}
};

#endif
