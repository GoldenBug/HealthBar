#ifdef __linux__


#include "HealthBar.h"
#include <stdlib.h>

HealthBar* HealthBar::m_pInstance = NULL;

HealthBar* HealthBar::Instance()
{
    if (!m_pInstance)
        m_pInstance = new HealthBar;
    return m_pInstance;
}

void HealthBar::writeStatusBar(int currAmount, int totalAmount, std::string text) {

}

void HealthBar::writeStatusBar(double currAmount, double totalAmount, std::string text) {

}

#endif