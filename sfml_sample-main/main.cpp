#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SFML/Audio.hpp>

using namespace sf;

class Player 
{ // DOOM SLAYER
public:
    RectangleShape shape;
    float speed;

    Player(float x, float y) {
        shape.setSize(Vector2f(50.f, 50.f));
        shape.setFillColor(Color::White);
        shape.setPosition(x, y);
        speed = 10.f; // параметры скорости палыча
    }

    void update() { // передвижение
        if (Keyboard::isKeyPressed(Keyboard::W)) shape.move(0, -speed);
        if (Keyboard::isKeyPressed(Keyboard::S)) shape.move(0, speed);
        if (Keyboard::isKeyPressed(Keyboard::A)) shape.move(-speed, 0);
        if (Keyboard::isKeyPressed(Keyboard::D)) shape.move(speed, 0);
    }
};

class Bullet // ну типа пульки 
{ 
public:
    CircleShape shape;
    Vector2f velocity;
    bool active;

    Bullet(float x, float y, float dirX, float dirY) {
        shape.setRadius(5.f);
        shape.setFillColor(Color::Yellow);
        shape.setPosition(x, y);
        velocity = Vector2f(dirX * 10.f, dirY * 10.f);
        active = true;
    }

    void update() {
        shape.move(velocity);
        if (shape.getPosition().x < 0 || shape.getPosition().x > 800 ||
            shape.getPosition().y < 0 || shape.getPosition().y > 600) {
            active = false;
        }
    }
};

class Enemy
{ // класс с вражинами
public:
    CircleShape shape;
    float speed;

    Enemy(float x, float y)
    {
        shape.setRadius(25.f);
        shape.setFillColor(Color::Green);
        shape.setPosition(x, y);
        speed = 1.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.f));
    }

    void update(Vector2f playerPos) 
    {
        Vector2f direction = playerPos - shape.getPosition();
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) direction /= length;
        
        shape.move(direction * speed);
    }
}; 

class Boss 
{
public:
    CircleShape shape;
    float speed;

    Boss(float x, float y)
    {
        shape.setRadius(25.f);
        shape.setFillColor(Color::Red);
        shape.setPosition(x, y);
        speed = 1.f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.f));
    }

    void update(Vector2f playerPos) 
    {
        Vector2f direction = playerPos - shape.getPosition();
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) direction /= length;
        
        shape.move(direction * speed);
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    RenderWindow window(VideoMode(800, 600), "DOOM Palych VS ALIENS");
    window.setFramerateLimit(60);

    // sf::Music music;
    // music.openFromFile("C::/git/labs_sem2/sfml_sample-main/build/debug/mesivo.wav");
    // music.play();
    // system("pause");
    // музыка не пашет(((
    
    Player player(350.f, 300.f);
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    Clock enemySpawnClock;
    Clock enemySpawnBoss;
    Clock shootClock;

    // начальные хп и счет
    int score = 0;
    int health = 100;


    Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        font = Font();
        Text text;
        text.setFont(font);
        text.setString("Score: 0");
        text.setString("Health: 100");
    }

    Text scoreText; // счетчик рекорда
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10.f, 10.f);

    Text healthText; // счетчик здоровица
    healthText.setFont(font);
    healthText.setCharacterSize(24);
    healthText.setFillColor(Color::White);
    healthText.setPosition(10.f, 40.f);

    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // передвижение палыча
        player.update();

        // пострелушки
        if (Mouse::isButtonPressed(Mouse::Left) && shootClock.getElapsedTime().asSeconds() > 0.2f) 
        {
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            Vector2f playerPos = player.shape.getPosition() + Vector2f(25.f, 25.f);
            Vector2f direction = mousePos - playerPos;
            float length = sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length != 0) direction /= length;

            bullets.emplace_back(playerPos.x, playerPos.y, direction.x, direction.y);
            shootClock.restart();
        }

        // спавн пришельцев
        if (enemySpawnClock.getElapsedTime().asSeconds() > 1.f) 
        {
            float x = static_cast<float>(rand() % 800);
            float y = static_cast<float>(rand() % 600);
            enemies.emplace_back(x, y);
            enemySpawnClock.restart();
        }


        // добавление пулек 
        for (size_t i = 0; i < bullets.size();) 
        {
            bullets[i].update();
            if (!bullets[i].active) {
                bullets.erase(bullets.begin() + i);
            } else {
                i++;
            }
        }

        // добавление пришельцев
        for (size_t i = 0; i < enemies.size();) 
        {
            enemies[i].update(player.shape.getPosition() + Vector2f(25.f, 25.f));
            

            // проверка на попадение врага в палыча
            if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) 
            {
                health -= 10;
                enemies.erase(enemies.begin() + i);
                continue;
            }


            // проверка попадения палыча во врага
            bool erased = false;
            for (size_t j = 0; j < bullets.size() && !erased; j++) 
            {
                if (enemies[i].shape.getGlobalBounds().intersects(bullets[j].shape.getGlobalBounds())) 
                {
                    bullets.erase(bullets.begin() + j);
                    enemies.erase(enemies.begin() + i);
                    score += 10;
                    erased = true;
                }

            }

            if (!erased) i++;
        }

        // проверка здоровья
        if (health <= 0) 
        {
            window.close();
        }

        // обновление текста (не знаю почему но оно не работает, скорей всего из-за шрфита)
        scoreText.setString("Score: " + std::to_string(score));
        healthText.setString("Health: " + std::to_string(health));

        // отрисовка
        window.clear();

        window.draw(player.shape);

        // изображение пулек
        for (auto& bullet : bullets) 
        {
            window.draw(bullet.shape);
        }

        // изображение пришельцев
        for (auto& enemy : enemies) 
        {
            window.draw(enemy.shape);
        }


        // UI
        window.draw(scoreText);
        window.draw(healthText);

        window.display();
    }

    return 0;
}
