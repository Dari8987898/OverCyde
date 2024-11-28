#include <random>
#include "GameLayer.h"

using namespace std;
using namespace Engine;
using namespace SnakePackage;
using namespace SnakePackageUtil;

/// @brief Aggiunge una parte al corpo di snake.
void GameLayer::AddSnakeBodyPart() {
    float newBodyX;
    float newBodyY;
    
    if (this->snake.getBodySize() == 0) {
        switch (this->snake.getHeadDirection()) {
            case MovementDirection::LEFT:
                newBodyX = this->snake.getHeadX() + (this->snakeDimension[0] * 2);
                newBodyY = this->snake.getHeadY();
                break;

            case MovementDirection::RIGHT:
                newBodyX = this->snake.getHeadX() - (this->snakeDimension[0] * 2);
                newBodyY = this->snake.getHeadY();
                break;

            case MovementDirection::UP:
                newBodyX = this->snake.getHeadX();
                newBodyY = this->snake.getHeadY() - (this->snakeDimension[1] * 2);
                break;

            case MovementDirection::DOWN:
                newBodyX = this->snake.getHeadX();
                newBodyY = this->snake.getHeadY() + (this->snakeDimension[1] * 2);
                break;

            default:
                return;
        }

        this->snake.AddBodyPart(newBodyX, newBodyY, this->snake.getHeadDirection());
    } else {
        SnakeBodyPart last = this->snake.getBodyPart(this->snake.getBodySize() - 1);
        
        switch (last.getDirection()) {
            case MovementDirection::LEFT:
                newBodyX = last.getX() + (this->snakeDimension[0] * 2);
                newBodyY = last.getY();
                break;

            case MovementDirection::RIGHT:
                newBodyX = last.getX() - (this->snakeDimension[0] * 2);
                newBodyY = last.getY();
                break;

            case MovementDirection::UP:
                newBodyX = last.getX();
                newBodyY = last.getY() - (this->snakeDimension[1] * 2);
                break;

            case MovementDirection::DOWN:
                newBodyX = last.getX();
                newBodyY = last.getY() + (this->snakeDimension[1] * 2);
                break;

            default:
                return;
        }

        this->snake.AddBodyPart(newBodyX, newBodyY, last.getDirection());
    }
}

/// @brief Controlla se snake ha colliso con i bordi dello schermo.
void GameLayer::CheckDeathCollision() {
    const float snakeRightEdge = this->snake.getHeadX() + (float)(this->snakeDimension[0] / 2);
    const float snakeLeftEdge = this->snake.getHeadX() - (float)(this->snakeDimension[0] / 2);
    const float snakeUpEdge = this->snake.getHeadY() + (float)(this->snakeDimension[1] / 2);
    const float snakeDownEdge = this->snake.getHeadY() - (float)(this->snakeDimension[1] / 2);

    if (
        snakeRightEdge >= 1
        || snakeLeftEdge <= -1
        || snakeUpEdge >= 1
        || snakeDownEdge <= -1
    ) {
        LOG_CLIENT_INFO(' ');
        LOG_CLIENT_INFO("CHE FALLITO, SEI MORTO.");
        LOG_CLIENT_INFO("Hai mangiato {0} mele.", this->snake.nAppleEaten);

        GameLayer::ResetGame();
    }
}

/// @brief Controlla se snake ha colliso con la mela.
void GameLayer::CheckAppleCollision() {
    if (this->snake.getHeadX() + (float)(this->snakeDimension[0] / 2) < this->appleCurrentPositionX - (float)(this->appleDimension / 2)) return;
    if (this->snake.getHeadX() - (float)(this->snakeDimension[0] / 2) > this->appleCurrentPositionX + (float)(this->appleDimension / 2)) return;
    if (this->snake.getHeadY() + (float)(this->snakeDimension[1] / 2) < this->appleCurrentPositionY - (float)(this->appleDimension / 2)) return;
    if (this->snake.getHeadY() - (float)(this->snakeDimension[1] / 2) > this->appleCurrentPositionY + (float)(this->appleDimension / 2)) return;
    
    this->snake.nAppleEaten++;
    this->appleEaten = true;
    this->appleDrawn = false;

    AddSnakeBodyPart();
}

/// @brief Genera una mela sullo schermo, se non è già presente.
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
    
    Renderer::Draw2DCircle(this->appleDimension, Vec2f(this->appleCurrentPositionX, this->appleCurrentPositionY), this->appleColor, 0);
}

/// @brief Disegna i cambi di direzione di snake sullo schermo.
void GameLayer::DrawDirectionChanges() {
    vector<DirectionChange> directionChanges = this->snake.getDirectionChanges();

    for (int i = 0; i < directionChanges.size(); i++) {
        DirectionChange dc = directionChanges[i];

        Renderer::Draw2DCircle(0.01, Vec2f(dc.x, dc.y), Vec4f(90, 90, 255, 0), 0);
    }
}

/// @brief Disegna snake sullo schermo.
void GameLayer::DrawSnake() {
    // Disegno la testa.
    Renderer::Draw2DSquare(Vec2f(this->snake.getHeadX(), this->snake.getHeadY()), this->snakeDimension, this->snakeColor, 0);

    for(int i = 0; i < this->snake.getBodySize(); i++) {
        SnakeBodyPart current = this->snake.getBodyPart(i);
        Renderer::Draw2DSquare(Vec2f(current.getX(), current.getY()), this->snakeDimension, this->snakeColor, 0);
    }
}

/// @brief Stabilisce quale key è stato premuto ed aggiorna la direzione di movimento di conseguenza.
/// @param kpe Oggetto KeyPressedEvent.
bool GameLayer::KeyPressed(KeyPressedEvent &kpe) {
    vector<int> indexes;

    for(int i = 0; i < this->snake.getBodySize(); i++)
        indexes.push_back(i);
    
    switch (kpe.GetKeyCode()) {
        case Key::W:
            if (this->snake.nAppleEaten < 1 || this->snake.getHeadDirection() != 'D')
                this->snake.ChangeDirection(MovementDirection::UP);

            break;

        case Key::A:
            if (this->snake.nAppleEaten < 1 || this->snake.getHeadDirection() != 'R')
                this->snake.ChangeDirection(MovementDirection::LEFT);
            
            break;

        case Key::S:
            if (this->snake.nAppleEaten < 1 || this->snake.getHeadDirection() != 'U')
                this->snake.ChangeDirection(MovementDirection::DOWN);
            
            break;
            break;

        case Key::D:
            if (this->snake.nAppleEaten < 1 || this->snake.getHeadDirection() != 'L')
                this->snake.ChangeDirection(MovementDirection::RIGHT);
            
            break;
        
        default:
            break;
    }

    return true;
}

/// @brief Resetta il gioco e logga le statistiche.
void GameLayer::ResetGame() {
    this->snake.Reset();
    this->appleDrawn = false;

    LOG_CLIENT_INFO("Gioco resettato.");
}

/// @brief Aggiorna la posizione di snake.
void GameLayer::UpdatePosition(float deltaTime) {
    const float normalizedSpeed = this->speed * deltaTime;

    this->snake.UpdatePosition(normalizedSpeed);
}

void GameLayer::OnEvent(Event& event) {
    EventDispatcher dispatcher = EventDispatcher(event);

    dispatcher.Dispatch<KeyPressedEvent>(BIND_FUN(GameLayer::KeyPressed));
}

void GameLayer::OnUpdate(float deltaTime) {
    Renderer::BeginScene(deltaTime);

    // Disegno i cambi di direzione di snake.
    this->DrawDirectionChanges();

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