/*
ThirdEye main window for testing of reading and display by opencv

Will read text on screen and display what it sees through opencv
*/
#include "MainWindow.h"
#include "VFrameReader.h"

/// <summary>
/// Constructor
/// </summary>
ThirdEye::MainWindow::MainWindow() {
	ThirdEye::MainWindow::InitializeComponent();
	
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