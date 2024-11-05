// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79
#include <iostream>
#include <assert.h>
#include <vector>
#include <string>
#include "Tile.h"
#include "Map.h"

using namespace std;

Map::Map(){
    Tile tile;
    startingTile = tile;
    rooms = 0;
    dimensions = 0;
    discovered = 1;


}

Map::Map(istream &is){
    vector<vector<vector<Tile>>> tiles;
    vector<vector<Tile>> tilePlane;
    vector<Tile> tileRow;
    discovered = 1;
    char type;
    is>>type;
    is>>rooms;
    is>>dimensions;

    tiles.resize(rooms);
    tilePlane.resize(dimensions);
    tileRow.resize(dimensions);
    //int counter = 0;
    if(type == 'L'){
        
        string line;
        getline(cin,line);
        char symbol;
        
        for(uint32_t room = 0; room < rooms; ++room){
            for(uint32_t row = 0; row < dimensions; ++row){
                for(uint32_t col = 0; col < dimensions; ++col){
                    Tile tile(room, row, col, '.', false);
                    tileRow[col] = tile;
                }
                tilePlane[row] = tileRow;
                }
            tiles[room] = (tilePlane);
        }
        while(getline(cin, line)){
            uint32_t room = 0;
            uint32_t row = 0;
            uint32_t col = 0;
            while(line[0] == '/'){
                getline(cin,line);
            }
            symbol = line[line.find(')') - 1];
            if(symbol != '#' && symbol != '!' && symbol != '.'
                    && (symbol < 48 || symbol > 57) && symbol != 'C'
                    && symbol != 'S'){
                        cerr<<"Unknown map character\n";
                        exit(1);
            }
            line = line.substr(1, line.length());
            for(uint8_t i = 0; i < 3; ++i){
                uint32_t commaLoc = static_cast<uint32_t>(line.find(','));
                string number = line.substr(0,commaLoc);
                uint32_t num = stoi(number);
                line = line.substr(commaLoc + 1, line.length() - commaLoc - 1);
                if(i == 0){
                    room = num;
                    if(room >= rooms){
                        cerr << "Invalid room number\n";
                        exit(1);
                    }
                }
                else if(i == 1){
                    row = num;
                    if(row >= dimensions){
                        cerr <<"Invalid row number\n";
                        exit(1);        
                    }
                }
                else{
                    col = num;
                    if(col >= dimensions){
                        cerr <<"Invalid column number\n";
                        exit(1);
                    }
                }
            }
            Tile tile(room, row, col, symbol, false);
            checkS(tile);            
            tiles[room][row][col] = tile;          
    }

    }//end of L initialization

    if(type == 'M'){
    string line;
    getline(cin,line);
    for(uint32_t room = 0; room < rooms; ++room){
        for(uint32_t row = 0; row < dimensions; ++row ){
            getline(cin,line);
            while(line[0] == '/'){
                getline(cin,line);
            }
            for(uint32_t col = 0; col < dimensions; ++col){
                char symbol = line.at(col);
                if(symbol != '#' && symbol != '!' && symbol != '.'
                && (symbol < 48 || symbol > 57) && symbol != 'C'
                && symbol != 'S'){
                    cerr<<"Unknown map character\n";
                    exit(1);
                }
                Tile tile(room, row, col, symbol, false);
                //tile.printTile(cout);
                checkS(tile);
                tileRow[col] = tile;
                //counter++;
            }
            tilePlane[row] = (tileRow);
        }//for row
        tiles[room] = (tilePlane);

    }//for room

}//if
    Map::tiles = tiles;
    Map::tiles.resize(rooms);
}   


bool Map::northWalkable(const Tile &tile){
    if(tile.row == 0){
        return 0;
    }
    else if(isWalkable(tiles[tile.room][tile.row-1][tile.col])){
        return 1;
    }
    return 0;

}

bool Map::eastWalkable(const Tile &tile){
    if(tile.col == dimensions -1){
        return 0;
    }
    else if(isWalkable(tiles[tile.room][tile.row][tile.col + 1])){
        return 1;
    }
    return 0;
}

bool Map::southWalkable(const Tile &tile){
    if(tile.row == dimensions - 1){
        return 0;
    }
    else if(isWalkable(tiles[tile.room][tile.row + 1][tile.col])){
        return 1;
    }
    return 0;
}

bool Map::westWalkable(const Tile &tile){
    if(tile.col == 0){
        return 0;
    }
    else if(isWalkable(tiles[tile.room][tile.row][tile.col - 1])){
        return 1;
    }
    return 0;
}

Tile& Map::north(const Tile &tile){
    return (tiles)[tile.room][tile.row - 1][tile.col];
}

Tile& Map::east(const Tile &tile){
    return tiles[tile.room][tile.row][tile.col + 1];
}

Tile& Map::south(const Tile &tile){
    return tiles[tile.room][tile.row + 1][tile.col];
}

Tile& Map::west(const Tile &tile){
    return tiles[tile.room][tile.row][tile.col - 1];
    
}


bool Map::isWalkable(Tile tile){
   
    if(tile.discovered){
        return 0;
    }

    if(tile.symbol == '!' || tile.symbol == '#'){
        return 0;
    }
    return 1;
}

Tile& Map::pipedTile(Tile &tile){
    uint32_t newRoom = static_cast<uint32_t>(tile.symbol - '0');
    Tile &newLoc = Map::tiles[newRoom][tile.row][tile.col];
    return newLoc;
}

void Map::checkS(Tile &tile){
    if(tile.symbol == 'S'){
        startingTile = tile;
        startingTile.discovered = true;
        tile.discovered = true;
    }
}

