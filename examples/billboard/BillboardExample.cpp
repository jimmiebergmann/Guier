#include <Guier/Guier.hpp>
#include <Guier/Skins/DefaultSkin.hpp>
#include <Guier/Renderers/OpenGL/OpenGLRenderer.hpp>
#include <chrono>
#include <thread>

int main()
{
    Guier::Context context;

    auto * window = new Guier::Window({ 800, 600 }, L"Hello world! åäö ÅÄÖ");
    
    window->Resized.Connect([](const Guier::Vector2i & size)
    {
        std::cout << "Resized: " << size.x << "  " << size.y << std::endl;
    });

    window->Showing.Connect([](const bool showing)
    {
        std::cout << "Showing: " << showing << std::endl;
    });

    window->Focused.Connect([](const bool focused)
    {
        std::cout << "Focused: " << focused << std::endl;
    });

    context.Add(window);


   /* Guier::Skins::DefaultSkin * pDefaultSkin = new  Guier::Skins::DefaultSkin;

    Guier::Renderers::OpenGLRenderer * pRenderer = new Guier::Renderers::OpenGLRenderer;

    Guier::Window * pWindow = new Guier::Window({800, 600}, "Hello world!");*/


    while(1)//for (int i = 0; i < 1000; i++)
    {
        context.Update();
        context.Render();

        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    

    


	return 0;
}