#pragma once


/////////////
// INCLUDE
#include "../core/object/ObjectCore.h"


namespace GameCore
{
    /////////////////////////
    // ENUM: OBJECT_LAYERS
    enum INTERACT_OBJECT_LAYER
    {
        IOL_BACKGROUND = 0,
        IOL_MAIN_GAME,
        IOL_INTERFACE,

        IOL_NUM_LAYER
    };
    
    
    //////////////////////////
    // CLASS: ObjectManager
    class ObjectManager
    {
    public:
        ObjectManager();
        ObjectManager(const ObjectManager& clone);
        ~ObjectManager();

        void Initialize();
        void Release();

        void AddObject(ObjectBase* object, INTERACT_OBJECT_LAYER layer);

        void Update(float timeStep);
        void Render(RenderManager::D2DManager& renderManager);

    private:
        LinkedList<ObjectBase> m_objects[IOL_NUM_LAYER];
    };
}
    
    
#define RENDER_LAYERS GameCore::RENDER_LAYERS