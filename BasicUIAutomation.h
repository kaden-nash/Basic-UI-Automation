#ifndef UIAUTO_H
#define UIAUTO_H

#include <windows.h>
#include <winuser.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

struct windowInfo_s
{
    vector<HWND> windowHandles;
    vector<string> windowTitles;
    vector<WINDOWINFO> windowInfo;
    int sizeOfVectors = 0;
};

// mouse
POINT getCursorPtr();
int moveMouse(int x, int y);

// keyboard
void kEvent(vector<WORD> input);
INPUT kEventPressHelper(INPUT inputStruct, WORD input);
INPUT kEventUnpressHelper(INPUT inputStruct, WORD input);
int getInputError(UINT sent, int sizeInput); 

// window manipulation
void getWindows(windowInfo_s *info);
void getChildWindows(windowInfo_s *childInfo, HWND hwnd);
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);


/*
    int main ()
    {
        
        
        // get cursor position
        // POINT p = getCursorPtr();
        // cout << "(" << p.x << ", " << p.y << ")" << endl;

        

        // Move mouse location
        // SetCursorPos(960, 540);
        // Sleep(500);
        // SetCursorPos(960 + 10, 540);
        // Sleep(500);
        // SetCursorPos(1800, 900);

        

        // Create a keyboard event
        
        // Letters must be capitalized or else they are taken to be ints.
        // To captialize a letter, you must press shift and then the key.
        // vector<WORD> vec = {VK_LWIN, 'F', 'I', 'L', 'E', ' ', 'E', 'X', 'P', 'L', 'O', 'R', 'E', 'R', VK_RETURN};
        // kEvent(vec);



        // Create a mouse event 

        // Track keyboard actions

        // Track mouse actions



        // list all open windows
        // windowInfo_s info;
        // getWindows(&info);
        
        // for(int i = 0; i < info.sizeOfVectors; i++)
        // {
        //     cout << "Title: " << info.windowTitles[i] << ", Handle: " << info.windowHandles[i] << ", Info[i]: " << info.windowInfo[i].cbSize << endl;
        // }

        // windowInfo_s childInfo;
        // EnumChildWindows(info.windowHandles[4], EnumChildProc, (LPARAM) &childInfo);

        // for (int i = 0; i < childInfo.sizeOfVectors; i++)
        //     cout << "Title: " << childInfo.windowTitles[i] << ", Handle: " << childInfo.windowHandles[i] << ", Info[i]: " << childInfo.windowInfo[i].cbSize << endl;



        // Enter a window

        // close window

        // Get the elements I can interact with in the window
        

    //     return 0;
    // }

*/




//  Mouse 


/*
    Moves mouse to specified (x,y) location.
    --param: relative x position, relative y position
    --return: none
*/ 
int moveMouse(int x, int y)
{
    UINT successfulInputs = SetCursorPos(x, y);

    if (successfulInputs == 0)
    {
        cout << "Mouse movement was not successful: " << GetLastError() << endl;
        return 0;
    }

    return 1;
}

/*
Retrieves a structure containing the exact relative position of the cursor.
--param: none
--return: a POINT structure containing the relative position of the mouse.
*/
POINT getCursorPtr()
{
    POINT p;
    GetCursorPos(&p);
    return p;
}





//  Keyboard 



