// /*
// 1) О чем
// 2) аналоги
// 3) реализация
// 4) структура
// 5) демонстрация
// */

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

int main()
{
    int height = 400;
    int width = 600;

    // create the window
    sf::RenderWindow window(sf::VideoMode(width, height), "My window", sf::Style::Close);
    std::vector <sf::CircleShape> lines;
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Image image;

    texture.create(width, height);

    int mousedown = 0;

    char command[] = "python3 ../python_script/script.py";
    int res;

    sf::Font font;
    
    if (!font.loadFromFile ("../PFAgoraSlabPro Bold.ttf"))
    {
        return 0;
    }

    sf::Text text;

    text.setFont (font);
    text.setCharacterSize (24);
    text.setFillColor (sf::Color::White);

    sf::Vector2f mouse_pos;

    auto my_draw = [&] (sf::CircleShape circle_) { window.draw(circle_); };

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();  
                    break;

                case sf::Event::MouseMoved:
                    if (mousedown == 1)
                    {
                        mouse_pos = sf::Vector2f (sf::Mouse::getPosition (window));
                        lines.emplace_back(10);
                        lines.back().setPosition (mouse_pos);
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    mousedown = 1;
                    break;

                case sf::Event::MouseButtonReleased:
                    mousedown = 0;

                    texture.update(window);

                    lines.clear();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Enter:
                            image = texture.copyToImage();
                        
                            image.saveToFile ("../pic.png");

                            res = system (command) / 256;

                            text.setString (std::to_string (res));

                            break;

                        case sf::Keyboard::Backspace:

                            window.clear(sf::Color::Black);
                            texture.update (window);
                            sprite.setTexture (texture);
                            lines.clear();

                            text.setString ("");
                            break;

                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                    
                        default:
                            break;
                    }

                    break;
                    

                default:
                    break;
            }
        }

        window.clear(sf::Color::Black);

        window.draw(sprite);

        std::for_each (lines.begin(), lines.end(), my_draw);

        window.draw (text);

        sprite.setTexture(texture);

        window.display();
    }

    return 0;
}
