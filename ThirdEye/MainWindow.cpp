/*
ThirdEye main window for testing of reading and display by opencv

Will read text on screen and display what it sees through opencv
*/
#include "MainWindow.h"

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

    // setup frame capture
    this->vreader = gcnew ThirdEye::VFrameReader();
}

/// <summary>
/// Deconstructor
/// </summary>
ThirdEye::MainWindow::~MainWindow() {
	if (components)
	{
		delete components;
	}

    // clean up frame reader
    this->vreader = nullptr;
}


/// <summary>
/// Worker to live capture window from desktop
/// </summary>
System::Void ThirdEye::MainWindow::WindowCaptureWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
    // check worker status
    Debug::WriteLine("DoWork Start");
    
    this->vreader->DoWork(e);
}

/// <summary>
/// Worker to live capture window from desktop
/// </summary>
System::Void ThirdEye::MainWindow::WindowCaptureWorker_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
{
   // run new worker with new selected app name
    Debug::WriteLine("Starting after old worker stopped");
    this->vreader->isCanceled = false;
    this->vreader->bgWorker->RunWorkerAsync(this->vreader->appName);
}


/// <summary>
/// Selection change for Window focus
/// </summary>
System::Void ThirdEye::MainWindow::WindowSelection_SelectionChangeCommitted(System::Object^ sender, System::EventArgs^ e) {
    ComboBox^ senderCB = (ComboBox^)sender;
    
    // set app title
    this->vreader->appName = senderCB->SelectedItem->ToString();

    // set capture window
    this->vreader->capView = this->CaptureView;

    // set background worker
    this->vreader->bgWorker = this->WindowCaptureWorker;

    // setup worker arguments

    // run worker for capture
    // stop previous capture if there is one
    Debug::WriteLine("Is busy?");
    Debug::Write(this->vreader->bgWorker->IsBusy);
    if (!this->vreader->bgWorker->IsBusy) {
        this->vreader->bgWorker->WorkerSupportsCancellation = true;
        this->vreader->bgWorker->RunWorkerAsync(this->vreader->appName);
    } else {
        if (!this->vreader->isCanceled) {
            Debug::WriteLine("\nStopping worker to start a new capture\n");

            // close and start new process
            this->vreader->bgWorker->CancelAsync();
            this->vreader->CancelWork();
        }
    }
}