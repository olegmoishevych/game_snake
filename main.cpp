#include <SFML/Graphics.hpp>
#include <vector>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int SIZE = 20;

class Snake {
public:
    Snake() {
        snake.push_back(sf::RectangleShape(sf::Vector2f(SIZE, SIZE)));
        snake[0].setPosition(100, 100);
        snake[0].setFillColor(sf::Color::Green);
    }

    void move() {
        // Перемещаем все сегменты, начиная с конца
        for (int i = snake.size() - 1; i > 0; --i) {
            snake[i].setPosition(snake[i - 1].getPosition());
        }

        // Двигаем голову
        switch (direction) {
            case 0: snake[0].move(0, -SIZE); break;  // Вверх
            case 1: snake[0].move(SIZE, 0); break;   // Вправо
            case 2: snake[0].move(0, SIZE); break;   // Вниз
            case 3: snake[0].move(-SIZE, 0); break;  // Влево
        }

        // Проверяем границы экрана и "заворачиваем" змейку
        if (snake[0].getPosition().x < 0)
            snake[0].setPosition(WIDTH - SIZE, snake[0].getPosition().y);
        if (snake[0].getPosition().x >= WIDTH)
            snake[0].setPosition(0, snake[0].getPosition().y);
        if (snake[0].getPosition().y < 0)
            snake[0].setPosition(snake[0].getPosition().x, HEIGHT - SIZE);
        if (snake[0].getPosition().y >= HEIGHT)
            snake[0].setPosition(snake[0].getPosition().x, 0);
    }

    void setDirection(int dir) {
        direction = dir;
    }

    void draw(sf::RenderWindow& window) {
        for (auto& segment : snake) {
            window.draw(segment);
        }
    }

private:
    std::vector<sf::RectangleShape> snake;
    int direction = 1;  // Начальное направление движения: вправо
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake Game");

    Snake snake;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Управление с клавиатуры
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) snake.setDirection(0);
                if (event.key.code == sf::Keyboard::Right) snake.setDirection(1);
                if (event.key.code == sf::Keyboard::Down) snake.setDirection(2);
                if (event.key.code == sf::Keyboard::Left) snake.setDirection(3);
            }
        }

        // Обновляем змейку каждые 0.1 секунды
        if (clock.getElapsedTime().asSeconds() > 0.1f) {
            snake.move();
            clock.restart();
        }

        // Рендерим
        window.clear();
        snake.draw(window);
        window.display();
    }

    return 0;
}
