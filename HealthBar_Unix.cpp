#ifdef __linux__

#include <stdlib.h>

#include "HealthBar.h"
#include "Utils.h"

HealthBar* HealthBar::m_pInstance = NULL;

HealthBar* HealthBar::Instance()
{
    if (!m_pInstance)
        m_pInstance = new HealthBar;
    return m_pInstance;
}

void HealthBar::writeStatusBar(double currAmount, double totalAmount, std::string text) {

}

#endif