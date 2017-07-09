#pragma once


/////////////
// INCLUDE
#include <string>

#include <hkUtilLib\core\Vector.h>
#include <hkUtilLib\dataManage\LinkedList.h>
#include <DXEngine\manager\render\RenderManager.h>
#include <hkUtilLib\Core.h>


namespace GameCore
{
    /////////////////////////
    // CLASS: ObjectFigure
    class ObjectFigure
    {
    public:
        ObjectFigure();
        ObjectFigure(const ObjectFigure& clone);
        ~ObjectFigure();
        virtual void Render(RenderManager::D2DManager&, const hkVector2F& pos);
        virtual void Render(RenderManager::D2DManager&, const hkVector2F& pos,
                            uint state1, uint state2);
        
        virtual void Show();
        virtual void Hide();
        virtual bool IsVisible();

    protected:
        bool m_isVisible;
    };


    //////////////////////////////
    // CLASS: ObjectBoundingBox
    class ObjectBoundingBox
    {
    public:
        // Collide status
        typedef enum BOUNDING_BOX_COLIDE_STATUS
        {
            NO_CONTACT = 0,
            CONTACTED_X_LEFT,
            CONTACTED_X_RIGHT,
            CONTACTED_Y_TOP,
            CONTACTED_Y_BOTTOM,
            OVERLAPPED
        } BOUNDING_BOX_COLIDE_STATUS;
        
    public:
        ObjectBoundingBox();
        ObjectBoundingBox(const ObjectBoundingBox&);
        ~ObjectBoundingBox();

        virtual BOUNDING_BOX_COLIDE_STATUS IsContact(WPtr<ObjectBoundingBox>&);
        virtual hkVector2F GetOverlapped(WPtr<ObjectBoundingBox>&);
        virtual void Update(hkVector2F&);
    };


    ///////////////////////
    // CLASS: ObjectBase
    class ObjectBase
    {
    public:
        ObjectBase();
        ObjectBase(const ObjectBase&);
        ~ObjectBase();

        virtual void SetPosition(const hkVector2F&);
        virtual hkVector2F GetPosition();
        virtual void Move(const hkVector2F&);
        virtual void Move(float x, float y);
        
        virtual void Show();
        virtual void Hide();
        virtual bool IsVisible();

        virtual void SetBoundingBox(ObjectBoundingBox*);
        virtual void SetFigure(ObjectFigure*);

        virtual WPtr<ObjectBoundingBox> GetBoundingBox();
        virtual WPtr<ObjectFigure> GetFigure();

        virtual void Update(float timePass);
        virtual void Render(RenderManager::D2DManager&);

    protected:
        hkVector2F m_position;

        SPtr<ObjectFigure> m_figure;
        SPtr<ObjectBoundingBox> m_boundingBox;
    };
}