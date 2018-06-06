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
            m_pSkin(skin),
            m_Dpi(0),
            m_ScaleFactor(0.0f)
        {

        }

        void GdipInterface::beginRendering(HDC deviceContextHandle)
        {
            m_DeviceContextHandle = deviceContextHandle;
            m_pGraphics = new Gdiplus::Graphics(m_DeviceContextHandle);
        }

        void GdipInterface::endRendering()
        {
            delete m_pGraphics;
        }

        void GdipInterface::renderRectangle(const Vector2i & position, const Vector2i & size, Core::Texture * texture)
        {
            // m_pGraphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);

           GdipTexture * pTexture = static_cast<GdipTexture*>(texture);
           const Vector2i & textSize = pTexture->size();
 /*

            Gdiplus::RectF rect;
            Gdiplus::Unit unit;

            pTexture->bitmap()->GetBounds(&rect, &unit);
*/

            //Gdiplus::Bitmap image(L"../skins/TestSkin.png");

          /*  int width = 96;
            int height = 96;
            const size_t dataSize = width * height * 3;

            int stride = width * 3;
            const int extraBytesMod = stride % 4;
            int extraBytes = 0;
            if (extraBytesMod)
            {
                extraBytes = 4 - extraBytesMod;
            }




            BYTE * data = new BYTE[dataSize];// = { 255, 255, 255,    255, 255, 255,   255, 255, 255,      255, 255, 255 };
            memset(data, 0, dataSize);

            
            

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    const int pos = (y * width * 3) + (x * 3);

                    data[pos + 2] = 255;

                }
            }

            Gdiplus::Bitmap image(width, height, stride, PixelFormat24bppRGB, data);
            m_pGraphics->DrawImage(&image, 10, 10, 0, 0, width, height, Gdiplus::Unit::UnitPixel);
            */

            Gdiplus::Bitmap * image = pTexture->bitmap();
            //m_pGraphics->DrawImage(image, 10, 10, 0, 0, textSize.x, textSize.y, Gdiplus::Unit::UnitInch);

            Gdiplus::RectF destRect(10, 10, static_cast<float>(textSize.x) * m_ScaleFactor, static_cast<float>(textSize.y) * m_ScaleFactor);

            destRect.Width = destRect.Width * 1.0f;
            destRect.Height = destRect.Height * 1.0f;


            //m_pGraphics->SetInterpolationMode(Gdiplus::InterpolationMode::InterpolationModeNearestNeighbor);

            m_pGraphics->DrawImage(image, destRect, 0, 0, textSize.x, textSize.y, Gdiplus::Unit::UnitPixel);





            const int fontSize = 12;
            int fontSizeDPI = MulDiv(fontSize, m_Dpi, 96);

            Gdiplus::FontFamily fontFamily(L"Segoe UI");

            Gdiplus::Font       font(&fontFamily, static_cast<Gdiplus::REAL>(fontSizeDPI), Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
            Gdiplus::SolidBrush solidbrush(Gdiplus::Color(255, 0, 0, 0));
            const WCHAR text[] = L"File   Edit   Format   View   Help";

            // Draw string.
            m_pGraphics->SetCompositingQuality(Gdiplus::CompositingQuality::CompositingQualityHighQuality);
            m_pGraphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeHighQuality);
            m_pGraphics->SetPixelOffsetMode(Gdiplus::PixelOffsetMode::PixelOffsetModeHighQuality);
            m_pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintClearTypeGridFit);

            m_pGraphics->DrawString(text, -1, &font, Gdiplus::PointF(150, 10), &solidbrush);
        }

        void GdipInterface::renderRectangle(const Vector2i & position, const Vector2i & size, Core::Texture * texture,
            const Vector2i & sourcPosition, const Vector2i & sourceSize)
        {
            GdipTexture * pTexture = static_cast<GdipTexture*>(texture);
            const Vector2i & textSize = pTexture->size();

            Gdiplus::RectF destination(position.x, position.y, size.x, size.y);
            m_pGraphics->DrawImage(pTexture->bitmap(), destination, sourcPosition.x, sourcPosition.y, sourceSize.x, sourceSize.y, Gdiplus::UnitPixel);
        }

        void GdipInterface::renderRectangle(const Vector2i & position, const Vector2i & size, const Color & color)
        {
            Gdiplus::SolidBrush solidbrush(Gdiplus::Color(color.a, color.r, color.g, color.b));
            m_pGraphics->FillRectangle(&solidbrush, position.x, position.y, size.x, size.y);
        }

        Skin * GdipInterface::skin() const
        {
            return m_pSkin;
        }

        /**
        * Get/set screen DPI.
        *
        */
        void GdipInterface::Dpi(unsigned int dpi)
        {
            m_Dpi = dpi;
            m_ScaleFactor = static_cast<float>(m_Dpi) / static_cast<float>(96);

           // int result = MulDiv(12, m_Dpi, 96);
        }

        unsigned int GdipInterface::Dpi() const
        {
            return m_Dpi;
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

        void GdipRenderer::beginRendering()
        {
            HDC hDC = BeginPaint(m_WindowHandle, &m_PaintStructure);
            GdipInterface::beginRendering(hDC);
        }

        void GdipRenderer::endRendering()
        {
            EndPaint(m_WindowHandle, &m_PaintStructure);
            GdipInterface::endRendering();
        }

        Texture * GdipRenderer::createTexture()
        {
            return new GdipTexture;
        }

        bool GdipRenderer::load()
        {

            return true;
        }

        Renderer::Interface * GdipRenderer::interface()
        {
            return this;
        }

    }
}

#endif