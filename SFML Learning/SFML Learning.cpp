#include <SFML/Graphics.hpp>

class GravitySource
{
    sf::Vector2f pos;
    float strength;
    sf::CircleShape s;


public:
    GravitySource(float pos_x, float pos_y, float strength)
    {
        pos.x = pos_x;
        pos.y = pos_y;
        this->strength = strength;

        s.setPosition(pos);
        s.setFillColor(sf::Color::White);
        s.setRadius(10);
    }

    void render(sf::RenderWindow& wind)
    {
        wind.draw(s);
    }

    sf::Vector2f get_pos()
    {
        return pos;
    }

    float get_strength()
    {
        return strength;
    }
};

class Particle
{
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::CircleShape s;


public:
    Particle(float pos_x, float pos_y, float vel_x, float vel_y)
    {
        pos.x = pos_x;
        pos.y = pos_y;

        vel.x = vel_x;
        vel.y = vel_y;

        s.setPosition(pos);
        s.setFillColor(sf::Color::Blue);
        s.setRadius(6);
    }

    void render(sf::RenderWindow& wind)
    {
        s.setPosition(pos);
        wind.draw(s);
    }

    void update_physics(GravitySource &s)
    {
        float distance_x = s.get_pos().x - pos.x;
        float distance_y = s.get_pos().y - pos.y;

        float distance = sqrt(distance_x * distance_x + distance_y * distance_y);

        float inverse_distance = 1.f / distance;

        float normalized_x = inverse_distance * distance_x;
        float normalized_y = inverse_distance * distance_y;

        float inverse_square_dropoff = inverse_distance * inverse_distance;

        float acceleration_x = normalized_x * s.get_strength() * inverse_square_dropoff;
        float acceleration_y = normalized_y * s.get_strength() * inverse_square_dropoff;

        vel.x += acceleration_x;
        vel.y += acceleration_y;

        pos.x += vel.x;
        pos.y += vel.y;

    }

};


int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "My Program");
    window.setFramerateLimit(60);

    GravitySource source(800, 500, 7000);

    Particle particle_one(600, 700, 4, 0);
    Particle particle_two(1000, 300, 4, 0);
    Particle particle_three(900, 200, 2, 0);
    Particle particle_four(700, 800, 2, 0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        window.clear();
        particle_one.update_physics(source);
        particle_two.update_physics(source);
        particle_three.update_physics(source);
        particle_four.update_physics(source);

        source.render(window);
        particle_one.render(window);
        particle_two.render(window);
        particle_three.render(window);
        particle_four.render(window);
        //draw calls
        window.display();
    }
    return 0;
}