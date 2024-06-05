#include <iostream>
#include "Target.h"
#include "Mark.h"
#include "MouseClick.h"

int main()
{
    TargetPic target;
    target.m_sPicFolder = "C:/Users/Lenovo/Desktop/target";
    target.CookData();
    MouseMove(std::get<0>(target.m_matchSite), std::get<1>(target.m_matchSite));
    return 0;
}