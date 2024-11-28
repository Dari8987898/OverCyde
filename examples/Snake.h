#include <Engine.h>
#include <vector>
#include "SnakeBodyPart.h"
#include "Util.h"

using namespace Engine;
using namespace SnakePackageUtil;
using namespace std;

namespace SnakePackage {
    class Snake {
        public:
            // Costanti
            const MovementDirection startingDirection = MovementDirection::NONE;
            const Vec2f startingPosition = Vec2f(0, 0);

            // Construttori 
            Snake() : head(SnakeBodyPart(startingPosition[0], startingPosition[1], startingDirection)) {}

            // Parametri
            int nAppleEaten = 0;

            // Get
            SnakeBodyPart getBodyPart(int index) const { return body[index]; }
            int getBodySize() const { return body.size(); }
            vector<DirectionChange> getDirectionChanges() const { return directionChanges; }
            MovementDirection getHeadDirection() const { return head.getDirection(); }
            SnakeBodyPart getHeadBodyPart() const { return head; }
            float getHeadX() const { return head.getX(); }
            float getHeadY() const { return head.getY(); }

            // Metodi
            void AddBodyPart(SnakeBodyPart bodyPart);
            void AddBodyPart(float x, float y, MovementDirection direction);
            void ChangeDirection(MovementDirection direction);
            void Reset();
            void UpdatePosition(float speed);

        private:
            SnakeBodyPart head;
            vector<SnakeBodyPart> body = {};
            vector<DirectionChange> directionChanges = {};

            void CheckBodyPartsDirectionChange();
    };
}