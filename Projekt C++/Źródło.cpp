#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Enemy {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;

public:
    Enemy(float x, float y) : velocity(0.f, 0.f) {
        shape.setPosition(x, y);
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Red);
    }

    void update(std::vector<Enemy>& all_enemies, float dt) {
        // Calculate separation vector to avoid collisions
        sf::Vector2f separation(0.f, 0.f);

        for (const auto& other : all_enemies) {
            if (&other != this) {
                sf::Vector2f toOther = other.getPosition() - getPosition();
                float distance = std::sqrt(toOther.x * toOther.x + toOther.y * toOther.y);

                // Adjust separation vector based on distance
                if (distance < 50.f) {
                    separation -= toOther / (distance * distance);
                }
            }
        }

        // Update velocity based on separation
        velocity += separation;

        // Update position based on velocity
        shape.move(velocity * dt);
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Collision Avoidance Example");

    std::vector<Enemy> all_enemies;
    all_enemies.emplace_back(100.f, 100.f);
    all_enemies.emplace_back(200.f, 200.f);
    // Add more enemies as needed...

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        // Update all enemies
        for (auto& enemy : all_enemies) {
            enemy.update(all_enemies, dt);
        }

        window.clear(sf::Color::White);

        // Draw all enemies
        for (const auto& enemy : all_enemies) {
            enemy.draw(window);
        }

        window.display();
    }

    return 0;
}
