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

#include <Guier/Core/Control.hpp>
#include <Guier/Control/VerticalGrid.hpp>
#include <stdexcept>

namespace Guier
{

    namespace Size
    {

        const Vector2i Fit = Vector2i(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());

    }

    namespace Core
    {

        Context * ControlParent::GetContext() const
        {
            return m_pContext;
        }

        bool ControlParent::Add(Control * control, const Index & index)
        {
            if (control == nullptr)
            {
                throw std::runtime_error("Control is nullptr.");
                return false;
            }

            if (AddChild(control, index) == false)
            {
                return false;
            }

            BecomeParentOf(control);
            return true;
        }

        bool ControlParent::Remove(Control * control)
        {
            if (control == nullptr)
            {
                return false;
            }

            if (RemoveChild(control) == false)
            {
                return false;
            }

            delete control;

            return true;
        }

        bool ControlParent::Remove(const Index & index)
        {
            Control * pControl = RemoveChild(index);
            
            if (pControl == nullptr)
            {
                return false;
            }

            delete pControl;

            return true;
        }

        ControlParent::ControlParent(Context * parent) :
            m_pContext(parent)
        {

        }

        ControlParent::ControlParent(Control * inheritor, ControlParent * parent, const Index & parentIndex) :
            m_pContext(parent->GetContext())
        {
            parent->Add(inheritor, parentIndex);
        }

        void ControlParent::BecomeParentOf(Control * control)
        {
            
        }


        // Vertical grid helper class.
        ControlParent::VerticalGrid::VerticalGrid(Control * inheritor, ControlParent * inheritorParent, ControlParent * parent, const Index & parentIndex) :
            ControlParent(inheritor, parent, parentIndex),
            m_pInheritor(inheritorParent),
            m_pChild(nullptr),
            m_pVerticalGrid(nullptr)
        {

        }

        ControlParent::VerticalGrid::~VerticalGrid()
        {
            std::lock_guard<std::recursive_mutex> sm(m_Mutex);

            if (m_pVerticalGrid)
            {
                delete m_pVerticalGrid;
            }
            else if (m_pChild)
            {
                delete m_pChild;
            }
        }

        bool ControlParent::VerticalGrid::AddChild(Control * control, const Index & index)
        {
            if (control == nullptr)
            {
                throw std::runtime_error("Control is nullptr.");
            }

            std::lock_guard<std::recursive_mutex> sm(m_Mutex);

            if (m_pVerticalGrid)
            {
                m_pVerticalGrid->Add(control, index);
            }
            else if (m_pChild == nullptr)
            {
                m_pChild = control;
            }
            else
            {
                // Temporary store the old child.
                Core::Control * tempChild = m_pChild;
                m_pChild = nullptr;

                // Create the vertical grid. Calling the constructor of ControlParent will cause the system
                // to call AddChild of this again, but this time m_ChildCount is 0 and will just add it.
                m_pVerticalGrid = new Guier::VerticalGrid(nullptr);

                m_pVerticalGrid->Add(tempChild, index);
            }

            return true;
        }

        bool ControlParent::VerticalGrid::RemoveChild(Control * control)
        {
            if (control == nullptr)
            {
                return false;
            }

            std::lock_guard<std::recursive_mutex> sm(m_Mutex);

            if (m_pVerticalGrid)
            {
                if (m_pVerticalGrid->Remove(control))
                {
                    if (m_pVerticalGrid->Count() == 0)
                    {
                        delete m_pVerticalGrid;
                        m_pVerticalGrid = nullptr;
                    }
                }
            }
            else if (m_pChild)
            {
                if(m_pChild == control)
                {
                    delete m_pChild;
                    m_pChild = nullptr;
                }
            }

            return false;
        }

        Control * ControlParent::VerticalGrid::RemoveChild(const Index & index)
        {
            std::lock_guard<std::recursive_mutex> sm(m_Mutex);

            if (m_pVerticalGrid)
            {
                if (m_pVerticalGrid->Remove(index))
                {
                    if (m_pVerticalGrid->Count() == 0)
                    {
                        delete m_pVerticalGrid;
                        m_pVerticalGrid = nullptr;
                    }
                }
            }
            else if (m_pChild)
            {
                if (index.GetSingleInteger() == 0 || index.IsFirst())
                {
                    delete m_pChild;
                    m_pChild = nullptr;
                }
            }

            return nullptr;
        }

        // Control class.
        Control::Control()
        {
        }

        Control::Control(Control * inheritor, ControlParent * parent, const Index & parentIndex)
        {
            parent->Add(inheritor, parentIndex);
        }

        Control::~Control()
        {
  
        }

    }

}