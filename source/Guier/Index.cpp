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

    const Index Index::First(std::numeric_limits<int>::min());
    const Index Index::Last(std::numeric_limits<int>::max());

    Index::Index(const int index) :
        m_Type(SingleInteger)
    {
        m_Value.SingleValue = index;
    }

    Index::Index(const int x, const int y) :
        m_Type(DoubleInteger)
    {
        m_Value.DoubleValue = new Vector2i(x, y);
    }

    Index::Index(const Vector2i & index) :
        m_Type(DoubleInteger)
    {
        m_Value.DoubleValue = new Vector2i(index);
    }

    Index::~Index()
    {
        switch (m_Type)
        {
        case DoubleInteger:
            delete m_Value.DoubleValue;
        default:
            break;
        }
    }

    int Index::GetSingleInteger() const
    {
        switch (m_Type)
        {
        case SingleInteger:
            return m_Value.SingleValue;
        case DoubleInteger:
            return (m_Value.DoubleValue->x * m_Value.DoubleValue->y) + m_Value.DoubleValue->x;
        default:
            break;
        }

        return 0;
    }

    Vector2i Index::GetDoubleInteger() const
    {
        switch (m_Type)
        {
        case SingleInteger:
            return Vector2i(m_Value.SingleValue, m_Value.SingleValue);
        case DoubleInteger:
            return *m_Value.DoubleValue;
        default:
            break;
        }

        return { 0, 0 };
    }

    bool Index::operator == (const Index & index) const
    {
        switch (m_Type)
        {
        case SingleInteger:
            return m_Value.SingleValue == index.GetSingleInteger();
        case DoubleInteger:
            return *m_Value.DoubleValue == index.GetDoubleInteger();
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