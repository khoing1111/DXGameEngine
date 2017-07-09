#include "BoundingBox.h"


//=============================================================================
#pragma region // RectBoundingBox
//=============================================================================

GameCore::BoundingBox::RectBoundingBox::RectBoundingBox()
{
    m_halfWidth = 0;
    m_halfHeight = 0;
}

GameCore::BoundingBox::RectBoundingBox::RectBoundingBox(const RectBoundingBox& clone)
{
    m_halfWidth = clone.m_halfWidth;
    m_halfHeight = clone.m_halfHeight;
    m_position = clone.m_position;
}

GameCore::BoundingBox::RectBoundingBox::~RectBoundingBox()
{
}

GameCore::ObjectBoundingBox::BOUNDING_BOX_COLIDE_STATUS 
        GameCore::BoundingBox::RectBoundingBox::IsContact(WPtr<ObjectBoundingBox>& other)
{
    SPtr<RectBoundingBox> rbb = other.As<RectBoundingBox>();
    if (rbb != nullptr)
    {
        if (!IsValid() || !rbb->IsValid())
            return NO_CONTACT;
        
        float top1 = m_position.y + m_halfHeight;
        float bottom1 = m_position.y - m_halfHeight;
        float left1 = m_position.x - m_halfWidth;
        float right1 = m_position.x + m_halfWidth;
        
        float top2 = rbb->m_position.y + rbb->m_halfHeight;
        float bottom2 = rbb->m_position.y - rbb->m_halfHeight;
        float left2 = rbb->m_position.x - rbb->m_halfWidth;
        float right2 = rbb->m_position.x + rbb->m_halfWidth;
        
        // If this rectangle bottom is above other rectangle top
        // Or if this rectangle top is bellow other rectangle bottom
        // Then two rectangle cannot be overlaped
        if (bottom1 > top2 || top1 < bottom2)
            return NO_CONTACT;
            
        
        // If this rectangle left is greater than other rectangle right
        // Or if this rectangle right is lesser than other rectangle left
        // Then two rectangle cannot be overlaped
        if (left1 > right2 || right1 < left2)
            return NO_CONTACT;  
        
        
        if (bottom1 == top2)
            return CONTACTED_Y_BOTTOM;
        else if (top1 == bottom2)
            return CONTACTED_Y_TOP;
        else if (right1 == left2)
            return CONTACTED_X_RIGHT;
        else if (left1 == right2)
            return CONTACTED_X_LEFT;
            
        // Other wise two rectangle overlap.
        return OVERLAPPED;
    }
    
    return NO_CONTACT;
}


hkVector2F GameCore::BoundingBox::RectBoundingBox::GetOverlapped(WPtr<ObjectBoundingBox>& other)
{
    hkVector2F result;
    SPtr<RectBoundingBox> rbb = other.As<RectBoundingBox>();
    
    if (rbb != nullptr)
    {
        if (!IsValid() || !rbb->IsValid())
            return result;
        
        float top1 = m_position.y + m_halfHeight;
        float bottom1 = m_position.y - m_halfHeight;
        float left1 = m_position.x - m_halfWidth;
        float right1 = m_position.x + m_halfWidth;
        
        float top2 = rbb->m_position.y + rbb->m_halfHeight;
        float bottom2 = rbb->m_position.y - rbb->m_halfHeight;
        float left2 = rbb->m_position.x - rbb->m_halfWidth;
        float right2 = rbb->m_position.x + rbb->m_halfWidth;
        
        if (top1 < top2 && top1 > bottom2) 
        {
            result.y = bottom2 - top1;
        } 
        else if (bottom1 < top2 && bottom1 > bottom2)
        {
            result.y = top2 - bottom1;
        }
        
        if (left1 < right2 && left1 > left2)
        {
            result.x = right2 - left1;
        }
        else if (right1 < right2 && right1 > left2)
        {
            result.x = right1 - left2;
        }
    }
    
    return result;
}

void GameCore::BoundingBox::RectBoundingBox::Initialize(hkVector2F& pos, float halfWidth, float halfHeight)
{
    m_position = pos;
    m_halfWidth = halfWidth;
    m_halfHeight = halfHeight;
}

bool GameCore::BoundingBox::RectBoundingBox::IsValid()
{
    return m_halfWidth > 0 && m_halfHeight > 0;
}

void GameCore::BoundingBox::RectBoundingBox::Update(hkVector2F& vec)
{
    m_position = vec;
}

//=============================================================================
#pragma endregion // RectBoundingBox
//=============================================================================