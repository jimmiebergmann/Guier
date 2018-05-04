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

#include <Guier/Context.hpp>
#include <Guier/Renderer.hpp>
#include <Guier/Window.hpp>
#include <Guier/Skin.hpp>

namespace Guier
{

    Context::Context(Renderer * renderer, Skin * skin) :
        m_DefaultRenderer(false),
        m_DefaultSkin(false),
        m_pRenderer(renderer),
        m_pSkin(skin)
    {
        // Create default renderer if needed.
        if (m_pRenderer == nullptr)
        {
            m_pRenderer = Renderer::CreateDefaultRenderer();
            m_DefaultRenderer = true;
        }

        // Create defailt skin if needed.
        if (m_pSkin == nullptr)
        {
            m_pSkin = Skin::CreateDefaultSkin();
            m_DefaultSkin = true;
        }
    }

    Context::Context(Skin * skin) :
        Context(nullptr, skin)
    {

    }

    Context::~Context()
    {
        Clear();
    }

    Context & Context::Clear()
    {
        if (m_pRenderer != nullptr)
        {
            delete m_pRenderer;
        }
        
        while(m_Windows.size())
        {
            delete *m_Windows.begin();
        }
        m_Windows.clear();

        return *this;
    }

    void Context::Update()
    {
        for (auto it = m_Windows.begin(); it != m_Windows.end(); it++)
        {
            (*it)->Update();
        }
    }

    void Context::Render()
    {
        if (m_pRenderer == nullptr)
        {
            throw std::runtime_error("No renderer is set in context.");
        }
    }

    Context & Context::Add(Renderer * renderer)
    {
        // Check if the renderer should be unallocated.
        if (m_pRenderer)
        {
            if (renderer == m_pRenderer || (renderer == nullptr && m_DefaultRenderer))
            {
                return *this;
            }
        }

        // Unallocate.
        delete m_pRenderer;

        // Allocate.
        if (renderer)
        {
            m_pRenderer = renderer;
            m_DefaultRenderer = false;
        }
        else
        {
            m_pRenderer = Renderer::CreateDefaultRenderer();
            m_DefaultRenderer = true;
        }

        return *this;
    }

    Context & Context::Add(Skin * skin)
    {
        // Check if the skin should be unallocated.
        if (m_pSkin)
        {
            if (skin == m_pSkin || (skin == nullptr && m_DefaultSkin))
            {
                return *this;
            }
        }

        // Unallocate.
        delete m_pSkin;

        // Allocate.
        if (skin)
        {
            m_pSkin = skin;
            m_DefaultSkin = false;
        }
        else
        {
            m_pSkin = Skin::CreateDefaultSkin();
            m_DefaultSkin = true;
        }

        return *this;
    }

    Context & Context::Add(Window * window, const bool show)
    {
        if (window == nullptr || m_Windows.find(window) != m_Windows.end())
        {
            return *this;
        }

        Renderer * pNewRenderer = m_pRenderer->AllocateNew();
        pNewRenderer->Load();

        window->m_pContext = this;
        window->m_pRenderer = pNewRenderer;

        m_Windows.insert(window);
        return *this;
    }

    Context & Context::Remove(Renderer * renderer)
    {
        if (m_pRenderer && renderer == m_pRenderer)
        {
            delete m_pRenderer;
            m_pRenderer = nullptr;
        }
        return *this;
    }

    Context & Context::Remove(Skin * skin)
    {
        if (m_pSkin && skin == m_pSkin)
        {
            delete m_pSkin;
            m_pSkin = nullptr;
        }
        return *this;
    }

    Context & Context::Remove(Window * window)
    {
        if (window == nullptr || m_Windows.find(window) == m_Windows.end())
        {
            return *this;
        }

        if (window->m_Deleted == false)
        {
            window->m_pContext = nullptr;
            delete window->m_pRenderer;
            window->m_pRenderer = nullptr;
        }

        m_Windows.erase(window);
        return *this;
    }

    Renderer * Context::GetRenderer() const
    {
        return m_pRenderer;
    }

    Skin * Context::GetSkin() const
    {
        return m_pSkin;
    }

}