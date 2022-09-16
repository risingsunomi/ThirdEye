#include "VFrameReader.h"
using namespace System;
using namespace System::Drawing;
using namespace System::Diagnostics;

///<summary>
/// Constructor
/// <summary>
ThirdEye::VFrameReader::VFrameReader(void) {
    // default 1920x1080
    this->cFrameWidth = 1920;
    this->cFrameHeight = 1080;
}

/// <summary>
/// Deconstructor
/// </summary>
ThirdEye::VFrameReader::~VFrameReader() {

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
    Bitmap^ cFrameBitmap = Bitmap::FromHbitmap((IntPtr)cFrameHBitmap);

    // clean up capture
    DeleteObject(cFrameHBitmap);
    DeleteObject(cFrameCopy);
    ReleaseDC(HWND_DESKTOP, cFrame);
    DeleteDC(cFrameMem);

    return (Image^)cFrameBitmap;
}

///<summary>
///GetFrameDX gets the current desktop or window frame like GetFrame
/// but with DirectX
///</summary>

Image^ ThirdEye::VFrameReader::GetFrameDX(HWND capWindow) {
    
    // use whole desktop to capture window to get over non windows api gui issue
    IDXGISwapChain* g_pSwapChain = NULL;
    IDXGISurface1* g_pSurface1 = NULL;
    HDC cFrame;

    RECT pgmRect;
    GetWindowRect(capWindow, &pgmRect);
    int pgmWidth = pgmRect.right - pgmRect.left;
    int pgmHeight = pgmRect.bottom - pgmRect.top;

    HRESULT hr = g_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&g_pSurface1);

    if (SUCCEEDED(hr)) {
        g_pSurface1->GetDC(FALSE, &cFrame);

        HDC cFrameMem = CreateCompatibleDC(cFrame);

        // width height of main desktop screen
        this->cFrameWidth = GetDeviceCaps(cFrame, HORZRES);
        this->cFrameHeight = GetDeviceCaps(cFrame, VERTRES);

        Debug::WriteLine("cFrame width height");
        Debug::Write(this->cFrameWidth);
        Debug::Write(this->cFrameHeight);


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
///GetFrameDX gets the current desktop or window frame like GetFrame
/// but with DirectX
///</summary>