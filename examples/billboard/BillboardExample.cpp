#include <Guier/Guier.hpp>
#include <Guier/Skins/DefaultSkin.hpp>
#include <Guier/Renderers/OpenGL/OpenGLRenderer.hpp>
#include <chrono>
#include <thread>

int main()
{
    Guier::Context context;

    context.Add(new Guier::Window({ 800, 600 }, "Hello world!"));


   /* Guier::Skins::DefaultSkin * pDefaultSkin = new  Guier::Skins::DefaultSkin;

    Guier::Renderers::OpenGLRenderer * pRenderer = new Guier::Renderers::OpenGLRenderer;

    Guier::Window * pWindow = new Guier::Window({800, 600}, "Hello world!");*/


    for (int i = 0; i < 1000; i++)
    {
        context.Update();
        context.Render();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    

    


	return 0;
}