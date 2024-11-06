#define ENGINE_PLATFORM
#include <Engine.h>
#include <EntryPoint.h>
#include "GameLayer.h"

using namespace Engine;

class Game : public Application {  
    friend class Application;

    private:
        Game(const ApplicationProps& props) : Application(props) {
            this->PushLayer(new GameLayer());
        }
};

Application* Application::Create() {
    ApplicationProps props = ApplicationProps();
    
    props.WProps.Title = "Snakeozzo diddio";
    props.WProps.Width = 600;
    props.WProps.Height = 600;
    props.RType = Renderer::RendererType::Renderer2D;

    return new Game(props);
}