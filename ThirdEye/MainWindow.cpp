/*
ThirdEye main window for testing of reading and display by opencv

Will read text on screen and display what it sees through opencv
*/
#include "MainWindow.h"
#include "VFrameReader.h"
#include <vector>
#include <string>
#include <iostream>


BOOL CALLBACK EnumCallback(HWND hwnd, LPARAM lParam) {
    const DWORD TITLE_SIZE = 1024;
    WCHAR windowTitle[TITLE_SIZE];

    GetWindowTextW(hwnd, windowTitle, TITLE_SIZE);

    int length = ::GetWindowTextLength(hwnd);
    std::wstring title(&windowTitle[0]);
    if (!IsWindowVisible(hwnd) || length == 0 || title == L"Program Manager") {
        return TRUE;
    }

    // Retrieve the pointer passed into this callback, and re-'type' it.
    // The only way for a C API to pass arbitrary data is by means of a void*.
    std::vector<std::wstring>& titles =
        *reinterpret_cast<std::vector<std::wstring>*>(lParam);
    titles.push_back(title);

    return TRUE;
}

/// <summary>
/// Constructor
/// </summary>
ThirdEye::MainWindow::MainWindow() {
	ThirdEye::MainWindow::InitializeComponent();

	// get list of HWNDs that are open
    std::vector<std::wstring> titles;
    EnumWindows(EnumCallback, reinterpret_cast<LPARAM>(&titles));
    // At this point, titles if fully populated and could be displayed, e.g.:
    for (const auto& title : titles) {
        HWND wHandle;
        wHandle = FindWindow(NULL, title.c_str());
        std::wcout << L"Title: " << title << L" HWND: " << wHandle << std::endl;
    }
        
	
	// call get frame to capture window
	ThirdEye::VFrameReader vfr;
	Image^ cFrame = vfr.GetFrame();
	this->CaptureView->Image = cFrame;
}

/// <summary>
/// Deconstructor
/// </summary>
ThirdEye::MainWindow::~MainWindow() {
	if (components)
	{
		delete components;
	}
}

