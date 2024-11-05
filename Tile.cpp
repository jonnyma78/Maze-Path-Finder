// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79

#include <iostream>
#include <vector>
#include <assert.h>
#include <string>
#include "Tile.h"

using namespace std;

Tile::Tile()
    : discovered(false), symbol('.'), room(0), row(0), col(0), direction('.') {}

Tile::Tile(const uint32_t room, const uint32_t row, const uint32_t col, const char symbol, const bool discovered)
    :  discovered(discovered), symbol(symbol), room(room), row(row), col(col){}



bool Tile::isPipe() const{
    if(symbol < 58 && symbol > 47){
        
        return 1;
    }
    return 0;
}


