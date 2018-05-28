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
#include <Guier/Index.hpp>

namespace Guier
{

    /**
    * Forward declarations
    *
    */
    class Context;
    class Parent;
 
    /**
    * Size namespace, containing methods for sizing of controls.
    *
    */
    namespace Size
    {
        extern const Vector2i Fit;  ///< Fit the size of the child/s.
        extern const Vector2i Max;  ///< Use maximum possible space given by parent.

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
        Control(Control * child, Parent * parent, const Index & parentIndex, const Vector2i & size);

        Vector2i m_Size; ///< Requested size of control.

        /**
        * Friend classes.
        *
        */
        friend class Parent;

    private:

        Parent *    m_pParent;      ///< Parent of control.
        Vector2i    m_RenderSize;   ///< Actual render size of control.

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
        *
        * @return True if removed, false if child is nullptr or not child of parent, or index is invalid.
        *
        */
        bool Remove(Control * child);
        bool Remove(const Index & index);

    protected:


        /**
        * Constructor.
        *
        */
        Parent();

    private:

        virtual bool AddChild(Control * child, const Index & index) = 0;
        virtual bool RemoveChild(Control * child) = 0;
        virtual Control * RemoveChild(const Index & index) = 0;

        /**
        * Become parent over controller.
        *
        */
        void BecomeParentOf(Control * child);

    };

}