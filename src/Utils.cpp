//
// Created by Ponto on 9/17/2019.
//

#include "../include/HealthBar/Utils.h"
#include <cmath>

std::string getPercentPortion(double currAmount, double totalAmount) {
    int percentage = ((currAmount / totalAmount) * 100);
    std::string percentString = "[";

    if (percentage < 10)
        percentString += "  " + std::to_string(percentage);
    else if (percentage < 100)
        percentString += " " + std::to_string(percentage);
    else
        percentString += std::to_string(percentage);

    percentString += "%]";

    return percentString;
}

std::string getPercentBar(double currAmount, double totalAmount, int maxCharacters) {
    double percentage = (currAmount / totalAmount);
    int numProgressChars = percentage * (maxCharacters - 3);
    std::string loadingBarString = "[";

    for (int count = 0; count < numProgressChars; ++count)
        loadingBarString += "#";
    for (int count = loadingBarString.length(); count < maxCharacters - 2; ++count)
        loadingBarString += " ";

    loadingBarString += "]";
    return loadingBarString;
}
