#include "VFrameReader.h"

///<summary>
/// Constructor
/// <summary>
ThirdEye::VFrameReader::VFrameReader(void) {

}

/// <summary>
/// Deconstructor
/// </summary>
ThirdEye::VFrameReader::~VFrameReader() {

}

///<summary>
///GetFrame gets the current desktop or window frame and display it in
/// output window CaptureView along with later analysis in OpenCV
///</summary>
System::Drawing::Image^ ThirdEye::VFrameReader::GetFrame() {
    // add in ability to take in window handle for specific programs, for now whole main desktop
    HDC cFrame = GetDC(nullptr);
    HDC cFrameMem = CreateCompatibleDC(cFrame);
    
    // width height of main desktop screen
    int cFrameWidth = GetDeviceCaps(cFrame, HORZRES);
    int cFrameHeight = GetDeviceCaps(cFrame, VERTRES);

    // create a bitmap to send to CaptureView
    HBITMAP cFrameHBitmap = CreateCompatibleBitmap(cFrame, cFrameWidth, cFrameHeight);
    HBITMAP cFrameCopy = (HBITMAP)SelectObject(cFrameMem, cFrameHBitmap);
    BitBlt(cFrameMem, 0, 0, cFrameWidth, cFrameHeight, cFrame, 0, 0, SRCCOPY);
    cFrameHBitmap = (HBITMAP)SelectObject(cFrameMem, cFrameCopy);
    
    // clean up capture
    DeleteDC(cFrame);
    DeleteDC(cFrameMem);

    // convert HBITMAP to BITMAP
    Bitmap^ cFrameBitmap = Bitmap::FromHbitmap((IntPtr)cFrameHBitmap);

    return (System::Drawing::Image^ ) cFrameBitmap;
}