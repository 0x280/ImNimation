/*
  /$$$$$$               /$$   /$$ /$$                           /$$     /$$                    
|_  $$_/              | $$$ | $$|__/                          | $$    |__/                    
  | $$   /$$$$$$/$$$$ | $$$$| $$ /$$ /$$$$$$/$$$$   /$$$$$$  /$$$$$$   /$$  /$$$$$$  /$$$$$$$ 
  | $$  | $$_  $$_  $$| $$ $$ $$| $$| $$_  $$_  $$ |____  $$|_  $$_/  | $$ /$$__  $$| $$__  $$
  | $$  | $$ \ $$ \ $$| $$  $$$$| $$| $$ \ $$ \ $$  /$$$$$$$  | $$    | $$| $$  \ $$| $$  \ $$
  | $$  | $$ | $$ | $$| $$\  $$$| $$| $$ | $$ | $$ /$$__  $$  | $$ /$$| $$| $$  | $$| $$  | $$
 /$$$$$$| $$ | $$ | $$| $$ \  $$| $$| $$ | $$ | $$|  $$$$$$$  |  $$$$/| $$|  $$$$$$/| $$  | $$
|______/|__/ |__/ |__/|__/  \__/|__/|__/ |__/ |__/ \_______/   \___/  |__/ \______/ |__/  |__/

https://github.com/0x280/imnimation

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/ 
#include <math.h>
#include <algorithm>
#include "imgui.h"

namespace imnimation {
    namespace internal {
        inline ImVec2 Lerp(const ImVec2& a, const ImVec2& b, const float& t) {
            return ImVec2 { 
              (1.f - t) * a.x + t * b.x,
              (1.f - t) * a.y + t * b.y
            };
        }
    }

    inline void AnimLerp(float* value, float max, float step) {
        if (*value == max)
        	return;
         
        const float frameTimeSpeed = abs(step * (1.f - ImGui::GetIO().DeltaTime));
        *value += frameTimeSpeed;
         
        if (*value > max)
        	*value = max;
    }

  
    inline void AnimCubicBezier(float* value, float* tOffset, float max, float step) {
        if (*value == max)
        	return;
        
        const float timeFactor = abs(step * (1.f - ImGui::GetIO().DeltaTime)) * 0.001f;
        *tOffset += timeFactor;
        if (*tOffset > 1.f)
          *tOffset = 1.f;
        
        const float t = *tOffset;
        
        const ImVec2 P1 = { -4.f, 0.f };
        const ImVec2 P2 = { -2.f, 4.f };
        const ImVec2 P3 = { 0.f, 0.f };
        const ImVec2 P4 = { 2.f, 4.f };
        
        const ImVec2 L1 = internal::Lerp(P1, P2, t);
        const ImVec2 L2 = internal::Lerp(P2, P3, t);
        const ImVec2 L3 = internal::Lerp(P3, P4, t);
        
        const ImVec2 Q1 = internal::Lerp(L1, L2, t);
        const ImVec2 Q2 = internal::Lerp(L2, L3, t);
        
        const ImVec2 N = internal::Lerp(Q1, Q2, t);
        
        *value += N.y * step;
        
        if (*value > max)
        	*value = max;
    }
}