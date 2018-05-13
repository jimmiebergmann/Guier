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

template<typename Type, class... Args>
std::shared_ptr<Window> Context::Add(Args &&... args)
{
    // std::lock_guard<std::mutex> sm(m_ObjectMutex);


    Core::WindowCreation * pWindowCreation = new Core::WindowCreation(std::forward<Args>(args)...);

    // Push and notify window thread.
    {
        std::lock_guard<std::mutex> sm(m_WindowCreationMutex);
        m_WindowCreationQueue.push(pWindowCreation);
    }
    
    InterruptWindowEvents();

    // Wait until created in main thread.
    pWindowCreation->semaphore.Wait();
    
    // Get created window and return it.
    auto window = pWindowCreation->window;
    delete pWindowCreation;

    return window;

   //auto window = std::shared_ptr<Window>(new Window(std::forward<Args>(args)...));
     /*//auto window = std::make_shared<Window>(std::forward<Args>(args)...);
     */
    // Set renderer of window.
    /*Renderer * pNewRenderer = m_pRenderer->AllocateNew();
    pNewRenderer->Load();
    //window->m_pContext = this;
    window->m_pRenderer = pNewRenderer;*/
    /*
    // Add window.
    m_Windows.insert(window);*/

    
}