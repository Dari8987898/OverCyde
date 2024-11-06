#include <random>
#include "GameLayer.h"

using namespace std;
using namespace Engine;

/**
 * Aggiunge una parte al corpo di snake.
 */
void GameLayer::AddSnakeBodyPart() {
    float newBodyX;
    float newBodyY;


    if (this->snakeBody.size() == 0) {
        newBodyX = this->snakeCurrentDirection == 'L' 
        ? this->snakeCurrentPositionX + (this->snakeSize[0] * 2)
        : this->snakeCurrentDirection == 'R' 
            ? this->snakeCurrentPositionX - (this->snakeSize[0] * 2)
            : this->snakeCurrentPositionX;

        newBodyY = this->snakeCurrentDirection == 'U' 
            ? this->snakeCurrentPositionY - (this->snakeSize[1] * 2)
            : this->snakeCurrentDirection == 'D' 
                ? this->snakeCurrentPositionY + (this->snakeSize[1] * 2)
                : this->snakeCurrentPositionY;
    } else {
        SnakeBodyPart last = this->snakeBody[this->snakeBody.size() - 1];

        newBodyX = last.currentDirection == 'L' 
        ? last.currentPositionX + (this->snakeSize[0] * 2)
        : last.currentDirection == 'R' 
            ? last.currentPositionX - (this->snakeSize[0] * 2)
            : last.currentPositionX;

        newBodyY = last.currentDirection == 'U' 
            ? last.currentPositionY - (this->snakeSize[1] * 2)
            : last.currentDirection == 'D' 
                ? last.currentPositionY + (this->snakeSize[1] * 2)
                : last.currentPositionY;
    }
    

    this->snakeBody.push_back(SnakeBodyPart(newBodyX, newBodyY, this->snakeCurrentDirection));
}

/**
 * Controlla se è avvenuta una collisione che provoca la morte.
 */
void GameLayer::CheckDeathCollision() {
    const float snakeRightEdge = this->snakeCurrentPositionX + (float)(this->snakeSize[0] / 2);
    const float snakeLeftEdge = this->snakeCurrentPositionX - (float)(this->snakeSize[0] / 2);
    const float snakeUpEdge = this->snakeCurrentPositionY + (float)(this->snakeSize[1] / 2);
    const float snakeDownEdge = this->snakeCurrentPositionY - (float)(this->snakeSize[1] / 2);

    if (
        snakeRightEdge >= 1
        || snakeLeftEdge <= -1
        || snakeUpEdge >= 1
        || snakeDownEdge <= -1
    ) {
        LOG_CLIENT_INFO("CHE FALLITO, SEI MORTO.");
        LOG_CLIENT_INFO("Hai mangiato {0} mele.", this->nAppleEaten);
        GameLayer::ResetGame();
    }
}

/**
 * Controlla se snake ha colliso con la mela.
 */
void GameLayer::CheckAppleCollision() {
    if (this->snakeCurrentPositionX + (float)(this->snakeSize[0] / 2) < this->appleCurrentPositionX - (float)(this->appleSize / 2)) return;
    if (this->snakeCurrentPositionX - (float)(this->snakeSize[0] / 2) > this->appleCurrentPositionX + (float)(this->appleSize / 2)) return;
    if (this->snakeCurrentPositionY + (float)(this->snakeSize[1] / 2) < this->appleCurrentPositionY - (float)(this->appleSize / 2)) return;
    if (this->snakeCurrentPositionY - (float)(this->snakeSize[1] / 2) > this->appleCurrentPositionY + (float)(this->appleSize / 2)) return;
    
    this->nAppleEaten++;
    this->appleEaten = true;
    this->appleDrawn = false;

    AddSnakeBodyPart();
}

/**
 * Genera una mela sullo schermo, se non è già presente.
 */
void GameLayer::DrawApple() {
    if (!this->appleDrawn) {
        this->appleDrawn = true;

        // Inizializzazione del generatore di numeri casuali
        random_device rd;  // Generatore per il seed
        mt19937 gen(rd()); // Generatore Mersenne Twister

        // Definizione dell'intervallo da -1.0 a 1.0
        uniform_real_distribution<float> dis(-1.0, 1.0);

        // Generazione di un numero casuale nell'intervallo
        this->appleCurrentPositionX = dis(gen);
        this->appleCurrentPositionY = dis(gen);
    }
    
    Renderer::Draw2DCircle(this->appleSize, Vec2f(this->appleCurrentPositionX, this->appleCurrentPositionY), this->appleColor, 0);
}

/**
 * Disegna snake.
 */
void GameLayer::DrawSnake() {
    // Disegno la testa.
    Renderer::Draw2DSquare(Vec2f(this->snakeCurrentPositionX, this->snakeCurrentPositionY), this->snakeSize, this->snakeColor, 0);

    for(int i = 0; i < this->snakeBody.size(); i++) {
        SnakeBodyPart current = this->snakeBody[i];
        Renderer::Draw2DSquare(Vec2f(current.currentPositionX, current.currentPositionY), this->snakeSize, this->snakeColor, 0);
    }
}

/**
 * Stabilisce quale key è stato premuto ed aggiorna la direzione di movimento di conseguenza.
 */
