//
// Created by Ponto on 9/17/2019.
//

#ifndef HEALTHBAR_HEALTHBAR_H
#define HEALTHBAR_HEALTHBAR_H

#include <string>

class HealthBar {

public:
    static HealthBar *Instance();
    void writeStatusBar(double currAmount, double totalAmount, std::string text);

private:
    HealthBar() = default;  // Private so that it can  not be called
    HealthBar(HealthBar const &) {};             // copy constructor is private
    HealthBar &operator=(HealthBar const &) {};  // assignment operator is private
    static HealthBar *m_pInstance;

    int lineWidth = 0;
};


#endif //HEALTHBAR_HEALTHBAR_H
