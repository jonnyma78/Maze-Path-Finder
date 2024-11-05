// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79

#include <iostream>
#include <deque>
#include <vector>
#include "Map.h"
#include "Tile.h"
#include "RoutingScheme.h"

using namespace std;



RoutingScheme::RoutingScheme(Map &mapOriginal, const char conType, const string &outFormat){
    map = mapOriginal;
    location = map.startingTile;
    (route).push_back(location);
    countessFound = 0;
    noSolution = 0;
    containerType = conType;
    outputFormat = outFormat;

     
}

 
void RoutingScheme::move(){
    if(containerType == 'S'){
        while(!countessFound && !noSolution){
            Tile pipeExit;
            if(!route.back().isPipe()){
                location = route.back();
            }
            else{
                pipeExit = route.back();
            }
            route.pop_back();
            examineLoc(location);
            while(pipeExit.isPipe() && !countessFound){
 
                uint32_t rm = pipeExit.room;
                char roomNum = static_cast<char>(rm + '0');
                
                if(static_cast<uint32_t>(pipeExit.symbol - '0') >= map.rooms){
                    break;
                }
                pipeExit = map.pipedTile(pipeExit);
                if(map.isWalkable(pipeExit) && !map.tiles[pipeExit.room][pipeExit.row][pipeExit.col].discovered){
                        
                        map.tiles[pipeExit.room][pipeExit.row][pipeExit.col].discovered = true;
                        map.tiles[pipeExit.room][pipeExit.row][pipeExit.col].direction = roomNum;
                        map.discovered++;
                       

                    if(!pipeExit.isPipe()){
                        route.push_back(pipeExit);
                        map.tiles[pipeExit.room][pipeExit.row][pipeExit.col].discovered = true;
                        map.tiles[pipeExit.room][pipeExit.row][pipeExit.col].direction = roomNum;
                        location = pipeExit;
                        examineLoc(location);
                    }
                }
                else{
                    break;
                }
            }
            discover();
            if(route.empty()){
                noSolution = true;
                cout<<"No solution, ";
                cout<<map.discovered;
                cout<<" tiles discovered.";
            }
        }
    }
    else if(containerType == 'Q'){
        while(!countessFound && !noSolution){
            Tile pipeExit;
            if(!route.front().isPipe()){
                location = route.front();
            }
            else{
                pipeExit = route.front();
            }
            route.pop_front();
            examineLoc(location);
            while(pipeExit.isPipe() && !countessFound){
 
                uint32_t rm = pipeExit.room;
                char roomNum = static_cast<char>(rm + '0');
                
                if(static_cast<uint32_t>(pipeExit.symbol - '0') >= map.rooms){
                    break;
                }
                pipeExit = map.pipedTile(pipeExit);
                if(map.isWalkable(pipeExit) && !map.tiles[pipeExit.room][pipeExit.row][pipeExit.col].discovered){
                        
                        map.tiles[pipeExit.room][pipeExit.row][pipeExit.col].discovered = true;
                        map.tiles[pipeExit.room][pipeExit.row][pipeExit.col].direction = roomNum;
                        map.discovered++;
                        route.push_back(pipeExit);
                        break;                       

                    if(!pipeExit.isPipe()){
                        route.push_back(pipeExit);
                        map.tiles[pipeExit.room][pipeExit.row][pipeExit.col].discovered = true;
                        map.tiles[pipeExit.room][pipeExit.row][pipeExit.col].direction = roomNum;
                        //location = pipeExit;
                        examineLoc(pipeExit);
                    }
                }
                else{
                    break;
                }
            }

            discover();
             if(route.empty()){
                noSolution = true;
                cout<<"No solution, ";
                cout<<map.discovered;
                cout<<" tiles discovered.";
            }
    }


}
}


