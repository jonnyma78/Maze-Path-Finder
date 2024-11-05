// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <assert.h>
#include <vector>
#include <string>
#include "Tile.h"

using namespace std;

class Map{

    public:

        vector<vector<vector<Tile>>> tiles;
        Tile startingTile;
        Tile countessTile;
        uint32_t rooms;
        uint32_t dimensions;
        uint32_t discovered;
        
      

        //Default Constructor
        Map();

        //Effect: Initializes the Map
        Map(istream &is);

        //Effect: Print the map in map output mode
        void printMap(ostream &os);

        //Effect: Print the map in list output mode
        void printList(ostream &os);

        //Effect: Replaces the tile with a new symbol
        void replace(const Tile &tile, const char symbol); 

        //Effect: Returns true if north tile Walkable
        bool northWalkable(const Tile &tile);

        //Effect: Returns true if east tile Walkable
        bool eastWalkable(const Tile &tile);

        //Effect: Returns true if south tile Walkable
        bool southWalkable(const Tile &tile);

        //Effect: Returns true if west tile Walkable
        bool westWalkable(const Tile &tile);

        //Effect: returns a Tile north of the current tile
        //Requires: north tile exists
        Tile &north(const Tile &tile);

        //Effect: returns a Tile east of the current tile
        //Requires: east tile exists
        Tile &east(const Tile &tile);

        //Effect: returns a Tile south of the current tile
        //Requires: south tile exists
        Tile &south(const Tile &tile);

        //Effect: returns a Tile west of the current tile
        //Requires: west tile exists
        Tile &west(const Tile &tile);

        //Effect: returns true if the given tile is adjacent to the current tile
        bool rhsAdjacentToLhs(const Tile &tileOne, const Tile &tileTwo);

        //Effect: returns a bool of whether a tile is able to be stepped on
        bool isWalkable(Tile tile);

        //Effect: Returns the tile of the corresponding pipe tile
        Tile& pipedTile(Tile &tile);

    private:

        //Effect: Initialize the Map when input is type "list"
        void initializeL(const uint32_t rooms, const uint32_t dimensions);

        //Effect: Initialize the Map when input is type "map"
        void initializeM(const uint32_t rooms, const uint32_t dimensions);

        //Effect: Find the starting tile
        void checkS(Tile &tile);

        //Effect: Find the countess tile
        void checkC(Tile &tile);

};

#endif
