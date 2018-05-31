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

#include <Guier/Renderers/Win32/GdipRenderer.hpp>

#ifdef GUIER_PLATFORM_WINDOWS

#include <gdiplus.h>
#include <Gdiplusheaders.h>
#include <atlstr.h> 
#include <ShellScalingAPI.h>

namespace Guier
{

    namespace Renderers
    {

        // Interface
        void GdipInterface::RenderControl(Control * control, const Core::RenderArea & renderArea)
        {
            ::
        }

        void GdipInterface::RenderRectangle(const Vector2i & position, const Vector2i & size, Core::Texture * texture)
        {

        }

        void GdipInterface::RenderRectangle(const Vector2i & position, const Vector2i & size, Core::Texture * texture,
            const Vector2i & portionPosition, const Vector2i & portionSize)
        {

        }

        void GdipInterface::RenderRectangle(const Vector2i & position, const Vector2i & size, const Color & color)
        {

        }

        GdipInterface::GdipInterface(HWND windowHandle) :
            m_WindowHandle(windowHandle)
        {

        }

        // Renderer
        GdipRenderer::GdipRenderer(HWND windowHandle) :
            GdipInterface(windowHandle)
        {

        }

        GdipRenderer::~GdipRenderer()
        {

        }

        bool GdipRenderer::Load()
        {

            return true;
        }

        Core::RenderInterface * GdipRenderer::GetInterface()
        {
            return this;
        }

    }
}

#endif