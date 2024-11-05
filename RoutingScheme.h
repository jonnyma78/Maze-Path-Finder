// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79
#ifndef ROUTINGSCHEME_H
#define ROUTINGSCHEME_H

#include <iostream>
#include <deque>
#include <vector>
#include "Map.h"
#include "Tile.h"


class RoutingScheme{

    public:

    Map map;
    deque<Tile> route;
    vector<Tile> path;
    Tile location;
    string outputFormat;
    char containerType;
    bool countessFound;
    bool noSolution;

    //Effects: Initializes the database
    RoutingScheme(Map &mapOriginal, const char conType, const string &outForm);

    //Effects: Examines if the current tile is a pipe or the countess
    void examineLoc(const Tile &loc);
   
    //Effects: Moves Marco to the next tile in the stack/queue
    void move();

    //Effects: Returns a path of the route to the countess
    vector<Tile> backtrace(Map &map,const Tile &countess);


    //Effects: Prints out the map with NESW
    void mapOutput(Map &map, const Tile &countess);


    //Effects: Prints out the list with NESW
    void listOutput(Map &map,const Tile &countess);

    private:

    //Effects: Searches vicinity for nearby tiles and adds discoverable tiles to the deque
    void discover();






    
};
#endif 