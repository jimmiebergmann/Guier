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


#include <Guier/Core/Windows/Win32/Win32WindowImpl.hpp>

#ifdef GUIER_PLATFORM_WINDOWS

#include <Guier/Core/WindowBase.hpp>
#include <Guier/Control/Plane.hpp>

namespace Guier
{

    namespace Core
    {

        // Helper functions
        static std::wstring StringToWideString(const std::string & string)
        {
            int len;
            int slength = static_cast<int>(string.length() + 1);
            len = MultiByteToWideChar(CP_ACP, 0, string.c_str(), slength, 0, 0);
            wchar_t* buf = new wchar_t[len];
            MultiByteToWideChar(CP_ACP, 0, string.c_str(), slength, buf, len);
            std::wstring r(buf);
            delete[] buf;
            return r;
        }

        static unsigned int ProcessStyle(const unsigned int style)
        {
            unsigned int newStyle = style;

            if (newStyle & static_cast<unsigned int>(Window::Style::TitleBar))
            {
                newStyle |= static_cast<unsigned int>(Window::Style::Border);
            }

            return newStyle;
        }

        static DWORD GetWin32Style(const unsigned int styles)
        {
            DWORD ret = 0;

            if (styles & static_cast<DWORD>(Window::Style::TitleBar))
            {
                ret |= WS_CAPTION | WS_SYSMENU;
            }

            if (styles & static_cast<DWORD>(Window::Style::Border))
            {
                ret |= WS_BORDER;
            }

            if (styles & static_cast<DWORD>(Window::Style::Minimize))
            {
                ret |= WS_MINIMIZEBOX;
            }

            if (styles & static_cast<DWORD>(Window::Style::Maximize))
            {
                ret |= WS_MAXIMIZEBOX;
            }

            if (styles & static_cast<DWORD>(Window::Style::Resize))
            {
                ret |= WS_SIZEBOX;
            }

            return ret;
        }

        static DWORD GetWin32ExtendedStyle(const unsigned int styles)
        {
            DWORD ret = WS_EX_APPWINDOW;

            if (!(styles & static_cast<DWORD>(Window::Style::Taskbar)))
            {
                ret = WS_EX_NOACTIVATE;
            }

            return ret;
        }


        // Win32 implementation.
        Win32WindowImpl::Win32WindowImpl(WindowBase * window, Skin * skin, const Vector2i & size, const String & title, const std::initializer_list<Window::Style> & styles) :
            m_pWindow(window),
            m_pPlane(nullptr),
            m_pSkin(skin),
            m_pRenderer(nullptr),
            m_Size(size),
            m_Position(-1, -1),
            m_Title(title),
            m_Styles(static_cast<unsigned int>(Window::Style::Default)),
            m_DPI(0),
            m_WindowHandle(0),
            m_DeviceContextHandle(0),
            m_Win32Style(0),
            m_Win32ExtendedStyle(0),
            m_WindowClassName(L"")
        {
            
        }

        Win32WindowImpl::~Win32WindowImpl()
        {
            Manager.UnloadWindowImpl(this);

            HINSTANCE Hinstance = GetModuleHandle(NULL);

            // Destroy the window
            if (m_WindowHandle)
            {
                // Release the device context
                if (m_DeviceContextHandle)
                {
                    ReleaseDC(m_WindowHandle, m_DeviceContextHandle);
                }

                DestroyWindow(m_WindowHandle);
            }

            // Unregister the window class
            if (m_WindowClassName.size())
            {
                UnregisterClass(m_WindowClassName.c_str(), Hinstance);
            }

            if (m_pPlane)
            {
                delete m_pPlane;
            }

            if (m_pRenderer)
            {
                delete m_pRenderer;
            }
        }

        void Win32WindowImpl::LoadImplementation()
        {
            Manager.LoadWindowImpl(this);
        }

        const Vector2i & Win32WindowImpl::Size() const
        {
            return m_Size;
        }

        void Win32WindowImpl::Size(const Vector2i & size)
        {
            m_Size = size;
        }

        const Vector2i & Win32WindowImpl::Position() const
        {
            return m_Position;
        }

        void Win32WindowImpl::Position(const Vector2i & position)
        {
            m_Position = position;
        }

        const String & Win32WindowImpl::Title() const
        {
            return m_Title;
        }

