
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

int main(int argc, char const** argv)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Card::InitializeClass();
    
    Card card[] = {Card::deck[0], Card::deck[1], Card::deck[2], Card::deck[3]};
    card[0].FlipCard();
    card[3].FlipCard();
    
    GridGenerator<Card>cardGrid(2,2,1920,1080,card);
    
    std::cout << cardGrid.gridHeight << std::endl;
    std::cout << cardGrid.gridWidth << std::endl;
    
    cardGrid.SetCellTransforms();

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
        }

        // Clear screen
        window.clear();

        window.draw(cardGrid);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
