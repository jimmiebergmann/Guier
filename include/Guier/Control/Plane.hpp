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
#include <list>

namespace Guier
{

    class VerticalGrid;

    /**
    * Base class of controls.
    */
    class GUIER_API Plane : public ParentControl
    {

    public:

        /**
        * Constructor.
        *
        * @param parent         Parent object to add this control to.
        * @param size           Size of button.
        * @param position       Position of button. {0,0} by default.
        *
        * @throw std::runtime_error If parent is nullptr.
        *
        */
        Plane(Parent * parent, const Vector2i & size = Size::Fit);
        Plane(Parent * parent, const Vector2i & position, const Vector2i & size);

        /**
        * Destructor.
        *
        */
        ~Plane();

        /**
        * Get type of controller.
        *
        */
        virtual unsigned int type() const;

    private:

        /**
        * Internal function, executed by Parent.
        *
        */
        virtual bool addChild(Control * child, const Index & index);
        virtual bool removeChild(Control * child);
        virtual Control * removeChild(const Index & index);

        /**
        * Render the control.
        *
        */
        virtual void render(Core::Renderer::Interface * renderInterface, const Vector2i & position, const Vector2i & size);

        std::list<Control *>       m_Childs;           ///< Childs of plane.

    };

}