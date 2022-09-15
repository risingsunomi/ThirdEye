/*
ThirdEye main window for testing of reading and display by opencv

Will read text on screen and display what it sees through opencv
*/
#include "MainWindow.h"

/// <summary>
/// Constructor
/// </summary>
ThirdEye::MainWindow::MainWindow() {
	ThirdEye::MainWindow::InitializeComponent();
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