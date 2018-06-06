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
        virtual unsigned int type() const = 0;

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
        ParentRoot * parentRoot() const;

        Vector2i m_Size; ///< Requested size of control.

    private:

        /**
        * Render the control.
        *
        */
        virtual void render(Core::Renderer::Interface * renderInterface, const Vector2i & position, const Vector2i & size) = 0;

        Parent *        m_pParent;      ///< Parent of control...
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
        bool add(Control * child, const Index & index = Index::Last);

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
        bool remove(Control * child);
        Control * remove(const Index & index);

    protected:

        /**
        * Constructor.
        *
        */
        Parent(Parent * parent);
        Parent(ParentRoot * parentRoot);

        /**
        * Get parent root.
        *
        */
        ParentRoot * root() const;

    private:

        virtual bool addChild(Control * child, const Index & index) = 0;
        virtual bool removeChild(Control * child) = 0;
        virtual Control * removeChild(const Index & index) = 0;

        ParentRoot * m_pParentRoot;   ///< Pointer to parent root.

        /**
        * Friend classes.
        *
        */
        friend class Control;
        friend class ParentControl;
    
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
        * @param skin        Skin used for rendering childs of root parent.
        * @param parentRoot  Parent root to copy skin pointer from.
        *
        */
        ParentRoot(Skin * skin);
        ParentRoot(ParentRoot * parentRoot);
        
        /**
        * Create texture from bitmap.
        *
        */
        virtual Core::Texture * createTexture(Bitmap * bitmap) = 0;

        Skin * m_pSkin;    ///< Pointer of skin.

    private:

        virtual bool addChild(Control * child, const Index & index) = 0;
        virtual bool removeChild(Control * child) = 0;
        virtual Control * removeChild(const Index & index) = 0;

        friend class Skin;

    };

}