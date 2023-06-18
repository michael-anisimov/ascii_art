#include <iostream>
#include "image.hpp"
#include "jpegimage.hpp"
#include "bmpimage.hpp"
#include <algorithm>
#include <string>
#include <iomanip>
#include <unistd.h>
#include "utils.hpp"

bool welcomeUser()
{
    // Clear terminal:
    std::cout << "\033[2J\033[1;1H";

    std::cout << "Welcome to the ASCII transformer!" << std::endl;

    JpegImage logo;
    if (!logo.loadImage("examples/logo.jpg"))
    {
        std::cout << "Sorry..." << std::endl;
        return 0;
    }

    logo.toGreyScale();
    logo.convertGreyToAscii();
    logo.resizeAsciiImage();
    logo.printAsciiArt();

    return 1;
}

void trimPath(std::string &path)
{
    // If there are ' sings in the path, remove them
    if (path[0] == '\'' && path[path.size() - 1] == '\'')
    {
        path.erase(0, 1);
        path.erase(path.size() - 1, 1);
    }
}

void changeTransition(std::unique_ptr<Image> &im)
{
    int choice = 0;
    do
    {
        std::cout << "Choose ascii transition string: " << std::endl;
        std::cout << "1. $@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. " << std::endl;
        std::cout << "2. @%#*+=-:. " << std::endl;
        std::cout << "3. Your own" << std::endl;

        std::cin >> choice;

        if (choice == 1)
        {
            im->setTransition("$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ");
        }
        else if (choice == 2)
        {
            im->setTransition("@%#*+=-:. ");
        }
        else if (choice == 3)
        {
            std::cout << "Enter your own transition string:" << std::endl;

            // Get the line from user with getline and remove last character (newline)
            std::string transition;
            std::cin.ignore();
            std::getline(std::cin, transition);
            transition.pop_back();

            // std::string transition;

            // std::cin >> quoted(transition);
            im->setTransition(transition);
        }
        else
        {
            std::cout << "Wrong input!" << std::endl;
        }
    } while (choice != 1 && choice != 2 && choice != 3);
}

void showPrompt()
{
    std::cout << "Write a path to the JPEG/BMP(24 bit) image or drop it here to add to list (Ctrl + C to quit):" << std::endl;
    std::cout << ">> ";
}

int showMainPrompt(std::vector<std::unique_ptr<Image>> &images)
{
    std::cout << "Choose what you want to do:" << std::endl;
    size_t i = 0;
    for (i = 0; i < images.size(); ++i)
    {
        std::cout << i + 1 << ". Edit " << images[i]->getPath() << std::endl;
    }
    std::cout << i + 1 << ". "
              << "Add image" << std::endl;
    std::cout << i + 2 << ". "
              << "Show animation" << std::endl;
    std::cout << i + 3 << ". "
              << "Quit" << std::endl;

    int choice;

    // get the user input, if itsnt a number, clear the buffer and try again
    while (!(std::cin >> choice) || choice < 1 || static_cast<size_t>(choice) > images.size() + 3)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Try again" << std::endl;
    }

    return choice == static_cast<int>(i + 3) ? -1 : choice - 1;
}

void showFilterOptions()
{
    std::cout << "Now, choose which filter(s) to apply (type up to 4 numbers separated by space):" << std::endl;
    std::cout << "0. No filter" << std::endl;
    std::cout << "1. Negate image" << std::endl;
    std::cout << "2. Mirror image" << std::endl;
    std::cout << "3. Change brightness" << std::endl;
    std::cout << "4. Change transition string" << std::endl;
    std::cout << "5. Quit to choose another image " << std::endl;
}

void animation(std::vector<std::unique_ptr<Image>> &images)
{
    std::cout << "Enter the delay between frames (in seconds):" << std::endl;
    std::cout << ">> ";
    double delay;
    while (!(std::cin >> delay) || delay < 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Try again" << std::endl;
    }

    std::cout << "Enter the number of loops:" << std::endl;
    std::cout << ">> ";
    int loops;
    while (!(std::cin >> loops) || loops < 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Try again" << std::endl;
    }

    // let user writes in what order and what images he wants to see or if he typed 0, show all
    std::cout << "Enter the order of images (0 for all):" << std::endl;
    std::cout << ">> ";
    std::vector<int> order;
    int number;
    while (std::cin >> number)
    {
        if (number == 0)
        {
            std::cout << "Order is zero" << std::endl;

            for (size_t i = 1; i <= images.size(); ++i)
            {
                order.push_back(i);
            }
            break;
        }
        if (number >= 1 && number <= static_cast<int>(images.size()))
            order.push_back(number);

        if (std::cin.peek() == '\n')
            break;
    }

    // show images in the given order
    while (loops != 0)
    {
        std::cout << "looping!" << loops << std::endl;
        std::cout << "order size: " << order.size() << std::endl;
        for (size_t i = 0; i < order.size(); ++i)
        {
            images[order[i] - 1]->resizeAsciiImage();
            images[order[i] - 1]->printAsciiArt();
            usleep(delay * 1000000);
        }
        if (loops != 0)
            --loops;
    }
}