/* 
Performs a set of keyboard events
--param: takes in a vector of strings where each string represents an input or a combination of inputs (up to 3 presses at once). 
--return: returns boolean int value indicating success or failure of input
NOTE: The letters in the WORD vector must be capitalized for the function to recognize them as the desired key. 
*/
void kEvent(vector<WORD> input)
{
    int delay = 50;
    INPUT sInputs[2] = {};
    INPUT dInputs[4] = {};
    INPUT tInputs[6] = {};
    UINT sError = 0;
    UINT dError = 0;
    UINT tError = 0;
    vector<int> dashIndexes = {};
    int isSingle = 0;
    int isDouble = 0;
    int totalDoubles = 0;
    int isTriple = 0;
    int totalTriples = 0;
    int firstIndex;
    int secondIndex;
    int iterations = 0;

    //  Check size of vector
    int size = input.size();

    for (int i = 0; i < size; i++)
        if (input[i] == '-')
            dashIndexes.push_back(i);

    int totalDashes = dashIndexes.size();

    // Determining double and triples
    do 
    {
        // for debugging purposes
        iterations++;

        // determine whether a single, double, or triple exists
        if (dashIndexes.size() > 1)
        {
            firstIndex = dashIndexes[0];
            secondIndex = dashIndexes[1];

            if (secondIndex - firstIndex == 2)
                isTriple++;
            else if (secondIndex - firstIndex > 2)
                isDouble++;
            
        } 
        else if (dashIndexes.size() > 0 && dashIndexes.size() < 2)
        {
            firstIndex = dashIndexes[0];
            isDouble++;
        }
        else if (dashIndexes.size() == 0)
            isSingle++;
        else {
            cout << "Something is wrong..." << endl;
            cout << "dashIndexes.size(): " << dashIndexes.size() << endl;
        }
        
        // handle double and triple cases
        if (isDouble == 1 && isTriple == 0)
        {
            totalDoubles++;
            dashIndexes.erase(dashIndexes.begin());
            isDouble--;
        }
        else if (isDouble == 0 && isTriple == 1)
        {
            totalTriples++;
            dashIndexes.erase(dashIndexes.begin());
            dashIndexes.erase(dashIndexes.begin());
            isTriple--;
        }
        else if (isDouble == 0 && isTriple == 0)
            isSingle--;
        else {
            cout << "Something is wrong..." << endl;
            cout << "Iterations: " << iterations << endl;
            cout << "isDouble: " << isDouble << ", isTriple: " << isTriple << endl;
            cout << "totalDoubles: " << totalDoubles << ", totalTriples: " << totalTriples << endl;
            dashIndexes.erase(dashIndexes.begin(), dashIndexes.begin() + dashIndexes.size());
        }

    } while (dashIndexes.size() > 0);

    int totalSingles = input.size() - (5 * totalTriples) - (3 * totalDoubles);
    iterations = 0;

    // cout << "dashIndexes.size(): " << dashIndexes.size() << endl;
    // cout << "Singles: " << totalSingles << ", Doubles: " << totalDoubles << ", Triples: " << totalTriples << endl;
    // cout << "Total: " << totalSingles + totalDoubles + totalTriples << endl;
    // cout << "Total Dashes: " << totalDashes << endl;

    int totalSingleInputs = 0;
    int totalDoubleInputs = 0;
    int totalTripleInputs = 0;
    int i = 0;


    // populating all structures and sending all input.
    do
    {
        iterations++;
        
        if (totalDashes >= 2 && input[i + 1] == '-' && input[i + 3] == '-' && input.size() >= 5)
        {
            tInputs[0] = kEventPressHelper(tInputs[0], input[0]);
            tInputs[1] = kEventPressHelper(tInputs[1], input[2]);
            tInputs[2] = kEventPressHelper(tInputs[2], input[4]);

            tInputs[3] = kEventUnpressHelper(tInputs[3], input[0]);
            tInputs[4] = kEventUnpressHelper(tInputs[4], input[2]);
            tInputs[5] = kEventUnpressHelper(tInputs[5], input[4]);

            tError = SendInput(6, tInputs, sizeof(INPUT));

            input.erase(input.begin(), input.begin() + 5);
            totalDashes -= 2;
            totalTripleInputs += 3;

            Sleep(delay +  800);
        }
        else if (totalDashes >= 1 && input[i + 1] == '-' && input.size() >= 3)
        {
            dInputs[0] = kEventPressHelper(dInputs[0], input[0]);
            dInputs[1] = kEventPressHelper(dInputs[1], input[2]);

            dInputs[2] = kEventUnpressHelper(dInputs[2], input[0]);
            dInputs[3] = kEventUnpressHelper(dInputs[3], input[2]);

            dError = SendInput(4, dInputs, sizeof(INPUT));

            input.erase(input.begin(), input.begin() + 3);
            totalDashes--;
            totalDoubleInputs += 2;

            Sleep(delay + 300);
        }
        else if (totalDashes >= 0 && input.size() >= 1)
        {
            sInputs[0] = kEventPressHelper(sInputs[0], input[0]);
            sInputs[1] = kEventUnpressHelper(sInputs[1], input[0]);
            
            sError = SendInput(2, sInputs, sizeof(INPUT));

            input.erase(input.begin());
            totalSingleInputs++;

            Sleep(delay);
        }
        else
        {
            cout << "Something is wrong..." << endl; 
            cout << "Iterations: " << iterations << endl;
            cout << "firstIndex: " << firstIndex << ", secondIndex: " << secondIndex << endl;
            input.erase(input.begin(), input.begin() + input.size());
        }


    } while (input.size() > 0);

        // display errors
        if (tError > 0 || dError > 0 || sError > 0)
            cout << "Keyboard inputs: " << totalSingleInputs + totalDoubleInputs + totalTripleInputs << endl;
        else
        {
            // cout << "First" << endl;
            getInputError(sError, 2);
            // cout << "Second" << endl;
            getInputError(dError, 4);
            // cout << "Last" << endl;
            getInputError(tError, 6);
        }
}

INPUT kEventPressHelper(INPUT inputStruct, WORD input)
{
    inputStruct.type = INPUT_KEYBOARD;
    inputStruct.ki.wVk = input;

    return inputStruct;
}

INPUT kEventUnpressHelper(INPUT inputStruct, WORD input)
{
    inputStruct.type = INPUT_KEYBOARD;
    inputStruct.ki.wVk = input;
    inputStruct.ki.dwFlags = KEYEVENTF_KEYUP;

    return inputStruct;
}

int getInputError(UINT sent, int sizeInput)
{
    if (sent == 0)
        cout << "Sent inputs: " << sent << endl;
    else
        cout << "Something went wrong: " << GetLastError() << endl;
}




//  Windows Manipulation 


/*
Enumerates top level windows open on computer, not including any with empty titles or "MSCTFIME UI" or "Default IME".
--param: takes a windowInfo_s struct object reference where info will be stored. 
--return: none
*/
void getWindows(windowInfo_s *info)
{
    EnumWindows(EnumWindowsProc, (LPARAM) info);
}

void getChildWindows(windowInfo_s *childInfo, HWND hwnd)
{
    EnumChildWindows((HWND) hwnd, EnumChildProc, (LPARAM) childInfo);
}

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

#endif