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

#include <Guier/Core/Windows/Win32/GdipTexture.hpp>

#ifdef GUIER_PLATFORM_WINDOWS


namespace Guier
{

    namespace Core
    {


        GdipTexture::GdipTexture(const String & filename) :
            m_pBitmap(nullptr)
        {

        }

        GdipTexture::GdipTexture(const void * data, const Vector2i & size, const Format format) :
            m_pBitmap(nullptr)
        {
            BITMAPINFO bmi;
            memset(&bmi, 0, sizeof(bmi));
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = size.x;
            bmi.bmiHeader.biHeight = size.y;
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biCompression = BI_RGB;
            bmi.bmiHeader.biBitCount = 24;

            // Should we really const case this?
           // m_pBitmap = new Gdiplus::Bitmap(&bmi, const_cast<void *>(data));

            //Bitmap(
            /*[in]  INT width,
                [in]  INT height,
                [in]  INT stride,
                [in]  PixelFormat format,
                [in]  BYTE *scan0
                );

                PixelFormat32bppARGB

                */

            const int stride = 4 * size.x;
            const size_t pixelDataSize = 4 * size.x * size.y;
            BYTE * pixelData = new BYTE[pixelDataSize];

            const BYTE * cdata = static_cast<const BYTE *>(data);

            for (int y = 0; y < size.y; y++)
            {
                for (int x = 0; x < size.x; x++)
                {
                    const int pixelPos = (size.x * 4 * y) + (4 * x);
                    /*pixelData[pixelPos] = cdata[pixelPos + 3];
                    pixelData[pixelPos + 1] = cdata[pixelPos];
                    pixelData[pixelPos + 2] = cdata[pixelPos + 1];
                    pixelData[pixelPos + 3] = cdata[pixelPos + 2];*/

                    pixelData[pixelPos] = 255;
                    pixelData[pixelPos + 1] = 255;
                    pixelData[pixelPos + 2] = 0;
                    pixelData[pixelPos + 3] = 0;
                }

            }

            m_pBitmap = new Gdiplus::Bitmap(size.x, size.y, stride, PixelFormat32bppARGB, pixelData);

            delete pixelData;
        }

        GdipTexture::~GdipTexture()
        {
            if (m_pBitmap)
            {
                delete m_pBitmap;
            }
        }

        Texture::Format GdipTexture::GetFormat() const
        {
            return m_Format;
        }

        const Vector2i & GdipTexture::GetSize() const
        {
            return m_Size;
        }

        Gdiplus::Bitmap * GdipTexture::GetBitmap() const
        {
            return m_pBitmap;
        }

    }
}

#endif