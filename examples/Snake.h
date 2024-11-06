#include <Engine.h>
#include <vector>
#include "SnakeBodyPart.h"

using namespace Engine;
using namespace std;

namespace SnakePackage {
    struct DirectionChange {
        public:
            // Costruttori
            DirectionChange(float x, float y, char direction, vector<int> snakeBodyIndexes) {
                this->x = x;
                this->y = y;
                this->direction = direction;
                this->snakeBodyIndexes = snakeBodyIndexes;
            };

            // Parametri
            float x;
            float y;
            char direction;
            vector<int> snakeBodyIndexes;
    };

    class Snake {
        public:
            // Costanti
            const char startingDirection = ' ';
            const Vec2f startingPosition = Vec2f(0, 0);

            // Construttori 
            Snake() : head(SnakeBodyPart(startingPosition[0], startingPosition[1], startingDirection)) {}

            // Parametri
            int nAppleEaten = 0;

            // Get
            SnakeBodyPart getBodyPart(int index) const { return body[index]; }
            int getBodySize() const { return body.size(); }
            vector<DirectionChange> getDirectionChanges() const { return directionChanges; }
            char getHeadDirection() const { return head.getDirection(); }
            SnakeBodyPart getHeadBodyPart() const { return head; }
            float getHeadX() const { return head.getX(); }
            float getHeadY() const { return head.getY(); }

            // Metodi
            void AddBodyPart(SnakeBodyPart bodyPart);
            void AddBodyPart(float x, float y, char direction);
            void ChangeDirection(char direction);
            void Reset();
            void UpdatePosition(float x, float y);

        private:
            SnakeBodyPart head;
            vector<SnakeBodyPart> body = {};
            vector<DirectionChange> directionChanges = {};
    };
}