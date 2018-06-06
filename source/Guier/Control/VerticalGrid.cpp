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

#include <Guier/Control/VerticalGrid.hpp>

namespace Guier
{

    VerticalGrid::VerticalGrid(Parent * parent, const Index & index, const Vector2i & size) :
        ParentControl(parent, index, size)
    {

    }

    VerticalGrid::VerticalGrid(Parent * parent, const Vector2i & size, const Index & index) :
        ParentControl(parent, index, size)
    {

    }

    VerticalGrid::~VerticalGrid()
    {

    }

    unsigned int VerticalGrid::type() const
    {
        return static_cast<unsigned int>(Types::VerticalGrid);
    }

    size_t VerticalGrid::count() const
    {
        return 0;
    }

    bool VerticalGrid::addChild(Control * child, const Index & index)
    {

        return false;
    }

    bool VerticalGrid::removeChild(Control * child)
    {

        return false;
    }

    Control * VerticalGrid::removeChild(const Index & index)
    {

        return nullptr;
    }

    void VerticalGrid::render(Core::Renderer::Interface * renderInterface, const Vector2i & position, const Vector2i & size)
    {

    }

}