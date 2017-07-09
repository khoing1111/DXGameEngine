#pragma once

//////////////
// INCLUDE
#include <hkUtilLib/Core/Vector.h>

#include "../ObjectCore.h"


namespace GameCore
{
    namespace BoundingBox
    {
        ////////////////////////////
        // CLASS: RectBoundingBox
        //
        // Note: This is an simple rectangle bounding box. Only contain
        // two variable: half-height and half-width which is half rectangle
        // height from it's core (center point) to it's top and half rectangle
        // width from it's core (center point) to it's left side. Center point
        // will always be at center of the rectangle.
        // This bounding box cannot be rotate and is very simple to calculate.
        class RectBoundingBox : public ObjectBoundingBox
        {
        public:
            RectBoundingBox();
            RectBoundingBox(const RectBoundingBox&);
            ~RectBoundingBox();

            virtual BOUNDING_BOX_COLIDE_STATUS IsContact(WPtr<ObjectBoundingBox>&) override;

            void Initialize(hkVector2F& pos, float halfWidth, float halfHeight);
            virtual hkVector2F GetOverlapped(WPtr<ObjectBoundingBox>&) override;

            void Update(hkVector2F&);
            bool IsValid();

        protected:
            hkVector2F m_position;
            float m_halfWidth;
            float m_halfHeight;
        };
    }
}