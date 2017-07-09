#pragma once


/////////////
// INCLUDE
#include <hkUtilLib\core\Vector.h>
#include <hkUtilLib\dataManage\LinkedList.h>

#include "../core/object/MoveableObject.h"


namespace GameCore
{   
    //////////////////////////
    // CLASS: PhysicManager
    class PhysicManager
    {
    public:
        PhysicManager();
        PhysicManager(const PhysicManager&);
        ~PhysicManager();

        void Update(float timeStep, 
                GameCore::MoveableObject& mainObjects,
                LinkedList<GameCore::MoveableObject>& moveableObjects, 
                LinkedList<GameCore::PhysicObject>& staticObjects);
        
    private:
        void ResolveActive(GameCore::MoveableObject& firstObject, GameCore::MoveableObject& secondObject);
        void ResolveStatic(GameCore::MoveableObject& object, GameCore::PhysicObject& staticObject);
    };
}
    
    
#define RENDER_LAYERS GameCore::RENDER_LAYERS