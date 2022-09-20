#pragma once
#include "dxgi.h"
#include <vcclr.h>

namespace ThirdEye {
	/// <summary>
	/// Video Frame Reader for grabbing data from the videogame
	/// using D3D
	/// </summary>

	public ref class VFrameReader {
		public:
			// public variables
			int cFrameWidth;
			int cFrameHeight;
			bool isCanceled = false;
			System::String^ appName = nullptr;
			System::Windows::Forms::PictureBox^ capView = nullptr;
			System::ComponentModel::BackgroundWorker^ bgWorker = nullptr;

			// public functions
			VFrameReader();

			// get frame with GDI
			System::Drawing::Image^ GetFrame(HWND);

			// get frame with DirectX9
			// BROKEN
			System::Drawing::Image^ GetFrameDX(HWND);

			// get words from an image
			System::Void GetSpatialWords(void);
			
			// background worker CancelWork
			System::Void CancelWork(void);

			// background worker DoWork
			System::Void DoWork(System::ComponentModel::DoWorkEventArgs^);
	
			protected:
				// public protected functions
				~VFrameReader();

	};
}