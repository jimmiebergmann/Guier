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

#include <Guier/Control.hpp>
#include <stdexcept>
#include <limits>

static const int g_MinInt = std::numeric_limits<int>::min();
static const int g_MaxInt = std::numeric_limits<int>::max();

namespace Guier
{

    // Size namespace.
    namespace Size
    {

        const Vector2i Fit = Vector2i(g_MinInt, g_MinInt);
        const Vector2i Max = Vector2i(g_MaxInt, g_MaxInt);

    }


    // Control class.
    Control::~Control()
    {
        if (m_pParent)
        {
            Parent * oldParent = m_pParent;
            m_pParent = nullptr;
            oldParent->Remove(this);
        }
    }

    Control::Control(Parent * parent, const Index & parentIndex, const Vector2i & size) :
        m_pParent(parent),
        m_Size(size),
        m_RenderSize(0, 0)
    {
        if (parent == nullptr)
        {
            throw std::runtime_error("Parent is nullptr.");
        }

        parent->Add(this, parentIndex);
    }

    ParentRoot * Control::GetParentRoot() const
    {
        return m_pParent->GetRoot();
    }
   
    bool Parent::Add(Control * child, const Index & index)
    {
        if (child == nullptr)
        {
            return false;
        }

        if (AddChild(child, index) == false)
        {
            return false;
        }

        BecomeParentOf(child);
        return true;
    }

    bool Parent::Remove(Control * child)
    {
        if (child == nullptr)
        {
            return false;
        }

        if (RemoveChild(child) == false)
        {
            return false;
        }

        // Actually unallocate child control.
        if (child->m_pParent)
        {
            child->m_pParent = nullptr; //< Set parent to nullptr to ensure control destructor wont call this function again.
        }
        delete child;

        return true;
    }

    Control * Parent::Remove(const Index & index)
    {
        Control * pChild = RemoveChild(index);
            
        if (pChild == nullptr)
        {
            return nullptr;
        }

        delete pChild;

        return pChild;
    }

    // Parent.
    Parent::Parent(ParentRoot * parentRoot) :
        m_pParentRoot(parentRoot)
    {

    }

    Parent::Parent(Parent * parent) :
        m_pParentRoot(parent->GetRoot())
    {

    }

    ParentRoot * Parent::GetRoot() const
    {
        return m_pParentRoot;
    }

    void Parent::BecomeParentOf(Control * child)
    {
            
    }

    // Parent control.
    ParentControl::~ParentControl()
    {

    }

    ParentControl::ParentControl(Parent * parent, const Index & parentIndex, const Vector2i & size) :
        Parent(parent),
        Control(parent, parentIndex, size)
    {

    }

    // Parent root.
    ParentRoot::ParentRoot(Skin * skin) :
        Parent(this),
        m_pSkin(skin)
    {
    }

    Skin * ParentRoot::GetSkin()
    {
        return m_pSkin;
    }

}