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
#include <mutex>

namespace Guier
{

    class Context; ///< Forward declaration.
    class VerticalGrid;
 
    namespace Size
    {

        extern const Vector2i Fit;

    }


    /*namespace Align
    {
        enum eType
        {
            Left,
            Center,
            Right,
            Top,
            Bottom
        };
    }*/

    namespace Core
    {

        class Control;

        /**
        * Class for handling parents of controls.
        */
        class GUIER_API ControlParent
        {

        public:

            /**
            * Get context.
            */
            Context * GetContext() const;

            /**
            * Add child to control parent.
            *
            * @throw std::runtime_error   If control == nullptr.
            *
            */
            bool Add(Control * control, const Index & index = Index::Last);

            /**
            * Remove child from control parent.
            *
            * @brief    The child is destroyed and unallocated.
            *       
            *
            * @return True if removed, false if control is nullptr or not child of parent, or index is not found.
            *
            */
            bool Remove(Control * control);
            bool Remove(const Index & index);

            class VerticalGrid;

        protected:


            /**
            * Constructor.
            *
            * @param inheritor  Pointer to inheritor. Always pass "this".
            * @param context    Parent of this object.
            *
            */
            ControlParent(Context * parent);
            ControlParent(Control * inheritor, ControlParent * parent, const Index & parentIndex = Index::Last);

        private:

            virtual bool AddChild(Control * control, const Index & index) = 0;
            virtual bool RemoveChild(Control * control) = 0;
            virtual Control * RemoveChild(const Index & index) = 0;

            /**
            * Become parent over control.
            *
            */
            void BecomeParentOf(Control * control);

            Context * const m_pContext; ///< Context pointer.

        };

        /**
        * Helper class for parent classes, basing their child on a vertical grid, such as buttons.
        */
        class GUIER_API ControlParent::VerticalGrid : public ControlParent
        {

        protected:

            /**
            * Constructor.
            *
            * @param inheritor  Pointer to inheritor. Always pass "this".
            * @param context    Parent of this object.
            *
            */
            VerticalGrid(Control * inheritor, ControlParent * inheritorParent, ControlParent * parent, const Index & parentIndex = Index::Last);

            /**
            * Destructor.
            *
            */
            virtual ~VerticalGrid();

            ControlParent *         m_pInheritor;       ///< Pointer of inheritor of this class.
            Control *               m_pChild;           ///< Parent to child item. Is pointing to a VerticalGrid, if m_ChildCount is larger than 1.
            Guier::VerticalGrid *   m_pVerticalGrid;    ///< Number of childs added.
            std::recursive_mutex    m_Mutex;            ///< Mutex lock for adding items.

        protected:

            virtual bool AddChild(Control * control, const Index & index);
            virtual bool RemoveChild(Control * control);
            virtual Control * RemoveChild(const Index & index);



        };

        /**
        * Base class of controls.
        */
        class GUIER_API Control
        {

        protected:

            friend class ControlParent;

            /**
            * Constructor.
            *
            */
            Control();
            Control(Control * inheritor, ControlParent * parent, const Index & parentIndex = Index::Last);

            /**
            * Destructor.
            *
            */
            virtual ~Control();

        };

    }

}