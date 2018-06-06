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

#include <Guier/Core/Build.hpp>

#ifdef GUIER_PLATFORM_WINDOWS

#include <Guier/Core/Win32/WindowsHeaders.hpp>
#include <Guier/Core/Renderer.hpp>


namespace Guier
{

    namespace Core
    {

        class GdipInterface : public Renderer::Interface
        {

        public:

            /**
            * Constructor
            *
            */
            GdipInterface(Skin * skin);

            /**
            * Begin rendering.
            *
            * @brief internally setting device handle and initialize Gdiplus::Graphics
            *
            */
            void beginRendering(HDC deviceContextHandle);

            /**
            * End rendering.
            *
            * @brief Internally clearing old rendering information.
            *
            */
            void endRendering();

            /**
            * Render rectangle.
            *
            */
            void renderRectangle(const Vector2i & position, const Vector2i & size, Core::Texture * texture);
            void renderRectangle(const Vector2i & position, const Vector2i & size, Core::Texture * texture, const Vector2i & sourcePosition, const Vector2i & sourceSize);
            void renderRectangle(const Vector2i & position, const Vector2i & size, const Color & color);

            /**
            * Get skin attached to interface.
            *
            */
            Skin * skin() const;

            /**
            * Get/set screen DPI.
            *
            */
            void Dpi(unsigned int dpi);
            unsigned int Dpi() const;

        private:

            HDC                 m_DeviceContextHandle;
            Gdiplus::Graphics * m_pGraphics;
            Skin *              m_pSkin;

            unsigned int        m_Dpi;
            float               m_ScaleFactor;

        };


        /**
        * Gdip render class. Used in Win32WindowImp.
        *
        */
        class GUIER_API GdipRenderer : public Renderer, public GdipInterface
        {

        public:

            /**
            * Constructor.
            *
            * @brief No loading should be done whatsoever in constructor. Use Load method instead.
            *
            */
            GdipRenderer(HWND windowHandle, Skin * skin);

            /**
            * Destructor.
            *
            */
            ~GdipRenderer();

            /**
            * Begin rendering.
            *
            * @brief Internally setting device handle and initialize Gdiplus::Graphics
            *
            */
            void beginRendering();

            /**
            * End rendering.
            *
            * @brief Internally clearing old rendering information.
            *
            */
            void endRendering();

            /**
            * Create texture.
            *
            */
            Texture * createTexture();

            /**
            * Load the renderer.
            *
            * @return True if succeeded, else false.
            *
            */
            virtual bool load();

            /**
            * Get renderer interface.
            *
            */
            Renderer::Interface * interface();

        private:

            const HWND          m_WindowHandle; ///< Window handle.
            PAINTSTRUCT         m_PaintStructure;

        };

    }

}

#endif
