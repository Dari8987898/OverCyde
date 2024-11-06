namespace SnakePackage {
    class SnakeBodyPart {
        public:
            // Costruttori
            SnakeBodyPart(float x, float y, char direction) : x(x), y(y), direction(direction) {}

            // Get
            float getX() const { return x; }
            float getY() const { return y; }
            char getDirection() const { return direction; }

            // Metodi
            void ChangeDirection(char direction);
            void UpdatePosition(float x, float y);
            
        private:
            float x;
            float y;
            char direction;
    };
}