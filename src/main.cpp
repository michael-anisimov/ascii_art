/**
 * @file main.cpp
 * @brief Main entry point of the image processing program.
 */

#include <iostream>
#include "image.hpp"
#include "jpegimage.hpp"
#include "bmpimage.hpp"
#include <algorithm>
#include <string>
#include <iomanip>
#include <unistd.h>
#include "utils.hpp"

/**
 * @brief Main function of the image processing program.
 * @return The exit status of the program.
 */
int main()
{
    if (!welcomeUser())
    {
        return 0;
    }

    // The vector of all images we are operating with:
    std::vector<std::unique_ptr<Image>> images;

    while (true)
    {
        int user_choice = showMainPrompt(images);
        if (user_choice == -1)
        {
            break;
        }

        // Adding image
        if (user_choice == static_cast<int>(images.size()))
        {
            if (!addImage(images))
            {
                continue;
            }
        }
        // Adding filter
        else if (user_choice >= 0 && user_choice < static_cast<int>(images.size()))
        {
            // On this step, image is successfully loaded
            addFilter(images, user_choice);
        }
        // Animation
        else
        {
            animation(images);
        }
    }

    return 0;
}
