//
//  GridGen.h
//  Memory Game
//
//  Created by Andrew Todd on 2/21/19.
//  Copyright © 2019 Andrew Todd. All rights reserved.
//


//-----------------------------------------------------
/*
    Template class GridGenerator is used to generate Grids of any given object.
    Maintains a pointer to an array of GridCell structs, also a templated object, that represent the grid's cells
    Each GridCell in turn maintains a pointer to the object in is "holding"
 
    For the purposes of this game the objects are Cards, defined in Card.hpp
*/

#ifndef GRID_GEN_H
#define GRID_GEN_H

#include<stdint.h>
#include<iostream>

#include <SFML/Graphics.hpp>


template<typename Type>
struct GridCell
{
    sf::Vector2i location;
    Type* cellContents;
};

template<typename Type>
class GridGenerator : public sf::Transformable, public sf::Drawable
{
private:
    GridCell<Type>* grid;
    
    uint8_t rows = 0;
    uint8_t columns = 0;
    
public:
    uint16_t gridWidth = 0;
    uint16_t gridHeight = 0;
    
    sf::FloatRect gridBoundingBox;
    
    sf::FloatRect* cellsBoundingBoxes;
    
    Type* lastThreeCards[3] = {nullptr, nullptr, nullptr};
    
    GridGenerator(uint8_t& rows, uint8_t& columns, uint16_t& xPos, uint16_t& yPos, uint16_t&  width, uint16_t& height)
    :Transformable()
    {
        this->grid = new GridCell<Type>[rows*columns];
        this->cellsBoundingBoxes = new sf::FloatRect[rows*columns];
        
        for (uint8_t r = 0; r < rows; r++)
        {
            for (uint8_t  c = 0; c < columns; c++)
            {
                this->grid[columns*r + c].location = sf::Vector2i(r,c);
            }
        }
        
        this->rows = rows;
        this->columns = columns;
        
        this->gridWidth = width;
        this->gridHeight = height;
        
        this->gridBoundingBox = sf::FloatRect(xPos,yPos,width,height);
    }
    GridGenerator(uint8_t&& rows, uint8_t&& columns,uint16_t&& xPos, uint16_t&& yPos, uint16_t&& width, uint16_t&& height)
    :Transformable(), rows(rows), columns(columns), gridWidth(width), gridHeight(height)
    {
        this->grid = new GridCell<Type>[rows*columns];
        
        this->cellsBoundingBoxes = new sf::FloatRect[rows*columns];
        
        for (uint8_t r = 0; r < rows; r++)
        {
            for (uint8_t  c = 0; c < columns; c++)
            {
                this->grid[columns*r + c].location = sf::Vector2i(r,c);
            }
        }
        
        this->gridBoundingBox = sf::FloatRect(xPos,yPos,width,height);
    }
    GridGenerator(uint8_t& rows, uint8_t& columns, uint16_t& xPos, uint16_t& yPos, uint16_t& width, uint16_t& height, Type* cellContentsArray)
    :Transformable()
    {
        uint8_t arrayLength = rows * columns;
        
        this->grid = new GridCell<Type>[arrayLength];
        
        this->cellsBoundingBoxes = new sf::FloatRect[rows*columns];
        
        this->rows = rows;
        this->columns = columns;
        
        this->gridWidth = width;
        this->gridHeight = height;
        
        for(uint8_t i = 0; i < arrayLength; i++)
        {
            this->grid[i].cellContents = &cellContentsArray[i];
        }
        
        for (uint8_t r = 0; r < rows; r++)
        {
            for (uint8_t  c = 0; c < columns; c++)
            {
                this->grid[columns*r + c].location = sf::Vector2i(r,c);
            }
        }
        
        this->gridBoundingBox = sf::FloatRect(xPos,yPos,width,height);
    }
    GridGenerator(uint8_t&& rows, uint8_t&& columns, uint16_t&& xPos, uint16_t&& yPos, uint16_t&& width, uint16_t&& height, Type* cellContentsArray)
    :Transformable(), rows(rows), columns(columns), gridWidth(width), gridHeight(height)
    {
        uint8_t arrayLength = this->rows * this->columns;
        
        this->grid = new GridCell<Type>[arrayLength];
        
        this->cellsBoundingBoxes = new sf::FloatRect[rows*columns];
        
        for(uint8_t i = 0; i < arrayLength; i++)
        {
            this->grid[i].cellContents = &cellContentsArray[i];
        }
        
        for (uint8_t r = 0; r < rows; r++)
        {
            for (uint8_t  c = 0; c < columns; c++)
            {
                this->grid[columns*r + c].location = sf::Vector2i(r,c);
            }
        }
        
        this->gridBoundingBox = sf::FloatRect(xPos,yPos,width,height);
    }
    GridGenerator(uint8_t& rows, uint8_t& columns, GridCell<Type>* cellContentsArray, uint16_t& xPos, uint16_t& yPos, uint16_t& width, uint16_t& height)
    :Transformable()
    {
        this->grid = cellContentsArray;
        
        this->rows = rows;
        this->columns = columns;
        
        this->gridWidth = width;
        this->gridHeight = height;
        
        this->gridBoundingBox = sf::FloatRect(xPos,yPos,width,height);
        
        this->cellsBoundingBoxes = new sf::FloatRect[rows*columns];

    }
    GridGenerator(uint8_t&& rows, uint8_t&& columns, GridCell<Type>* cellContentsArray, uint16_t&& xPos, uint16_t&& yPos, uint16_t&& width, uint16_t&& height)
    :Transformable(), rows(rows), columns(columns), gridWidth(width), gridHeight(height)
    {
        this->grid = cellContentsArray;
        
        this->gridBoundingBox = sf::FloatRect(xPos,yPos,width,height);
        
        this->cellsBoundingBoxes = new sf::FloatRect[rows*columns];
    }
    
