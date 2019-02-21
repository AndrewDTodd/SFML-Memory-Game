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
#include "Vector2.h"


template<typename Type>
struct GridCell
{
    Vector2 location = Vector2();
    Type cellContents;
};

template<typename Type>
class GridGenerator
{
private:
    GridCell<Type>* grid;
    
    uint8_t rows = 0;
    uint8_t columns = 0;
    
public:
    GridGenerator(uint8_t& rows, uint8_t& columns)
    {
        this->grid = new GridCell<Type>[rows*columns];
        
        this->rows = rows;
        this->columns = columns;
    }
    GridGenerator(uint8_t&& rows, uint8_t&& columns)
    :rows(rows), columns(columns)
    {
        this->grid = new GridCell<Type>[rows*columns];
    }
    GridGenerator(uint8_t& rows, uint8_t& columns, Type* cellContentsArray)
    {
        uint8_t arrayLength = rows * columns;
        
        this->grid = new GridCell<Type>[arrayLength];
        
        this->rows = rows;
        this->columns = columns;
        
        for(uint8_t i = 0; i < arrayLength; i++)
        {
            this->grid[i].cellContents = cellContentsArray[i];
        }
    }
    GridGenerator(uint8_t&& rows, uint8_t&& columns, Type* cellContentsArray)
    :rows(rows), columns(columns)
    {
        uint8_t arrayLength = this->rows * this->columns;
        
        this->grid = new GridCell<Type>[arrayLength];
        
        for(uint8_t i = 0; i < arrayLength; i++)
        {
            this->grid[i].cellContents = cellContentsArray[i];
        }
    }
    GridGenerator(uint8_t& rows, uint8_t& columns, GridCell<Type>* cellContentsArray)
    {
        this->grid = cellContentsArray;
        
        this->rows = rows;
        this->columns = columns;
    }
    GridGenerator(uint8_t&& rows, uint8_t&& columns, GridCell<Type>* cellContentsArray)
    :rows(rows), columns(columns)
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
            this->grid[i].cellContents = cellContentsArray[i];
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
};
#endif
