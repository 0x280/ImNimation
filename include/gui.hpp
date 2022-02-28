#pragma once

#pragma warning( push )
#pragma warning( disable: 26495 )
#pragma warning( disable: 4005 )
#include <d3d11.h>
#pragma warning( pop )

class GUI {
private:
    inline static GUI* m_pInst;

    void ApplyStyles();
public:
    static GUI* GetInstance();

    GUI();
    ~GUI();

    void Destroy();

    void Tick();
};
