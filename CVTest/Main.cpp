#include <iostream>
#include "Target.h"
#include "Mark.h"
#include "MouseClick.h"

int main()
{
    double a = 0.0f, b = 0.0f;
    while (1) {
        std::cin >> a >> b;
        MouseMove(a, b);       
    }
    return 0;
}