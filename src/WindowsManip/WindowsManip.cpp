#include "..\..\include\WindowsManip.h"
#include <iostream>

/*

namespace WindowsManip {
    using std::cout;
    using std::endl;

    void getWindows(windowInfo_s *info)
    {
        EnumWindows(EnumWindowsProc, (LPARAM) info);
    }

    void getChildWindows(windowInfo_s *childInfo, HWND hwnd)
    {
        EnumChildWindows((HWND) hwnd, EnumChildProc, (LPARAM) childInfo);
    }

    namespace {
        BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
        {
            char title[257];
            WINDOWINFO windowInfo;
            windowInfo_s* info = (windowInfo_s*)lParam;
            windowInfo.cbSize = sizeof(WINDOWINFO);

            int windowTextLength = GetWindowText(hwnd, title, 257);
            int windowInfoRes = GetWindowInfo(hwnd, &windowInfo);

            if (windowTextLength != strlen(title))
                cout << "Something went wrong getting window text: " << GetLastError() << endl;

            if (windowInfoRes == 0)
                cout << "Something went wrong getting window info: " << GetLastError() << endl;


            if ((int)title[0] > 0 && strcmp(title, "Default IME") != 0 && strcmp(title, "MSCTFIME UI") != 0)
            {
                info->sizeOfVectors = info->windowTitles.size();

                info->windowHandles.push_back(hwnd); 
                info->windowTitles.push_back((string) title);
                info->windowInfo.push_back(windowInfo);

                info->sizeOfVectors++;
            }

            return TRUE;
        }

        BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
        {
            char title[1080];
            WINDOWINFO windowInfo;
            windowInfo_s* info = (windowInfo_s*)lParam;
            windowInfo.cbSize = sizeof(WINDOWINFO);

            int windowTextLength = GetWindowText(hwnd, title, 257);
            int windowInfoRes = GetWindowInfo(hwnd, &windowInfo);

            if (windowTextLength != strlen(title))
                cout << "Something went wrong getting window text: " << GetLastError() << endl;

            if (windowInfoRes == 0)
                cout << "Something went wrong getting window info: " << GetLastError() << endl;


            if ((int)title[0] > 0 && strcmp(title, "Default IME") != 0 && strcmp(title, "MSCTFIME UI") != 0)
            {
                info->sizeOfVectors = info->windowTitles.size();

                info->windowHandles.push_back(hwnd); 
                info->windowTitles.push_back((string) title);
                info->windowInfo.push_back(windowInfo);

                info->sizeOfVectors++;
            }

            return TRUE;
        }
    }
}
*/