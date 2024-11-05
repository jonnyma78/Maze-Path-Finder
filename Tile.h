// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79
#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <assert.h>
#include <vector>
#include <string>


class Tile{
    public:
        bool discovered;
        char symbol;
        uint32_t room, row, col;
        char direction;


       
    
        //Effect: Default constructor
        Tile();

        //Effect: initializes a tile of room, row, col, and symbol
        Tile(const uint32_t room, const uint32_t row, const uint32_t col, const char symbol, const bool discovered);

        //Effect: takes symbol and determines if it is an integer (pipe)
        bool isPipe() const;


};


#endif
