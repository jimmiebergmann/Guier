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

#include <Guier/Bitmap.hpp>
#include <Guier/Core/Thirdparty/Lodepng/lodepng.h>
#include <vector>
#include <fstream>
#include <iterator>
#include <memory>

#define NANOSVG_IMPLEMENTATION
#include <Nanosvg/src/nanosvg.h>
#define NANOSVGRAST_IMPLEMENTATION
#include <Nanosvg/src/nanosvgrast.h>

namespace Guier
{

    static const size_t g_DataSize[3] = { 1, 3, 4 }; // Gray, RGB, RGBA
    static LodePNGColorType g_LodeColorType[3] = { LodePNGColorType::LCT_GREY, LodePNGColorType::LCT_RGB, LodePNGColorType::LCT_RGBA};

    Bitmap::Bitmap() :
        m_Format(Format::Gray),
        m_pData(nullptr),
        m_Size(0, 0)
    {

    }

    Bitmap::Bitmap(const String & filename) :
        Bitmap()
    {
        load(filename);
    }

    Bitmap::Bitmap(const String & filename, const Format force) :
        Bitmap()
    {
        load(filename, force);
    }

    Bitmap::Bitmap(const void * memory, const Vector2ui & size, const Format format) :
        Bitmap()
    {
        load(memory, size, format);
    }

    Bitmap::Bitmap(const void * memory, const Vector2ui & size, const Format format, const Format force) :
        Bitmap()
    {
        load(memory, size, format, force);
    }

    Bitmap::~Bitmap()
    {
        if (m_pData)
        {
            delete[] m_pData;
        }
    }

    Bitmap::Bitmap(const Bitmap & bitmap) :
        m_Format(bitmap.m_Format),
        m_pData(nullptr),
        m_Size(bitmap.m_Size)
    {
        const size_t dataSize = bitmap.m_Size.x * bitmap.m_Size.y * g_DataSize[static_cast<size_t>(bitmap.m_Format)];
        m_pData = new unsigned char[dataSize];
        memcpy(m_pData, bitmap.m_pData, dataSize);
    }


    Bitmap & Bitmap::operator = (const Bitmap & bitmap)
    {
        if (m_pData)
        {
            delete m_pData;
        }

        m_Format = bitmap.m_Format;
        m_Size = bitmap.m_Size;

        const size_t dataSize = bitmap.m_Size.x * bitmap.m_Size.y * g_DataSize[static_cast<size_t>(bitmap.m_Format)];
        m_pData = new unsigned char[dataSize];
        memcpy(m_pData, bitmap.m_pData, dataSize);

        return *this;
    }

    bool Bitmap::load(const String & filename, const Format force)
    {
        const std::wstring & wFilename = filename.get();

        if (wFilename.size() < 5)
        {
            return false;
        }

        const wchar_t * compPos = wFilename.data() + wFilename.size() - 4;

        if (wcscmp(compPos, L".png") == 0)
        {
            return loadPng(filename, force);
        }
        else if (wcscmp(compPos, L".svg") == 0)
        {
            return loadSvg(filename, force);
        }

        return false;
    }

    void Bitmap::load(const void * memory, const Vector2ui & dimensions, const Format format)
    {
        load(memory, dimensions, format, format);
    }

    void Bitmap::load(const void * memory, const Vector2ui & dimensions, const Format format, const Format force)
    {
        if (memory == nullptr || dimensions.x == 0 || dimensions.y == 0)
        {
            return;
        }

        copyData(memory, dimensions, format);

        if (format != force)
        {
            convert(force);
        }
    }

    bool Bitmap::loadPng(const String & filename, const Format force)
    {
        // open the file.
        std::ifstream file(filename.get(), std::ios::binary);
        if (file.is_open() == false)
        {
            return false;
        }

        // Stop eating new lines in binary mode!!!
        file.unsetf(std::ios::skipws);

        // get its size:
        std::streampos fileSize;

        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        // reserve capacity
        std::vector<unsigned char> png;
        png.reserve(static_cast<size_t>(fileSize));

        // read the data:
        png.insert(png.begin(),
            std::istream_iterator<unsigned char>(file),
            std::istream_iterator<unsigned char>());

        file.close();

        std::vector<unsigned char> image; //the raw pixels
        unsigned width, height;
        unsigned int error = lodepng::decode(image, width, height, png, g_LodeColorType[static_cast<size_t>(force)], 8U);
        if (error)
        {
            return false;
        }

        const size_t dataSize = width * height * g_DataSize[static_cast<size_t>(force)];
        if (image.size() != dataSize)
        {
            return false;
        }

        m_Format = force;
        m_Size.x = width;
        m_Size.y = height;
        m_pData = new unsigned char[dataSize];
        memcpy(m_pData, image.data(), dataSize);

        return true;
    }

