//
//  Vector2.h
//  Memory Game
//
//  Created by Andrew Todd on 2/21/19.
//  Copyright © 2019 Andrew Todd. All rights reserved.
//

#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2
{
    uint8_t x;
    uint8_t y;
    uint8_t magnitude;
    
    Vector2(uint8_t& x, uint8_t y)
    {
        this->x = x;
        this->y = y;
        this->magnitude += x;
        this->magnitude += y;
        this->magnitude = sqrt(this->magnitude);
    }
    Vector2()
    {
        this->x = 0;
        this->y = 0;
        this->magnitude = 0;
    }
};
#endif
