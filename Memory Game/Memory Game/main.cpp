
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

//
//  Memory Game
//
//  Created by Andrew Todd on 2/21/19.
//  Copyright © 2019 Andrew Todd. All rights reserved.
//

//---------------------------------------------------------------------------
/*
    Memory Game is a simple card flipping memory game that is built on top of SFML
 
    ******************************************************************************
    This means you need SFML Framework to compile and need to follow the above instructions in the above disclaimer from the SFML team
    ******************************************************************************
 
 //////////////////////////////////////////////////////////////////////////////////////////////////////
    ---->The game allows the player to flip all the cards by pressing the Enter/Return key<----
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Card.hpp"
#include "GridGen.hpp"
#include <stdlib.h>
#include <time.h>


//this global variable is incremented by the game board ("grid") HandleMouseEvent method
//player is awarded points for finding pairs, and then three or four of a kind
int PlayerScore = 0;
//this global variable is incremented by the game board ("grid") HandleMouseEvent method
//increased for every card flip
int TurnCount = 0;
//maintains the number of cards cerently on the board
uint8_t CardCount = 52;


//simple swap shuffle function
//used to shuffle the Card::deck
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
//simple swap shuffle function
//used to shuffle the Card::deck
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
    //must be called
    //creates the Card::deck array used for the game
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
            //for mouse clicks send location to cardGrid for event handling
            if(event.type == sf::Event::MouseButtonReleased)
            {
                sf::Vector2i location = sf::Mouse::getPosition(window);
                cardGrid.HandleMouseEvent(location);
            }
        }

        // Clear screen
        window.clear();

        //gridGen is SFML aware and so is Card
        //they both have sf::Draw functionality being inherited from sf::Drawable
        window.draw(cardGrid);

        // Update the window
        window.display();
        
        //when there are no more cards, close the game and display user points and turn count
        if(CardCount <= 0)
        {
            window.close();
            std::cout << std::endl << std::endl << "Your Final score was: " << PlayerScore << std::endl;
            std::cout << "You took " << TurnCount << " turns to compleat the game" << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
