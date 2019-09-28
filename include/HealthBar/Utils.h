//
// Created by Ponto on 9/17/2019.
//

#ifndef HEALTHBAR_UTILS_H
#define HEALTHBAR_UTILS_H

#include <string>

std::string getPercentPortion(double currAmount, double totalAmount);

std::string getPercentBar(double currAmount, double totalAmount, int maxCharacters);

#endif //HEALTHBAR_UTILS_H
