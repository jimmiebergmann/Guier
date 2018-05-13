#include <Guier/Guier.hpp>
#include <Guier/Skins/DefaultSkin.hpp>
#include <Guier/Renderers/OpenGL/OpenGLRenderer.hpp>
#include <chrono>
#include <thread>
#include <vector>

int main()
{
    bool running1 = true;
    bool running2 = true;


    Guier::Context context;

    //Guier::Window::Settings settings;


    /*Window * pWindow = nullptr,

    context.Add
    (
        pWindow = new Window({ 800, 600 }, "Window title!",
        {
            new Text("Header text, over button."),
            new Button({100, 50,
            {
                new Text("Button text")
            })->OnClick.Connect(pWindow, &Window::Maximize);

        })
    );*/


    auto window = context.Add<Guier::Window>(800, 600, L"My window 1!")/*->Size({800, 600}).Show()*/;
    auto window2 = context.Add<Guier::Window>(L"My window 2!")->Size({800, 400})/*.Show()*/;
    //window->Add<Text>("Header text, over button.");
    /*auto button = window->Add<Button>({ 100, 50 });
    button->Add<Text>("Button text");
    button->OnClick(window, Window::Maximize);*/



   // context.Add<Guier::Window>({ 800, 600 }, L"Hello world! åäö ÅÄÖ", Guier::Window::Settings());

    /*auto * window = new Guier::Window({ 800, 600 }, L"Hello world! åäö ÅÄÖ");
    */
    window->Resized.Connect([](const Guier::Vector2i & size)
    {
        std::cout << "Resized: " << size.x << "  " << size.y << std::endl;
    });

    window->Moved.Connect([](const Guier::Vector2i & position)
    {
        std::cout << "Moved: " << position.x << "  " << position.y << std::endl;
    });

    window->Showing.Connect([]()
    {
        std::cout << "Showing." << std::endl;
    });

    window->Minimized.Connect([]()
    {
        std::cout << "Minimized." << std::endl;
    });

    window->Focused.Connect([](const bool focused)
    {
        std::cout << "Focused: " << focused << std::endl;
    });

    window->Opened.Connect([]()
    {
        std::cout << "Opened." << std::endl;
    });

    window->Closed.Connect([&running1]()
    {
        std::cout << "Closed 1." << std::endl;
        running1 = false;
    });
    window2->Closed.Connect([&running2]()
    {
        std::cout << "Closed 2." << std::endl;
        running2 = false;
    });

   // context.Add(window);


   /* Guier::Skins::DefaultSkin * pDefaultSkin = new  Guier::Skins::DefaultSkin;

    Guier::Renderers::OpenGLRenderer * pRenderer = new Guier::Renderers::OpenGLRenderer;

    Guier::Window * pWindow = new Guier::Window({800, 600}, "Hello world!");*/


    while(running1 || running2)//for (int i = 0; i < 1000; i++)
    {
        //context.Update();
        //context.Render();

       /* char c = 0;
        c = std::cin.get();

        switch (c)
        {
        case '1':
            window->Minimize();
            break;
        case '2':
            window->Maximize();
            break;
        case '3':
            window->Show();
            break;
        case '4':
            window->Focus();
            break;
        case '5':
            window->Open();
            break;
        case '6':
            window->Close();
            break;
        case '7':
            window->Hide(true);
            break;
        case '8':
            window->Hide(false);
            break;
        default:
            break;
        }*/

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    

    


	return 0;
}