#include "Target.h"
#include <Windows.h>
#include <opencv2/core.hpp>
#include <string>
#include <vector>
#include "CommonUtils.h"

using namespace cv;

bool TargetPic::LoadPics(std::string &picFolder)
{
    std::vector<std::string> picPaths;
    GetAllFiles(picFolder, picPaths);
    if (picPaths.empty()) {
        MessageBox(NULL, "LoadPics: there is no pic in this folder", "", MB_OK);
        return false;
    }
    for (size_t i = 0; i < picPaths.size(); ++i) {
        Mat img = imread(picPaths[i]);
        m_vTargets.push_back(img);
    }
    return true;
}

bool TargetPic::GetRealPic()
{
    HWND hwnd = GetDesktopWindow();
    HDC  hwindowDC, hwindowCompatibleDC;

    int              height, width, srcheight, srcwidth;
    HBITMAP          hbwindow;
    cv::Mat          src;
    BITMAPINFOHEADER bi;

    hwindowDC           = GetDC(hwnd);
    hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    RECT windowsize; // get the height and width of the screen
    GetClientRect(hwnd, &windowsize);

    srcheight = windowsize.bottom;
    srcwidth  = windowsize.right;
    height    = windowsize.bottom;
    width     = windowsize.right;

    src.create(height, width, CV_8UC4);

    // create a bitmap
    hbwindow           = CreateCompatibleBitmap(hwindowDC, width, height);
    bi.biSize          = sizeof(BITMAPINFOHEADER);
    bi.biWidth         = width;
    bi.biHeight        = -height; // this is the line that makes it draw upside down or not
    bi.biPlanes        = 1;
    bi.biBitCount      = 32;
    bi.biCompression   = BI_RGB;
    bi.biSizeImage     = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed       = 0;
    bi.biClrImportant  = 0;

    // use the previously created device context with the bitmap
    SelectObject(hwindowCompatibleDC, hbwindow);
    // copy from the window device context to the bitmap device context
    StretchBlt(
      hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight,
      SRCCOPY); // change SRCCOPY to CAPTUREBLT to capture layered windows
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);

    // avoid memory leak
    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);
    m_realPic = src;
    return true;
}

bool TargetPic::CookData()
{
    // Get realtime pic
    if (!GetRealPic()) {
        MessageBox(NULL, "CookData: GetRealPic Fail!", "", MB_OK);
        return false;
    }

    // Load target pic
    std::cout << "print in pic folder path" << std::endl;
    std::string tmp;
    std::cin >> tmp;
    if (!LoadPics(tmp)) {
        return false;
    }

    // Match
    if (!MatchPic(m_realPic, m_vTargets[0])) { // todo
        return false;
    }
    // Return match result

    // Use SIFT algorithm to get keypoints and descriptors

    return false;
}

bool TargetPic::MatchPic(cv::Mat picR, cv::Mat picT)
{
    int     result_cols = picR.cols;
    int     result_rows = picR.rows;
    cv::Mat result(result_rows, result_cols, CV_32FC1);

    // 执行模板匹配
    cv::matchTemplate(picR, picT, result, cv::TM_CCOEFF_NORMED);

    // 归一化结果
    // cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

    // 找到最佳匹配位置
    double    minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    // 绘制匹配结果
    cv::Point matchLoc = maxLoc;
    cv::rectangle(
      picR, matchLoc, cv::Point(matchLoc.x + picT.cols, matchLoc.y + picT.rows), cv::Scalar(0, 255, 0), 2, 8, 0);
    m_matchSite = std::tuple<double, double>(minVal, maxVal);
    // 显示结果
    // cv::imshow("Matched Image", picR);
    // cv::waitKey(0);
    // cv::destroyAllWindows();
    return true;
}
