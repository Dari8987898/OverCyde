#include <Engine.h>
#include "SnakeBodyPart.h"

using namespace Engine;
using namespace std;

struct DirectionChange {
    public:
        DirectionChange(float x, float y, char direction, vector<int> snakeBodyIndexes) {
            this->x = x;
            this->y = y;
            this->direction = direction;
            this->snakeBodyIndexes = snakeBodyIndexes;
        };

        float x;
        float y;
        char direction;
        vector<int> snakeBodyIndexes;
};

class GameLayer : public Layer {
    public:
        GameLayer() : Layer("GameLayer") {}

        void OnEvent(Event& event) override;
        void OnUpdate(float deltaTime) override;
        
    private:
        const Vec4f appleColor = Vec4f(255, 0, 0, 0);
        const float appleSize = 0.025;
        const Vec4f snakeColor = Vec4f(0, 255, 0, 0);
        const Vec2f snakeSize = Vec2f(0.025, 0.025);
        const Vec2f startingPosition = Vec2f(0, 0);
        const float speed = 0.3;
        const char startingDirection = ' ';

        vector<DirectionChange> directionChanges;
        vector<SnakeBodyPart> snakeBody;
        bool appleEaten = false;
        bool appleDrawn = false;
        float appleCurrentPositionX = 0;
        float appleCurrentPositionY = 0;
        int nAppleEaten = 0;
        float snakeCurrentPositionX = startingPosition[0];
        float snakeCurrentPositionY = startingPosition[1];
        char snakeCurrentDirection = startingDirection;
        
        void AddSnakeBodyPart();
        void CheckDeathCollision();
        void CheckAppleCollision();
        void DrawApple();
        void DrawSnake();
        bool KeyPressed(KeyPressedEvent& kpe);
        void ResetGame();
        void UpdatePosition(float deltaTime);
};