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


#include <Guier/Core/Window/Win32WindowImpl.hpp>
#include <Guier/Window.hpp>
#include <Guier/Context.hpp>
#include <sstream>

#ifdef GUIER_PLATFORM_WINDOWS

namespace Guier
{

    namespace Core
    {

        /*static const DWORD g_DefaultWin32Style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_SIZEBOX | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_BORDER;
        static const DWORD g_DefaultWin32ExtStyle = WS_EX_APPWINDOW;*/

        static unsigned int ProcessStyle(const unsigned int style)
        {
            unsigned int newStyle = style;

            if (newStyle & static_cast<unsigned int>(Window::Styles::TitleBar))
            {
                newStyle |= static_cast<unsigned int>(Window::Styles::Border);
            }

            return newStyle;
        }

        static DWORD GetWin32Style(const unsigned int styles)
        {
            DWORD ret = 0;

            if (styles & static_cast<DWORD>(Window::Styles::TitleBar))
            {
                ret |= WS_CAPTION | WS_SYSMENU;
            }

            if (styles & static_cast<DWORD>(Window::Styles::Border))
            {
                ret |= WS_BORDER;
            }

            if (styles & static_cast<DWORD>(Window::Styles::Minimize))
            {
                ret |= WS_MINIMIZEBOX;
            }

            if (styles & static_cast<DWORD>(Window::Styles::Maximize))
            {
                ret |= WS_MAXIMIZEBOX;
            }

            if (styles & static_cast<DWORD>(Window::Styles::Resize))
            {
                ret |= WS_SIZEBOX;
            }

            return ret;
        }

        static DWORD GetWin32ExtendedStyle(const unsigned int styles)
        {
            DWORD ret = WS_EX_APPWINDOW;

            if (styles & static_cast<DWORD>(Window::Styles::HideInTaskbar))
            {
                ret = WS_EX_NOACTIVATE;
            }

            return ret;
        }

        static std::wstring StringToWideString(const std::string & p_String)
        {
            int len;
            int slength = static_cast<int>(p_String.length() + 1);
            len = MultiByteToWideChar(CP_ACP, 0, p_String.c_str(), slength, 0, 0);
            wchar_t* buf = new wchar_t[len];
            MultiByteToWideChar(CP_ACP, 0, p_String.c_str(), slength, buf, len);
            std::wstring r(buf);
            delete[] buf;
            return r;
        }


