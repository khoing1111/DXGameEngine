#include "ObjectFigure.h"
#include <DXEngine\manager\render\RenderManager.h>


//=============================================================================
#pragma region // Rectangle figure
//=============================================================================

GameCore::StaticFigure::RectFigure::RectFigure()
{
    m_halfWidth = 1.0f;
    m_halfHeight = 1.0f;
    m_borderSize = 1.0f;
    
    m_fillColor = hkRGBAColor::GRAY;
    m_borderColor = hkRGBAColor::BLUE;
    
    m_isFill = true;
    m_haveBorder = true;
}

GameCore::StaticFigure::RectFigure::RectFigure(const RectFigure& other) : ObjectFigure(other)
{
    m_halfWidth = other.m_halfWidth;
    m_halfHeight = other.m_halfHeight;
    m_borderSize = other.m_borderSize;
    
    m_fillColor = other.m_fillColor;
    m_borderColor = other.m_borderColor;
    
    m_isFill = other.m_isFill;
    m_haveBorder = other.m_haveBorder;
}

GameCore::StaticFigure::RectFigure::~RectFigure()
{

}

void GameCore::StaticFigure::RectFigure::Initialize(
        float halfW, float halfH, const hkRGBAColor& fillColor, const hkRGBAColor& borderColor,
        float borderSize, bool isFill, bool haveBorder)
{
    SetRect(halfW, halfH);
    SetBorderSize(borderSize);
    
    m_fillColor = fillColor;
    m_borderColor = borderColor;
    
    m_isFill = isFill;
    m_haveBorder = haveBorder;
}

void GameCore::StaticFigure::RectFigure::SetRect(float halfW, float halfH)
{
    m_halfWidth = halfW;
    m_halfHeight = halfH;
    
    if (m_halfWidth < 0) 
        m_halfWidth = -m_halfWidth;
    
    if (m_halfHeight < 0)
        m_halfHeight = -m_halfHeight;
}

void GameCore::StaticFigure::RectFigure::SetFillColor(const hkRGBAColor& fillColor)
{
    m_fillColor = fillColor;
}

void GameCore::StaticFigure::RectFigure::SetBorderColor(const hkRGBAColor& borderColor)
{
    m_borderColor = borderColor;
}

void GameCore::StaticFigure::RectFigure::SetBorderSize(float borderSize)
{
    m_borderSize = borderSize;
    
    if (m_borderSize < 0) 
        m_borderSize = -m_borderSize;
}

void GameCore::StaticFigure::RectFigure::EnableBorder(bool haveBorder)
{
    m_haveBorder = haveBorder;
}

void GameCore::StaticFigure::RectFigure::EnableFill(bool isFill)
{
    m_isFill = isFill;
}

bool GameCore::StaticFigure::RectFigure::HaveBorder()
{
    return m_haveBorder;
}

bool GameCore::StaticFigure::RectFigure::IsFill()
{
    return m_isFill;
}

float GameCore::StaticFigure::RectFigure::GetBorderSize()
{
    return m_borderSize;
}

hkVector2F GameCore::StaticFigure::RectFigure::GetSize()
{
    return hkVector2F(m_halfWidth, m_halfHeight);
}

hkRGBAColor GameCore::StaticFigure::RectFigure::GetFillColor()
{
    return m_fillColor;
}

hkRGBAColor GameCore::StaticFigure::RectFigure::GetBorderColor()
{
    return m_borderColor;
}

void GameCore::StaticFigure::RectFigure::Render(RenderManager::D2DManager& manager, const hkVector2F& pos)
{
    if (m_isVisible)
    {
        hkRect2F rect(pos.y + m_halfHeight, pos.y - m_halfHeight, pos.x - m_halfWidth, pos.x + m_halfWidth);
        
        if (m_isFill)
        {
            manager.SetDrawColor(m_fillColor);
            manager.FillRect(rect);
        }
        
        if (m_haveBorder && m_borderSize > 0)
        {
            manager.SetDrawColor(m_borderColor);
            manager.DrawRect(rect, m_borderSize);
        }
    }
}

//=============================================================================
#pragma endregion // Rectangle figure
//=============================================================================



//=============================================================================
#pragma region // Bitmap figure
//=============================================================================

GameCore::StaticFigure::BitmapFigure::BitmapFigure()
{
    m_flags = RENDER_BEHAVE_DEFAULT;
}

GameCore::StaticFigure::BitmapFigure::BitmapFigure(const BitmapFigure& clone) : ObjectFigure(clone)
{
    m_bitmap = clone.m_bitmap;
    m_srcRect = clone.m_srcRect;
    m_destRect = clone.m_destRect;
    m_flags = clone.m_flags;
}

GameCore::StaticFigure::BitmapFigure::~BitmapFigure()
{
    m_bitmap.Release();
}

void GameCore::StaticFigure::BitmapFigure::Enable(uint flags)
{
    m_flags |= flags;
}

void GameCore::StaticFigure::BitmapFigure::Disable(uint flags)
{
    m_flags &= !flags;
}

bool GameCore::StaticFigure::BitmapFigure::IsEnable(uint flags)
{
    return m_flags & flags;
}

hkRect2F GameCore::StaticFigure::BitmapFigure::GetSrcRect()
{
    return m_srcRect;
}

hkRect2F GameCore::StaticFigure::BitmapFigure::GetDestRect()
{
    return m_destRect;
}

bool GameCore::StaticFigure::BitmapFigure::Initialize(
    WPtr<ID2D1Bitmap> bitmap, hkRect2F destRect, hkRect2F srcRect)
{
    m_bitmap = bitmap;
    if (m_bitmap == nullptr)
        return false;

    m_srcRect = srcRect;
    m_destRect = destRect;

    return true;
}

void GameCore::StaticFigure::BitmapFigure::SetSrcRect(hkRect2F& srcRect)
{
    m_srcRect = srcRect;
}

void GameCore::StaticFigure::BitmapFigure::SetDestRect(hkRect2F& destRect)
{
    m_destRect = destRect;
}

void GameCore::StaticFigure::BitmapFigure::Render(RenderManager::D2DManager& manager, const hkVector2F& pos)
{
    if (m_isVisible)
    {
        hkRect2F dest = m_destRect;
        dest.Move(pos.x, pos.y);
    
        if (IsEnable(RENDER_ALL_SOURCE))
        {
            manager.DrawFullBitmap(m_bitmap, dest);
        }
        else
        {
            manager.DrawBitmap(m_bitmap, dest, m_srcRect);
        }
    }
}

void GameCore::StaticFigure::BitmapFigure::Render(RenderManager::D2DManager& manager, 
                                                  const hkVector2F& pos, uint state1, uint state2)
{
    if (m_isVisible)
    {
        hkRect2F dest = m_destRect;
        dest.Move(pos.x, pos.y);
        
        hkRect2F src = m_srcRect;
        src.Move(state2 * src.GetWidth(), state1 * src.GetHeight());
    
        if (IsEnable(RENDER_ALL_SOURCE))
        {
            manager.DrawFullBitmap(m_bitmap, dest);
        }
        else
        {
            manager.DrawBitmap(m_bitmap, dest, src);
        }
    }
}

void GameCore::StaticFigure::BitmapFigure::MoveSrc(float x, float y)
{
    m_srcRect.Move(x, y);
}

void GameCore::StaticFigure::BitmapFigure::MoveDest(float x, float y)
{
    m_destRect.Move(x, y);
}

//=============================================================================
#pragma endregion // Bitmap figure
//=============================================================================