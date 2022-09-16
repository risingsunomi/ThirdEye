#pragma once
#include "dxgi.h"

namespace ThirdEye {
	/// <summary>
	/// Video Frame Reader for grabbing data from the videogame
	/// using D3D
	/// </summary>
	
	

	public ref class VFrameReader {
		public: 
			VFrameReader(void);
			System::Drawing::Image^ GetFrame(HWND); // get frame with GDI
			System::Drawing::Image^ GetFrameDX(HWND); // get frame with DirectX9
			int cFrameWidth;
			int cFrameHeight;
	
		protected: 
			~VFrameReader();

	};
}