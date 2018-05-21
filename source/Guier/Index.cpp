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

#include <Guier/Index.hpp>
#include <limits>


namespace Guier
{

    static const int g_First = std::numeric_limits<int>::min();
    static const int g_Last = std::numeric_limits<int>::max();

    const Index Index::First(g_First);
    const Index Index::Last(g_Last);

    Index::Index(const int index) :
        m_Type(SingleInteger),
        m_X(index),
        m_Y(0)
    {
        
    }

    Index::Index(const int x, const int y) :
        m_Type(DoubleInteger),
        m_X(x),
        m_Y(y)
    {

    }

    Index::Index(const Vector2i & index) :
        m_Type(DoubleInteger),
        m_X(index.x),
        m_Y(index.y)
    {
    }

    Index::Index(const Index & index) :
        m_Type(index.m_Type),
        m_X(index.m_X),
        m_Y(index.m_Y)
    {

    }

    Index::~Index()
    {

    }

    int Index::GetSingleInteger() const
    {
        return m_X;
    }

    Vector2i Index::GetDoubleInteger() const
    {
        switch (m_Type)
        {
        case SingleInteger:
            return Vector2i(m_X, 0);
        case DoubleInteger:
            return Vector2i(m_X, m_Y);
        default:
            break;
        }

        return { 0, 0 };
    }

    bool Index::IsFirst() const
    {
        return m_X == g_First;
    }

    bool Index::IsLast() const
    {
        return m_X == g_Last;
    }

    bool Index::operator == (const Index & index) const
    {
        switch (m_Type)
        {
            case SingleInteger:
            {
                return m_X == index.m_X;
            }
            break;
            case DoubleInteger:
            {
                return m_X == index.m_X && m_Y == index.m_Y;
            }
            break;
        default:
            break;
        }

        return false;
    }

    bool Index::operator != (const Index & index) const
    {
        return !(*this == index);
    }

}