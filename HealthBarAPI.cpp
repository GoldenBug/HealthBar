#include "HealthBarAPI.h"

#include <iostream>
#include "healthbar.h"

void hello() {
    std::cout << "Hello, World!" << std::endl;
}

void writeStatusBar(int currAmount, int totalAmount, std::string text) {
    std::cout << "Here" << std::endl;
    HealthBar::Instance()->writeStatusBar(0, 0, "");
}

void writeStatusBar(double currAmount, double totalAmount, std::string text) {

}
