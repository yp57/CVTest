#include "CommonUtils.h"
#include <io.h>
#include <ctime>
#include <random>

void GetAllFiles(std::string path, std::vector<std::string> &files)
{
    // �ļ����
    intptr_t hFile = 0;
    // �ļ���Ϣ�ṹ��
    struct _finddata_t fileinfo;
    std::string        p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                    files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                    GetAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
                }
            } else {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

int BigRandomTime() { return rand() % (200 - 100 + 1) + 100; }

int SmallRandomTime() { return rand() % (50 - 20 + 1) + 20; }
