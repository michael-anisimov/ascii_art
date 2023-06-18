#ifndef UTILS_HPP
#define UTILS_HPP

#include "image.hpp"
#include <string>
#include <iomanip>

bool welcomeUser();
/**
 * @brief Display a welcome message to the user.
 * @return True if the user is welcomed successfully, false otherwise.
 *
 * This function displays a welcome message to the user.
 * It can be used to greet the user when the program starts.
 * The function returns true if the welcome message is displayed successfully, and false otherwise.
 */

void trimPath(std::string &path);
/**
 * @brief Trim the path string.
 * @param path The path string to be trimmed.
 *
 * This function trims the leading and trailing spaces from the path string.
 * It modifies the input string in-place.
 */

void changeTransition(std::unique_ptr<Image> &im);
/**
 * @brief Change the transition of an image.
 * @param im A unique pointer to the Image object.
 *
 * This function allows the user to change the transition of the specified image.
 * It takes a unique pointer to the Image object as a parameter and modifies the transition value.
 */

void showPrompt();
/**
 * @brief Display the program prompt.
 *
 * This function displays the prompt for user input in the program.
 */

int showMainPrompt(std::vector<std::unique_ptr<Image>> &images);
/**
 * @brief Display the main menu prompt.
 * @param images A vector of unique pointers to Image objects.
 * @return The user's choice.
 *
 * This function displays the main menu prompt and returns the user's choice.
 * The available options are numbered, and the user is prompted to enter a number corresponding to the desired option.
 * The function validates the user's input and returns the chosen option.
 */

void showFilterOptions();
/**
 * @brief Display the filter options.
 *
 * This function displays the available filter options to the user.
 * It can be used in the program menu to show the user the available filters.
 */

void animation(std::vector<std::unique_ptr<Image>> &images);
/**
 * @brief Perform an animation with the images.
 * @param images A vector of unique pointers to Image objects.
 *
 * This function performs an animation using the images in the specified vector.
 * It can be used to create a visual display or effect using the images.
 */

bool getOptions(std::vector<int> &numbers);
/**
 * @brief Get user options.
 * @param numbers A vector to store the user's options.
 * @return True if the user's options are retrieved successfully, false otherwise.
 *
 * This function prompts the user to enter a series of options and stores them in the specified vector.
 * The function validates the user's input and returns true if the options are retrieved successfully, and false otherwise.
 */

void listImages(std::vector<std::unique_ptr<Image>> &images);
/**
 * @brief List the available images.
 * @param images A vector of unique pointers to Image objects.
 *
 * This function lists the available images in the specified vector.
 * It can be used to display the names or details of the images to the user.
 */

bool addImage(std::vector<std::unique_ptr<Image>> &images);
/**
 * @brief Add an image to the collection.
 * @param images A vector of unique pointers to Image objects.
 * @return True if the image is added successfully, false otherwise.
 *
 * This function allows the user to add an image to the collection.
 * It prompts the user for the image file path, loads the image, and adds it to the vector.
 * The function returns true if the image is added successfully, and false otherwise.
 */

void addFilter(std::vector<std::unique_ptr<Image>> &images, int user_choice);
/**
 * @brief Add a filter to an image.
 * @param images A vector of unique pointers to Image objects.
 * @param user_choice The user's choice of filter.
 *
 * This function allows the user to add a filter to the specified image.
 * It takes the user's choice of filter as input and applies the corresponding filter to the image.
 */

#endif
