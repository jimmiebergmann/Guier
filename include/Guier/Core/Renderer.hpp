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
#include <Guier/Vector2.hpp>
#include <Guier/String.hpp>
#include <Guier/Color.hpp>

namespace Guier
{

    class Control;
    class Skin;
    class Font;

    namespace Core
    {

        /**
        * Forward declarations.
        *
        */
        class Texture;

        /**
        * Base class of renderer.
        *
        * @brief    A customer renderer should not perform any graphic API creation in the constructor.
        *           Perform all initialization in the Load() method.
        *
        */
        class GUIER_API Renderer
        {

        public:

            /**
            * Render area class.
            *
            */
            class RenderArea
            {

            public:

                /**
                * Constructor.
                *
                */
                RenderArea(const Vector2i & position, const Vector2i & size);

                Vector2i position;
                Vector2i size;

            };

            /**
            * Interface class, making it possible for controls to perform draw calls.
            *
            */
            class Interface
            {

            public:

                /**
                * Virtual destructor.
                *
                */
                virtual ~Interface();

                /**
                * Render Controller.
                *
                */
                void renderControl(Control * control, const Vector2i & position, const Vector2i & size);

                /**
                * Render chunk.
                *
                * @return true if skin is valid and chunk is found, or if the default skin is available,
                *         else false.
                *
                */
                bool renderChunk(const unsigned int item, const unsigned int state, const Vector2i & position, const Vector2i & size);

                /**
                * Render Rectangle.
                *
                */
                virtual void renderRectangle(const Vector2i & position, const Vector2i & size, Texture * texture) = 0;
                virtual void renderRectangle(const Vector2i & position, const Vector2i & size, Texture * texture, const Vector2i & sourcePosition, const Vector2i & sourceSize) = 0;
                virtual void renderRectangle(const Vector2i & position, const Vector2i & size, const Color & color) = 0;

                /**
                * Render font.
                *
                */
                virtual void renderFont(Font * font, const String & string, const unsigned int size, const Vector2i & position, const Color & color = Color::Black);

                /**
                * Get skin attached to interface.
                *
                */
                virtual Skin * skin() const = 0;

                /**
                * Get/set screen DPI.
                *
                */
                virtual void Dpi(unsigned int dpi) = 0;
                virtual unsigned int Dpi() const = 0;

            };

            /**
            * Destructor.
            *
            */
            virtual ~Renderer();

            /**
            * Begin rendering.
            *
            * @brief Internally setting device handle and initialize Gdiplus::Graphics
            *
            */
            virtual void beginRendering() = 0;

            /**
            * End rendering.
            *
            * @brief Internally clearing old rendering information.
            *
            */
            virtual void endRendering() = 0;

            /**
            * Create texture.
            *
            */
            virtual Texture * createTexture() = 0;

        protected:

            /**
            * Constructor.
            *
            * @brief No loading should be done whatsoever in constructor. Use Load method instead.
            *
            */
            Renderer();

        private:


            /**
            * Load the renderer.
            *
            * @return True if succeeded, else false.
            *
            */
            virtual bool load() = 0;

            /**
            * Get renderer interface.
            *
            */
            virtual Interface * interface() = 0;

        };

    }

}