        Win32WindowImpl::Win32WindowImpl(Context * context, std::shared_ptr<Window> window, const Vector2i & size, const std::wstring & title) :
            m_pContext(context),
            m_Window(window),
            m_Showing(false),
            m_HideWhenClosed(false),
            m_HideFromTaskbar(false),
            m_Position(-1, -1),
            m_Size(size),
            m_Title(title),
            m_Styles(Window::Styles::Default),
            m_Win32Style(0),
            m_Win32ExtendedStyle(0),
            m_WindowHandle(0)
        {
            if (m_pContext == nullptr)
            {
                throw std::runtime_error("Context is nullptr.");
            }

            if (m_Window == nullptr)
            {
                throw std::runtime_error("Window is nullptr.");
            }

            // Get default styles.
            m_Styles = ProcessStyle(m_Styles);
            m_Win32Style = GetWin32Style(m_Styles);
            m_Win32ExtendedStyle = GetWin32ExtendedStyle(m_Styles);

            // Create an unique window class name
            static unsigned int uniqueNumber = 0;
            std::stringstream ss;
            ss << "guil_widow_class_number_" << uniqueNumber;
            uniqueNumber++;
            std::wstring className = StringToWideString(ss.str().c_str()).c_str();

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
            //HBRUSH hb = ::CreateSolidBrush(RGB(255, 0, 0));
            //winClass.hbrBackground = hb;
            winClass.hbrBackground = NULL;
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

            // Create background brush
            /*static const unsigned char bgRed = 150;
            static const unsigned char bgGreen = 170;
            static const unsigned char bgBlue = 170;
            m_BackgroundBrush = ::CreateSolidBrush(RGB((BYTE)bgRed, (BYTE)bgGreen, (BYTE)bgBlue));*/

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
                m_Title.c_str(),

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



            /*
   
            // Get the device context
            m_DeviceContextHandle = GetDC(m_WindowHandle);

            // Filling the pixel fromat structure.
            /*static PIXELFORMATDESCRIPTOR PFD = {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW |
            PFD_SUPPORT_OPENGL |
            PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            24,
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            8, //DepthBits,
            8, //StencilBits,
            0,
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
            };

            // Choose and set the pixel format
            GLuint PixelFormat;

            if ((PixelFormat = ChoosePixelFormat(m_DeviceContextHandle, &PFD)) == 0)
            {
            GUIL_THROW_EXCEPTION("Can not choose pixel format.");
            return;
            }
            if ((SetPixelFormat(m_DeviceContextHandle, PixelFormat, &PFD)) == false)
            {
            GUIL_THROW_EXCEPTION("Can not set pixel format.");
            return;
            }

            // Create a temporary regual context.
            // We need this context to create any other context.
            HGLRC temporaryContext = wglCreateContext(m_DeviceContextHandle);

            if (temporaryContext == NULL)
            {
            GUIL_THROW_EXCEPTION("Can not create a regular OpenGL context.");
            return;
            }

            // Make the temporary context to the current one
            wglMakeCurrent(NULL, NULL);
            wglMakeCurrent(m_DeviceContextHandle, temporaryContext);

            // Attributes for the OGL 3.3 context
            int attribs[] =
            {
            WGL_CONTEXT_MAJOR_VERSION_ARB, static_cast<int>(2),
            WGL_CONTEXT_MINOR_VERSION_ARB, static_cast<int>(0),
            0
            };

            // We need the proc address for the function
            // we are going to use for OGL 3.3 context creation.
            PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
            if ((wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB")) == NULL)
            {
            GUIL_THROW_EXCEPTION("Can not get the function for creating the context.");
            return;
            }

            // Create the context
            if ((m_OpenGLContext = wglCreateContextAttribsARB(m_DeviceContextHandle, 0, attribs)) == NULL)
            {
            GUIL_THROW_EXCEPTION("Failed to create OpenGL 2 context.");
            return;
            }

            // Delete the old temporary context
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(temporaryContext);

            // Make the new OpenGL context to the current one.
            wglMakeCurrent(m_DeviceContextHandle, m_OpenGLContext);


            // Bind the OpenGL extensions
            if (OpenGL::BindOpenGLExtensions(2, 0) != true)
            {
            GUIL_THROW_EXCEPTION("Binding opengl extensions failed.");
            return;
            }


            // Set the default viewport to the window's size
            glViewport(0, 0, m_Settings.Size.x, m_Settings.Size.y);


            glDisable(GL_DEPTH_TEST);
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_STENCIL_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glClearColor((float)bgRed / 256.0f, (float)bgGreen / 256.0f, (float)bgBlue / 256.0f, 1.0f);
            glClearStencil(0);
            glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            glMatrixMode(GL_TEXTURE);
            glLoadIdentity();
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glMatrixMode(GL_PROJECTION);
            Matrix4x4<float> projection;
            projection.Orthographic(0.0f, (float)m_Settings.Size.x, (float)m_Settings.Size.y, 0.0f, -1.0f, 1.0f);
            glLoadMatrixf(projection.m);
            */

            /*COLORREF color = RGB(255, 0, 255);
            SetBkColor(m_DeviceContextHandle, color);
            */

            // Default signal for closing the window
            m_CloseConnection = m_Window->Closed.Connect([this]()
            {
                m_pContext->Remove(m_Window);
            });
        }

        Win32WindowImpl::~Win32WindowImpl()
        {
            m_Window->Closed.DisconnectAll();

            if (m_BackgroundBrush)
            {
                DeleteObject(m_BackgroundBrush);
            }




            // Delete the context
            /*if (m_OpenGLContext)
            {
            // Release the context from the current thread
            wglMakeCurrent(NULL, NULL);

            // Delete the opengl context
            wglDeleteContext(m_OpenGLContext);
            }*/


            // Get the module handler.
            HINSTANCE Hinstance = GetModuleHandle(NULL);

            // Change back to normal display settings.
            ChangeDisplaySettings(NULL, 0);



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

            m_Window.reset();
        }

