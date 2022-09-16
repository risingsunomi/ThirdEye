/*
ThirdEye main window for testing of reading and display by opencv

Will read text on screen and display what it sees through opencv
*/
#include "MainWindow.h"
#include "VFrameReader.h"
#include "ComboboxItem.h"
#include <vector>
#include <string>
#include <iostream>
#include <codecvt>
#include <vcclr.h>
#include <list>


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
    
    // setup background workers
    this->WindowCaptureWorker->WorkerReportsProgress = false;
    this->WindowCaptureWorker->WorkerSupportsCancellation = true;

	// get list of HWNDs that are open
    std::vector<std::wstring> titles;
    EnumWindows(EnumCallback, reinterpret_cast<LPARAM>(&titles));

    // At this point, titles if fully populated and could be displayed, e.g.:
    for (const auto& title : titles) {
        // getting the hwnd per title
        // HWND wHandle;
        // wHandle = FindWindow(NULL, title.c_str());
        // std::wcout << L"Title: " << title << L" HWND: " << wHandle << std::endl;

        // add titles to combobox
        System::String^ sTitle = gcnew System::String(title.c_str());
        ThirdEye::ComboboxItem^ cbi = gcnew ThirdEye::ComboboxItem(sTitle, 0);
        this->WindowSelection->Items->Add(cbi);
    }
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


/// <summary>
/// Worker to live capture window from desktop
/// </summary>
System::Void ThirdEye::MainWindow::WindowCaptureWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
    String^ swTitle = safe_cast<String^>(e->Argument);

    // get window info
    HWND wHandle;
    pin_ptr<const wchar_t> lcTitle = PtrToStringChars(swTitle);
    wHandle = FindWindow(NULL, lcTitle);
    Debug::WriteLine(swTitle);
    
    // capture live
    for (;;) {
        // call get frame to capture window
        ThirdEye::VFrameReader vfr;
        // Image^ cFrame = vfr.GetFrame(wHandle);
        Image^ cFrame = vfr.GetFrameDX(wHandle);
        Debug::WriteLine("Grabbing frame from GDXI");
        Debug::WriteLine("Size " + cFrame->Size.ToString());
        this->CaptureView->Image = cFrame;
    }
}


/// <summary>
/// Selection change for Window focus
/// </summary>
System::Void ThirdEye::MainWindow::WindowSelection_SelectionChangeCommitted(System::Object^ sender, System::EventArgs^ e) {
    ComboBox^ senderCB = (ComboBox^)sender;
    String^ swTitle = senderCB->SelectedItem->ToString();

    // stop previous capture if there is one
    if (swTitle->Length > 0) {
        this->WindowCaptureWorker->CancelAsync();
    }

    // setup worker arguments

    // run worker for capture
    this->WindowCaptureWorker->RunWorkerAsync(swTitle);

    
}