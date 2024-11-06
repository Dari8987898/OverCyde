#include <Engine.h>
#include "Snake.h"

using namespace Engine;
using namespace SnakePackage;
using namespace std;

class GameLayer : public Layer {
    public:
        GameLayer() : Layer("GameLayer") {}

        void OnEvent(Event& event) override;
        void OnUpdate(float deltaTime) override;
        
    private:
        const Vec4f appleColor = Vec4f(255, 0, 0, 0);
        const float appleDimension = 0.025;
        const Vec4f snakeColor = Vec4f(0, 255, 0, 0);
        const Vec2f snakeDimension = Vec2f(0.025, 0.025);
        const float speed = 0.3;

        Snake snake;
        bool appleEaten = false;
        bool appleDrawn = false;
        float appleCurrentPositionX = 0;
        float appleCurrentPositionY = 0;
        
        void AddSnakeBodyPart();
        void CheckDeathCollision();
        void CheckAppleCollision();
        void DrawApple();
        void DrawDirectionChanges();
        void DrawSnake();
        bool KeyPressed(KeyPressedEvent& kpe);
        void ResetGame();
        void UpdatePosition(float deltaTime);
};