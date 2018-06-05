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

#include <Guier/Vector2.hpp>
#include <Guier/String.hpp>

namespace Guier
{

    class GUIER_API Bitmap
    {

    public:

        /**
        * Enumerator of different bitmap formats.
        *
        */
        enum class Format : size_t
        {
            Gray,
            RGB,
            RGBA
        };

        /**
        * Constructors.
        *
        * @param filename       Path of bitmap file to load.
        * @param force          Force the data to be stored in a specific format. Alpha channel is always 255 if original format is missing alpha channel.
        * @param memory         Pointer to data in memory to copy.
        * @param dimensions     Dimensions of bitmap data.
        * @param format         Format of bitmap data. If passing filename, the content will be converted to the passed format.
        *
        */
        Bitmap();
        Bitmap(const String & filename);
        Bitmap(const String & filename, const Format force);
        Bitmap(const void * memory, const Vector2ui & dimensions, const Format format);
        Bitmap(const void * memory, const Vector2ui & dimensions, const Format format, const Format force);

        /**
        * Destructor.
        *
        */
        ~Bitmap();

        /**
        * Load bitmap file or from memory.
        *
        * @param filename       Path of bitmap file to load.
        * @param force          Force the data to be stored in a specific format. Alpha channel is always 255 if original format is missing alpha channel.
        * @param memory         Pointer to data in memory to copy.
        * @param dimensions     Dimensions of bitmap data.
        * @param format         Format of bitmap data. If passing filename, the content will be converted to the passed format.
        *
        * @return true if filename were found and the file is a vaild bitmap file, else false.
        *
        */
        bool load(const String & filename, const Format force = Format::RGBA);
        void load(const void * memory, const Vector2ui & dimensions, const Format format);
        void load(const void * memory, const Vector2ui & dimensions, const Format format, const Format force);

        /**
        * Unload bitmap.
        *
        * @brief The format is untouched.
        *
        */
        void unload();

        /**
        * Get format.
        *
        */
        Format format() const;

        /**
        * Get dimensions of bitmap.
        *
        */
        const Vector2ui & dimensions() const;

        /**
        * Get data size of bitmap.
        *
        */
        const size_t size() const;

        /**
        * Get data of bitmap.
        *
        */
        unsigned char * data() const;

        /**
        * Convert the internal data to the given format.
        *
        */
        void convert(const Format format);

    private:

        /**
        * Copy data from memory.
        *
        */
        void copyData(const void * memory, const Vector2ui & dimensions, const Format format);

        /**
        * Convert functions
        *
        */
        void convertFrom_Gray_to_RGB();
        void convertFrom_Gray_to_RGBA();
        void convertFrom_RGB_to_Gray();
        void convertFrom_RGB_to_RGBA();
        void convertFrom_RGBA_to_Gray();
        void convertFrom_RGBA_to_RGB();

        Format          m_Format;
        unsigned char * m_pData;
        Vector2ui       m_Dimensions;

    };

}