    ~GridGenerator()
    {
        delete [] this->grid;
        this->grid = nullptr;
    }
    
    void FillGrid(Type* cellContentsArray)
    {
        uint8_t arrayLength = this->rows * this->columns;
        
        for(uint8_t i = 0; i < arrayLength; i++)
        {
            this->grid[i].cellContents = &cellContentsArray[i];
        }
        
        for (uint8_t r = 0; r < rows; r++)
        {
            for (uint8_t  c = 0; c < columns; c++)
            {
                this->grid[columns*r + c].location = sf::Vector2i(r,c);
            }
        }
    }
    
    void SetCellTransforms()
    {
        uint16_t cellWidth = this->gridWidth / this->columns;
        uint16_t cellHeight = this->gridHeight / this->rows;
        
        float rotation = this->getRotation();
        
        for(uint8_t r = 0; r < this->rows; r++)
        {
            for(uint8_t c = 0; c < this->columns ; c++)
            {
                float scale = this->grid[this->columns*r +c].cellContents->scale * this->getScale().x;
                float whiteSpaceX = cellWidth - (this->grid[this->columns*r +c].cellContents->dimentions.x * this->grid[this->columns*r +c].cellContents->scale);
                float whiteSpaceY = cellHeight - (this->grid[this->columns*r +c].cellContents->dimentions.y * this->grid[this->columns*r +c].cellContents->scale);
                float xLocation = c*cellWidth + (whiteSpaceX / 2);
                float yLocation = r*cellHeight + (whiteSpaceY / 2);
                
                sf::Vector2f location = sf::Vector2f(xLocation, yLocation);
                
                this->grid[this->columns*r + c].cellContents->SetTransform(location, rotation, scale);
                
                this->cellsBoundingBoxes[this->columns*r + c] = this->grid[this->columns*r + c].cellContents->getGlobalBounds();
            }
        }
    }
    
    void ClampCellContents()
    {
        uint16_t cellWidth = this->gridWidth / this->columns;
        uint16_t cellHeight = this->gridHeight / this->rows;
        
        //std::cout << "cell dimentions: " << cellWidth << "," << cellHeight << std::endl;
        
        for(uint8_t r = 0; r < this->rows; r++)
        {
            for(uint8_t c = 0; c < this->columns; c++)
            {
                uint8_t index = this->columns*r + c;
                
                float maxXScale = cellWidth / this->grid[index].cellContents->dimentions.x;
                
                float maxYScale = cellHeight / this->grid[index].cellContents->dimentions.y;
                
                //std::cout << "Maximum scales: " << maxXScale << "," << maxYScale << std::endl;
                
                float scale = maxXScale > maxYScale ? maxYScale:maxXScale;
                //std::cout << "scale is: " << scale << std::endl;
                
                this->grid[index].cellContents->SetScale(scale);
                //std::cout << "sprite scale is now: " << this->grid[index].cellContents->GetScale() << std::endl;
            }
        }
    }
    
