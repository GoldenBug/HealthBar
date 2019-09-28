#include "../include/HealthBar/HealthBarAPI.h"
#include "../include/HealthBar/HealthBar.h"

void writeStatusBar(double currAmount, double totalAmount, std::string &text) {
    HealthBar::Instance()->writeStatusBar(currAmount, totalAmount, text);
}

void setBarPositionBottom(bool isBottom) {
    HealthBar::Instance()->setBarPositionBottom(isBottom);
}