    bool Bitmap::loadSvg(const String & filename, const Format force)
    {
        NSVGimage *image = NULL;
        NSVGrasterizer *rast = NULL;
        //unsigned char* img = NULL;
        int w, h;
        const char* filename2 = "23.svg";

        //std::string stringFilename(filename.get().begin(), filename.get().end());

        printf("parsing %s\n", filename2);
        image = nsvgParseFromFile(filename2/*stringFilename.c_str()*/, "px", 96.0f);
        if (image == NULL) {
            printf("Could not open SVG image.\n");
            goto error;
        }
        w = (int)image->width;
        h = (int)image->height;

        rast = nsvgCreateRasterizer();
        if (rast == NULL) {
            printf("Could not init rasterizer.\n");
            goto error;
        }

        /*img = static_cast<unsigned char*>(malloc(w*h * 4));
        if (img == NULL) {
            printf("Could not alloc image buffer.\n");
            goto error;
        }*/

        m_pData = new unsigned char[w*h * 4];

        printf("rasterizing image %d x %d\n", w, h);
        nsvgRasterize(rast, image, 0, 0, 1, m_pData, w, h, w * 4);

        m_Format = Bitmap::Format::RGBA;
        m_Size.x = w;
        m_Size.y = h;

    error:
        nsvgDeleteRasterizer(rast);
        nsvgDelete(image);

        return true;
    }

    void Bitmap::unload()
    {
        if (m_pData)
        {
            delete[] m_pData;
            m_pData = nullptr;
        }
        m_Size = Vector2ui(0, 0);
    }

    Bitmap::Format Bitmap::format() const
    {
        return m_Format;
    }

    const Vector2ui & Bitmap::size() const
    {
        return m_Size;
    }

    const size_t Bitmap::dataSize() const
    {
        return static_cast<size_t>(m_Size.x) * static_cast<size_t>(m_Size.y) * g_DataSize[static_cast<size_t>(m_Format)];
    }

    unsigned char * Bitmap::data() const
    {
        return m_pData;
    }

    void Bitmap::convert(const Format format)
    {
        if (m_pData == nullptr || m_Size.x == 0 || m_Size.y == 0)
        {
            return;
        }

        switch (m_Format)
        {
        case Format::Gray:
            switch (format)
            {
            case Format::RGB:
                convertFrom_Gray_to_RGB();
                break;
            case Format::RGBA:
                convertFrom_Gray_to_RGBA();
                break;
            default:
                throw std::runtime_error("Converting bitmap to unkown format.");
                break;
            }
            break;
        case Format::RGB:
            switch (format)
            {
            case Format::Gray:
                convertFrom_RGB_to_Gray();
                break;
            case Format::RGBA:
                convertFrom_RGB_to_RGBA();
                break;
            default:
                throw std::runtime_error("Converting bitmap to unkown format.");
                break;
            }
            break;
        case Format::RGBA:
            switch (format)
            {
            case Format::Gray:
                convertFrom_RGBA_to_Gray();
                break;
            case Format::RGB:
                convertFrom_RGBA_to_RGB();
                break;
            default:
                throw std::runtime_error("Converting bitmap to unkown format.");
                break;
            }
            break;
        default:
            throw std::runtime_error("Converting bitmap from unkown format.");
            break;
        }
    }

    void Bitmap::copyData(const void * memory, const Vector2ui & size, const Format format)
    {
        if (m_pData)
        {
            unload();
        }

        const size_t dataSize = size.x * size.y * g_DataSize[static_cast<size_t>(format)];

        m_Format = format;
        m_pData = new unsigned char[dataSize];
        m_Size = size;
        memcpy(m_pData, memory, dataSize);
    }

