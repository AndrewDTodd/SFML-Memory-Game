//
//  Card.hpp
//  Memory Game
//
//  Created by Andrew Todd on 2/18/19.
//  Copyright © 2019 Andrew Todd. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Card
{
private:
    static sf::Texture cardsTexture;
    
    sf::Sprite cardSprite;
    
    static sf::IntRect cardBackTextureRect;
    sf::IntRect cardFrontTexture;
    
    static std::string cardNames[52];
    
    bool fliped = false;
    
public:
    std::string* cardName;
    
    Card();
    Card(sf::IntRect cardTexRec, std::string* cardName);
    //Card(Card&& cardToMove);
    Card(Card& cardToCopy);
    ~Card();
    
    static void InitializeClass();
    
    static Card deck[52];
    
    void FlipCard();
    
    friend std::ostream& operator<<(std::ostream& stream, Card& card);
    
    void QueForDraw(sf::RenderWindow* window);
};

#endif /* Card_hpp */
