#pragma once

#include <Windows.h>
#include <thread>
#include <condition_variable>
#include <mutex>
#pragma warning( push )
#pragma warning( disable: 26495 )
#pragma warning( disable: 4005 )
#include <d3d11.h>
#pragma warning( pop )

using namespace std::chrono_literals;

class Instance {
private:
    inline static Instance* m_pInst;
public:
    Instance();
    ~Instance();

    static Instance* GetInstance();
    void Destroy();

    bool CreateDeviceD3D();
    void CleanupDeviceD3D();
    void CreateRenderTarget();
    void CleanupRenderTarget();

    ID3D11Device* g_pd3dDevice;
    ID3D11DeviceContext* g_p3dDeviceContext;
    IDXGISwapChain* g_pSwapChain;
    ID3D11RenderTargetView* g_mainRenderTargetView;

    HWND m_hwnd;
    WNDCLASSEXA m_wc;
};