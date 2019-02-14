//
//  Card.hpp
//  MemoryGame
//
//  Created by Andrew Todd on 2/14/19.
//  Copyright © 2019 Andrew Todd. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#include <SFML/Graphics.hpp>

class Card
{
private:
    static sf::Texture cardsTexture;
    
    sf::Sprite cardSprite;
    
    static sf::IntRect cardBackTextureRect;
    sf::IntRect cardFrontTexture;
    
    std::string* cardName;
    
    static std::string cardNames[52];
    
    bool fliped = false;
    
public:
    Card(sf::IntRect cardTexRec, std::string* cardName);
    ~Card();
    
    static void InitializeClass();
    
    static Card deck[52];
    
    void FlipCard();
    
    friend std::ostream& operator<<(std::ostream& stream, Card card);
    
    void QueForDraw(sf::RenderWindow* window);
};

#endif /* Card_hpp */