        void Win32WindowImpl::HandleEvents()
        {
            // Go through all the window event messages
            MSG message;
            BOOL bRet = 0;
            //while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
            while( (bRet = GetMessage(&message, NULL, 0, 0)) != 0)
            {
                if (bRet == -1)
                {
                    throw std::runtime_error("GetMessage returned -1.");
                    
                }
                else
                {
                    // A modal function is being called when you press the alt key,
                    // fix this by ignoring the alt(menu) key event.
                    if (message.message == WM_SYSCOMMAND &&
                        message.wParam == SC_KEYMENU)
                    {
                        break;
                    }

                    // Translate the dispatch the message
                    // This will call the WindowProcStatic function
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
            }
        }


        const Vector2i & Win32WindowImpl::Size() const
        {
            return m_Size;
        }

        void Win32WindowImpl::Size(const Vector2i & size)
        {
            m_Size = size;
            UpdatePositionSize();
        }

        const std::wstring & Win32WindowImpl::Title() const
        {
            return m_Title;
        }

        void Win32WindowImpl::Title(const std::wstring & title)
        {

        }

        void Win32WindowImpl::Title(const std::string & title)
        {

        }

        const Vector2i & Win32WindowImpl::Position() const
        {
            return m_Position;
        }

        void Win32WindowImpl::Position(const Vector2i & position)
        {
            m_Position = position;
            UpdatePositionSize();
        }

        void Win32WindowImpl::Show()
        {
            ShowWindow(m_WindowHandle, /*show ?*/ SW_RESTORE/* : SW_HIDE*/);
            SetForegroundWindow(m_WindowHandle);
            SetFocus(m_WindowHandle);
        }

        void Win32WindowImpl::Minimize()
        {
            ShowWindow(m_WindowHandle, SW_MINIMIZE);
        }

        void Win32WindowImpl::Maximize()
        {
            ShowWindow(m_WindowHandle, SW_MAXIMIZE);
        }

        void Win32WindowImpl::HideFromTaskbar(const bool hide)
        {
            ShowWindow(m_WindowHandle, SW_HIDE);
           /* if (hide && m_HideFromTaskbar == false)
            {
                m_CloseConnection->Disconnect();
                m_CloseConnection.reset();
                m_CloseConnection = m_Window->Closed.Connect([this]()
                {
                    m_Window->Minimize();
                    //m_pContext->Remove()
                    //m_pWindow->Close();
                });

                m_HideFromTaskbar = true;
            }
            else if (hide == false && m_HideFromTaskbar == true)
            {
                m_CloseConnection->Disconnect();
                m_CloseConnection.reset();
                m_CloseConnection = m_Window->Closed.Connect([this]()
                {
                   m_pContext->Remove(m_Window);
                });

                m_HideFromTaskbar = false;
            }*/

            
            //ShowWindow(m_WindowHandle, hide ? SW_HIDE : SW_SHOW);
        }

        void Win32WindowImpl::Close()
        {
            m_Window->Closed();
        }

        unsigned int Win32WindowImpl::GetStyle() const
        {
            std::lock_guard<std::mutex> sm(m_StyleMutex);

            return m_Styles;
        }

        void Win32WindowImpl::NewStyleInternal(const unsigned int styles)
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
            if (changes & static_cast<unsigned int>(Window::Styles::Close))
            {
                UINT dwExtra = 0;

                // Close style is being disabled. Make it gray and disabled.
                if (!(m_Styles & static_cast<DWORD>(Window::Styles::Close)))
                {
                    dwExtra = MF_DISABLED | MF_GRAYED;
                }
                
                HMENU hMenu = GetSystemMenu(m_WindowHandle, false);
                EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | dwExtra);
            }
        }

        void Win32WindowImpl::NewStyle(const unsigned int styles)
        {
            std::lock_guard<std::mutex> sm(m_StyleMutex);

            NewStyleInternal(ProcessStyle(styles));
        }

        void Win32WindowImpl::EnableStyles(const unsigned int styles)
        {
            std::lock_guard<std::mutex> sm(m_StyleMutex);

            NewStyleInternal(ProcessStyle(m_Styles | styles));
        }

