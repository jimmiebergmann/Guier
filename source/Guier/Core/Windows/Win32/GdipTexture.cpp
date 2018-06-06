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

#include <Guier/Bitmap.hpp>
#include <iostream>

namespace Guier
{

    namespace Core
    {

        static int calcExtraBytes(unsigned int lineBytes)
        {
            const int extraBytesMod = lineBytes % 4;
            int extraBytes = 0;
            if (extraBytesMod)
            {
                extraBytes = 4 - extraBytesMod;
            }

            return extraBytes;
        }

        static BYTE * createPixelDataGray(Bitmap * bitmap, INT & stride, Gdiplus::PixelFormat & pixelFormat)
        {
            const unsigned char * pBitmapData = bitmap->data();
            const Vector2ui & size = bitmap->size();

            stride = 2 * size.x;
            pixelFormat = PixelFormat16bppGrayScale;

            const size_t dataSize = stride * size.y;
            BYTE * pData = new BYTE[dataSize];

            for (int y = 0; y < size.y; y++)
            {
                for (int x = 0; x < size.x; x++)
                {
                    const unsigned int bitmapPixelPos = (size.x * y) + x;
                    const unsigned int pixelPos = (size.x * 2 * y) + (2 * x);

                    unsigned short value = static_cast<unsigned short>(pBitmapData[bitmapPixelPos]) * 255;
                    memcpy(pData + pixelPos, &value, 2);
                }
            }

            return pData;
        }

        static BYTE * createPixelDataRGB(Bitmap * bitmap, INT & stride, Gdiplus::PixelFormat & pixelFormat)
        {
            const unsigned char * pBitmapData = bitmap->data();
            const Vector2ui & size = bitmap->size();

            stride = 3 * size.x;

            unsigned int extraBytes = calcExtraBytes(stride);
            stride += extraBytes;
            
            pixelFormat = PixelFormat24bppRGB;

            const size_t dataSize = stride * size.y;
            BYTE * pData = new BYTE[dataSize];

            for (int y = 0; y < size.y; y++)
            {
                const unsigned int curPosY = stride * y;

                for (int x = 0; x < size.x; x++)
                {
                    const unsigned int pixelPos = curPosY + (3 * x);
                    const unsigned int bitmapPixelPos = (size.x * 3 * y) + (3 * x);

                    pData[pixelPos]     = pBitmapData[bitmapPixelPos + 2];
                    pData[pixelPos + 1] = pBitmapData[bitmapPixelPos + 1];
                    pData[pixelPos + 2] = pBitmapData[bitmapPixelPos ];
                }
            }

            return pData;
        }

        static BYTE * createPixelDataARGB(Bitmap * bitmap, INT & stride, Gdiplus::PixelFormat & pixelFormat)
        {
            const unsigned char * pBitmapData = bitmap->data();
            const Vector2ui & size = bitmap->size();

            stride = 4 * size.x;

           /* unsigned int extraBytes = calcExtraBytes(stride);
            stride += extraBytes;*/

            pixelFormat = PixelFormat32bppARGB;

            const size_t dataSize = stride * size.y;
            BYTE * pData = new BYTE[dataSize];

            for (int y = 0; y < size.y; y++)
            {
                const unsigned int curPosY = stride * y;

                for (int x = 0; x < size.x; x++)
                {
                    const unsigned int pixelPos = curPosY + (4 * x);
                    const unsigned int bitmapPixelPos = (size.x * 4 * y) + (4 * x);

                    pData[pixelPos]     = pBitmapData[bitmapPixelPos + 2];
                    pData[pixelPos + 1] = pBitmapData[bitmapPixelPos + 1];
                    pData[pixelPos + 2] = pBitmapData[bitmapPixelPos + 0];

                    pData[pixelPos + 3] = pBitmapData[bitmapPixelPos + 3];
                }
            }

            return pData;

           /* const unsigned char * pBitmapData = bitmap->data();
            const Vector2ui & size = bitmap->size();

            stride = 4 * size.x;
            pixelFormat = PixelFormat32bppARGB;

            const size_t dataSize = stride * size.y;
            BYTE * pData = new BYTE[dataSize];

            for (int y = 0; y < size.y; y++)
            {
                for (int x = 0; x < size.x; x++)
                {
                    const unsigned int pixelPos = (size.x * 4 * y) + (4 * x);

                    pData[pixelPos]     = pBitmapData[pixelPos + 3];
                    pData[pixelPos + 1] = pBitmapData[pixelPos];
                    pData[pixelPos + 2] = pBitmapData[pixelPos + 1];
                    pData[pixelPos + 3] = pBitmapData[pixelPos + 2];

                   // std::cout << (int)pData[pixelPos] << " " << (int)pData[pixelPos+1] << " " << (int)pData[pixelPos+2] << " " << (int)pData[pixelPos+3] << std::endl;
                }
                //std::cout << std::endl;
            }

            return pData;*/
        }

        static BYTE * createPixelData(Bitmap * bitmap, INT & stride, Gdiplus::PixelFormat & pixelFormat)
        {
            //PixelFormat16bppGrayScale - 16 bits per pixel, grayscale.
            //PixelFormat24bppRGB       - 8 bits each are used for the red, green, and blue components.
            //PixelFormat32bppARGB      - 8 bits each are used for the alpha, red, green, and blue components.

            switch (bitmap->format())
            {
            case Bitmap::Format::Gray:
                return createPixelDataGray(bitmap, stride, pixelFormat);
                break;
            case Bitmap::Format::RGB:
                return createPixelDataRGB(bitmap, stride, pixelFormat);
                break;
            case Bitmap::Format::RGBA:
                return createPixelDataARGB(bitmap, stride, pixelFormat);
                break;
            default:
                return nullptr;
                break;
            }

            return nullptr;
        }

        GdipTexture::GdipTexture() :
            m_pBitmap(nullptr),
            m_Size(0,0),
            m_Format(Bitmap::Format::Gray)
        {

        }

        GdipTexture::~GdipTexture()
        {
            if (m_pBitmap)
            {
                delete m_pBitmap;
            }
        }

        void GdipTexture::load(Bitmap * bitmap)
        {
            const Vector2ui & size = bitmap->size();
            INT stride = 0;
            Gdiplus::PixelFormat pixelFormat;

            BYTE * pixelData = createPixelData(bitmap, stride, pixelFormat);
            if (pixelData == nullptr)
            {
                return;
            }

            m_Format = bitmap->format();
            m_Size = size;
            m_pBitmap = new Gdiplus::Bitmap(size.x, size.y, stride, pixelFormat, pixelData);
            //delete pixelData;
        }

        Bitmap::Format GdipTexture::format() const
        {
            return m_Format;
        }

        const Vector2ui & GdipTexture::size() const
        {
            return m_Size;
        }

        Gdiplus::Bitmap * GdipTexture::bitmap() const
        {
            return m_pBitmap;
        }

    }
}

#endif