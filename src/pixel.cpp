#include "image.hpp"

/**
 * @brief Get the grayscale value of the pixel.
 * @return The grayscale value of the pixel.
 *
 * This function calculates the grayscale value of the pixel based on its red, green, and blue color components.
 * The color components are first gamma-compressed, then converted to linear components.
 * The linear components are used to calculate the basic linear luminance.
 * The linear luminance is then converted back to gamma-compressed luminance.
 * The final grayscale value is obtained by scaling the gamma-compressed luminance to the range [0, 255].
 */
unsigned char Image::Pixel::getGrey()
{
    // get gamma compressed components
    double gammaCompressedR = red / 255.0,
           gammaCompressedG = green / 255.0,
           gammaCompressedB = blue / 255.0;

    // convert to linear components
    double Rlin = (gammaCompressedR <= 0.04045) ? gammaCompressedR / 12.92 : pow((gammaCompressedR + 0.055) / 1.055, 2.4);
    double Glin = (gammaCompressedG <= 0.04045) ? gammaCompressedG / 12.92 : pow((gammaCompressedG + 0.055) / 1.055, 2.4);
    double Blin = (gammaCompressedB <= 0.04045) ? gammaCompressedB / 12.92 : pow((gammaCompressedB + 0.055) / 1.055, 2.4);

    // get basic linear luminance
    double linearLuminance = Rlin * 0.2126 + Glin * 0.7152 + Blin * 0.0722;

    // convert to gamma compressed luminance
    double gammaCompressedLuminance = (linearLuminance <= 0.0031308) ? linearLuminance * 12.92 : 1.055 * pow(linearLuminance, 1.0 / 2.4) - 0.055;

    unsigned char value = static_cast<unsigned char>(gammaCompressedLuminance * 255.0);

    // return grey Pixel
    return value;
}
