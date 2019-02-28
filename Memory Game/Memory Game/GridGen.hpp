//
//  GridGen.h
//  Memory Game
//
//  Created by Andrew Todd on 2/21/19.
//  Copyright © 2019 Andrew Todd. All rights reserved.
//

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
    
    GridGenerator(uint8_t& rows, uint8_t& columns, uint16_t&  width, uint16_t& height)
    :Transformable()
    {
        this->grid = new GridCell<Type>[rows*columns];
        
        for (uint8_t r = 0; r < rows; r++)
        {
            for (uint8_t  c = 0; c < columns; c++)
            {
                this->grid[rows*r + c].location = sf::Vector2i(r,c);
            }
        }
        
        this->rows = rows;
        this->columns = columns;
        
        this->gridWidth = width;
        this->gridHeight = height;
    }
    GridGenerator(uint8_t&& rows, uint8_t&& columns, uint16_t&& width, uint16_t&& height)
    :Transformable(), rows(rows), columns(columns), gridWidth(width), gridHeight(height)
    {
        this->grid = new GridCell<Type>[rows*columns];
        
        for (uint8_t r = 0; r < rows; r++)
        {
            for (uint8_t  c = 0; c < columns; c++)
            {
                this->grid[rows*r + c].location = sf::Vector2i(r,c);
            }
        }
    }
    GridGenerator(uint8_t& rows, uint8_t& columns, uint16_t& width, uint16_t& height, Type* cellContentsArray)
    :Transformable()
    {
        uint8_t arrayLength = rows * columns;
        
        this->grid = new GridCell<Type>[arrayLength];
        
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
                this->grid[rows*r + c].location = sf::Vector2i(r,c);
            }
        }
    }
    GridGenerator(uint8_t&& rows, uint8_t&& columns, uint16_t&& width, uint16_t&& height, Type* cellContentsArray)
    :Transformable(), rows(rows), columns(columns), gridWidth(width), gridHeight(height)
    {
        uint8_t arrayLength = this->rows * this->columns;
        
        this->grid = new GridCell<Type>[arrayLength];
        
        for(uint8_t i = 0; i < arrayLength; i++)
        {
            this->grid[i].cellContents = &cellContentsArray[i];
        }
        
        for (uint8_t r = 0; r < rows; r++)
        {
            for (uint8_t  c = 0; c < columns; c++)
            {
                this->grid[rows*r + c].location = sf::Vector2i(r,c);
            }
        }
    }
    GridGenerator(uint8_t& rows, uint8_t& columns, GridCell<Type>* cellContentsArray)
    :Transformable()
    {
        this->grid = cellContentsArray;
        
        this->rows = rows;
        this->columns = columns;
    }
    GridGenerator(uint8_t&& rows, uint8_t&& columns, GridCell<Type>* cellContentsArray)
    :Transformable(), rows(rows), columns(columns)
    {
        this->grid = cellContentsArray;
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
    }
    
    void SetCellTransforms()
    {
        uint16_t cellWidth = this->gridWidth / this->columns;
        uint16_t cellHeight = this->gridHeight / this->rows;
        
        float rotation = this->getRotation();
        sf::Vector2f scale = this->getScale();
        
        for(uint8_t r = 0; r < this->rows; r++)
        {
            for(uint8_t c = 0; c < this->columns ; c++)
            {
                sf::Vector2f location = sf::Vector2f(c*cellWidth, r*cellHeight);
                
                this->grid[this->rows*r + c].cellContents->SetTransform(location, rotation, scale);
            }
        }
    }
    
    void FillCells()
    {
        uint16_t cellWidth = this->gridWidth / this->columns;
        uint16_t cellHeight = this->gridHeight / this->rows;
        
        for(uint8_t r = 0; r < this->rows; r++)
        {
            for(uint8_t c = 0; c < this->columns; c++)
            {
                uint8_t index = this->rows*r + c;
                
                uint16_t widthStretch = cellWidth / this->grid[index].cellContents->dimentions.x;
                uint16_t heightStretch = cellHeight / this->grid[index].cellContents->dimentions.y;
                
                float scale = heightStretch > widthStretch ? widthStretch:heightStretch;
                
                this->grid[index].cellContents->SetScale(sf::Vector2f(scale,scale));
            }
        }
    }
    
    friend std::ostream& operator<<(std::ostream& stream,GridGenerator<Type>& Grid)
    {
        for(uint8_t i = 0; i < Grid.rows; i++)
        {
            for(uint8_t u = 0; u < Grid.columns; u++)
            {
                stream << (Type)Grid.grid[Grid.rows*i + u].cellContents << ' ';
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
                target.draw(*(Type*)this->grid[this->rows*i + u].cellContents);
            }
        }
    }
};
#endif