    void HandleMouseEvent(sf::Vector2i location)
    {
        extern int PlayerScore;
        extern int TurnCount;
        
        
        bool stop = false;
        for(uint8_t r = 0; r < this->rows && !stop; r++)
        {
            for(uint8_t c = 0; c < this->columns && !stop; c++)
            {
                if(this->grid[this->columns*r +c].cellContents)
                {
                    if((this->cellsBoundingBoxes[this->columns*r + c].contains(location.x,location.y)) && (!this->grid[this->columns*r +c].cellContents->fliped))
                    {
                        this->grid[this->columns*r + c].cellContents->FlipCard();
                        
                        //cheack to see if you are begining a new series of card pairs
                        if(this->lastThreeCards[0])
                        {
                            //check to see if the last card you clicked on is the same kind as the one you just clicked on
                            //if it is you get points and the searies continues
                            if(this->lastThreeCards[0]->cardNumber == this->grid[this->columns*r + c].cellContents->cardNumber)
                            {
                                PlayerScore++;
                                
                                //check to see if you are clicking on a third card now
                                if(this->lastThreeCards[1])
                                {
                                    PlayerScore++;
                                    
                                    if(this->lastThreeCards[2])
                                    {
                                        PlayerScore++;
                                        
                                        this->removeCards(this->lastThreeCards[2]->cardNumber);
                                        
                                        this->lastThreeCards[2] = this->lastThreeCards[1] = this->lastThreeCards[0] = nullptr;
                                    }
                                    else
                                    {
                                        this->lastThreeCards[2] = this->lastThreeCards[1];
                                        this->lastThreeCards[1] = this->lastThreeCards[0];
                                        this->lastThreeCards[0] = this->grid[this->columns*r + c].cellContents;
                                    }
                                }
                                //if not we will keep track of the last two you clicked on because they are a pair
                                else
                                {
                                    this->lastThreeCards[1] = this->lastThreeCards[0];
                                    this->lastThreeCards[0] = this->grid[this->columns*r + c].cellContents;
                                }
                            }
                            //if the cards arnt the same, you get no points and the lastThreeCards needs to be reset for a new series
                            else
                            {
                                this->lastThreeCards[0]->FlipCard();
                                this->lastThreeCards[0] = this->grid[this->columns*r + c].cellContents;
                                
                                if(this->lastThreeCards[1])
                                {
                                    this->removeCards(this->lastThreeCards[1]->cardNumber);
                                    
                                    this->lastThreeCards[2] = nullptr;
                                    this->lastThreeCards[1] = nullptr;
                                    //this->lastThreeCards[0] = nullptr;
                                }
                            }
                        }
                        else
                        {
                            this->lastThreeCards[0] = this->grid[this->columns*r +c].cellContents;
                        }
                        
                        TurnCount++;
                        
                        stop = true;
                    }
                }
            }
        }
        
        if((this->lastThreeCards[1]))
        {
            if(this->lastThreeCards[0]->cardNumber == this->lastThreeCards[1]->cardNumber)
            {
                PlayerScore++;
            }
        }
    }
    
    friend std::ostream& operator<<(std::ostream& stream,GridGenerator<Type>& Grid)
    {
        for(uint8_t i = 0; i < Grid.rows; i++)
        {
            for(uint8_t u = 0; u < Grid.columns; u++)
            {
                stream << (Type)Grid.grid[Grid.columns*i + u].cellContents << ' ';
            }
            stream << std::endl;
        }
        
        return stream;
    }
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for(uint8_t i = 0; i < this->rows; i++)
        {
            for(uint8_t u = 0; u < this->columns; u++)
            {
                if(this->grid[this->columns*i + u].cellContents)
                    target.draw(*(Type*)this->grid[this->columns*i + u].cellContents);
            }
        }
    }
    
    void removeCards(uint8_t& cardNumber)
    {
        extern uint8_t CardCount;
        
        for(uint8_t r = 0; r < this->rows; r++)
        {
            for(uint8_t c = 0; c < this->columns; c++)
            {
                if(this->grid[this->columns*r +c].cellContents)
                {
                    if(this->grid[this->columns*r + c].cellContents->cardNumber == cardNumber)
                    {
                        this->grid[this->columns*r + c].cellContents = nullptr;
                    }
                }
            }
        }
        
        CardCount -= 4;
    }
};
#endif
