#include "Snake.h"

using namespace SnakePackageUtil;
using namespace std;

namespace SnakePackage {
    /// @brief Aggiunge una parte al corpo di snake.
    /// @param bodyPart Un oggetto SnakeBodyPart.
    void Snake::AddBodyPart(SnakeBodyPart bodyPart) {
        this->body.push_back(bodyPart);
    }

    /// @brief Aggiunge una parte al corpo di snake.
    /// @param x Coordinata x.
    /// @param y Coordinata y.
    /// @param direction Direzione di movimento.
    void Snake::AddBodyPart(float x, float y, MovementDirection direction) {
        SnakeBodyPart bodyPart = SnakeBodyPart(x, y, direction);
        this->body.push_back(bodyPart);
    }

    /// @brief Cambia la direzione di movimento di snake.
    /// @param direction Direzione di movimento.
    void Snake::ChangeDirection(MovementDirection direction) {
        this->head.ChangeDirection(direction);

        vector<int> indexes;

        for (int i = 0; i < this->body.size(); i++)
            indexes.push_back(i);

        if (this->nAppleEaten > 0)
            this->directionChanges.push_back(DirectionChange(this->head.getX(), this->head.getY(), direction, indexes));
    }

    /// @brief Controlla se ci sono cambiamenti di direzione per le parti del corpo di snake.
    void Snake::CheckBodyPartsDirectionChange() {
        // bool changeDirection;
        // vector<int> snakeBodyIndexesToRemove = {};

        // for (int i = 0; i < this->directionChanges.size(); i++) {
        //     DirectionChange currentDc = this->directionChanges.at(i);
        //     snakeBodyIndexesToRemove.clear();

        //     for (int j = 0; j < currentDc.snakeBodyIndexes.size(); j++) {
        //         SnakeBodyPart currentSbp = this->getBodyPart(currentDc.snakeBodyIndexes.at(j));
        //         changeDirection = false;

        //         switch (currentDc.direction) {
        //             case MovementDirection::UP:
        //                 if (currentDc.y >= currentSbp.getY())
        //                     changeDirection = true;
        //                 break;

        //             case MovementDirection::LEFT:
        //                 if (currentDc.x <= currentSbp.getX())
        //                     changeDirection = true;
        //                 break;

        //             case MovementDirection::DOWN:
        //                 if (currentDc.y <= currentSbp.getY())
        //                     changeDirection = true;
        //                 break;

        //             case MovementDirection::RIGHT:
        //                 if (currentDc.x >= currentSbp.getX())
        //                     changeDirection = true;
        //                 break;

        //             default:
        //                 break;
        //         }

        //         if (changeDirection) {
        //             this->body.at(currentDc.snakeBodyIndexes.at(j)).ChangeDirection(currentDc.direction);
        //             snakeBodyIndexesToRemove.push_back(j);
        //         }
        //     }

        //     for (int k = snakeBodyIndexesToRemove.size() - 1; k >= 0; k--) {
        //         this->directionChanges.at(i).snakeBodyIndexes.erase(this->directionChanges.at(i).snakeBodyIndexes.begin() + snakeBodyIndexesToRemove.at(k));
        //     }
        // }

        // for (int i = 0; i < this->directionChanges.size(); i++) {
        //     if (this->directionChanges.at(i).snakeBodyIndexes.size() == 0)
        //         this->directionChanges.erase(this->directionChanges.begin() + i);
        // }
    }

    /// @brief Re-inizializza snake.
    void Snake::Reset() {
        SnakeBodyPart newHead = SnakeBodyPart(startingPosition[0], startingPosition[1], startingDirection);

        this->head = newHead;
        this->body.clear();
        this->directionChanges.clear();
        this->nAppleEaten = 0;
    }

    /// @brief Aggiorna la posizione di snake e delle sue parti del corpo.
    /// @param speed Velocità di movimento.
    void Snake::UpdatePosition(float speed) {
        float currentHeadX = this->getHeadX();
        float currentHeadY = this->getHeadY();

        if (this->getHeadDirection() != ' ') {
            switch (this->getHeadDirection()) {
                case MovementDirection::UP:
                    currentHeadY += speed;
                    break;

                case MovementDirection::LEFT:
                    currentHeadX -= speed;
                    break;

                case MovementDirection::DOWN:
                    currentHeadY -= speed;
                    break;

                case MovementDirection::RIGHT:
                    currentHeadX += speed;
                    break;
                
                default:
                    break;
            }

            this->head.UpdatePosition(currentHeadX, currentHeadY);
        }
        
        if (this->getBodySize() > 0) {
            this->CheckBodyPartsDirectionChange();

            float newX;
            float newY;

            for (int i = 0; i < this->getBodySize(); i++) {
                SnakeBodyPart current = this->getBodyPart(i);

                newX = current.getX();
                newY = current.getY();

                switch (current.getDirection()) {
                    case MovementDirection::UP:
                        newY += speed;
                        break;

                    case MovementDirection::LEFT:
                        newX -= speed;
                        break;

                    case MovementDirection::DOWN:
                        newY -= speed;
                        break;

                    case MovementDirection::RIGHT:
                        newX += speed;
                        break;
                    
                    default:
                        break;
                }

                this->body.at(i).UpdatePosition(newX, newY);
            }
        }
    }
}