#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <torch/script.h>

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1375, 820), "neural network", sf::Style::Titlebar | sf::Style::Close);

    // sf::Clock clock;

    // sf::Font font;
    
    // if (!font.loadFromFile ("../PFAgoraSlabPro Bold.ttf"))
    // {
    //     return 0;
    // }

    // sf::Text text;

    // text.setFont (font);
    // text.setCharacterSize (24);
    // text.setFillColor (sf::Color::Black);

    // sf::Text names[6];

    // for (int i = 0; i < 6; ++i)
    // {
    //     names[i].setFont (font);
    //     names[i].setCharacterSize (24);
    //     names[i].setFillColor (sf::Color::Black);
    //     names[i].setPosition (sf::Vector2f (220 + (i % 3) * 425, 390 + (i / 3) * 360));
    // }

    // sf::FileInputStream streams[argc - 1];
    
    // for (int i = 0; i < argc - 1; ++i)
    //     streams[i].open(argv[i + 1]);

    // sf::Texture textures[argc - 1];
    
    // for (int i = 0; i < argc - 1; ++i)
    //     textures[i].loadFromStream(streams[i]);
    
    // sf::Sprite sprites[argc - 1];
    
    // for (int i = 0; i < argc - 1; ++i)
    // {
    //     sprites[i].setTexture(textures[i]);
    //     sprites[i].setPosition(sf::Vector2f (100 + (i % 3) * 425, 100 + ((i % 6) / 3) * 360));
    // }

    // unsigned j = 0;
    // unsigned fr = 0;
    // int str_number = 0;
    // int max_string = (argc + 4) / 6 - 1; //argc - 1 + 5

    // while (window.isOpen ())
    // {
    //     sf::Event event;
    //     sf::Time time = clock.getElapsedTime();
        
    //     while (window.pollEvent (event))
    //     {
    //         switch (event.type)
    //         {
    //             case sf::Event::Closed:
    //                 window.close();
    //                 break;
                
    //             case sf::Event::KeyPressed:
    //                 if (event.key.code == sf::Keyboard::Up)
    //                 {
    //                     if (str_number == max_string)
    //                         str_number = 0;

    //                     else
    //                         ++str_number;
    //                 }
                        
    //                 if (event.key.code == sf::Keyboard::Down)
    //                 {
    //                     if (str_number == 0)
    //                         str_number = max_string;

    //                     else
    //                         --str_number;
    //                 }

    //                 break;
                
    //             default:
    //                 break;
    //         }
    //     }


    //     ++j;

    //     if (j == 2000)
    //     {
    //         time = clock.restart();

    //         fr = j / time.asSeconds();
    //         j = 0;

    //         text.setString (std::to_string (fr));

    //         // std::cout << fr << std::endl;
    //     }   
    
    //     window.clear (sf::Color::White);
        
    //     for (int i = 0; i < 6 and str_number * 6 + i < argc - 1; ++i)
    //     {
    //         window.draw (sprites[str_number * 6 + i]);

    //         names[i].setString (argv[str_number * 6 + i + 1]);
    //         window.draw (names[i]);
    //     }

    //     window.draw (text);

    //     window.display();
    // }

    return 0;
}