    void Bitmap::convertFrom_Gray_to_RGB()
    {
        const size_t newDataSize = m_Size.x * m_Size.y * 3;
        unsigned char * pNewData = new unsigned char[newDataSize];

        for (unsigned int y = 0; y < m_Size.y; y++)
        {
            for (unsigned int x = 0; x < m_Size.x; x++)
            {
                const unsigned int newPos = (y * m_Size.x * 3) + (x * 3);
                const unsigned int oldPos = (y * m_Size.x) + x;

                pNewData[newPos]     = m_pData[oldPos];
                pNewData[newPos + 1] = m_pData[oldPos];
                pNewData[newPos + 2] = m_pData[oldPos];
            }
        }

        delete m_pData;
        m_pData = pNewData;
        m_Format = Format::RGB;
    }
    void Bitmap::convertFrom_Gray_to_RGBA()
    {
        const size_t newDataSize = m_Size.x * m_Size.y * 4;
        unsigned char * pNewData = new unsigned char[newDataSize];

        for (unsigned int y = 0; y < m_Size.y; y++)
        {
            for (unsigned int x = 0; x < m_Size.x; x++)
            {
                const unsigned int newPos = (y * m_Size.x * 4) + (x * 4);
                const unsigned int oldPos = (y * m_Size.x) + x;

                pNewData[newPos]     = m_pData[oldPos];
                pNewData[newPos + 1] = m_pData[oldPos];
                pNewData[newPos + 2] = m_pData[oldPos];
                pNewData[newPos + 3] = 255;
            }
        }

        delete m_pData;
        m_pData = pNewData;
        m_Format = Format::RGBA;
    }
    void Bitmap::convertFrom_RGB_to_Gray()
    {
        const size_t newDataSize = m_Size.x * m_Size.y;
        unsigned char * pNewData = new unsigned char[newDataSize];

        for (unsigned int y = 0; y < m_Size.y; y++)
        {
            for (unsigned int x = 0; x < m_Size.x; x++)
            {
                const unsigned int newPos = (y * m_Size.x) + x;
                const unsigned int oldPos = (y * m_Size.x * 3) + (x * 3);

                // Compute Clinear = 0.2126 R + 0.7152 G + 0.0722 B

                float gray = 0.2126f * static_cast<float>(m_pData[oldPos]) + 
                             0.7152f * static_cast<float>(m_pData[oldPos + 1]) +
                             0.0722f * static_cast<float>(m_pData[oldPos + 2]);

                pNewData[newPos] = static_cast<unsigned char>(gray);                
            }
        }

        delete m_pData;
        m_pData = pNewData;
        m_Format = Format::Gray;
    }
    void Bitmap::convertFrom_RGB_to_RGBA()
    {
        const size_t newDataSize = m_Size.x * m_Size.y * 4;
        unsigned char * pNewData = new unsigned char[newDataSize];

        for (unsigned int y = 0; y < m_Size.y; y++)
        {
            for (unsigned int x = 0; x < m_Size.x; x++)
            {
                const unsigned int newPos = (y * m_Size.x * 4) + (x * 4);
                const unsigned int oldPos = (y * m_Size.x * 3) + (x * 3);

                pNewData[newPos]     = m_pData[oldPos];
                pNewData[newPos + 1] = m_pData[oldPos + 1];
                pNewData[newPos + 2] = m_pData[oldPos + 2];
                pNewData[newPos + 3] = 255;
            }
        }

        delete m_pData;
        m_pData = pNewData;
        m_Format = Format::RGBA;
    }
    void Bitmap::convertFrom_RGBA_to_Gray()
    {
        const size_t newDataSize = m_Size.x * m_Size.y;
        unsigned char * pNewData = new unsigned char[newDataSize];

        for (unsigned int y = 0; y < m_Size.y; y++)
        {
            for (unsigned int x = 0; x < m_Size.x; x++)
            {
                const unsigned int newPos = (y * m_Size.x) + x;
                const unsigned int oldPos = (y * m_Size.x * 4) + (x * 4);

                // Compute Clinear = 0.2126 R + 0.7152 G + 0.0722 B

                float gray = 0.2126f * static_cast<float>(m_pData[oldPos]) +
                             0.7152f * static_cast<float>(m_pData[oldPos + 1]) +
                             0.0722f * static_cast<float>(m_pData[oldPos + 2]);

                pNewData[newPos] = static_cast<unsigned char>(gray);
            }
        }

        delete m_pData;
        m_pData = pNewData;
        m_Format = Format::Gray;
    }
    void Bitmap::convertFrom_RGBA_to_RGB()
    {
        const size_t newDataSize = m_Size.x * m_Size.y * 3;
        unsigned char * pNewData = new unsigned char[newDataSize];

        for (unsigned int y = 0; y < m_Size.y; y++)
        {
            for (unsigned int x = 0; x < m_Size.x; x++)
            {
                const unsigned int newPos = (y * m_Size.x * 3) + (x * 3);
                const unsigned int oldPos = (y * m_Size.x * 4) + (x * 4);

                pNewData[newPos]     = m_pData[oldPos];
                pNewData[newPos + 1] = m_pData[oldPos + 1];
                pNewData[newPos + 2] = m_pData[oldPos + 2];
            }
        }

        delete m_pData;
        m_pData = pNewData;
        m_Format = Format::RGB;
    }


}