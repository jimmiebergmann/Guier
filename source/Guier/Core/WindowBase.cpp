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

#include <Guier/Core/WindowBase.hpp>

#ifdef GUIER_DEFAULT_SKIN
    #include <Guier/Skins/DefaultSkin.hpp>
    static Guier::Skin * g_pDefaultSkin = nullptr;
#endif

#ifdef GUIER_PLATFORM_WINDOWS
#include <Guier/Core/Windows/Win32/Win32WindowImpl.hpp>
#else
#error Unkown platform. Specify in Build.hpp
#endif

namespace Guier
{

    static Skin * g_pDefaultSkin = nullptr;

    namespace Core
    {

        WindowBase::WindowBase(Skin * skin, const Vector2i & size, const String & title, const std::initializer_list<Style> & styles) :
            ParentRoot(skin),
            m_pImpl(nullptr)
        {
            #ifdef GUIER_PLATFORM_WINDOWS
                if (skin == nullptr)
                {
                    skin = GetDefaultSkin();
                }
                Win32WindowImpl * pWin32Impl = new Win32WindowImpl(this, skin, size, title, styles);
                m_pImpl = pWin32Impl;
                pWin32Impl->LoadImplementation();
            #else
            #error Unkown platform. Specify in Build.hpp
            #endif
        }

        WindowBase::~WindowBase()
        {
            delete m_pImpl;
        }

        Skin * WindowBase::GetDefaultSkin()
        {
            #ifdef GUIER_DEFAULT_SKIN
                if (g_pDefaultSkin == nullptr)
                {
                    g_pDefaultSkin = new Skins::DefaultSkin();
                }
                return g_pDefaultSkin;
            #endif

            return nullptr;
        }

        bool WindowBase::AddChild(Control * child, const Index & index)
        {
            return m_pImpl->Add(child, index);
        }

        bool WindowBase::RemoveChild(Control * child)
        {
            return m_pImpl->Remove(child);
        }

        Control * WindowBase::RemoveChild(const Index & index)
        {
            return m_pImpl->Remove(index);
        }

    }

}