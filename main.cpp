
#include "HealthBarAPI.h"
#include "iostream"
#include <chrono>
#include <thread>

#define MAXVALUE 1000

int main() {
    for (int num = 0; num <= MAXVALUE; ++num) {
        writeStatusBar(num, MAXVALUE, "");
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    int x;
    std::cin >> x;
}