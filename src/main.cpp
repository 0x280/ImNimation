#include "instance.hpp"
#include "gui.hpp"

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) {
    auto instance = Instance::GetInstance();
    auto gui = GUI::GetInstance();

    while (true) {
        MSG msg;
        bool bShutdown = false;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                bShutdown = true;
        }
        if (bShutdown)
            break;

        gui->Tick();
    }

    gui->Destroy();
    instance->Destroy();
    
    exit(0);
}