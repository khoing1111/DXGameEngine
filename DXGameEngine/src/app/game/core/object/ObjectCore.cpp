#include "ObjectCore.h"

//=============================================================================
#pragma region // ObjectFigure
//=============================================================================

GameCore::ObjectFigure::ObjectFigure() 
{
    m_isVisible = false; 
}

GameCore::ObjectFigure::ObjectFigure(const ObjectFigure& clone) 
{
    m_isVisible = clone.m_isVisible; 
}

GameCore::ObjectFigure::~ObjectFigure() 
{

}

void GameCore::ObjectFigure::Render(RenderManager::D2DManager& manager, const hkVector2F& pos)
{

}

void GameCore::ObjectFigure::Render(RenderManager::D2DManager& manager, const hkVector2F& pos,
                                    uint state1, uint state2)
{

}

void GameCore::ObjectFigure::Show() 
{
    m_isVisible = true;
}

void GameCore::ObjectFigure::Hide() 
{
    m_isVisible = false;
}

bool GameCore::ObjectFigure::IsVisible() 
{
    return m_isVisible;
}

//=============================================================================
#pragma endregion // ObjectFigure
//=============================================================================


//=============================================================================
#pragma region // ObjectBase
//=============================================================================

GameCore::ObjectBase::ObjectBase() 
{
}

GameCore::ObjectBase::ObjectBase(const ObjectBase& clone)
{
}

GameCore::ObjectBase::~ObjectBase()
{
}

void GameCore::ObjectBase::SetPosition(const hkVector2F& pos)
{
    m_position = pos;
}

hkVector2F GameCore::ObjectBase::GetPosition()
{
    return m_position;
}

void GameCore::ObjectBase::Move(const hkVector2F& direction)
{
    m_position += direction;
}

void GameCore::ObjectBase::Move(float x, float y)
{
    m_position += hkVector2F(x, y);
}

void GameCore::ObjectBase::Show()
{
    if (m_figure != nullptr)
        m_figure->Show();
}

void GameCore::ObjectBase::Hide()
{
    if (m_figure != nullptr)
        m_figure->Hide();
}

bool GameCore::ObjectBase::IsVisible()
{
    if (m_figure != nullptr)
        return m_figure->IsVisible();
    
    return false;
}

void GameCore::ObjectBase::SetBoundingBox(ObjectBoundingBox* boundingBox)
{
    m_boundingBox.Set(boundingBox);
}

void GameCore::ObjectBase::SetFigure(ObjectFigure* figure)
{
    m_figure.Set(figure);
}

WPtr<GameCore::ObjectBoundingBox> GameCore::ObjectBase::GetBoundingBox()
{
    return m_boundingBox;
}

WPtr<GameCore::ObjectFigure> GameCore::ObjectBase::GetFigure()
{
    return m_figure;
}

void GameCore::ObjectBase::Update(float timePass)
{
    if (m_boundingBox != nullptr)
        m_boundingBox->Update(m_position);
}

void GameCore::ObjectBase::Render(RenderManager::D2DManager& renderManager)
{
    if (m_figure != nullptr && m_figure->IsVisible())
        m_figure->Render(renderManager, m_position);
}

//=============================================================================
#pragma endregion // ObjectBase
//=============================================================================



//=============================================================================
#pragma region // ObjectBoundingBox
//=============================================================================

GameCore::ObjectBoundingBox::ObjectBoundingBox()
{}

GameCore::ObjectBoundingBox::ObjectBoundingBox(const ObjectBoundingBox&)
{}

GameCore::ObjectBoundingBox::~ObjectBoundingBox()
{}

GameCore::ObjectBoundingBox::BOUNDING_BOX_COLIDE_STATUS 
GameCore::ObjectBoundingBox::IsContact(WPtr<ObjectBoundingBox>&)
{
    return BOUNDING_BOX_COLIDE_STATUS::NO_CONTACT;
}

hkVector2F GameCore::ObjectBoundingBox::GetOverlapped(WPtr<ObjectBoundingBox>&)
{
    return hkVector2F();
}

void GameCore::ObjectBoundingBox::Update(hkVector2F&)
{

}

//=============================================================================
#pragma endregion // ObjectBoundingBox
//=============================================================================