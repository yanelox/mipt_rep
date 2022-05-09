// #include <SFML/Graphics.hpp>
// #include <iostream>
// #include <string>
// #include <cstdlib>

// int main(int argc, char* argv[])
// {
//     if (argc <= 1)
//     {
//         std::cout << "incorrect input\n";

//         return 0;
//     }       

//     int results[argc - 1];

//     char res[1000];

//     for (int i = 0; i < argc - 1; ++i)
//     {
//         sprintf (res, "python3 ../python_script/script.py %s", argv[i + 1]);

//         results[i] = system (res) / 256;
//     }

//     sf::RenderWindow window {sf::VideoMode(1375, 820), "neural network", sf::Style::Titlebar | sf::Style::Close};

//     sf::Clock clock;

//     sf::Font font;
    
//     if (!font.loadFromFile ("../PFAgoraSlabPro Bold.ttf"))
//     {
//         return 0;
//     }

//     sf::Text text;

//     text.setFont (font);
//     text.setCharacterSize (24);
//     text.setFillColor (sf::Color::Black);

//     sf::Text names[6];

//     for (int i = 0; i < 6; ++i)
//     {
//         names[i].setFont (font);
//         names[i].setCharacterSize (24);
//         names[i].setFillColor (sf::Color::Black);
//         names[i].setPosition (sf::Vector2f (260 + (i % 3) * 425, 390 + (i / 3) * 360));
//     }

//     sf::FileInputStream streams[argc - 1];
    
//     for (int i = 0; i < argc - 1; ++i)
//         streams[i].open(argv[i + 1]);

//     sf::Texture textures[argc - 1];
    
//     for (int i = 0; i < argc - 1; ++i)
//         textures[i].loadFromStream(streams[i]);
    
//     sf::Sprite sprites[argc - 1];
    
//     for (int i = 0; i < argc - 1; ++i)
//     {
//         sprites[i].setTexture(textures[i]);
//         sprites[i].setPosition(sf::Vector2f (100 + (i % 3) * 425, 100 + ((i % 6) / 3) * 360));
//     }

//     unsigned j = 0;
//     unsigned fr = 0;
//     int str_number = 0;
//     int max_string = (argc + 4) / 6 - 1; //argc - 1 + 5

//     while (window.isOpen ())
//     {
//         sf::Event event;
//         sf::Time time = clock.getElapsedTime();
        
//         while (window.pollEvent (event))
//         {
//             switch (event.type)
//             {
//                 case sf::Event::Closed:
//                     window.close();
//                     break;
                
//                 case sf::Event::KeyPressed:
//                     if (event.key.code == sf::Keyboard::Down)
//                     {
//                         if (str_number == max_string)
//                             str_number = 0;

//                         else
//                             ++str_number;
//                     }
                        
//                     if (event.key.code == sf::Keyboard::Up)
//                     {
//                         if (str_number == 0)
//                             str_number = max_string;

//                         else
//                             --str_number;
//                     }

//                     break;
                
//                 default:
//                     break;
//             }
//         }


//         ++j;

//         if (j == 2000)
//         {
//             time = clock.restart();

//             fr = j / time.asSeconds();
//             j = 0;

//             text.setString (std::to_string (fr));

//             // std::cout << fr << std::endl;
//         }   
    
//         window.clear (sf::Color::White);
        
//         for (int i = 0; i < 6 and str_number * 6 + i < argc - 1; ++i)
//         {
//             window.draw (sprites[str_number * 6 + i]);

//             names[i].setString (std::to_string (results[str_number * 6 + i]));
//             window.draw (names[i]);
//         }

//         window.draw (text);

//         window.display();
//     }

//     return 0;
// }

// /*
// 1) О чем
// 2) аналоги
// 3) реализация
// 4) структура
// 5) демонстрация
// */

#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    int height = 400;
    int width = 600;

    // create the window
    sf::RenderWindow window(sf::VideoMode(width, height), "My window", sf::Style::Close);
    // std::vector <sf::CircleShape> lines(100);
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Image image;

    texture.create(width, height);

    int mousedown = 0;

    window.setFramerateLimit(30);

    char command[] = "python3 ../python_script/script.py ../pic.png >> /dev/null";
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

    std::vector <sf::Vertex> mouse_pos;

    sf::CircleShape circle_(5);

    auto my_draw = [&] (sf::Vertex& pos) { circle_.setPosition (pos.position); window.draw(circle_); };

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
                        mouse_pos.emplace_back (sf::Vector2f (sf::Mouse::getPosition (window)));
                        // lines.emplace_back(5);
                        // lines.back().setPosition (mouse_pos);
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    mousedown = 1;
                    break;

                case sf::Event::MouseButtonReleased:
                    mousedown = 0;

                    std::for_each (mouse_pos.begin(), mouse_pos.end(), my_draw);

                    texture.update(window);

                    // lines.clear();
                    mouse_pos.clear();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Enter:
                            image.saveToFile ("../pic.png");

                            res = system (command) / 256;

                            text.setString (std::to_string (res));

                            break;

                        case sf::Keyboard::Backspace:
                            image = texture.copyToImage();

                            window.clear(sf::Color::Black);
                            texture.update (window);
                            sprite.setTexture (texture);

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

        if (mousedown == 1)
        {
            window.draw (&mouse_pos[0], mouse_pos.size(), sf::LinesStrip);
        }

        else
        {
            window.clear(sf::Color::Black);

            window.draw(sprite);

            window.draw (text);

            sprite.setTexture(texture);
        }

        window.display();
    }

    return 0;
}
