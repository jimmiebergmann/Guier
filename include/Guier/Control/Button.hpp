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

#include <Guier/Core/Control.hpp>
#include <Guier/String.hpp>

namespace Guier
{

    class VerticalGrid;

    /**
    * Base class of controls.
    */
    class GUIER_API Button : public Core::Control, public Core::ControlParent::VerticalGrid
    {

    public:
            
        /**
        * Constructor.
        *
        * @param parent         Parent object to add this control to.
        * @param parentIndex    Index of parents container where to control should be added to.
        * @param label          Attach label automatically if length of label != 0.
        * @param size           Size of button. Size::Fit by default.
        *
        */
        Button(Core::ControlParent * parent, const String & label = L"");
        Button(Core::ControlParent * parent, const Index & parentIndex, const String & label = L"");
        Button(Core::ControlParent * parent, const Vector2i & size, const String & label = L"");
        Button(Core::ControlParent * parent, const Vector2i & size, const Index & parentIndex, const String & label = L"");
        
        /**
        * Destructor.
        *
        */
        ~Button();

    public:

        /**
        * Internal function, executed by ControlParent.
        *
        */
        virtual bool AddChild(Core::Control * control, const Index & index);
        virtual bool RemoveChild(Control * control);
        virtual Core::Control * RemoveChild(const Index & index);

        void CreateText(const String & label);

        Vector2i        m_Size;             ///< Size of the button.

    };

}