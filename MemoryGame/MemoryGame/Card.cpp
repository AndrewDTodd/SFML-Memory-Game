//
//  Card.cpp
//  MemoryGame
//
//  Created by Andrew Todd on 2/14/19.
//  Copyright © 2019 Andrew Todd. All rights reserved.
//

#include "Card.hpp"
#include <SFML/Graphics.hpp>

std::string Card::cardNames[] = {"Ace of Clubs", "Two of CLubs", "Three of CLubs", "Four of Clubs", "Five of Clubs", "Six of Clubs", "Seven of Clubs", "Eight of Clubs", "Nine of Clubs", "Ten of CLubs", "Jack of CLubs", "Queen of Clubs", "King of Clubs",
    
    "Ace of Diamonds", "Two of Diamonds", "Three of Diamonds", "Four of Diamonds", "Five of Diamonds", "Six of Diamonds", "Seven of Diamonds", "Eight of Diamonds", "Nine of Diamonds", "Ten of Diamonds", "Jack of Diamonds", "Queen of Diamonds", "King of Diamonds",
    
    "Ace of Hearts", "Two of Hearts", "Three of Hearts", "Four of Hearts", "Five of Hearts", "Six of Hearts", "Seven of Hearts", "Eight of Hearts", "Nine of Hearts", "Ten of Hearts", "Jack of Hearts", "Queen of Hearts", "King of Hearts",
    
    "Ace of Spades", "Two of Spades", "Three of Spades", "Four of Spades", "Five of Spades", "Six of Spades", "Seven of Spades", "Eight of Spades", "Nine of Spades", "Ten of Spades", "Jack of Spades", "Queen of Spades", "King of Spades"
};

Card::Card(sf::IntRect cardTexRec, std::string* cardName)
{
    this->cardSprite.setTextureRect(Card::cardBackTextureRect);
    this->cardFrontTexture = cardTexRec;
    this->cardName = cardName;
}
Card::~Card()
{
    
}

void Card::InitializeClass()
{
    Card::cardsTexture.loadFromFile("Cards.png");
    
    int i = 0;
    for(int y = 0; y < 492; y+123)
    {
        for(int x = 0; x < 948; x+79)
        {
            Card::deck[i] = Card(sf::IntRect(x,y,79,123), &Card::cardNames[i]);
            i++;
        }
    }
    
    Card::cardBackTextureRect = sf::IntRect(158,492,79,123);
}

void Card::FlipCard()
{
    if(this->fliped)
    {
        this->cardSprite.setTextureRect(Card::cardBackTextureRect);
    }
    else
    {
        this->cardSprite.setTextureRect(this->cardFrontTexture);
    }
    this->fliped = !this->fliped;
}

std::ostream& operator<<(std::ostream& stream, Card card)
{
    stream << *card.cardName;
    
    return stream;
}

void Card::QueForDraw(sf::RenderWindow* win)
{
    win->draw(this->cardSprite);
}
