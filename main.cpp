#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>

#include "GameState.h"
#include "Utils.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML AIR HOCKEY");

    // TITLE SCREEN
    sf::Font font;
    sf::Text title;
    sf::Text prompt;

    if (!font.loadFromFile("./Fonts/COMIC.TTF"))
    {
        std::cerr << "Font is broken, quitting game!" << std::endl;
        return -1;
    }

    // BACKGROUND COLOR
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color::Color(0xEE, 0xEE, 0xFF));

    title.setFont(font);
    title.setString("SFML Air Hockey");
    title.setCharacterSize(84);
    title.setFillColor(sf::Color::Green);
    title.setStyle(sf::Text::Bold);
    title.setPosition(sf::Vector2f(700, 200));

    prompt.setFont(font);
    prompt.setString("Press ENTER to begin playing!");
    prompt.setCharacterSize(64);
    prompt.setFillColor(sf::Color::Green);
    prompt.setStyle(sf::Text::Bold);
    prompt.setPosition(sf::Vector2f(500, 400));

    sf::Text red_wins;
    red_wins.setFont(font);
    red_wins.setString("Red Wins!");
    red_wins.setCharacterSize(84);
    red_wins.setFillColor(sf::Color::Red);
    red_wins.setStyle(sf::Text::Bold);
    red_wins.setPosition(sf::Vector2f(500, 200));

    sf::Text blue_wins;
    blue_wins.setFont(font);
    blue_wins.setString("Blue Wins!");
    blue_wins.setCharacterSize(84);
    blue_wins.setFillColor(sf::Color::Blue);
    blue_wins.setStyle(sf::Text::Bold);
    blue_wins.setPosition(sf::Vector2f(500, 200));

    sf::Text play_again_prompt;
    play_again_prompt.setFont(font);
    play_again_prompt.setString("Press ENTER to play again!");
    play_again_prompt.setFillColor(sf::Color::Black);
    play_again_prompt.setCharacterSize(64);
    play_again_prompt.setStyle(sf::Text::Bold);
    play_again_prompt.setPosition(sf::Vector2f(200, 400));

    bool puck_been_hit_yet = false;

    // GAME STATE INITIALIZATION
    GameState state = GameState::MENU;

    // SPAWN PUCK
    sf::RectangleShape puck_hitbox(sf::Vector2f(40, 40));
    puck_hitbox.setFillColor(sf::Color::Color(0x0F, 0xAF, 0x50));
    puck_hitbox.setPosition(sf::Vector2f(window.getSize().x / 2 - puck_hitbox.getSize().x / 2, window.getSize().y / 2));

    // MIDLINE
    sf::RectangleShape midline(sf::Vector2f(20, window.getSize().y));
    midline.setPosition(sf::Vector2f(window.getSize().x / 2 - 10, 0));
    midline.setFillColor(sf::Color::Color(10, 87, 51));

    // BOUNDARY
    sf::RectangleShape top_bound(sf::Vector2f(window.getSize().x, 20));
    top_bound.setPosition(0, 0);
    top_bound.setFillColor(sf::Color::Color(255, 87, 51));
    sf::RectangleShape bottom_bound(sf::Vector2f(window.getSize().x, 20));
    bottom_bound.setPosition(0, window.getSize().y - 20);
    bottom_bound.setFillColor(sf::Color::Color(255, 87, 51));
    sf::RectangleShape left_bound(sf::Vector2f(20, window.getSize().y));
    left_bound.setPosition(0, 0);
    left_bound.setFillColor(sf::Color::Color(255, 87, 51));
    sf::RectangleShape right_bound(sf::Vector2f(20, window.getSize().y));
    right_bound.setPosition(window.getSize().x - 20, 0);
    right_bound.setFillColor(sf::Color::Color(255, 87, 51));

    // GOAL POSTS
    sf::RectangleShape left_goal(sf::Vector2f(20, window.getSize().y / 5));
    left_goal.setFillColor(sf::Color::Black);
    left_goal.setPosition(0, 2 * window.getSize().y / 5);

    sf::RectangleShape right_goal(sf::Vector2f(20, window.getSize().y / 5));
    right_goal.setFillColor(sf::Color::Black);
    right_goal.setPosition(window.getSize().x - 20, 2 * window.getSize().y / 5);

    // RED PLAYER
    sf::RectangleShape red_boi(sf::Vector2f(60, 60));
    red_boi.setFillColor(sf::Color::Red);
    red_boi.setPosition(40.f, 540.f);

    // BLUE PLAYER
    sf::RectangleShape blue_boi(sf::Vector2f(60, 60));
    blue_boi.setFillColor(sf::Color::Blue);
    blue_boi.setPosition(WIDTH - 40 - 60, 540);

    // PUCK START DIRECTION
    srand(time(NULL));
    float x_vel_puck = rand() % 2 == 1 ? 1.f : -1.f;
    srand(time(NULL));
    float y_vel_puck = rand() % 2 == 1 ? 1.f : -1.f;
    std::cout << "X rand: " << x_vel_puck << std::endl;
    std::cout << "Y rand: " << y_vel_puck << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        switch (state)
        {
        case GameState::MENU:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                state = GameState::TUTORIAL;
                window.setTitle("TUTORIAL STATE");
            }
            window.clear();
            window.draw(title);
            window.draw(prompt);
            window.display();
            break;
        case GameState::TUTORIAL:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                state = GameState::GAME;
                window.setTitle("GAME STATE");
            }
            window.clear();

            // RED MOVEMENT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && red_boi.getPosition().x > 20)
            {
                red_boi.move(sf::Vector2f(-1, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && red_boi.getPosition().y < HEIGHT - 20 - red_boi.getSize().y)
            {
                red_boi.move(sf::Vector2f(0, 1));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && red_boi.getPosition().x < midline.getPosition().x - red_boi.getSize().x)
            {
                red_boi.move(sf::Vector2f(1, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && red_boi.getPosition().y > 20)
            {
                red_boi.move(sf::Vector2f(0, -1));
            }

            // BLUE MOVEMENT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && blue_boi.getPosition().x > midline.getPosition().x + 20)
            {
                blue_boi.move(sf::Vector2f(-1, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && blue_boi.getPosition().y < HEIGHT - 20 - blue_boi.getSize().y)
            {
                blue_boi.move(sf::Vector2f(0, 1));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && blue_boi.getPosition().x < WIDTH - 20 - blue_boi.getSize().x)
            {
                blue_boi.move(sf::Vector2f(1, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && blue_boi.getPosition().y > 20)
            {
                blue_boi.move(sf::Vector2f(0, -1));
            }

            window.draw(background);
            window.draw(midline);
            window.draw(top_bound);
            window.draw(bottom_bound);
            window.draw(left_bound);
            window.draw(right_bound);
            window.draw(left_goal);
            window.draw(right_goal);

            window.draw(red_boi);
            window.draw(blue_boi);
            window.draw(puck_hitbox);
            window.display();
            break;
        case GameState::GAME:
            window.clear();

            // RED MOVEMENT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && red_boi.getPosition().x > 20)
            {
                red_boi.move(sf::Vector2f(-1, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && red_boi.getPosition().y < HEIGHT - 20 - red_boi.getSize().y)
            {
                red_boi.move(sf::Vector2f(0, 1));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && red_boi.getPosition().x < midline.getPosition().x - red_boi.getSize().x)
            {
                red_boi.move(sf::Vector2f(1, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && red_boi.getPosition().y > 20)
            {
                red_boi.move(sf::Vector2f(0, -1));
            }

            // BLUE MOVEMENT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && blue_boi.getPosition().x > midline.getPosition().x + 20)
            {
                blue_boi.move(sf::Vector2f(-1, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && blue_boi.getPosition().y < HEIGHT - 20 - blue_boi.getSize().y)
            {
                blue_boi.move(sf::Vector2f(0, 1));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && blue_boi.getPosition().x < WIDTH - 20 - blue_boi.getSize().x)
            {
                blue_boi.move(sf::Vector2f(1, 0));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && blue_boi.getPosition().y > 20)
            {
                blue_boi.move(sf::Vector2f(0, -1));
            }

            // PUCK MOVEMENT       
            if (!puck_been_hit_yet)
                puck_hitbox.move(x_vel_puck * 0.125f, y_vel_puck * 0.125f);
            else
                puck_hitbox.move(x_vel_puck, y_vel_puck);

            if (puck_hitbox.getPosition().y <= 20)
                y_vel_puck = 1.0f;
            else if (puck_hitbox.getPosition().y >= HEIGHT - 20 - puck_hitbox.getSize().y)
                y_vel_puck = -1.0f;
            else if (puck_hitbox.getPosition().x <= 20)
                x_vel_puck = 1.0f;
            else if (puck_hitbox.getPosition().x >= WIDTH - 20 - puck_hitbox.getSize().x)
                x_vel_puck = -1.0f;

            // PUCK HITS RED RIGHT SIDE [x]
            if (puck_hitbox.getPosition().x - (red_boi.getPosition().x + red_boi.getSize().x) <= 0
                && puck_hitbox.getPosition().x - (red_boi.getPosition().x + red_boi.getSize().x) >= -8
                && puck_hitbox.getPosition().y <= red_boi.getPosition().y + red_boi.getSize().y
                && puck_hitbox.getPosition().y >= red_boi.getPosition().y - puck_hitbox.getSize().y)
            {
                x_vel_puck = 1.0f;
                puck_been_hit_yet = true;
            }

            // PUCK HITS RED LEFT SIDE [x]
            if (puck_hitbox.getPosition().x + puck_hitbox.getSize().x - red_boi.getPosition().x >= 0
                && puck_hitbox.getPosition().x + puck_hitbox.getSize().x - red_boi.getPosition().x <= 8
                && puck_hitbox.getPosition().y <= red_boi.getPosition().y + red_boi.getSize().y
                && puck_hitbox.getPosition().y >= red_boi.getPosition().y - puck_hitbox.getSize().y)
            {
                x_vel_puck = -1.0f;
                puck_been_hit_yet = true;
            }

            // PUCK HITS RED TOP SIDE [x]
            // original bound: puck_hitbox.getPosition().y + puck_hitbox.getSize().y == red_boi.getPosition().y
            if (puck_hitbox.getPosition().y + puck_hitbox.getSize().y  - red_boi.getPosition().y >= 0
                && puck_hitbox.getPosition().y + puck_hitbox.getSize().y - red_boi.getPosition().y <= 8
                && puck_hitbox.getPosition().x <= red_boi.getPosition().x + red_boi.getSize().x
                && puck_hitbox.getPosition().x >= red_boi.getPosition().x - puck_hitbox.getSize().x)
            {
                y_vel_puck = -1.0f;
                puck_been_hit_yet = true;
            }

            // PUCK HITS RED BOTTOM SIDE [x]
            // orig bound: puck_hitbox.getPosition().y == red_boi.getPosition().y + red_boi.getSize().y
            if (puck_hitbox.getPosition().y - (red_boi.getPosition().y + red_boi.getSize().y) >= 0
                && puck_hitbox.getPosition().y - (red_boi.getPosition().y + red_boi.getSize().y) <= 8
                && puck_hitbox.getPosition().x <= red_boi.getPosition().x + red_boi.getSize().x
                && puck_hitbox.getPosition().x >= red_boi.getPosition().x - puck_hitbox.getSize().x)
            {
                y_vel_puck = 1.0f;
                puck_been_hit_yet = true;
            }

            // PUCK HITS BLUE RIGHT SIDE [x]
            if (puck_hitbox.getPosition().x - (blue_boi.getPosition().x + blue_boi.getSize().x) <= 0
                && puck_hitbox.getPosition().x - (blue_boi.getPosition().x + blue_boi.getSize().x) >= -8
                && puck_hitbox.getPosition().y <= blue_boi.getPosition().y + blue_boi.getSize().y
                && puck_hitbox.getPosition().y >= blue_boi.getPosition().y - puck_hitbox.getSize().y)
            {
                x_vel_puck = 1.0f;
                puck_been_hit_yet = true;
            }

            // PUCK HITS BLUE LEFT SIDE [x]
            if (puck_hitbox.getPosition().x + puck_hitbox.getSize().x - blue_boi.getPosition().x >= 0
                && puck_hitbox.getPosition().x + puck_hitbox.getSize().x - blue_boi.getPosition().x <= 8
                && puck_hitbox.getPosition().y <= blue_boi.getPosition().y + blue_boi.getSize().y
                && puck_hitbox.getPosition().y >= blue_boi.getPosition().y - puck_hitbox.getSize().y)
            {
                x_vel_puck = -1.0f;
                puck_been_hit_yet = true;
            }

            // PUCK HITS BLUE TOP SIDE [x]
            if (puck_hitbox.getPosition().y + puck_hitbox.getSize().y - blue_boi.getPosition().y >= 0
                && puck_hitbox.getPosition().y + puck_hitbox.getSize().y - blue_boi.getPosition().y <= 8
                && puck_hitbox.getPosition().x <= blue_boi.getPosition().x + blue_boi.getSize().x
                && puck_hitbox.getPosition().x >= blue_boi.getPosition().x - puck_hitbox.getSize().x)
            {
                y_vel_puck = -1.0f;
                puck_been_hit_yet = true;
            }

            // PUCK HITS BLUE BOTTOM SIDE [x]
            if (puck_hitbox.getPosition().y - (blue_boi.getPosition().y + blue_boi.getSize().y) >= 0
                && puck_hitbox.getPosition().y - (blue_boi.getPosition().y + blue_boi.getSize().y) <= 8
                && puck_hitbox.getPosition().x <= blue_boi.getPosition().x + blue_boi.getSize().x
                && puck_hitbox.getPosition().x >= blue_boi.getPosition().x - puck_hitbox.getSize().x)
            {
                y_vel_puck = 1.0f;
                puck_been_hit_yet = true;
            }

            // PUCK HITS BLUE'S GOAL
            if (puck_hitbox.getPosition().x + puck_hitbox.getSize().x >= right_goal.getPosition().x
                && puck_hitbox.getPosition().y >= right_goal.getPosition().y
                && puck_hitbox.getPosition().y + puck_hitbox.getSize().y <= right_goal.getPosition().y + right_goal.getSize().y)
            {

                state = GameState::REDWIN;
                window.setTitle("RED WINS");
            }

            // PUCK HITS RED'S GOAL
            if (puck_hitbox.getPosition().x <= left_goal.getPosition().x + left_goal.getSize().x
                && puck_hitbox.getPosition().y >= left_goal.getPosition().y
                && puck_hitbox.getPosition().y + puck_hitbox.getSize().y <= left_goal.getPosition().y + left_goal.getSize().y)
            {
                state = GameState::BLUEWIN;
                window.setTitle("BLUE WINS");
            }

            window.draw(background);
            window.draw(midline);
            window.draw(top_bound);
            window.draw(bottom_bound);
            window.draw(left_bound);
            window.draw(right_bound);
            window.draw(left_goal);
            window.draw(right_goal);

            window.draw(red_boi);
            window.draw(blue_boi);
            window.draw(puck_hitbox);
            window.display();
            break;
        case GameState::REDWIN:
            window.clear();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                state = GameState::TUTORIAL;
                window.setTitle("TUTORIAL STATE");
            }

            puck_hitbox.setPosition(sf::Vector2f(WIDTH - 100 - puck_hitbox.getSize().x, window.getSize().y / 2));
            puck_been_hit_yet = false;

            play_again_prompt.setFillColor(sf::Color::Red);

            window.draw(background);
            window.draw(midline);
            window.draw(top_bound);
            window.draw(bottom_bound);
            window.draw(left_bound);
            window.draw(right_bound);
            window.draw(left_goal);
            window.draw(right_goal);
            window.draw(red_wins);
            window.draw(play_again_prompt);
            window.display();
            break;
        case GameState::BLUEWIN:
            window.clear();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                state = GameState::TUTORIAL;
                window.setTitle("TUTORIAL STATE");
            }

            puck_hitbox.setPosition(sf::Vector2f(100, window.getSize().y / 2));
            puck_been_hit_yet = false;

            play_again_prompt.setFillColor(sf::Color::Blue);

            window.draw(background);
            window.draw(midline);
            window.draw(top_bound);
            window.draw(bottom_bound);
            window.draw(left_bound);
            window.draw(right_bound);
            window.draw(left_goal);
            window.draw(right_goal);
            window.draw(blue_wins);
            window.draw(play_again_prompt);
            window.display();
            break;
        default:
            break;
        }

        
    }

    return 0;
}