bool getOptions(std::vector<int> &numbers)
{
    numbers.clear();

    char number;
    bool end = false;

    while (std::cin >> number)
    {
        // if number is not a digit or is 0, clear the buffer and try again
        if ((!isdigit(number) && number != '0') || number > '5')
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Try again" << std::endl;
            continue;
        }
        else
        { // transform char to digit
            number -= '0';
        }

        if (number == 5) // The user wants to quit
        {
            end = true;
            break;
        }
        if (std::find(numbers.begin(), numbers.end(), number) == numbers.end() && number >= 1 && number <= 4)
            numbers.push_back(number);

        if (std::cin.peek() == '\n' || numbers.size() == 4 || std::cin.peek() == '0')
            break;
    }

    std::cin.clear();

    return end ? 0 : 1;
}

void listImages(std::vector<std::unique_ptr<Image>> &images)
{
    // List path to all images:
    for (size_t i = 0; i < images.size(); ++i)
    {
        std::cout << i + 1 << ". " << images[i]->getPath() << std::endl;
    }
}

bool addImage(std::vector<std::unique_ptr<Image>> &images)
{
    // Prompt:
    showPrompt();

    // Get the path from user:
    std::string path;
    std::cin >> path;

    trimPath(path);

    // Check if the path is correct:
    if (path.find(".jpg") == std::string::npos && path.find(".bmp") == std::string::npos && path.find(".jpeg") == std::string::npos)
    {
        std::cout << "Not an image of specified format!" << std::endl;
        return 0;
    }

    // Add an image to the vector of images if it is successfully loaded:
    if (path.find(".jpg") != std::string::npos || path.find(".jpeg") != std::string::npos)
    {
        images.push_back(std::make_unique<JpegImage>());
    }
    else if (path.find(".bmp") != std::string::npos)
    {
        images.push_back(std::make_unique<BmpImage>());
    }
    else
    {
        std::cout << "Not an image of specified format!" << std::endl;
        return 0;
    }

    // Load the image:
    images.back()->setPath(path);
    if (!images.back()->loadImage(path))
    {
        images.pop_back();
        std::cout << "Try again!" << std::endl;
        return 0;
    }

    images.back()->toGreyScale();
    images.back()->convertGreyToAscii();
    images.back()->resizeAsciiImage();
    // images.back()->printAsciiArt();

    return 1;
}

void addFilter(std::vector<std::unique_ptr<Image>> &images, int user_choice)
{
    while (true)
    {
        showFilterOptions();

        // Get the vector of numbers from user:
        std::vector<int> numbers;
        if (!getOptions(numbers))
        {
            break;
        }

        listImages(images);
        // First, convert to grey:
        images[user_choice]->toGreyScale();

        // Choose filters here:
        if (std::find(numbers.begin(), numbers.end(), 1) != numbers.end())
        {
            images[user_choice]->negateImage();
        }
        if (std::find(numbers.begin(), numbers.end(), 2) != numbers.end())
        {
            images[user_choice]->mirrorImage();
        }
        if (std::find(numbers.begin(), numbers.end(), 3) != numbers.end())
        {
            std::cout << "Enter the brightness change (from -255 to 255):" << std::endl;
            std::cout << ">> ";
            int brightness;

            // Ask for brighness until user enter a valid integer
            while (!(std::cin >> brightness) || brightness < -255 || brightness > 255)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Try again" << std::endl;
            }

            images[user_choice]->changeBrigtness(brightness);
        }
        if (std::find(numbers.begin(), numbers.end(), 4) != numbers.end())
        {
            changeTransition(images[user_choice]);
        }

        images[user_choice]->convertGreyToAscii();
        images[user_choice]->resizeAsciiImage();
        images[user_choice]->printAsciiArt();
    }
}
