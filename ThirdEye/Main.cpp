#include "MainWindow.h"
#include "opencv2/opencv.hpp"
#include <Windows.h>
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args) {

	HWND hwndDesktop = GetDesktopWindow();
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(0);
	ThirdEye::MainWindow mw;
	Application::Run(% mw);
}