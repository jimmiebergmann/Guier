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

#include <Guier/Control.hpp>
#include <Guier/Control/VerticalGrid.hpp>
#include <mutex>

namespace Guier
{


    namespace Core
    {

        /*class GUIER_API VerticalGridHelper : public Parent
        {

        protected:

            /**
            * Constructor.
            *
            * @param inheritor  Pointer to inheritor. Always pass "this".
            * @param context    Parent of this object.
            *
            */
           // VerticalGridHelper(Control * inheritor, Parent * inheritorParent, Parent * parent, const Index & parentIndex = Index::Last);

            /**
            * Destructor.
            *
            */
          /*  virtual ~VerticalGridHelper();

            virtual bool AddChild(Control * control, const Index & index);
            virtual bool RemoveChild(Control * control);
            virtual Control * RemoveChild(const Index & index);

            Parent *                m_pInheritor;       ///< Pointer of inheritor of this class.
            Control *               m_pChild;           ///< Parent to child item. Is pointing to a VerticalGrid, if m_ChildCount is larger than 1.
            VerticalGrid *          m_pVerticalGrid;    ///< Number of childs added.
            std::recursive_mutex    m_Mutex;            ///< Mutex lock for adding items.

        };*/

    }

}







/**
* Helper class for parent classes, basing their child on a vertical grid, such as buttons.
*/
/*class GUIER_API ControlParent::VerticalGrid : public ControlParent
{

protected:
    */
    /**
    * Constructor.
    *
    * @param inheritor  Pointer to inheritor. Always pass "this".
    * @param context    Parent of this object.
    *
    */
 //   VerticalGrid(Control * inheritor, ControlParent * inheritorParent, ControlParent * parent, const Index & parentIndex = Index::Last);

    /**
    * Destructor.
    *
    */
    /*virtual ~VerticalGrid();

    ControlParent *         m_pInheritor;       ///< Pointer of inheritor of this class.
    Control *               m_pChild;           ///< Parent to child item. Is pointing to a VerticalGrid, if m_ChildCount is larger than 1.
    Guier::VerticalGrid *   m_pVerticalGrid;    ///< Number of childs added.
    std::recursive_mutex    m_Mutex;            ///< Mutex lock for adding items.

protected:

    virtual bool AddChild(Control * control, const Index & index);
    virtual bool RemoveChild(Control * control);
    virtual Control * RemoveChild(const Index & index);



};

*/