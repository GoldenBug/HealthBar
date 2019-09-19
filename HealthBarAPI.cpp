#include "HealthBarAPI.h"

#include <iostream>
#include "healthbar.h"

void writeStatusBar(double currAmount, double totalAmount, std::string &text) {
    HealthBar::Instance()->writeStatusBar(currAmount, totalAmount, text);
}

void setBarPositionBottom(bool isBottom) {
    HealthBar::Instance()->setBarPositionBottom(isBottom);
}
