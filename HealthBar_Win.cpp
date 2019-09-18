#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__) || defined(__CYGWIN__)

#include <windows.h>
#include "HealthBar.h"
#include <iostream>

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

void HealthBar::writeStatusBar(int currAmount, int totalAmount, std::string text) {

}

void HealthBar::writeStatusBar(double currAmount, double totalAmount, std::string text) {

}

#endif