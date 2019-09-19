#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__) || defined(__CYGWIN__)

#include <windows.h>
#include <iostream>

#include "HealthBar.h"
#include "Utils.h"

HealthBar *HealthBar::m_pInstance = nullptr;

HealthBar *HealthBar::Instance() {
    if (!m_pInstance) {
        m_pInstance = new HealthBar;

        // Get console width on windows.
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        if (ret) {
            m_pInstance->lineWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            m_pInstance->lineHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        }
    }

    return m_pInstance;
}

void HealthBar::writeStatusBar(double currAmount, double totalAmount, std::string text) {
    HANDLE screenHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret = GetConsoleScreenBufferInfo(screenHandle, &csbi);

    std::string percentString = getPercentPortion(currAmount, totalAmount);
    std::string percentBar = getPercentBar(currAmount, totalAmount, this->lineWidth - percentString.length());

    if (ret && this->BarPositionBottom) {
        short newY = this->lineHeight - 1;
        COORD pos = {csbi.dwCursorPosition.X, newY};
        SetConsoleCursorPosition(screenHandle, pos);
    }

    std::cout << percentString << percentBar << '\r' << std::flush;

    if (ret && this->BarPositionBottom) {
        SetConsoleCursorPosition(screenHandle, csbi.dwCursorPosition);
    }

    if (currAmount == totalAmount)
        std::cout << std::endl;
}

void HealthBar::setBarPositionBottom(bool isBottom) {
    this->BarPositionBottom = isBottom;
}

#endif