        void Win32WindowImpl::Title(const String & title)
        {
            m_Title = title;
        }

        void Win32WindowImpl::SetStyle(const Window::Style style)
        {
            SetStyleInternal(ProcessStyle(static_cast<unsigned int>(style) ));
        }

        void Win32WindowImpl::SetStyle(const std::initializer_list<Window::Style> & styles)
        {
            unsigned int style = 0;
            for (auto it = styles.begin(); it != styles.end(); it++)
            {
                style += static_cast<unsigned int>(*it);
            }

            SetStyleInternal(ProcessStyle(static_cast<unsigned int>(style)));
        }

        void Win32WindowImpl::AddStyle(const Window::Style style)
        {
            SetStyleInternal(ProcessStyle(m_Styles | static_cast<unsigned int>(style)));
        }

        void Win32WindowImpl::AddStyle(const std::initializer_list<Window::Style> & styles)
        {
            unsigned int style = 0;
            for (auto it = styles.begin(); it != styles.end(); it++)
            {
                style += static_cast<unsigned int>(*it);
            }

            SetStyleInternal(ProcessStyle(m_Styles | static_cast<unsigned int>(style)));
        }

        void Win32WindowImpl::RemoveStyle(const Window::Style style)
        {
            SetStyleInternal(ProcessStyle(m_Styles & (~static_cast<unsigned int>(style) ) ));
        }

        void Win32WindowImpl::RemoveStyle(const std::initializer_list<Window::Style> & styles)
        {
            unsigned int style = 0;
            for (auto it = styles.begin(); it != styles.end(); it++)
            {
                style += static_cast<unsigned int>(*it);
            }

            SetStyleInternal(ProcessStyle(m_Styles & (~static_cast<unsigned int>(style))));
        }

        void Win32WindowImpl::Show()
        {

        }

        void Win32WindowImpl::Hide()
        {
        }

        void Win32WindowImpl::Minimize()
        {
        }

        void Win32WindowImpl::Maximize()
        {
        }

        void Win32WindowImpl::Close()
        {
        }

        bool Win32WindowImpl::Add(Control * child, const Index & index)
        {
            if (m_pPlane)
            {
                return m_pPlane->Add(child, index);
            }

            return false;
        }

        bool Win32WindowImpl::Remove(Control * child)
        {
            return m_pPlane->Remove(child);
        }

        Control * Win32WindowImpl::Remove(const Index & index)
        {
            return m_pPlane->Remove(index);
        }

        void Win32WindowImpl::Load()
        {
            // Get default styles.
            m_Styles = ProcessStyle(m_Styles);
            m_Win32Style = GetWin32Style(m_Styles);
            m_Win32ExtendedStyle = GetWin32ExtendedStyle(m_Styles);

            // Generate class name.
            GUID guid = { 0 };
            const size_t guidArraySize = 64;
            wchar_t guidArray[guidArraySize] = { 0 };
            CoCreateGuid(&guid);
            StringFromGUID2(guid, guidArray, guidArraySize);
            std::wstring className = L"guier_" + std::wstring(guidArray);

            // Create a window class(WNDCLASS - win32)
            WNDCLASS winClass;
            HINSTANCE winInstance = GetModuleHandle(NULL); // Grab any old handle
            winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
            winClass.lpfnWndProc = (WNDPROC)Win32WindowImpl::WindowProcStatic;
            winClass.cbClsExtra = 0;
            winClass.cbWndExtra = 0;
            winClass.hInstance = winInstance;
            winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
            winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
            winClass.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
            winClass.lpszClassName = className.c_str();
            winClass.lpszMenuName = NULL;

            // Register the window class
            if (!RegisterClass(&winClass))
            {
                throw std::runtime_error("Failed to register Window class.");
                return;
            }
            // The class is now registered.
            m_WindowClassName = className;

            // Apply the style
            RECT windowRect;
            windowRect.left = static_cast<LONG>(0);
            windowRect.right = static_cast<LONG>(m_Size.x);
            windowRect.top = static_cast<LONG>(0);
            windowRect.bottom = static_cast<LONG>(m_Size.y);

            AdjustWindowRectEx(&windowRect, m_Win32Style, FALSE, m_Win32ExtendedStyle);

            // Let's create the window.
            m_WindowHandle = CreateWindowEx(
                m_Win32ExtendedStyle,
                className.c_str(),
                m_Title.Get().c_str(),

                WS_CLIPSIBLINGS |
                WS_CLIPCHILDREN |
                m_Win32Style,
                CW_USEDEFAULT,
                CW_USEDEFAULT,

                windowRect.right - windowRect.left,
                windowRect.bottom - windowRect.top,
                NULL,
                NULL,
                winInstance,
                this);

            // Did the window creation succeed?
            if (m_WindowHandle == NULL)
            {
                throw std::runtime_error("Failed to create window.");
            }

            // Get the device context
            m_DeviceContextHandle = GetDC(m_WindowHandle);
            m_DPI = GetDpiForWindow(m_WindowHandle);
            m_pRenderer = new GdipRenderer(m_WindowHandle, m_pSkin);

            // Create plane control
            m_pPlane = new Plane(m_pWindow);
            

            ShowWindow(m_WindowHandle, SW_RESTORE);
            SetForegroundWindow(m_WindowHandle);
            SetFocus(m_WindowHandle);
        }

