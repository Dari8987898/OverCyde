#include "Util.h"

using namespace SnakePackageUtil;

namespace SnakePackage {
    class SnakeBodyPart {
        public:
            // Costruttori
            SnakeBodyPart(float x, float y, MovementDirection direction) : x(x), y(y), direction(direction) {}

            // Get
            float getX() const { return x; }
            float getY() const { return y; }
            MovementDirection getDirection() const { return direction; }

            // Metodi
            void ChangeDirection(MovementDirection direction);
            void UpdatePosition(float x, float y);
            
        private:
            float x;
            float y;
            MovementDirection direction;
    };
}