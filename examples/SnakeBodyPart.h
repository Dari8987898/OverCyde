#include <Engine.h>

using namespace Engine;

class SnakeBodyPart {
    public:
        SnakeBodyPart(float currentPositionX, float currentPositionY, char currentDirection) {
            this->currentPositionX = currentPositionX;
            this->currentPositionY = currentPositionY;
            this->currentDirection = currentDirection;
        };
        float currentPositionX;
        float currentPositionY;
        char currentDirection;
};