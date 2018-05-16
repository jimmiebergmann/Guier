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

namespace Guier
{

    namespace Core
    {
        class WindowBase;
    }

    class GUIER_API WindowStyle
    {

    public:

        /**
        * Styles of window.
        *
        */
        enum eStyle
        {
            None = 0,
            TitleBar = 1, ///< Includes border.
            Border = 2,
            Close = 4,
            Minimize = 8,
            Maximize = 16,
            Resize = 32,
            HideInTaskbar = 64,

            Default = 63
        };

        /**
        * Set window styles.
        *
        * @param Bitfield of styles, defined in eStyle.
        *
        */
        WindowStyle * Set(const unsigned int styles);

        /**
        * Enable styles.
        *
        * @param Bitfield of styles, defined in eStyle.
        *
        */
        WindowStyle * Enable(const unsigned int styles);

        /**
        * Disable styles.
        *
        * @param Bitfield of styles, defined in eStyle.
        *
        */
        WindowStyle * Disable(const unsigned int styles);

    private:

        friend class Core::WindowBase; ///< Friend class.

        /**
        * Constructor.
        *
        */
        WindowStyle(Core::WindowBase * windowBase);

        /**
        * Destructor.
        *
        */
        ~WindowStyle();

        /**
        * Copy constructor.
        *
        * @brief No implementation is defined.
        *
        */
        WindowStyle(const WindowStyle & windowStyle);

        Core::WindowBase * const m_pWindowBase; ///< Pointer to parent.

    };

}