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

#include <Guier/Control.hpp>
#include <Guier/Vector2.hpp>
#include <Guier/String.hpp>
#include <initializer_list>

namespace Guier
{ 

    class Skin;
    
    namespace Core
    {

        class WindowImpl;

        /**
        * Base class of renderable window.
        *
        */
        class GUIER_API WindowBase : public ParentRoot
        {

        public:

            /**
            * Styles of window.
            *
            */
            enum class Style : unsigned int
            {
                None            = 0,
                Default         = 127,

                TitleBar        = 1,  ///< Includes border.
                Border          = 2,
                Close           = 4,
                Minimize        = 8,
                Maximize        = 16,
                Resize          = 32,
                Taskbar         = 64, ///< Is the wíndow visible in the taskbar?
            };

        protected:

            /**
            * Constructor.
            *
            * @throw std::runtime_error If context == nullptr.
            *
            */
            WindowBase(Skin * skin, const Vector2i & size, const String & title, const std::initializer_list<Style> & styles);

            /**
            * Destructor.
            *
            */
            virtual ~WindowBase();

            WindowImpl * m_pImpl;   ///< Implementation of platform window.
           
        private:

            bool addChild(Control * child, const Index & index);
            bool removeChild(Control * child);
            Control * removeChild(const Index & index);     

            /**
            * Create texture from bitmap.
            *
            */
            Core::Texture * createTexture(Bitmap * bitmap);
            
        };

    }

}