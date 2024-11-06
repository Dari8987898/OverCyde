#include "Snake.h"

using namespace std;

namespace SnakePackage {
    // @brief Aggiunge una parte al corpo di snake.
    // @param bodyPart Un oggetto SnakeBodyPart.
    void Snake::AddBodyPart(SnakeBodyPart bodyPart) {
        this->body.push_back(bodyPart);
    }

    // @brief Aggiunge una parte al corpo di snake.
    // @param x Coordinata x.
    // @param y Coordinata y.
    // @param direction Direzione. U - up, D - down, L - left, R - right
    void Snake::AddBodyPart(float x, float y, char direction) {
        SnakeBodyPart bodyPart = SnakeBodyPart(x, y, direction);
        this->body.push_back(bodyPart);
    }

    // @brief Cambia la direzione di movimento di snake.
    // @param direction Direzione. U - up, D - down, L - left, R - right
    void Snake::ChangeDirection(char direction) {
        this->head.ChangeDirection(direction);

        vector<int> indexes;

        for (int i = 0; i < this->body.size(); i++)
            indexes.push_back(i);

        if (this->nAppleEaten > 0)
            this->directionChanges.push_back(DirectionChange(this->head.getX(), this->head.getY(), direction, indexes));
    }

    // @brief Re-inizializza snake.
    void Snake::Reset() {
        SnakeBodyPart newHead = SnakeBodyPart(startingPosition[0], startingPosition[1], startingDirection);

        this->head = newHead;
        this->body.clear();
        this->directionChanges.clear();
        this->nAppleEaten = 0;
    }

    /// @brief Aggiorna la posizione di snake e delle sue parti del corpo.
    /// @param x Coordinata x.
    /// @param y Coordinata y.
    void Snake::UpdatePosition(float x, float y) {
        this->head.UpdatePosition(x, y);
        
        float newX = 0;
        float newY = 0;
        
        for (int i = 0; i < this->getBodySize(); i++) {
            SnakeBodyPart beforeCurrent = i == 0 ? this->head : this->getBodyPart(i - 1);

            switch (beforeCurrent.getDirection()) {
                case 'L':
                    newX = beforeCurrent.getX() + (0.025 * 2);
                    newY = beforeCurrent.getY();
                    break;

                case 'R':
                    newX = beforeCurrent.getX() - (0.025 * 2);
                    newY = beforeCurrent.getY();
                    break;

                case 'U':
                    newX = beforeCurrent.getX();
                    newY = beforeCurrent.getY() - (0.025 * 2);
                    break;

                case 'D':
                    newX = beforeCurrent.getX();
                    newY = beforeCurrent.getY() + (0.025 * 2);
                    break;

                default:
                    break;
            }

            this->body.at(i).UpdatePosition(newX, newY);
        }
    }
}