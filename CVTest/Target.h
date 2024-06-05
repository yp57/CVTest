#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

// Data repo, load, cook
struct TargetPic
{
    std::string                m_sPicFolder;
    std::vector<cv::Mat>       m_vTargets;
    cv::Mat                    m_realPic;
    std::tuple<double, double> m_matchSite;

    bool LoadPics(std::string &picFolder); // load pics by folder path
    bool GetRealPic();
    bool CookData();
    bool MatchPic(cv::Mat picR, cv::Mat picT);
};