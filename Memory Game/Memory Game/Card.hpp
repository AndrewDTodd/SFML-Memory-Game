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

class Card : public sf::Drawable
{
private:
    static sf::Texture cardsTexture;
    
    sf::Sprite cardSprite;
    
    static sf::IntRect cardBackTextureRect;
    sf::IntRect cardFrontTexture;
    
    static std::string cardNames[52];
    
    bool fliped = false;
    
public:
    
    sf::Vector2f dimentions;
    float scale;
    std::string* cardName;
    uint8_t cardNumber;
    
    Card();
    Card(sf::IntRect cardTexRec, std::string* cardName, uint8_t& cardNumber);
    //Card(Card&& cardToMove);
    Card(Card& cardToCopy);
    ~Card();
    
    static void InitializeClass();
    
    void SetPosition(sf::Vector2f& cardPos);
    void SetScale(float& scale);
    float GetScale();
    void SetRotation(float& degrees);
    
    void SetPosition(sf::Vector2f&& cardPos);
    void SetScale(float&& scale);
    void SetRotation(float&& degrees);
    
    void SetTransform(sf::Vector2f& location, float& rotation, float& scale);
    void SetTransform(sf::Vector2f&& location, float&& rotation, float&& scale);
    
    sf::FloatRect getGlobalBounds();
    
    static Card deck[52];
    
    void FlipCard();
    static void FlipDeckCards();
    
    friend std::ostream& operator<<(std::ostream& stream, Card& card)
    {
        sf::Vector2f pos = card.cardSprite.getPosition();
        
        stream << *card.cardName << " Card Number: " << (int)card.cardNumber << std::endl << "Location: (" << pos.x << "," << pos.y << ")";
        
        return stream;
    }
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* Card_hpp */
