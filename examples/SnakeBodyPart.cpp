#include "SnakeBodyPart.h"

namespace SnakePackage {
    // @brief Cambia la direzione di movimento dei questa parte del corpo di snake.
    // @param direction Direzione. U - up, D - down, L - left, R - right
    void SnakeBodyPart::ChangeDirection(char direction) {
        this->direction = direction;
    }

    // @brief Cambia la posizione di questa parte del corpo di snake.
    // @param x Coordinata x.
    // @param y Coordinata y.
    void SnakeBodyPart::UpdatePosition(float x, float y) {
        this->x = x;
        this->y = y;
    }
}