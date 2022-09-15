#pragma once
#include "d3d9.h"
#include "d3dx9.h"

namespace ThirdEye {
	using namespace System;
	using namespace System::Drawing;

	/// <summary>
	/// Video Frame Reader for grabbing data from the videogame
	/// using D3D
	/// </summary>
	public ref class VFrameReader {
		public: 
			VFrameReader(void);
			Image^ GetFrame(void);
	
		protected: 
			~VFrameReader();

	};
}