        void Win32WindowImpl::SetStyleInternal(const unsigned int styles)
        {
            const unsigned int oldStyle = m_Styles;
            m_Styles = ProcessStyle(styles);
            const unsigned int changes = oldStyle ^ m_Styles;

            const DWORD newWin32Style = GetWin32Style(m_Styles);
            const DWORD newWin32ExtendedStyle = GetWin32ExtendedStyle(m_Styles);

            if (m_Win32Style != newWin32Style)
            {
                m_Win32Style = newWin32Style;
                SetWindowLongPtr(m_WindowHandle, GWL_STYLE, m_Win32Style);
            }
            if (m_Win32ExtendedStyle != newWin32ExtendedStyle)
            {
                m_Win32ExtendedStyle = newWin32ExtendedStyle;
                SetWindowLongPtr(m_WindowHandle, GWL_EXSTYLE, m_Win32ExtendedStyle);
            }

            // Enable/disale [X] button if the close style has been changed.
            if (changes & static_cast<unsigned int>(Window::Style::Close))
            {
                UINT dwExtra = 0;

                // Close style is being disabled. Make it gray and disabled.
                if (!(m_Styles & static_cast<DWORD>(Window::Style::Close)))
                {
                    dwExtra = MF_DISABLED | MF_GRAYED;
                }

                HMENU hMenu = GetSystemMenu(m_WindowHandle, false);
                EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | dwExtra);
            }
        }

        LRESULT Win32WindowImpl::WindowProcStatic(HWND p_HWND, UINT p_Message,
            WPARAM p_WParam, LPARAM p_LParam)
        {
            if (p_Message == WM_NCCREATE)
            {
                SetWindowLongPtr(p_HWND, GWLP_USERDATA, (LONG_PTR)((LPCREATESTRUCT)p_LParam)->lpCreateParams);
            }
            else
            {
                Win32WindowImpl * pWnd = (Win32WindowImpl*)GetWindowLongPtr(p_HWND, GWLP_USERDATA);

                if (pWnd != NULL)
                {
                    return pWnd->WindowProc(p_HWND, p_Message, p_WParam, p_LParam);
                }
            }

            return DefWindowProc(p_HWND, p_Message, p_WParam, p_LParam);
        }

        LRESULT Win32WindowImpl::WindowProc(HWND p_HWND, UINT p_Message,
            WPARAM p_WParam, LPARAM p_LParam)
        {
            switch (p_Message)
            {

            case WM_CREATE:
            {
               // SetProcessDpiAwareness(PROCESS_DPI_AWARENESS::PROCESS_PER_MONITOR_DPI_AWARE);
            }
            case WM_ERASEBKGND:
                return 1;
            break;
                case WM_PAINT:
                {
                    m_pRenderer->BeginRendering();
                    Renderer::RenderArea a({}, {});
                    m_pRenderer->RenderControl(m_pPlane, Vector2i(0, 0), m_Size);
                    m_pRenderer->EndRendering();
                }
                break;
                default:
                    break;
                    
            }
            
            return DefWindowProc(p_HWND, p_Message, p_WParam, p_LParam);
        }
        
    }

}

#endif

