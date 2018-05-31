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

#include <stdlib.h>     /* srand, rand */


#ifdef GUIER_PLATFORM_WINDOWS

#include <Guier/Renderers/Win32/GdipRenderer.hpp>

// REMOVE THIS!!!
#include <gdiplus.h>
#include <Gdiplusheaders.h>
#include <atlstr.h> 
#include <ShellScalingAPI.h>

namespace Guier
{

    namespace Core
    {

        /*static const DWORD g_DefaultWin32Style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_SIZEBOX | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_BORDER;
        static const DWORD g_DefaultWin32ExtStyle = WS_EX_APPWINDOW;*/

        static unsigned int ProcessStyle(const unsigned int style)
        {
            unsigned int newStyle = style;

            if (newStyle & static_cast<unsigned int>(WindowStyle::TitleBar))
            {
                newStyle |= static_cast<unsigned int>(WindowStyle::Border);
            }

            return newStyle;
        }

        static DWORD GetWin32Style(const unsigned int styles)
        {
            DWORD ret = 0;

            if (styles & static_cast<DWORD>(WindowStyle::TitleBar))
            {
                ret |= WS_CAPTION | WS_SYSMENU;
            }

            if (styles & static_cast<DWORD>(WindowStyle::Border))
            {
                ret |= WS_BORDER;
            }

            if (styles & static_cast<DWORD>(WindowStyle::Minimize))
            {
                ret |= WS_MINIMIZEBOX;
            }

            if (styles & static_cast<DWORD>(WindowStyle::Maximize))
            {
                ret |= WS_MAXIMIZEBOX;
            }

            if (styles & static_cast<DWORD>(WindowStyle::Resize))
            {
                ret |= WS_SIZEBOX;
            }

            return ret;
        }

