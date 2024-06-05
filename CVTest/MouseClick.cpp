#include "MouseClick.h"
#include <Windows.h>
#include <memory>

bool MouseMove(double x, double y)
{
    double fScreenWidth  = ::GetSystemMetrics(SM_CXSCREEN) - 1; // ��ȡ��Ļ�ֱ��ʿ��?
    double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1; // ��ȡ��Ļ�ֱ��ʸ߶�?
    double fx            = x * (65535.0f / fScreenWidth);
    double fy            = y * (65535.0f / fScreenHeight);

    printf("fScreenWidth %lf , fScreenHeight %lf, fx %lf, fy %lf \n", fScreenWidth, fScreenHeight, fx, fy);

    INPUT input      = {0};
    input.type       = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    input.mi.dx      = fx;
    input.mi.dy      = fy;
    SendInput(1, &input, sizeof(INPUT));
    return true;
}

void MouseLeftDown() // ����������
{
    INPUT input      = {0};
    input.type       = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
}

void MouseLeftUp() // �������ſ�
{
    INPUT input      = {0};
    input.type       = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

void MouseRightDown() // ����Ҽ�����
{
    INPUT input      = {0};
    input.type       = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &input, sizeof(INPUT));
}

void MouseRightUp() // ����Ҽ��ſ�
{
    INPUT input      = {0};
    input.type       = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));
}