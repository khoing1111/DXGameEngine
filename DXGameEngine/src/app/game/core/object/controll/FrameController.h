#pragma once

#include <hkUtilLib\Core.h>

namespace GameCore
{
    namespace Frame
    {
        ////////////////////////////
        // CLASS: FrameController
        class FrameController
        {
        public:
            FrameController();
            FrameController(const FrameController& clone);
            ~FrameController();

            void SetTimePerFrame(float tpf);
            void Advance(float time);
            void ResetCounter();

            void SetNumFrame(uint numFrame);

            uint GetNumFrame();
            uint GetCurrentFrame();

        private:
            uint m_currentFrame;
            uint m_numFrame;
            float m_timePerFrame;
            float m_currentTime;
        };
    }
}