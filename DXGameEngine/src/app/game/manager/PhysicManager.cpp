#include "PhysicManager.h"

#include <math.h>

//=============================================================================
#pragma region // PhysicManager
//=============================================================================


GameCore::PhysicManager::PhysicManager()
{

}

GameCore::PhysicManager::PhysicManager(const PhysicManager&)
{

}

GameCore::PhysicManager::~PhysicManager()
{

}

void GameCore::PhysicManager::Update(float timeStep,
    GameCore::MoveableObject& mainObject,
    LinkedList<GameCore::MoveableObject>& moveableObjects,
    LinkedList<GameCore::PhysicObject>& staticObjects)
{
    // Loop through all move-able objects
    SPtr<ListIterator<GameCore::MoveableObject>> iterator = moveableObjects.GetIterator();
    if (iterator->IsValid())
        do
            ResolveActive(mainObject, *iterator->Get());
        while (iterator->Next());

    // Loop through all static objects
        SPtr<ListIterator<GameCore::PhysicObject>> iteratorStatic = staticObjects.GetIterator();
    if (iteratorStatic->IsValid())
        do
            ResolveStatic(mainObject, *iteratorStatic->Get());
        while (iteratorStatic->Next());
}

void GameCore::PhysicManager::ResolveActive(GameCore::MoveableObject& firstObject, GameCore::MoveableObject& secondObject)
{
    // Check if two object colide.
    int contactStatus = firstObject.GetBoundingBox()->IsContact(secondObject.GetBoundingBox());

    // If two objects contact with each other.
    if (contactStatus > GameCore::ObjectBoundingBox::NO_CONTACT)
    {
        // If two objects overlapped. Move them out of each other.
        if (contactStatus == GameCore::ObjectBoundingBox::OVERLAPPED)
        {
            // Get vector represent how much two objects is overlapping.
            hkVector2F overlapped = firstObject.GetBoundingBox()->GetOverlapped(secondObject.GetBoundingBox());

            // Get the minmum overlap direction to translate
            float halfX = 0;
            float halfY = 0;

            if (std::abs(overlapped.x) > std::abs(overlapped.y))
            {
                halfY = overlapped.y / 2.0f;

                // Update contact status
                if (halfY > 0)
                    contactStatus = GameCore::ObjectBoundingBox::CONTACTED_Y_BOTTOM;
                else
                    contactStatus = GameCore::ObjectBoundingBox::CONTACTED_Y_TOP;
            }
            else
            {
                halfX = overlapped.x / 2.0f;

                // Update contact status
                if (halfX > 0)
                    contactStatus = GameCore::ObjectBoundingBox::CONTACTED_X_LEFT;
                else
                    contactStatus = GameCore::ObjectBoundingBox::CONTACTED_X_RIGHT;
            }

            // Move each object out of each other.
            firstObject.Move(halfX, halfY);
            secondObject.Move(-halfX, -halfY);
        }

        // Calculate relative speed from object 1 to object 2
        hkVector2F velocity1 = firstObject.GetVelocity();
        hkVector2F velocity2 = secondObject.GetVelocity();

        hkVector2F relativeVelocity = velocity1 - velocity2;

        // If two objects is moving toward each other. Update velocity.
        float elastic1 = firstObject.GetElastic();
        float elastic2 = secondObject.GetElastic();
        float combineElastic = elastic1 * elastic2;

        if ((contactStatus == GameCore::ObjectBoundingBox::CONTACTED_X_LEFT && relativeVelocity.x > 0) ||
            (contactStatus == GameCore::ObjectBoundingBox::CONTACTED_X_RIGHT && relativeVelocity.x < 0))
        {
            float impuseVelocity = relativeVelocity.x * combineElastic;
            velocity1.x -= impuseVelocity;
            velocity2.x += impuseVelocity;
        }
        else if ((contactStatus == GameCore::ObjectBoundingBox::CONTACTED_Y_TOP && relativeVelocity.y > 0) ||
            (contactStatus == GameCore::ObjectBoundingBox::CONTACTED_Y_BOTTOM && relativeVelocity.y < 0))
        {
            float impuseVelocity = relativeVelocity.y * combineElastic;
            velocity1.y -= impuseVelocity;
            velocity2.y += impuseVelocity;
        }

        // Set new velocity to two objects
        firstObject.SetVelocity(velocity1);
        secondObject.SetVelocity(velocity2);
    }
}

void GameCore::PhysicManager::ResolveStatic(GameCore::MoveableObject& object, GameCore::PhysicObject& staticObject)
{
    // Check if two object colide.
    int contactStatus = object.GetBoundingBox()->IsContact(staticObject.GetBoundingBox());

    // If two objects contact with each other.
    if (contactStatus > GameCore::ObjectBoundingBox::NO_CONTACT)
    {
        // If two objects overlapped. Move them out of each other.
        if (contactStatus == GameCore::ObjectBoundingBox::OVERLAPPED)
        {
            // Get vector represent how much two objects is overlapping.
            hkVector2F overlapped = object.GetBoundingBox()->GetOverlapped(staticObject.GetBoundingBox());

            // Get the minmum overlap direction to translate
            float recoverX = 0;
            float recoverY = 0;

            if (std::abs(overlapped.x) > std::abs(overlapped.y))
            {
                recoverY = overlapped.y;

                // Update contact status
                if (recoverY > 0)
                    contactStatus = GameCore::ObjectBoundingBox::CONTACTED_Y_BOTTOM;
                else
                    contactStatus = GameCore::ObjectBoundingBox::CONTACTED_Y_TOP;
            }
            else
            {
                recoverX = overlapped.x;

                // Update contact status
                if (recoverX > 0)
                    contactStatus = GameCore::ObjectBoundingBox::CONTACTED_X_LEFT;
                else
                    contactStatus = GameCore::ObjectBoundingBox::CONTACTED_X_RIGHT;
            }

            // Move object out of static other.
            object.Move(recoverX, recoverY);
        }

        // Calculate relative speed from object 1 to object 2
        hkVector2F velocity = object.GetVelocity();

        // If two objects is moving toward each other. Update velocity.
        float elastic1 = object.GetElastic();
        float elastic2 = staticObject.GetElastic();
        float combineElastic = elastic1 * elastic2;

        if ((contactStatus == GameCore::ObjectBoundingBox::CONTACTED_X_LEFT && velocity.x > 0) ||
            (contactStatus == GameCore::ObjectBoundingBox::CONTACTED_X_RIGHT && velocity.x < 0))
        {
            velocity.x -= velocity.x * combineElastic;
        }
        else if ((contactStatus == GameCore::ObjectBoundingBox::CONTACTED_Y_TOP && velocity.y > 0) ||
            (contactStatus == GameCore::ObjectBoundingBox::CONTACTED_Y_BOTTOM && velocity.y < 0))
        {
            velocity.y -= velocity.y * combineElastic;
        }

        // Set velocity to object
        object.SetVelocity(velocity);
    }
}

//=============================================================================
#pragma endregion // PhysicManager
//=============================================================================