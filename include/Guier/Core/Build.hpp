#pragma once

// Define the platform
#if defined( _WIN32 ) || defined( __WIN32__ ) || defined( _WIN64 ) || defined( __WIN64__ )
    #define GUIER_PLATFORM_WINDOWS
#elif defined( linux ) || defined( __linux )
    #define GUIER_PLATFORM_LINUX
#else
    #error Unkown build platform.
#endif

// Define the build type ( release / debug )
#if defined( NDEBUG ) || !defined( _DEBUG )
#define GUIER_BUILD_RELEASE
#else
#define GUIER_BUILD_DEBUG
#endif

// Define BIT_API
// If this build is not a static library build
#ifndef GUIER_STATIC
    // Turn off microsoft vsc warning
    #ifdef _MSC_VER
        #pragma warning(disable : 4251)
    #endif
    // Define as export or import depending on if BIT_EXPORTS is defined
    #ifdef GUIER_PLATFORM_WINDOWS
        #ifdef GUIER_API_EXPORTS
            #define GUIER_API __declspec(dllexport)
        #else
            #define GUIER_API __declspec(dllimport)
        #endif
    #else
        #define GUIER_API
    #endif
#else
    // Define it as nothing
    #define GUIER_API
#endif

#include <exception>

// Macro for creating unique control IDs.
#define GUIER_CUSTOM_CONTROLLER_ID(name) static const unsigned int TypeId = \
    static_cast<unsigned int>(Guier::Control::Types::Custom) + \
    static_cast<unsigned int>(__COUNTER__)

#define GUIER_SOFTWARE_RENDERER 0
#define GUIER_HARDWARE_RENDERER 1



/**
* Default constructor.
*
*/

#define GUIER_DEFAULT_SKIN ///< Comment out this line to remove default skin from build.

// Select the default renderer type.
// Options:
// - GUIER_SOFTWARE_RENDERER
// - GUIER_HARDWARE_RENDERER
#define GUIER_DEFAULT_RENDERER GUIER_SOFTWARE_RENDERER