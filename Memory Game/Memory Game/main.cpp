
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Card.hpp"
#include "GridGen.hpp"
#include <stdlib.h>
#include <time.h>

int PlayerScore = 0;
int TurnCount = 0;

template<typename Type>
void ShuffleArray(Type* array, uint8_t& length)
{
    srand(time(nullptr));
    
    for(uint8_t i = 0; i < length; i++)
    {
        Type holder = array[i];
        
        uint8_t index = rand() % length;
        
        array[i] = array[index];
        array[index] = holder;
    }
}
template<typename Type>
void ShuffleArray(Type* array, uint8_t&& length)
{
    srand(time(nullptr));
    
    for(uint8_t i = 0; i < length; i++)
    {
        Type holder = array[i];
        
        uint8_t index = rand() % length;
        
        array[i] = array[index];
        array[index] = holder;
    }
}

int main(int argc, char const** argv)
{
    Card::InitializeClass();
    
    //Card::FlipDeckCards();
    
    ShuffleArray<Card>(Card::deck, 52);
    
    
    //Card cards[] = {Card::deck[0],Card::deck[1],Card::deck[2],Card::deck[3]};
    
    GridGenerator<Card>cardGrid(4,13,0,0,1920,1080,Card::deck);
    
    cardGrid.ClampCellContents();
    cardGrid.SetCellTransforms();
    
    //std::cout << Card::deck[0] << std::endl;
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                Card::FlipDeckCards();
            }
            
            if(event.type == sf::Event::MouseButtonReleased)
            {
                sf::Vector2i location = sf::Mouse::getPosition(window);
                cardGrid.HandleMouseEvent(location);
                
                std::cout << PlayerScore << std::endl;
                std::cout << TurnCount << std::endl;
            }
        }

        // Clear screen
        window.clear();

        window.draw(cardGrid);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
