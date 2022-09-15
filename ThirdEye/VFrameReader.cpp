#include "VFrameReader.h";
#include "d3d9.h";
#include "d3dx9.h";

///<summary>
///Dump Back Buffer
///</summary>
void ThirdEye::VFrameReader::DumpBackBuffer() {
    IDirect3DSurface9* pRenderTarget = NULL;
    IDirect3DSurface9* pDestTarget = NULL;
    const char file[] = "Pickture.bmp";
    // sanity checks.
    if (Device == NULL)
        return;

    // get the render target surface.
    HRESULT hr = Device->GetRenderTarget(0, &pRenderTarget);
    // get the current adapter display mode.
    //hr = pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddisplaymode);

    // create a destination surface.
    hr = Device->CreateOffscreenPlainSurface(DisplayMde.Width,
        DisplayMde.Height,
        DisplayMde.Format,
        D3DPOOL_SYSTEMMEM,
        &pDestTarget,
        NULL);
    //copy the render target to the destination surface.
    hr = Device->GetRenderTargetData(pRenderTarget, pDestTarget);
    //save its contents to a bitmap file.
    /*hr = D3DXSaveSurfaceToFile(file,
        D3DXIFF_BMP,
        pDestTarget,
        NULL,
        NULL);*/

    // clean up.
    pRenderTarget->Release();
    pDestTarget->Release();
}