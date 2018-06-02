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
#include <Guier/String.hpp>

namespace Guier
{

    /**
    * Base class of controls.
    */
    class GUIER_API Text : public Control
    {

    public:

        /**
        * Constructor.
        *
        * @param text   Content of text.
        *
        * @throw std::runtime_error If parent is nullptr.
        *
        */
        Text(Parent * parent, const String & content = L"");
        Text(Parent * parent, const Index & index, const String & content = L"");

        /**
        * Destructor.
        *
        */
        ~Text();

        /**
        * Get type of controller.
        *
        */
        virtual unsigned int Type() const;

        /**
        * Get/set content of text.
        *
        */
        const String & Content() const;
        void Content(const String & content);

    private:

        /**
        * Render the control.
        *
        */
        virtual void Render(Core::Renderer::Interface * renderInterface);

        String m_Content;    ///< Text content.

    };

}