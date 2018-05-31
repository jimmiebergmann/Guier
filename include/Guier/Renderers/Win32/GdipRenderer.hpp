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

#include <Guier/Renderer.hpp>

#ifdef GUIER_PLATFORM_WINDOWS

#include <Guier/Core/RenderInterface.hpp>
#include <Windows.h>

namespace Guier
{

    namespace Core { class Win32WindowImp; }

    namespace Renderers
    {

        class GdipInterface : public Core::RenderInterface
        {

        public:

            /**
            * Render Controller.
            *
            */
            virtual void RenderControl(Control * control, const Core::RenderArea & renderArea);

            /**
            * Render rectangle.
            *
            */
            virtual void RenderRectangle(const Vector2i & position, const Vector2i & size, Core::Texture * texture);
            virtual void RenderRectangle(const Vector2i & position, const Vector2i & size, Core::Texture * texture, const Vector2i & portionPosition, const Vector2i & portionSize);
            virtual void RenderRectangle(const Vector2i & position, const Vector2i & size, const Color & color);

        protected:

            /**
            * Constructor
            *
            */
            GdipInterface(HWND windowHandle);

        private:

            HWND m_WindowHandle; ///< Handle to window.

            friend class GdipRenderer; ///< Friend class of parent.

        };

        class GUIER_API GdipRenderer : private GdipInterface, public Renderer
        {

        public:

            /**
            * Constructor.
            *
            * @brief No loading should be done whatsoever in constructor. Use Load method instead.
            *
            */
            GdipRenderer(HWND windowHandle);

            /**
            * Destructor.
            *
            */
            ~GdipRenderer();

        private:

            /**
            * Load the renderer.
            *
            * @return True if succeeded, else false.
            *
            */
            virtual bool Load();

            /**
            * Get renderer interface.
            *
            */
            virtual Core::RenderInterface * GetInterface();          

            friend class Core::Win32WindowImp;

        };

    }

}

#endif
