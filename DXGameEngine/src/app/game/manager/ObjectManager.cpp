#include "ObjectManager.h"

//=============================================================================
#pragma region // Object manager
//=============================================================================

GameCore::ObjectManager::ObjectManager()
{
}

GameCore::ObjectManager::ObjectManager(const GameCore::ObjectManager& clone)
{

}

GameCore::ObjectManager::~ObjectManager()
{
    Release();
}

void GameCore::ObjectManager::Initialize()
{
}

void GameCore::ObjectManager::Release()
{
    // Clear object list
    for (int i = 0; i < IOL_NUM_LAYER; i++)
        m_objects[i].Clear();
}

void GameCore::ObjectManager::AddObject(GameCore::ObjectBase* object, INTERACT_OBJECT_LAYER layer)
{
    m_objects[layer].Add(object);
}

void GameCore::ObjectManager::Update(float timeStep)
{
    for (int i = 0; i < IOL_NUM_LAYER; i++)
    {
        // Use iterator to traverse object list
        SPtr<ListIterator<ObjectBase>> iterator = m_objects[i].GetIterator();
        if (iterator->IsValid())
        {
            do
            {
                iterator->Get()->Update(timeStep);
            }
            while (iterator->Next());
        }
    }
}

void GameCore::ObjectManager::Render(RenderManager::D2DManager& renderManager)
{
    for (int i = 0; i < IOL_NUM_LAYER; i++)
    {
        // Use iterator to traverse object list
        SPtr<ListIterator<ObjectBase>> iterator = m_objects[i].GetIterator();
        if (iterator->IsValid())
        {
            do
            {
                iterator->Get()->Render(renderManager);
            }
            while (iterator->Next());
        }
    }
}

//=============================================================================
#pragma endregion // Object manager
//=============================================================================