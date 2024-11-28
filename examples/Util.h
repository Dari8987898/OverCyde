#pragma once

#include <vector>

using namespace std;

namespace SnakePackageUtil {
    enum MovementDirection {
        NONE = -1,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    struct DirectionChange {
        public:
            // Costruttori
            DirectionChange(float x, float y, MovementDirection direction, vector<int> snakeBodyIndexes) {
                this->x = x;
                this->y = y;
                this->direction = direction;
                this->snakeBodyIndexes = snakeBodyIndexes;
            };

            // Parametri
            float x;
            float y;
            MovementDirection direction;
            vector<int> snakeBodyIndexes;
    };
}