        static DWORD GetWin32ExtendedStyle(const unsigned int styles)
        {
            DWORD ret = WS_EX_APPWINDOW;

            if (styles & static_cast<DWORD>(WindowStyle::HideInTaskbar))
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


        Win32WindowImpl::Win32WindowImpl(Context * context, Window * window, const Vector2i & size, const String & title) :
            m_pContext(context),
            m_pGdipRenderer(nullptr),
            m_Showing(false),
            m_HideWhenClosed(false),
            m_HideFromTaskbar(false),
            m_Position(-1, -1),
            m_Size(size),
            m_Hiding(true),
            m_Styles(WindowStyle::Default),
            m_Win32Style(0),
            m_Win32ExtendedStyle(0),
            m_WindowHandle(0),
            m_DPI(0),

            m_pVerticalGrid(new VerticalGrid(window))
        {
            if (m_pContext == nullptr)
            {
                throw std::runtime_error("Context is nullptr.");
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
            winClass.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
            //winClass.hbrBackground = NULL;
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
                title.Get().c_str(),

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
/*
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
           /* m_CloseConnection = m_Window->Closed.Connect([this]()
            {
                m_pContext->Remove(m_Window);
            });*/
            
            m_pGdipRenderer = new Renderers::GdipRenderer(m_WindowHandle);

            m_DPI = GetDpiForWindow(m_WindowHandle);

            ShowWindow(m_WindowHandle, SW_RESTORE);
            SetForegroundWindow(m_WindowHandle);
            SetFocus(m_WindowHandle);

           /* COLORREF color = RGB(255, 0, 255);
            SetBkColor(m_DeviceContextHandle, color);
            */
           
        }

        Win32WindowImpl::~Win32WindowImpl()
        {
            //m_Window->Closed.DisconnectAll();

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

            //m_Window.reset();
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

        void Win32WindowImpl::Title(const String & title)
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
            m_Hiding = false;
            ShowWindow(m_WindowHandle, SW_RESTORE);
            SetForegroundWindow(m_WindowHandle);
            SetFocus(m_WindowHandle);
        }

        void Win32WindowImpl::Hide()
        {
            m_Hiding = true;
            ShowWindow(m_WindowHandle, SW_HIDE);
        }

        void Win32WindowImpl::Minimize()
        {
            if (m_Hiding == false)
            {
                ShowWindow(m_WindowHandle, SW_MINIMIZE);
            }
        }

        void Win32WindowImpl::Maximize()
        {
            ShowWindow(m_WindowHandle, SW_MAXIMIZE);
        }

        void Win32WindowImpl::Close()
        {
            //m_Window->Closed();
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
            if (changes & static_cast<unsigned int>(WindowStyle::Close))
            {
                UINT dwExtra = 0;

                // Close style is being disabled. Make it gray and disabled.
                if (!(m_Styles & static_cast<DWORD>(WindowStyle::Close)))
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

            /*BOOL ret = SetWindowPos(
                m_WindowHandle,
                NULL,
                newPos.x,
                newPos.y,
                m_Size.x,
                m_Size.y,
                0
            );*/


            BOOL ret = MoveWindow(
                m_WindowHandle,
                newPos.x,
                newPos.y,
                m_Size.x,
                m_Size.y,
                FALSE
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

            static bool keyPress = false;

            switch (p_Message)
            {

          /*  case WM_ERASEBKGND:
                return 1;*/

            /*case WM_NCCREATE:
            {
                EnableNonClientDpiScaling(p_HWND);
            }
            break;*/

            case WM_DPICHANGED:
            {
                int dpi = HIWORD(p_WParam);
                if (dpi != m_DPI)
                {
                    m_DPI = dpi;

                    RECT windowRect;
                    GetWindowRect(m_WindowHandle, &windowRect);

                    RECT rect;
                    rect.left = 0;
                    rect.right = windowRect.right - windowRect.left;
                    rect.top = 0;
                    rect.bottom = windowRect.bottom - windowRect.top;
                    InvalidateRect(m_WindowHandle, &rect, false);
                }
            }
            break;

            case WM_CREATE:
            {
                // In top of main
                ULONG_PTR gdiplusToken;
                Gdiplus::GdiplusStartupInput gdiplusStartupInput;
                GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

                //SetProcessDPIAware();
                SetProcessDpiAwareness(PROCESS_DPI_AWARENESS::PROCESS_PER_MONITOR_DPI_AWARE);
            }
            break;
            case WM_PAINT:
            {
                m_pGdipRenderer->GetInterface()->RenderControl(m_pVerticalGrid);

                //Render(m_WindowHandle, m_pContext->GetRenderer());
                
                
                /*PAINTSTRUCT ps;
                HDC hDC = BeginPaint(m_WindowHandle, &ps);
                Gdiplus::Graphics graphics(hDC);

                Gdiplus::SolidBrush solidbrush(Gdiplus::Color(255, 255, 0, 0));
                graphics.FillRectangle(&solidbrush, 0, 0, 300, 300);*/

/*
                const int fontSize = 12;
                int fontSizeDPI = MulDiv(fontSize, m_DPI, 96);


                Gdiplus::FontFamily fontFamily(L"Segoe UI");
                //fontFamily.IsAvailable();

                Gdiplus::Font       font(&fontFamily, static_cast<Gdiplus::REAL>(fontSizeDPI), Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
                Gdiplus::SolidBrush solidbrush(Gdiplus::Color(255, 0, 0, 0));
                const WCHAR text[] = L"File   Edit   Format   View   Help";

                // Draw string.
                graphics.SetCompositingQuality(Gdiplus::CompositingQuality::CompositingQualityHighQuality);
                graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeHighQuality);
                graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetMode::PixelOffsetModeHighQuality);
                graphics.SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintClearTypeGridFit);

                graphics.DrawString(text, -1, &font, Gdiplus::PointF(10, 10), &solidbrush);


                // Draw string.
                graphics.SetCompositingQuality(Gdiplus::CompositingQuality::CompositingQualityHighQuality);
                graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeHighQuality);
                graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetMode::PixelOffsetModeHighQuality);
                graphics.SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintSingleBitPerPixelGridFit);

                graphics.DrawString(text, -1, &font, Gdiplus::PointF(10, 30), &solidbrush);

                */
               // EndPaint(m_WindowHandle, &ps);

                return 0;


               /* RECT winRec;
                GetWindowRect(m_WindowHandle, &winRec);
                LONG randomX = static_cast<LONG>(rand() % winRec.right - winRec.left);
                LONG randomY = static_cast<LONG>(rand() % winRec.bottom - winRec.top);


                PAINTSTRUCT ps;
                HDC hDC = BeginPaint(m_WindowHandle, &ps);

                
                RECT rect = { 30, 50, 100, 200 };
                
                rect.left += randomX;
                rect.right += randomX;
                rect.top += randomY;
                rect.bottom += randomY;

                HBRUSH brush = CreateSolidBrush(RGB(50, 151, 151));
                FillRect( m_DeviceContextHandle, &rect, brush);
                DeleteObject(brush);

                EndPaint(m_WindowHandle, &ps);
                */

                //if (keyPress)
               // {

               

                   // std::cout << ps.rcPaint.left << "  " << ps.rcPaint.right << "  " << ps.rcPaint.top << "  " << ps.rcPaint.bottom << std::endl;

                   // Gdiplus::Graphics graphics(m_DeviceContextHandle);

                    /*Gdiplus::PrivateFontCollection m_fontcollection;
                    //...
                    CString szFontFile =  L"SkiCargo.ttf";

                    Gdiplus::Status nResults = m_fontcollection.AddFontFile(szFontFile);


                    // When painting the text
                    Gdiplus::FontFamily fontFamily;
                    int nNumFound = 0;
                    m_fontcollection.GetFamilies(1, &fontFamily, &nNumFound);

                    if (nNumFound>0)
                    {
                        Gdiplus::Font font(&fontFamily, 28, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

                        Gdiplus::StringFormat strformat;
                        wchar_t buf[] = L"The quick brown fox jumps over the lazy dog!";
                        Gdiplus::SolidBrush solidbrush(Gdiplus::Color(255, 0, 0, 0));
                        graphics.DrawString(buf, wcslen(buf), &font, Gdiplus::PointF(10.0f, 10.0f), &strformat, &solidbrush);
                    }
                    */

                    // Create a FontFamily object.
                  //  Gdiplus::FontFamily nameFontFamily(/*L"Roboto light"*/L"Segoe UI");

                    // Get the cell ascent of the font family in design units.
                    //WCHAR      familyName[LF_FACESIZE];
                    //nameFontFamily.GetFamilyName(familyName);

                    // Copy the cell ascent into a string and draw the string.
                  /*  Gdiplus::SolidBrush solidbrush(Gdiplus::Color(255, 0, 0, 0));
                    Gdiplus::SolidBrush whiteBrush(Gdiplus::Color(255, 255, 255, 255));


                    Gdiplus::Font       font(&nameFontFamily, 9/*, Gdiplus::FontStyle::FontStyleItalic*///);
                    
                   /* Gdiplus::Pen pens(&solidbrush);
                   // graphics.DrawRectangle(pens, 0, 0, 300, 300);


                    Gdiplus::Pen blackPen(Gdiplus::Color(255, 0, 255, 0), 3);

                    // Define the rectangle.
                    int x = 0;
                    int y = 0;
                    int width = 200;
                    int height = 200;

                    Gdiplus::Rect bgRect();
                    */
                    // Draw the rectangle.
             
                   // Gdiplus::SolidBrush whiteBrush(Gdiplus::Color(255, 255, 255, 255));
                   // graphics.FillRectangle(&whiteBrush, 0, 0, winRec.right - winRec.left, winRec.bottom - winRec.top);


                  /*  Gdiplus::TextRenderingHint hits[6] = 
                    {
                        Gdiplus::TextRenderingHintSystemDefault,
                        Gdiplus::TextRenderingHintSingleBitPerPixelGridFit,
                        Gdiplus::TextRenderingHintSingleBitPerPixel,
                        Gdiplus::TextRenderingHintAntiAliasGridFit,
                        Gdiplus::TextRenderingHintAntiAlias,
                        Gdiplus::TextRenderingHintClearTypeGridFit
                    };*/
                    /*
                    TextRenderingHintSystemDefault = 0,
                        TextRenderingHintSingleBitPerPixelGridFit = 1,
                        TextRenderingHintSingleBitPerPixel = 2,
                        TextRenderingHintAntiAliasGridFit = 3,
                        TextRenderingHintAntiAlias = 4,
                        TextRenderingHintClearTypeGridFit = 5
                        */


                   /* for (int i = 0; i < 6; i++)
                    {
                        graphics.SetTextRenderingHint(hits[i]);
                        //graphics.SetTextContrast(100);
                        graphics.SetCompositingQuality(Gdiplus::CompositingQuality::CompositingQualityAssumeLinear);

                       // graphics.SetCompositingMode(Gdiplus::CompositingMode::CompositingModeSourceCopy);

                    
                        graphics.DrawString(L"The quick brown fox jumps over the lazy dog.", -1, &font, Gdiplus::PointF(20, 20 + (20 * i)), &solidbrush);
                    }*/

      /*              graphics.SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintClearTypeGridFit);
                    graphics.SetTextContrast(0xffffffff);
                    graphics.SetCompositingMode(Gdiplus::CompositingMode::CompositingModeSourceOver);
                    graphics.SetCompositingQuality(Gdiplus::CompositingQuality::CompositingQualityHighQuality);
                    graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetMode::PixelOffsetModeHighQuality);

                    const Gdiplus::FontFamily oFamily(L"Tahoma", NULL);


                    Gdiplus::Font oF600(&oFamily, 6.00, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
                    Gdiplus::Font oF800(&oFamily, 8.00, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
                    Gdiplus::Font oF848(&oFamily, 8.48, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
                    Gdiplus::Font oF849(&oFamily, 9.0, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
                    Gdiplus::Font oF1200(&oFamily, 12.00, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
                    Gdiplus::Font oF1500(&oFamily, 15.00, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
                    Gdiplus::Font oF1648(&oFamily, 16.48, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
                    Gdiplus::Font oF1649(&oFamily, 16.49, Gdiplus::FontStyle::FontStyleRegular, Gdiplus::Unit::UnitPixel);
*/
                    
                    /*
                    Font oF600(&oFamily, 6.00, FontStyle::FontStyleRegular, Unit::UnitPixel);
                    Font oF800(&oFamily, 8.00, FontStyle::FontStyleRegular, Unit::UnitPixel);
                    Font oF848(&oFamily, 8.48, FontStyle::FontStyleRegular, Unit::UnitPixel);
                    Font oF849(&oFamily, 8.49, FontStyle::FontStyleRegular, Unit::UnitPixel);
                    Font oF1200(&oFamily, 12.00, FontStyle::FontStyleRegular, Unit::UnitPixel);
                    Font oF1500(&oFamily, 15.00, FontStyle::FontStyleRegular, Unit::UnitPixel);
                    Font oF1648(&oFamily, 16.48, FontStyle::FontStyleRegular, Unit::UnitPixel);
                    Font oF1649(&oFamily, 16.49, FontStyle::FontStyleRegular, Unit::UnitPixel);
                    */
/*
                    Gdiplus::Color g_oTextColor(255, 0, 0, 0);
                    Gdiplus::SolidBrush oBrush(g_oTextColor);

                    double dy = 1.0;
                    graphics.DrawString(L"Size 6.00", -1, &oF600, Gdiplus::PointF(30.0, dy += 18.0), &oBrush);
                    graphics.DrawString(L"Size 8.00", -1, &oF800, Gdiplus::PointF(30.0, dy += 18.0), &oBrush);
                    graphics.DrawString(L"Size 8.48", -1, &oF848, Gdiplus::PointF(30.0, dy += 18.0), &oBrush);
                    graphics.DrawString(L"abcdefghijklmnopqrstuvwxyzåäö", -1, &oF849, Gdiplus::PointF(30.0, dy += 18.0), &oBrush);
                    graphics.DrawString(L"Size 12.00", -1, &oF1200, Gdiplus::PointF(30.0, dy += 18.0), &oBrush);
                    graphics.DrawString(L"Size 15.00", -1, &oF1500, Gdiplus::PointF(30.0, dy += 18.0), &oBrush);
                    graphics.DrawString(L"Size 16.48", -1, &oF1648, Gdiplus::PointF(30.0, dy += 18.0), &oBrush);
                    graphics.DrawString(L"Size 16.49", -1, &oF1649, Gdiplus::PointF(30.0, dy += 18.0), &oBrush);
 */
                    /*
                    e.Graphics.CompositingQuality = Drawing2D.CompositingQuality.AssumeLinear
                    e.Graphics.SmoothingMode = Drawing2D.SmoothingMode.HighQuality
                    e.Graphics.PixelOffsetMode = Drawing2D.PixelOffsetMode.HighQuality
                    
                    */

                   

// Draw white background
//Gdiplus::SolidBrush mySolidBrush(Gdiplus::Color::White);
//graphics.FillRectangle(&mySolidBrush, 0, 0, 100, 100);

//Gdiplus::Bitmap b(100, 100);
//b.GetWidth();

                  

                   

//  Gdiplus::RectF rectF;
// auto imgSize = graphics.MeasureString(text, -1, &font, Gdiplus::PointF(10, 10), &rectF);

/* Gdiplus::Bitmap b(100, 100);
Gdiplus::Graphics *g = Gdiplus::Graphics::FromImage(&b);
*/

                    

//  Gdiplus::RectF rectF;
// auto imgSize = graphics.MeasureString(text, -1, &font, Gdiplus::PointF(10, 10), &rectF);

/* Gdiplus::Bitmap b(100, 100);
Gdiplus::Graphics *g = Gdiplus::Graphics::FromImage(&b);
*/
                    


                    //graphics.DrawImage(&b, )
                    
     /*
                    
                    CLSID pngClsid;
CLSIDFromString(L"{557CF406-1A04-11D3-9A73-0000F81EF32E}", &pngClsid);
bmp.Save(L"file.png", &pngClsid, NULL);

and here's IDs for other formats:

bmp: {557cf400-1a04-11d3-9a73-0000f81ef32e}
jpg: {557cf401-1a04-11d3-9a73-0000f81ef32e}
gif: {557cf402-1a04-11d3-9a73-0000f81ef32e}
tif: {557cf405-1a04-11d3-9a73-0000f81ef32e}
png: {557cf406-1a04-11d3-9a73-0000f81ef32e}
                    */
                    
/* CLSID pngClsid;
CLSIDFromString(L"{557cf406-1a04-11d3-9a73-0000f81ef32e}", &pngClsid);

b.Save(L"C:\\Users\\sours\\Documents\\GitHub\\Guier\\bin\\out.png", &pngClsid, NULL);
*/
//graphics.SetTextContrast(0x00000000);

//graphics.DrawRectangle(&blackPen, x, y, width, height);
/* graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);
graphics.DrawString(L"C:\\Users\\sours\\Documents\\GitHub\\Guier\\include\\Guier\\Core\\fil.txt", -1, &font, Gdiplus::PointF(randomX, randomY), &solidbrush);
graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintSystemDefault);
graphics.DrawString(L"C:\\Users\\sours\\Documents\\GitHub\\Guier\\include\\Guier\\Core\\fil.txt", -1, &font, Gdiplus::PointF(randomX, randomY + 20), &solidbrush);
graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintSystemDefault);
graphics.DrawString(L"C:\\Users\\sours\\Documents\\GitHub\\Guier\\include\\Guier\\Core\\fil.txt", -1, &font, Gdiplus::PointF(randomX, randomY + 40), &solidbrush);

*/

/*LPCWSTR message = L"abcdefghijklmnopqrstuvwxyzåäö.";

RECT rect;
SetTextColor(m_DeviceContextHandle, 0x00000000);
                
SetBkMode(m_DeviceContextHandle, TRANSPARENT);
rect.left = 40;
rect.top = 10;
                    
HFONT hFont = CreateFont(
9, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE,
DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
CLEARTYPE_QUALITY, FF_DONTCARE, L"Tahoma");

//HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
LOGFONT logfont;
GetObject(hFont, sizeof(LOGFONT), &logfont);
//logfont.lfHeight = 9;

logfont.lfHeight = -MulDiv(9, GetDeviceCaps(m_DeviceContextHandle, LOGPIXELSY), 72);
// Now change the logfont.lfHeight member

HFONT hNewFont = CreateFontIndirect(&logfont);
HFONT hOldFont = (HFONT)SelectObject(m_DeviceContextHandle, hNewFont);
                    
// Do your text drawing
DrawText(m_DeviceContextHandle, message, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

// Always select the old font back into the DC
SelectObject(m_DeviceContextHandle, hOldFont);
DeleteObject(hNewFont);
*/
                    
                   
              
                  
/*
                    keyPress = false;
                }
                */

                /*

                Gdiplus::PrivateFontCollection m_fontcollection;
                //...
                CString szFontFile = szExePath + L"SkiCargo.ttf";

                Gdiplus::Status nResults = m_fontcollection.AddFontFile(szFontFile);

      
                FontFamily fontFamily;
                int nNumFound = 0;
                m_fontcollection.GetFamilies(1, &fontFamily, &nNumFound);

                if (nNumFound>0)
                {
                    Font font(&fontFamily, 28, FontStyleRegular, UnitPixel);

                    StringFormat strformat;
                    wchar_t buf[] = L"The quick brown fox jumps over the lazy dog!";
                    graphics.DrawString(buf, wcslen(buf), &font,
                        PointF(10.0f, 10.0f), &strformat, &brush);
                }*/

            }
            break;
            case WM_CLOSE:
            {
               // m_Window->Closed();

                // Do not forward the event.
                return 0;
            }
            break;
            case WM_SETFOCUS:
            {
                //m_Window->Focused(true);
            }
            break;
            case WM_KILLFOCUS:
            {
                //m_Window->Focused(false);
            }
            break;
            case WM_MOVE:
            {
                const auto newPosition = Vector2i(  static_cast<int>(LOWORD(p_LParam)),
                                                    static_cast<int>(HIWORD(p_LParam)));

                m_Position = newPosition;
                //m_Window->Moved(newPosition);
            }
            break;
            case WM_SIZE:
            {
                const auto oldSize = Vector2i(m_Size);
                const auto newSize = Vector2i(  static_cast<int>(LOWORD(p_LParam)),
                                                static_cast<int>(HIWORD(p_LParam)));
                
                // Check if minimized.
               /* if (newSize == Vector2i(0, 0))
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
                }*/
                


                // Set the default viewport to the window's size
 /*               glViewport(0, 0, m_Settings.Size.x, m_Settings.Size.y);

                glMatrixMode(GL_PROJECTION);
                Matrix4x4<float> projection;
                projection.Orthographic(0.0f, (float)m_Settings.Size.x, (float)m_Settings.Size.y, 0.0f, -1.0f, 1.0f);
                glLoadMatrixf(projection.m);*/

                // Fill border background
                //FillWin32Background(oldSize, newSize);

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

                //RedrawWindow(m_WindowHandle, NULL, NULL, RDW_INTERNALPAINT);
                //RedrawWindow(m_WindowHandle, NULL, NULL, RDW_INVALIDATE | RDW_INTERNALPAINT);
                keyPress = true;

                RECT rect;
                rect.left = 0;
                rect.right = 200;
                rect.top = 0;
                rect.bottom = 200;
                InvalidateRect(m_WindowHandle, &rect, false);


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