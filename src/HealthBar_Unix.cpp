
#include "HealthBar/HealthBar.h"
#include "HealthBar/Utils.h"
#include <iostream>
#include <sys/ioctl.h> // For ioctl, TIOCGWINSZ
#include <unistd.h> // For STDOUT_FILENO

HealthBar *HealthBar::m_pInstance = nullptr;

HealthBar *HealthBar::Instance() {
    if (!m_pInstance) {
        m_pInstance = new HealthBar;
    }

    return m_pInstance;
}

void HealthBar::writeStatusBar(double currAmount, double totalAmount, std::string &text) {

    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    text = "[" + text + "]";
    std::string percentString = getPercentPortion(currAmount, totalAmount);
    int percentBarLength = size.ws_col - (percentString.length() + text.length());
    std::string percentBar = getPercentBar(currAmount, totalAmount, percentBarLength);
    std::string completeString = text + percentString + percentBar;

    if (this->BarPositionBottom) {

        if (currAmount == totalAmount)
            finalizeProgressBar(completeString, 0);
        else
            std::cout << "\r" << std::flush;
    } else {
        std::cout << completeString;
        if (currAmount == totalAmount)
            std::cout << "\n" << std::flush;
        else
            std::cout << "\r" << std::flush;
    }

}

void HealthBar::finalizeProgressBar(std::string &progressBar, short startingPosition) {

    std::cout << progressBar << std::endl;
}

void HealthBar::setBarPositionBottom(bool isBottom) {
    this->BarPositionBottom = isBottom;
}