vector<Tile> RoutingScheme::backtrace(Map &map, const Tile &countess){
    vector<Tile> path;
    Tile original = map.tiles[countess.room][countess.row][countess.col];
    path.push_back(original);
    bool startFound = false;
    while(!startFound){
        if(original.direction == 'n'){
            original = map.north(original);
            path.push_back(original);
        }
        else if(original.direction == 'e'){
            original = map.east(original);
            path.push_back(original);
        }
        else if(original.direction == 's'){
            original = map.south(original);
            path.push_back(original);
        }
        else if(original.direction == 'w'){
            original = map.west(original);
            path.push_back(original);
        }
        else if(original.direction > 47 && original.direction < 58){
            uint32_t rm = static_cast<uint32_t>(original.direction - '0');
            original = map.tiles[rm][original.row][original.col];
            path.push_back(original);
        }

        else{
            startFound = true;
        }
    }
    uint32_t pathSize = static_cast<uint32_t>(path.size());
    for(uint32_t i = pathSize - 1; i > 0; --i){
        if(path[i-1].direction == 'n'){
            path[i].symbol = 's';
        }
        else if(path[i-1].direction == 's'){
            path[i].symbol = 'n';
        }
        else if(path[i-1].direction == 'e'){
            path[i].symbol = 'w';
        }
        else if(path[i-1].direction == 'w'){
            path[i].symbol = 'e';
        }
        else{
            path[i].symbol = 'p';
        }
    }
        return path;

}

void RoutingScheme::mapOutput(Map &map,const Tile &countess){
    vector<Tile> path = backtrace(map, countess);
    uint32_t pathSize = static_cast<uint32_t>(path.size());
    for(uint32_t i = 0; i < pathSize; ++i){
        uint32_t room = path[i].room;
        uint32_t row = path[i].row;
        uint32_t col = path[i].col;
        map.tiles[room][row][col].symbol = path[i].symbol;
    }
    cout<<"Start in room "<<map.startingTile.room<<", row "
    <<map.startingTile.row<<", column "<<map.startingTile.col<<"\n";
    for(uint32_t room = 0; room < map.rooms; ++room){
        cout<<"//castle room "<<room<<"\n";
        for(uint32_t row = 0; row < map.dimensions; ++row){
            for(uint32_t col = 0; col < map.dimensions; ++col){
                cout<<map.tiles[room][row][col].symbol;
            }
            cout<<"\n";
        }
    }
}

void RoutingScheme::listOutput(Map &map, const Tile &countess){
    vector<Tile> path = backtrace(map, countess);
    cout<<"Path taken:\n";
    uint32_t pathSize = static_cast<uint32_t>(path.size());
    for(uint32_t i = pathSize - 1; i > 0; --i){
        //path[i-1].symbol = path[i].direction;
        //path[i].printNESW(cout);
        cout<<"("<<path[i].room<<","<<path[i].row<<","<<path[i].col<<","<<path[i].symbol<<")\n";
    }    
}

void RoutingScheme::discover(){
    if(map.northWalkable(location)){
        if(!map.north(location).discovered){
                map.north(location).discovered = true;
                map.north(location).direction = 's';
                map.discovered++;
                route.push_back(map.north(location));
                examineLoc(map.north(location));
            }
    }
    if(map.eastWalkable(location)){
        if(!map.east(location).discovered){
            map.east(location).discovered = true;
            map.east(location).direction = 'w';
            map.discovered++;
            route.push_back(map.east(location));
            examineLoc(map.east(location));
        }
    }
    if(map.southWalkable(location)){
        if(!map.south(location).discovered){
            map.south(location).discovered = true;
            map.south(location).direction = 'n';
            map.discovered++;
            route.push_back(map.south(location));
            examineLoc(map.south(location));
        }
    }
    if(map.westWalkable(location)){
        if(!map.west(location).discovered){
            map.west(location).discovered = true;
            map.west(location).direction = 'e';
            map.discovered++;
            route.push_back(map.west(location));
            examineLoc(map.west(location));
        }
    }
}

void RoutingScheme::examineLoc(const Tile &loc){
    if(loc.symbol == 'C'){
        countessFound = true;
        map.countessTile = loc;
        route.push_back(loc);
        if(outputFormat == "L"){
            listOutput(map, loc);
        }
        if(outputFormat == "M"){
            mapOutput(map, loc);
        }
    }
}



