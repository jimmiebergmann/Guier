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

#include <Guier/Core/Windows/Win32/GdipRenderer.hpp>

#ifdef GUIER_PLATFORM_WINDOWS

#include <Guier/Core/Windows/Win32/GdipTexture.hpp>

namespace Guier
{

    namespace Core
    {

        // Hacky way of initializing GdiPlus one and also cleaning it up.
        static ULONG_PTR m_GdipStartupToken = 0;
        inline int GdpiInitializerHelper()
        {
            Gdiplus::GdiplusStartupInput gdiplusStartupInput;
            Gdiplus::GdiplusStartup(&m_GdipStartupToken, &gdiplusStartupInput, NULL);
            return 1;
        }
        static const int g_GdipInitializerHelper = GdpiInitializerHelper();
        class GdipFinalizerHelper
        {
        public:
            inline GdipFinalizerHelper() {}
            inline ~GdipFinalizerHelper()
            {
                if (m_GdipStartupToken != 0)
                {
                    Gdiplus::GdiplusShutdown(m_GdipStartupToken);
                }
            }
        } g_Finalizer;

        // Interface
        GdipInterface::GdipInterface(Skin * skin) :
            m_DeviceContextHandle(0),
            m_pGraphics(nullptr),
            m_pSkin(skin)
        {

        }

        void GdipInterface::BeginRendering(HDC deviceContextHandle)
        {
            m_DeviceContextHandle = deviceContextHandle;
            m_pGraphics = new Gdiplus::Graphics(m_DeviceContextHandle);
        }

        void GdipInterface::EndRendering()
        {
            delete m_pGraphics;
        }

        void GdipInterface::RenderRectangle(const Vector2i & position, const Vector2i & size, Core::Texture * texture)
        {
            // m_pGraphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);

            GdipTexture * pTexture = static_cast<GdipTexture*>(texture);
            const Vector2i & textSize = pTexture->GetSize();
            m_pGraphics->DrawImage(pTexture->GetBitmap(), position.x, position.y, size.x, size.y); 
        }

        void GdipInterface::RenderRectangle(const Vector2i & position, const Vector2i & size, Core::Texture * texture,
            const Vector2i & sourcPosition, const Vector2i & sourceSize)
        {
            GdipTexture * pTexture = static_cast<GdipTexture*>(texture);
            const Vector2i & textSize = pTexture->GetSize();

            Gdiplus::RectF destination(position.x, position.y, size.x, size.y);
            m_pGraphics->DrawImage(pTexture->GetBitmap(), destination, sourcPosition.x, sourcPosition.y, sourceSize.x, sourceSize.y, Gdiplus::UnitPixel);
        }

        void GdipInterface::RenderRectangle(const Vector2i & position, const Vector2i & size, const Color & color)
        {
            Gdiplus::SolidBrush solidbrush(Gdiplus::Color(color.A, color.R, color.G, color.B));
            m_pGraphics->FillRectangle(&solidbrush, position.x, position.y, size.x, size.y);
        }

        Skin * GdipInterface::GetSkin() const
        {
            return m_pSkin;
        }


        // Renderer
        GdipRenderer::GdipRenderer(HWND windowHandle, Skin * skin) :
            GdipInterface(skin),
            m_WindowHandle(windowHandle)
        {
        }

        GdipRenderer::~GdipRenderer()
        {
        }

        void  GdipRenderer::BeginRendering()
        {
            HDC hDC = BeginPaint(m_WindowHandle, &m_PaintStructure);
            GdipInterface::BeginRendering(hDC);
        }

        void  GdipRenderer::EndRendering()
        {
            EndPaint(m_WindowHandle, &m_PaintStructure);
            GdipInterface::EndRendering();
        }

        bool GdipRenderer::Load()
        {

            return true;
        }

        Renderer::Interface * GdipRenderer::GetInterface()
        {
            return this;
        }

    }
}

#endif