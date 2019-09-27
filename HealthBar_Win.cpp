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

void HealthBar::writeStatusBar(double currAmount, double totalAmount, std::string &text) {
    HANDLE screenHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret = GetConsoleScreenBufferInfo(screenHandle, &csbi);

    text = "[" + text + "]";
    std::string percentString = getPercentPortion(currAmount, totalAmount);
    int percentBarLength = this->lineWidth - (percentString.length() + text.length());
    std::string percentBar = getPercentBar(currAmount, totalAmount, percentBarLength);
    std::string completeString = text + percentString + percentBar;

    if (ret && this->BarPositionBottom) {
        COORD pos = {csbi.dwCursorPosition.X, csbi.srWindow.Bottom};
        SetConsoleCursorPosition(screenHandle, pos);
    }

    if (currAmount == totalAmount) {
        HealthBar::finalizeProgressBar(completeString, csbi.dwCursorPosition.Y);
    } else {
        std::cout << completeString << "\r" << std::flush;
        if (ret && this->BarPositionBottom) {
            SetConsoleCursorPosition(screenHandle, csbi.dwCursorPosition);
        }
    }
}

void HealthBar::finalizeProgressBar(std::string &progressBar, short startingPosition) {
    HANDLE screenHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret = GetConsoleScreenBufferInfo(screenHandle, &csbi);

    if (ret && this->BarPositionBottom) {
        std::cout << std::string(this->lineWidth, ' ') << std::flush;
        COORD pos = {0, startingPosition};
        SetConsoleCursorPosition(screenHandle, pos);
    }

    std::cout << progressBar << std::endl;
}

void HealthBar::setBarPositionBottom(bool isBottom) {
    this->BarPositionBottom = isBottom;
}

#endif