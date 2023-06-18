/**
 * @file Image.cpp
 * @brief Implementation of the Image class.
 */

#include "image.hpp"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>

/**
 * @brief Sets the transition string for converting grayscale values to ASCII symbols.
 * @param transition The transition string.
 */
void Image::setTransition(const std::string &transition)
{
    m_transition = transition;
    std::cout << "Transition string set to: " << m_transition << std::endl;
}

/**
 * @brief Sets the path of the image.
 * @param path The path of the image.
 */
void Image::setPath(std::string &path)
{
    m_path = path;
}

/**
 * @brief Gets the path of the image.
 * @return The path of the image.
 */
std::string &Image::getPath()
{
    return m_path;
}

/**
 * @brief Converts the image to grayscale.
 */
void Image::toGreyScale()
{
    m_grey_image.resize(m_height, std::vector<unsigned char>(m_width));
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            m_grey_image[y][x] = m_raw_image[y][x].getGrey();
        }
    }
}

/**
 * @brief Converts a grayscale value to an ASCII symbol.
 * @param brightness The grayscale value.
 * @return The corresponding ASCII symbol.
 */
char Image::greyToAsciiSymbol(int brightness)
{
    int index = brightness * (m_transition.size() - 1) / 255;
    return m_transition[index];
}

/**
 * @brief Converts the grayscale image to ASCII art.
 */
void Image::convertGreyToAscii()
{
    m_ascii_image.resize(m_height, std::vector<char>(m_width));
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            m_ascii_image[y][x] = greyToAsciiSymbol(m_grey_image[y][x]);
        }
    }
}

/**
 * @brief Resizes the ASCII image to fit the terminal size.
 */
void Image::resizeAsciiImage()
{
    if (!m_scaled_ascii_image.empty() && m_scaled_ascii_image.size() == static_cast<size_t>(m_width) && m_scaled_ascii_image[0].size() == static_cast<size_t>(m_height))
        return;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int terminal_width = w.ws_col;
    int terminal_height = w.ws_row;

    int width = m_width;
    int height = 0.5 * m_height;

    if (width > terminal_width)
    {
        double scale = (double)terminal_width / width;
        width = terminal_width;
        height = height * scale;
    }
    if (height > terminal_height)
    {
        double scale = (double)terminal_height / height;
        height = terminal_height;
        width = width * scale;
    }

    m_scaled_ascii_image.clear();
    m_scaled_ascii_image.resize(height, std::vector<char>(width));

    double x_scale = (double)m_width / width;
    double y_scale = (double)m_height / height;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            m_scaled_ascii_image[y][x] = m_ascii_image[y * y_scale][x * x_scale];
        }
    }
}

/**
 * @brief Negates the colors of the image.
 */
void Image::negateImage()
{
    std::cout << "negateImage" << std::endl;
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            m_grey_image[y][x] = 255 - m_grey_image[y][x];
        }
    }
}

/**
 * @brief Mirrors the image horizontally.
 */
void Image::mirrorImage()
{
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width / 2; ++x)
        {
            std::swap(m_grey_image[y][x], m_grey_image[y][m_width - x - 1]);
        }
    }
}

/**
 * @brief Changes the brightness of the image.
 * @param delta The amount of change in brightness.
 */
void Image::changeBrigtness(int delta)
{
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            m_grey_image[y][x] = std::min(std::max(m_grey_image[y][x] + delta, 0), 255);
        }
    }
}

/**
 * @brief Prints the ASCII art of the image.
 */
void Image::printAsciiArt()
{
    std::cout << "\033[2J\033[1;1H";
    for (size_t y = 0; y < m_scaled_ascii_image.size(); ++y)
    {
        for (size_t x = 0; x < m_scaled_ascii_image[0].size(); ++x)
        {
            std::cout << m_scaled_ascii_image[y][x];
        }
        std::cout << std::endl;
    }
}
