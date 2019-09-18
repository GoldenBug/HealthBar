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
        if (ret)
            m_pInstance->lineWidth = csbi.dwSize.X;
    }

    return m_pInstance;
}

void HealthBar::writeStatusBar(double currAmount, double totalAmount, std::string text) {
    std::string percentString = getPercentPortion(currAmount, totalAmount);
    std::string percentBar = getPercentBar(currAmount, totalAmount, this->lineWidth - percentString.length());
    std::cout << percentString << percentBar << '\r' << std::flush;
}

#endif