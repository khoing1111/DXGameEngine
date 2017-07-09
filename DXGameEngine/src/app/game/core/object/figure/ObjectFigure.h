#pragma once


/////////////
// INCLUDE
#include <d2d1.h>

#include "../ObjectCore.h"
#include <hkUtilLib\core\Vector.h>
#include <hkUtilLib\core\Color.h>
#include <hkUtilLib\core\Shape.h>
#include <hkUtilLib\core\Matrix.h>


namespace GameCore
{
    namespace StaticFigure
    {
        ///////////////////////
        // CLASS: RectFigure
        class RectFigure : public ObjectFigure
        {
        public:
            RectFigure();
            RectFigure(const RectFigure& clone);
            ~RectFigure();

            virtual void Render(RenderManager::D2DManager& manager, const hkVector2F& pos) override;

            void Initialize(float halfW = 1.0f, float halfH = 1.0f, 
                const hkRGBAColor& fillColor = hkRGBAColor::GRAY,
                const hkRGBAColor& borderColor = hkRGBAColor::BLUE, 
                float borderSize = 1.0f, bool isFill = true,
                bool haveBorder = true);
            
            void SetRect(float halfW, float halfH);
            void SetFillColor(const hkRGBAColor& fillColor);
            void SetBorderColor(const hkRGBAColor& borderColor);
            void SetBorderSize(float borderSize);
            void EnableBorder(bool haveBorder);
            void EnableFill(bool isFill);
            
            bool HaveBorder();
            bool IsFill();
            float GetBorderSize();
            hkVector2F GetSize();
            hkRGBAColor GetFillColor();
            hkRGBAColor GetBorderColor();

        private:
            float m_halfWidth;
            float m_halfHeight;
            float m_borderSize;
            
            hkRGBAColor m_fillColor;
            hkRGBAColor m_borderColor;
            
            bool m_isFill;
            bool m_haveBorder;
        };


        /////////////////////////
        // CLASS: BitmapFigure
        class BitmapFigure : public ObjectFigure
        {
        public:
            typedef enum RENDER_BITMAP_BEHAVIOR
            {
                RENDER_BEHAVE_DEFAULT = 0x0,
                RENDER_ALL_SOURCE = 0x1,
            };


        public:
            BitmapFigure();
            BitmapFigure(const BitmapFigure& clone);
            ~BitmapFigure();

            virtual void Render(RenderManager::D2DManager& manager, const hkVector2F& pos) override;
            virtual void Render(RenderManager::D2DManager& manager, 
                                const hkVector2F& pos, uint state1, uint state2) override;

            bool Initialize(WPtr<ID2D1Bitmap> bitmap, 
                hkRect2F destRect = hkRect2F(0, 0, 0, 0),
                hkRect2F srcRect = hkRect2F(0, 0, 0, 0));

            void SetSrcRect(hkRect2F& srcRect);
            void SetDestRect(hkRect2F& destRect);
            
            void MoveSrc(float x, float y);
            void MoveDest(float x, float y);

            void Enable(uint);
            void Disable(uint);
            bool IsEnable(uint);

            hkRect2F GetSrcRect();
            hkRect2F GetDestRect();

        private:
            WPtr<ID2D1Bitmap> m_bitmap;

            hkRect2F m_srcRect;
            hkRect2F m_destRect;

            uint m_flags;
        };
    }
}