#ifndef HEALTHBAR_LIBRARY_H
#define HEALTHBAR_LIBRARY_H

#include <string>

void writeStatusBar(int currAmount, int totalAmount, std::string text);

void writeStatusBar(double currAmount, double totalAmount, std::string text);

#endif