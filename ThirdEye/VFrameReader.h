#pragma once
namespace ThirdEye {
	/// <summary>
	/// Video Frame Reader for grabbing data from the videogame
	/// using D3D
	/// </summary>
	public ref class VFrameReader {
	public: VFrameReader(void);
	protected: ~VFrameReader();

	protected:
	private: void DumpBackBuffer(void);
	};
}