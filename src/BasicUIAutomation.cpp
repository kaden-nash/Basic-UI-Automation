#include <windows.h>
#include <winuser.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

// mouse
POINT getCursorPtr();
int moveMouse(int x, int y);

// keyboard
void kEvent(vector<WORD> input);
INPUT kEventPressHelper(INPUT inputStruct, WORD input);
INPUT kEventUnpressHelper(INPUT inputStruct, WORD input);
int getInputError(UINT sent, int sizeInput); 



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







//  Windows Manipulation 