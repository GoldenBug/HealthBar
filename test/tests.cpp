
#include "HealthBar/HealthBarAPI.h"
#include "iostream"
#include <chrono>
#include <thread>

#define MAXVALUE 1000

int main() {
    for (int num = 0; num <= MAXVALUE; ++num) {
        std::string text = "Testing 1";
        writeStatusBar(num, MAXVALUE, text);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (num % 20 == 0)
            std::cout << "test " << num << std::endl;
    }
    for (int num = 0; num <= MAXVALUE; ++num) {
        std::string text = "Testing 2";
        writeStatusBar(num, MAXVALUE, text);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    int x;
    std::cin >> x;
}