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

namespace Guier
{

    /**
    * Vertical grid controller.
    *
    */
    class GUIER_API VerticalGrid : public Control, public Parent
    {

    public:

        /**
        * Constructor.
        *
        * @param parent         Parent object to add this control to.
        * @param index          Index of parents container where to control should be added to.
        * @param size           Size of button. Size::Fit by default.
        *
        * @throw std::runtime_error If parent is nullptr.
        *
        */
        VerticalGrid(Parent * parent, const Index & index = Index::Last, const Vector2i & size = Size::Fit);
        VerticalGrid(Parent * parent, const Vector2i & size, const Index & index = Index::Last);

        /**
        * Destructor.
        *
        */
        ~VerticalGrid();

        /**
        * Get type of controller.
        *
        */
        virtual unsigned int Type() const;

        /**
        * Get child count.
        *
        */
        size_t Count() const;

    private:

        virtual bool AddChild(Control * child, const Index & index);
        virtual bool RemoveChild(Control * child);
        virtual Control * RemoveChild(const Index & index);

        /**
        * Render the control.
        *
        */
        virtual void Render(Core::RenderInterface * renderInterface, const Core::RenderArea & renderArea);

    };

}