bool GameLayer::KeyPressed(KeyPressedEvent &kpe) {
    vector<int> indexes;
    for(int i = 0; i < this->snakeBody.size(); i++)
        indexes.push_back(i);
        
    switch (kpe.GetKeyCode()) {
        case Key::W:
            if (this->nAppleEaten < 1 || this->snakeCurrentDirection != 'D') {
                this->snakeCurrentDirection = 'U';

                if (this->nAppleEaten > 0)
                    directionChanges.push_back(DirectionChange(this->snakeCurrentPositionX, this->snakeCurrentPositionY, 'U', indexes));
            }
            break;

        case Key::A:
            if (this->nAppleEaten < 1 || this->snakeCurrentDirection != 'R') {
                this->snakeCurrentDirection = 'L';

                if (this->nAppleEaten > 0)
                    directionChanges.push_back(DirectionChange(this->snakeCurrentPositionX, this->snakeCurrentPositionY, 'L', indexes));
            }
            break;

        case Key::S:
            if (this->nAppleEaten < 1 || this->snakeCurrentDirection != 'U') {
                this->snakeCurrentDirection = 'D';

                if (this->nAppleEaten > 0)
                    directionChanges.push_back(DirectionChange(this->snakeCurrentPositionX, this->snakeCurrentPositionY, 'D', indexes));
            }
            break;

        case Key::D:
            if (this->nAppleEaten < 1 || this->snakeCurrentDirection != 'L') {
                this->snakeCurrentDirection = 'R';

                if (this->nAppleEaten > 0)
                    directionChanges.push_back(DirectionChange(this->snakeCurrentPositionX, this->snakeCurrentPositionY, 'R', indexes));
            }
                
            break;
        
        default:
            break;
    }

    return false;
}

/**
 * Resetta il gioco e logga le statistiche del gioco concluso.
 */
void GameLayer::ResetGame() {
    this->snakeCurrentPositionX = this->startingPosition[0];
    this->snakeCurrentPositionY = this->startingPosition[1];
    this->snakeCurrentDirection = this->startingDirection;
    this->appleDrawn = false;
    this->nAppleEaten = 0;
    this->directionChanges.clear();
    this->snakeBody.clear();

    LOG_CLIENT_INFO("\n\n\n\n\n\nGioco resettato.");
}

/**
 * Aggiorna la posizione in base alla direzione corrente.
 */
void GameLayer::UpdatePosition(float deltaTime) {
    const float normalizedSpeed = this->speed * deltaTime;

    if (this->snakeCurrentDirection != ' ') {
        switch (snakeCurrentDirection) {
            case 'U':
                this->snakeCurrentPositionY += normalizedSpeed;
                break;

            case 'L':
                this->snakeCurrentPositionX -= normalizedSpeed;
                break;

            case 'D':
                this->snakeCurrentPositionY -= normalizedSpeed;
                break;

            case 'R':
                this->snakeCurrentPositionX += normalizedSpeed;
                break;
            
            default:
                break;
        }
    }

    for (int i = 0; i < this->directionChanges.size(); i++) {
        DirectionChange dc = this->directionChanges[i];

        for (int j = 0; j < dc.snakeBodyIndexes.size(); j++) {
            SnakeBodyPart currentSB = this->snakeBody[j];

            bool changeDirection = false;
        
            switch (currentSB.currentDirection) {
                case 'U':
                    if (currentSB.currentPositionY >= dc.y)
                        changeDirection = true;
                    break;

                case 'R':
                    if (currentSB.currentPositionX >= dc.x)
                        changeDirection = true;
                    break;

                case 'D':
                    if (currentSB.currentPositionY <= dc.y)
                        changeDirection = true;
                    break;

                case 'L':
                    if (currentSB.currentPositionX <= dc.x)
                        changeDirection = true;
                    break;
            }

            if (changeDirection) {
                this->snakeBody.at(j).currentDirection = dc.direction;
                this->snakeBody.at(j).currentPositionX = dc.x;
                this->snakeBody.at(j).currentPositionY = dc.y;
                
                this->directionChanges.at(i).snakeBodyIndexes.erase(this->directionChanges.at(i).snakeBodyIndexes.begin() + j);
            }
        }
    }

    for(int i = 0; i < this->snakeBody.size(); i++) {
        switch (this->snakeBody.at(i).currentDirection) {
            case 'U':
                this->snakeBody.at(i).currentPositionY += normalizedSpeed;
                break;

            case 'L':
                this->snakeBody.at(i).currentPositionX -= normalizedSpeed;
                break;

            case 'D':
                this->snakeBody.at(i).currentPositionY -= normalizedSpeed;
                break;

            case 'R':
                this->snakeBody.at(i).currentPositionX += normalizedSpeed;
                break;
            
            default:
                break;
        }
    }
}

void GameLayer::OnEvent(Event& event) {
    EventDispatcher dispatcher = EventDispatcher(event);

    dispatcher.Dispatch<KeyPressedEvent>(BIND_FUN(GameLayer::KeyPressed));
}

void GameLayer::OnUpdate(float deltaTime) {
    Renderer::BeginScene(deltaTime);

    // Disegno la mela.
    this->DrawApple();

    // Aggiorno le variabili della posizione di snake.
    this->UpdatePosition(deltaTime);

    // Disegno snake.
    this->DrawSnake();

    // Controllo se snake è morto.
    this->CheckDeathCollision();

    // Controllo se snake sta mangiando una mela.
    this->CheckAppleCollision();
    
    Renderer::EndScene();
}