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

#include <Guier/Core/RenderTarget.hpp>
#include <Guier/Vector2.hpp>
#include <string>
#include <memory>
#include <atomic>

namespace Guier
{
    class Context;
    class Window;
    
    namespace Core
    {
        class ContextBase;
        class WindowImpl;

        class GUIER_API WindowBase : public RenderTarget
        {

        public:

            friend class Guier::Context; ///< Friend class of context.
            friend class ContextBase; ///< Friend class of context base.

            WindowBase(Context * context, const Vector2i & size, const std::wstring & title);

            virtual ~WindowBase();

            struct Style
            {
                enum eStyle
                {
                    None = 0,
                    Close = 1,
                    Minimize = 2,
                    Resize = 4,
                    TitleBar = 8,
                    Default = 15,
                    Fullscreen = 16
                };
            };

        protected:

            void CreatePlatformWindow(std::shared_ptr<Window> window);

            void DestroyPlatformWindow();

            std::atomic<bool> & Removed();

            static void HandleEvents();

            Context *               m_pContext;         ///< Pointer to context interface.    
            WindowImpl *            m_pImpl;            ///< Implementation of platform dependent functionality.
            std::shared_ptr<Window> m_SharedPtrWindow;  ///< Shared pointer of window.
            std::atomic<bool>       m_Removed;
        };

    }

}