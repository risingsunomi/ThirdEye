#include "VFrameReader.h"
using namespace System;
using namespace System::Drawing;
using namespace System::Diagnostics;

///<summary>
/// Constructor
/// <summary>
ThirdEye::VFrameReader::VFrameReader() {
    // default 1920x1080
    this->cFrameWidth = 1920;
    this->cFrameHeight = 1080;

    
}

/// <summary>
/// Deconstructor
/// </summary>
ThirdEye::VFrameReader::~VFrameReader() {
    this->capView = nullptr;
    this->bgWorker = nullptr;
}

///<summary>
///GetFrame gets the current desktop or window frame and display it in
/// output window CaptureView along with later analysis in OpenCV
/// GDI based
///</summary>
Image^ ThirdEye::VFrameReader::GetFrame(HWND capWindow) {
    SetProcessDPIAware();

    // set window to top 
    // SetForegroundWindow(capWindow);
    // Sleep(250); // sleep to wait for the window to move

    // use whole desktop to capture window to get over non windows api gui issue
    HDC cFrame = GetDC(HWND_DESKTOP);

    RECT fRect;
    GetWindowRect(capWindow, &fRect);
    int frWidth = fRect.right - fRect.left;
    int frHeight = fRect.bottom - fRect.top;


    HDC cFrameMem = CreateCompatibleDC(cFrame);

    // width height of main desktop screen
    this->cFrameWidth = GetDeviceCaps(cFrame, HORZRES);
    this->cFrameHeight = GetDeviceCaps(cFrame, VERTRES);

    // create a bitmap to send to CaptureView
    HBITMAP cFrameHBitmap = CreateCompatibleBitmap(cFrame, frWidth, frHeight);
    HBITMAP cFrameCopy = (HBITMAP)SelectObject(cFrameMem, cFrameHBitmap);
    BitBlt(cFrameMem, 0, 0, frWidth, frHeight, cFrame, fRect.left, fRect.top, SRCCOPY | CAPTUREBLT);
    cFrameHBitmap = (HBITMAP)SelectObject(cFrameMem, cFrameCopy);
    
    //restore the foreground
    // SetForegroundWindow(GetConsoleWindow());

    // convert HBITMAP to BITMAP
    if (cFrameHBitmap != nullptr) {
        Bitmap^ cFrameBitmap = Bitmap::FromHbitmap((IntPtr)cFrameHBitmap);

        // clean up capture
        DeleteObject(cFrameHBitmap);
        DeleteObject(cFrameCopy);
        ReleaseDC(HWND_DESKTOP, cFrame);
        DeleteDC(cFrameMem);

        return (Image^)cFrameBitmap;
    }

    return nullptr;
    
}

///<summary>
///GetFrameDX gets the current desktop or window frame like GetFrame
/// but with DirectX - this is only supported by Win10+
///</summary>

Image^ ThirdEye::VFrameReader::GetFrameDX(HWND capWindow) {
    
    // use whole desktop to capture window to get over non windows api gui issue
    IDXGISwapChain* g_pSwapChain = NULL;
    IDXGISurface1* g_pSurface1;
    HDC cFrame;

    RECT pgmRect;
    GetWindowRect(capWindow, &pgmRect);
    int pgmWidth = pgmRect.right - pgmRect.left;
    int pgmHeight = pgmRect.bottom - pgmRect.top;

    HRESULT hr = g_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (LPVOID*)&g_pSurface1);

    if (SUCCEEDED(hr)) {
        g_pSurface1->GetDC(FALSE, &cFrame);

        HDC cFrameMem = CreateCompatibleDC(cFrame);

        // width height of main desktop screen
        this->cFrameWidth = GetDeviceCaps(cFrame, HORZRES);
        this->cFrameHeight = GetDeviceCaps(cFrame, VERTRES);

        //Debug::WriteLine("cFrame width height");
        //Debug::Write(this->cFrameWidth);
        //Debug::Write(this->cFrameHeight);


        // create a bitmap to send to CaptureView
        HBITMAP cFrameHBitmap = CreateCompatibleBitmap(cFrame, pgmWidth, pgmHeight);
        HBITMAP cFrameCopy = (HBITMAP)SelectObject(cFrameMem, cFrameHBitmap);
        BitBlt(cFrameMem, 0, 0, pgmWidth, pgmHeight, cFrame, pgmRect.left, pgmRect.top, SRCCOPY | CAPTUREBLT);
        cFrameHBitmap = (HBITMAP)SelectObject(cFrameMem, cFrameCopy);

        //restore the foreground
        // SetForegroundWindow(GetConsoleWindow());

        // convert HBITMAP to BITMAP
        Bitmap^ cFrameBitmap = Bitmap::FromHbitmap((IntPtr)cFrameHBitmap);

        // clean up capture
        DeleteObject(cFrameHBitmap);
        DeleteObject(cFrameCopy);
        ReleaseDC(HWND_DESKTOP, cFrame);
        DeleteDC(cFrameMem);
        g_pSurface1->ReleaseDC(NULL);

        return (Image^)cFrameBitmap;
    }

    return (Image^) nullptr;
}

///<summary>
/// CancelWork, Cancels work of frame grabbing done by WindowCaptureWorker in MainWindow
///</summary>
System::Void ThirdEye::VFrameReader::CancelWork(void) {
    this->isCanceled = true;
}

///<summary>
/// DoWork, runs frame capture for WindowCaptureWorker and selected app
///</summary>
System::Void ThirdEye::VFrameReader::DoWork(System::ComponentModel::DoWorkEventArgs^ e) {
    // get app name from argument
    this->appName = safe_cast<String^>(e->Argument);

    // get window info
    HWND wHandle;
    pin_ptr<const wchar_t> lcTitle = PtrToStringChars(this->appName);
    wHandle = FindWindow(NULL, lcTitle);

    if (wHandle != nullptr) {
        Debug::WriteLine("\n"); 
        Debug::Write(this->appName);
        Debug::WriteLine("\n");

        // capture live
        while(!this->isCanceled) {
            // Image^ cFrame = vfr.GetFrameDX(wHandle);
            Image^ cFrame = this->GetFrame(wHandle);

            if (cFrame != nullptr) {
                Debug::WriteLine("Grabbing frame from GDI");
                Debug::WriteLine("Size " + cFrame->Size.ToString());
                this->capView->Image = cFrame;
            }

            Debug::WriteLine("\nCancellationPending?");
            Debug::WriteLine(this->bgWorker->CancellationPending);
            if (this->bgWorker->CancellationPending) {
                e->Cancel = true;
                break;
            }

        }
    }
}


///<summary>
/// GetSpatialWords, get all the words or letter found in the image
/// model should be stored in C:\%userprofile%\AppData\Roaming\AlphaThirdEye
///</summary>
System::Void ThirdEye::VFrameReader::GetSpatialWords(void) {

}