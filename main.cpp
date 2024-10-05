#include <SFML/Graphics.hpp>
#include <time.h>

const int M = 20;
const int N = 10;

int field[M][N] = {0};

struct Point {
    int x, y;
} a[4], b[4];

int figures[7][4] = {
    1, 3, 5, 7,
    2, 4, 5, 7,
    3, 5, 4, 6,
    3, 5, 4, 7,
    2, 3, 5, 7,
    3, 5, 7, 6,
    2, 3, 4, 5
};

sf::Color colors[8] = {
    sf::Color::Transparent,
    sf::Color::Cyan,
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Yellow,
    sf::Color::Magenta,
    sf::Color::Blue,
    sf::Color::White
};

bool check() {
    for (int i = 0; i < 4; i++) {
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return false;
        if (field[a[i].y][a[i].x]) return false;
    }
    return true;
}

int main() {
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(320, 640), "Tetris");

    int dx = 0;
    bool rotate = false;
    int colorNum = 1;
    float timer = 0, delay = 0.3;

    sf::Clock clock;

    sf::RectangleShape block(sf::Vector2f(32, 32));

    int n = rand() % 7;
    for (int i = 0; i < 4; i++) {
        a[i].x = figures[n][i] % 2 + N / 2 - 1;
        a[i].y = figures[n][i] / 2;
    }

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Up)
                    rotate = true;
                else if (e.key.code == sf::Keyboard::Left)
                    dx = -1;
                else if (e.key.code == sf::Keyboard::Right)
                    dx = 1;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delay = 0.05;

        for (int i = 0; i < 4; i++) {
            b[i] = a[i];
            a[i].x += dx;
        }
        if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];

        if (rotate) {
            Point p = a[1];
            for (int i = 0; i < 4; i++) {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
        }

        if (timer > delay) {
            for (int i = 0; i < 4; i++) {
                b[i] = a[i];
                a[i].y += 1;
            }

            if (!check()) {
                for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;

                colorNum = 1 + rand() % 7;
                n = rand() % 7;
                for (int i = 0; i < 4; i++) {
                    a[i].x = figures[n][i] % 2 + N / 2 - 1;
                    a[i].y = figures[n][i] / 2;
                }
            }

            timer = 0;
        }

        int k = M - 1;
        for (int i = M - 1; i > 0; i--) {
            int count = 0;
            for (int j = 0; j < N; j++) {
                if (field[i][j]) count++;
                field[k][j] = field[i][j];
            }
            if (count < N) k--;
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (field[i][j] == 0) continue;
                block.setFillColor(colors[field[i][j]]);
                block.setPosition(j * 32, i * 32);
                block.move(28, 31);
                window.draw(block);
            }
        }

        for (int i = 0; i < 4; i++) {
            block.setFillColor(colors[colorNum]);
            block.setPosition(a[i].x * 32, a[i].y * 32);
            block.move(28, 31);
            window.draw(block);
        }

        window.display();

        dx = 0;
        rotate = 0;
        delay = 0.3;
    }

    return 0;
}