        void Win32WindowImpl::DisableStyles(const unsigned int styles)
        {
            std::lock_guard<std::mutex> sm(m_StyleMutex);

            NewStyleInternal(ProcessStyle(m_Styles & (~styles)));
        }

        HWND Win32WindowImpl::GetWindowHandle() const
        {
            return m_WindowHandle;
        }

        HDC Win32WindowImpl::GetDeviceContextHandle() const
        {
            return m_DeviceContextHandle;
        }

        void Win32WindowImpl::UpdatePositionSize()
        {
            if (m_WindowHandle == 0)
            {
                return;
            }
            
            const Vector2i newPos(m_Position.x < 0 ? CW_USEDEFAULT : m_Position.x, m_Position.y < 0 ? CW_USEDEFAULT : m_Position.y);

            BOOL ret = SetWindowPos(
                m_WindowHandle,
                m_WindowHandle,
                newPos.x,
                newPos.y,
                m_Size.x,
                m_Size.y,
                0
            );

            if (ret == 0)
            {
                throw std::runtime_error("SetWindowPos returned != 0.");
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
 //           Event e;

            switch (p_Message)
            {
            case WM_CLOSE:
            {
                m_Window->Closed();

                // Do not forward the event.
                return 0;
            }
            break;
            case WM_SETFOCUS:
            {
                m_Window->Focused(true);
            }
            break;
            case WM_KILLFOCUS:
            {
                m_Window->Focused(false);
            }
            break;
            case WM_MOVE:
            {
                const auto newPosition = Vector2i(  static_cast<int>(LOWORD(p_LParam)),
                                                    static_cast<int>(HIWORD(p_LParam)));

                m_Window->Moved(newPosition);
            }
            break;
            case WM_SIZE:
            {
                const auto oldSize = Vector2i(m_Size);
                const auto newSize = Vector2i(  static_cast<int>(LOWORD(p_LParam)),
                                                static_cast<int>(HIWORD(p_LParam)));
                
                // Check if minimized.
                if (newSize == Vector2i(0, 0))
                {
                    m_Showing = false;
                    m_Window->Minimized();
                    break;
                }
                
                // Not minimized, just resized.
                m_Size = newSize;
                
                if (m_Showing == false)
                {
                    m_Showing = true;
                    m_Window->Showing();
                }
                else
                {
                    m_Window->Resized(m_Size);
                }
                


                // Set the default viewport to the window's size
 /*               glViewport(0, 0, m_Settings.Size.x, m_Settings.Size.y);

                glMatrixMode(GL_PROJECTION);
                Matrix4x4<float> projection;
                projection.Orthographic(0.0f, (float)m_Settings.Size.x, (float)m_Settings.Size.y, 0.0f, -1.0f, 1.0f);
                glLoadMatrixf(projection.m);*/

                // Fill border background
                FillWin32Background(oldSize, newSize);

                // Redraw canvas.
  /*              m_RedrawStatus = true;
                if (m_pCanvas)
                {
                    m_pCanvas->Render();
                }*/
            }
            break;
            // Key events
            case WM_KEYDOWN:
            {
                const unsigned short win32Key = static_cast<unsigned short>(LOWORD(p_WParam));
                const unsigned short win32Key2 = static_cast<unsigned short>(HIWORD(p_WParam));

                if (win32Key >= 256)
                {
                    break;
                }

                // Special key checks
                if (p_WParam == VK_CONTROL)
                {
//                    Event::Key::eKey key = (HIWORD(p_LParam) & KF_EXTENDED) ? tKey::ControlRight : tKey::ControlLeft;
 //                   m_EventHandler.PressKey(key);
                    break;
                }
                /*else if (p_WParam == VK_MENU)
                {
                Event::Key::eKey key = (HIWORD(p_LParam) & KF_EXTENDED) ? tKey::AltRight : tKey::AltLeft;
                m_EventHandler.PressKey(key);
                break;
                }*/

                // Get mapped key
 /*               const unsigned char mappedKey = g_Win32KeyMap[win32Key];
                if (mappedKey == 0)
                {
                    break;
                }

                Event::Key::eKey key = static_cast<Event::Key::eKey>(mappedKey);
                m_EventHandler.PressKey(key);*/
            }
            break;
            case WM_KEYUP:
            {
                const unsigned short win32Key = static_cast<unsigned short>(LOWORD(p_WParam));
                if (win32Key >= 256)
                {
                    break;
                }

                // Special key checks
                if (p_WParam == VK_CONTROL)
                {
 //                   Event::Key::eKey key = (HIWORD(p_LParam) & KF_EXTENDED) ? tKey::ControlRight : tKey::ControlLeft;
 //                   m_EventHandler.ReleaseKey(key);
                    break;
                }
                /*else if (p_WParam == VK_MENU)
                {
                Event::Key::eKey key = (HIWORD(p_LParam) & KF_EXTENDED) ? tKey::AltRight : tKey::AltLeft;
                m_EventHandler.ReleaseKey(key);
                break;
                }*/

                // Get mapped key
 /*               const unsigned char mappedKey = g_Win32KeyMap[win32Key];
                if (mappedKey == 0)
                {
                    break;
                }

                Event::Key::eKey key = static_cast<Event::Key::eKey>(mappedKey);
                m_EventHandler.ReleaseKey(key);*/
            }
            break;
            // Mouse events
            case WM_MOUSEMOVE:
            {
//                m_EventHandler.MoveMouse({ static_cast<int>(LOWORD(p_LParam)), static_cast<int>(HIWORD(p_LParam)) });
            }
            break;
            case WM_LBUTTONDOWN:
            {
 //               m_EventHandler.PressMouseButton(Event::Mouse::Left,
  //                  { static_cast<int>(LOWORD(p_LParam)), static_cast<int>(HIWORD(p_LParam)) });
            }
            break;
            case WM_LBUTTONUP:
            {
//                m_EventHandler.ReleaseMouseButton(Event::Mouse::Left,
 //                   { static_cast<int>(LOWORD(p_LParam)), static_cast<int>(HIWORD(p_LParam)) });
            }
            break;
            case WM_MBUTTONDOWN:
            {
 /*               m_EventHandler.PressMouseButton(Event::Mouse::Middle,
                    { static_cast<int>(LOWORD(p_LParam)), static_cast<int>(HIWORD(p_LParam)) });*/
            }
            break;
            case WM_MBUTTONUP:
            {
//                m_EventHandler.ReleaseMouseButton(Event::Mouse::Middle,
 //                   { static_cast<int>(LOWORD(p_LParam)), static_cast<int>(HIWORD(p_LParam)) });
            }
            break;
            case WM_RBUTTONDOWN:
            {
//                m_EventHandler.PressMouseButton(Event::Mouse::Right,
//                    { static_cast<int>(LOWORD(p_LParam)), static_cast<int>(HIWORD(p_LParam)) });
            }
            break;
            case WM_RBUTTONUP:
            {
 //               m_EventHandler.ReleaseMouseButton(Event::Mouse::Right,
 //                   { static_cast<int>(LOWORD(p_LParam)), static_cast<int>(HIWORD(p_LParam)) });
            }
            break;
            case WM_MOUSEWHEEL:
            {
 //               int delta = static_cast<int>(GET_WHEEL_DELTA_WPARAM(p_WParam)) / WHEEL_DELTA;
  //              m_EventHandler.SpinMouseWheel(delta);
            }
            break;
            default:
            {
            }
            break;
            }

            return DefWindowProc(p_HWND, p_Message, p_WParam, p_LParam);
        }

        void Win32WindowImpl::FillWin32Background(const Vector2i & p_OldSize, const Vector2i & p_NewSize)
        {
            // X
            RECT rect =
            {
                p_OldSize.x,
                0,
                p_NewSize.x,
                p_NewSize.y
            };

            BeginPaint(m_WindowHandle, NULL);
            FillRect(m_DeviceContextHandle, &rect, m_BackgroundBrush);
            EndPaint(m_WindowHandle, NULL);

            // Y
            rect =
            {
                0,
                p_OldSize.y,
                p_NewSize.x,
                p_NewSize.y
            };

            BeginPaint(m_WindowHandle, NULL);
            FillRect(m_DeviceContextHandle, &rect, m_BackgroundBrush);
            EndPaint(m_WindowHandle, NULL);
        }


    }

}

#endif