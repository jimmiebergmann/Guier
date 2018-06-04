/*
* MIT License
*
* Copyright(c) 2018 Jimmie Bergmann
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/

#pragma once

#include <Guier/Core/Build.hpp>
#include <Guier/Core/Renderer.hpp>
#include <Guier/Index.hpp>
#include <Guier/Skin.hpp>

namespace Guier
{

    /**
    * Forward declarations
    *
    */
    class Parent;
    class ParentRoot;
 
    /**
    * Size namespace, containing methods for sizing of controls.
    *
    */
    namespace Size
    {
        extern const Vector2i GUIER_API Fit;  ///< Fit the size of the child/s.
        extern const Vector2i GUIER_API Max;  ///< Use maximum possible space given by parent.

    }

    /**
    * Align namespace, containing methods specifying control alignment.
    *
    */
    namespace Align
    {
        enum eType
        {
            Left,
            Center,
            Right,
            Top,
            Bottom
        };
    }   


    /**
    * Control base class.
    *
    * @brief    All controlers must inherit this class and implement the virtual functions.
    *
    */
    class GUIER_API Control
    {

    public:

        /**
        * Enumeration of each type.
        *
        */
        enum class Types : unsigned int
        {
            Plane,
            Button,
            VerticalGrid,
            Text,
            Custom

        };

        /**
        * Destructor.
        *
        */
        virtual ~Control();

        /**
        * Get type of controller.
        *
        */
        virtual unsigned int Type() const = 0;

    protected:

        /**
        * Constructor.
        *
        * @throw std::runtime_error If child or parent is nullptr.
        *
        */
        Control(Parent * parent, const Index & parentIndex, const Vector2i & size);

        /**
        * Get root from parent.
        *
        */
        ParentRoot * GetParentRoot() const;

        Vector2i m_Size; ///< Requested size of control.

    private:

        /**
        * Render the control.
        *
        */
        virtual void Render(Core::Renderer::Interface * renderInterface, const Vector2i & position, const Vector2i & size) = 0;

        Parent *        m_pParent;      ///< Parent of control.
        Vector2i        m_RenderSize;   ///< Actual render size of control.

        /**
        * Friend classes.
        *
        */
        friend class Parent;
        friend class Core::Renderer::Interface;

    };


    /**
    * Parent control base class.
    *
    * @brief    All parents of controllers must inherit this class and implement the virtual functions.
    *
    */
    class GUIER_API Parent
    {

    public:

        /**
        * Get context.
        */
       // Context * GetContext() const;

        /**
        * Add child to control parent.
        *
        * @return   True if child is added, else false if child = nullptr,
        *           or if AddChild returns false.
        *
        */
        bool Add(Control * child, const Index & index = Index::Last);

        /**
        * Remove child from parent.
        *
        * @brief    The child is destroyed and unallocated.
        *           Do not access the child pointer after execution of this function.
        *
        * @return True if removed, false if child is nullptr or not child of parent,.
        *         Pointer to removed control if removed, else nullptr.
        *
        */
        bool Remove(Control * child);
        Control * Remove(const Index & index);

    protected:

        /**
        * Constructor.
        *
        */
        Parent(ParentRoot * parentRoot);
        Parent(Parent * parent);

        /**
        * Get root parent.
        *
        */
        ParentRoot * GetRoot() const;

    private:

        virtual bool AddChild(Control * child, const Index & index) = 0;
        virtual bool RemoveChild(Control * child) = 0;
        virtual Control * RemoveChild(const Index & index) = 0;

        /**
        * Become parent over controller.
        *
        */
        void BecomeParentOf(Control * child);

        ParentRoot * m_pParentRoot;   ///< Pointer to parent root.

        /**
        * Friend classes.
        *
        */
        friend class Control;
    
    };


    /**
    * Parent controll class.
    *
    * @brief    Iherit this class if your parent also is a controller.
    *
    */
    class GUIER_API ParentControl : public Parent, public Control
    {

    public:


        /**
        * Destructor.
        *
        */
        virtual ~ParentControl();

    protected:

        /**
        * Constructor.
        *
        * @throw std::runtime_error If child or parent is nullptr.
        *
        */
        ParentControl(Parent * parent, const Index & parentIndex, const Vector2i & size);

    };


    /**
    * Root control base class.
    *
    * @brief The root of a controller tree.
    *        For example Windows.
    *
    */
    class GUIER_API ParentRoot : public Parent
    {

    protected:

        /**
        * Constructor.
        *
        * @param skin   Skin used for rendering childs of root parent.
        *              If skin == nullpt, default skin is used if available(check Build.hpp)
        *
        */
        ParentRoot(Skin * skin);

        Skin *  m_pSkin;    ///< Pointer of skin.
        
    protected:

        /**
        * Get skin of parent root.
        *
        */
        Skin * GetSkin();

    private:

        virtual bool AddChild(Control * child, const Index & index) = 0;
        virtual bool RemoveChild(Control * child) = 0;
        virtual Control * RemoveChild(const Index & index) = 0;

        friend class Control;
        friend class Parent;

    };

}