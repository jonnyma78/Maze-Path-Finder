// Project Identifier: B99292359FFD910ED13A7E6C7F9705B8742F0D79



#include <iostream>
#include <getopt.h>
#include <string>
#include "Tile.h"
#include "Map.h"
#include "RoutingScheme.h"

using namespace std;
class Info{
    public:
        string outputFormat;
        char containerType;
        bool help;        

        Info(int argc, char *argv[]){
            outputFormat = "";
            containerType = '.';
            help = false;

            int choice;
            int option_index = 0;
            option long_options[] = {
                {"stack", no_argument, nullptr, 's'},
                {"queue", no_argument, nullptr, 'q'},
                {"output", required_argument, nullptr, 'o'},
                {"help", no_argument, nullptr, 'h'},
                { nullptr, 0,                 nullptr, '\0' }
            };

            while((choice = getopt_long(argc, argv, "sqo:h", long_options, &option_index)) != -1){
                switch(choice){
                    case 's':
                    if(containerType == 'Q' || containerType == 'S'){
                        cerr<<"Stack or queue can only be specified once\n";
                        exit(1);
                    
                    }
                    containerType = 'S';
                    break;
                    case 'q':
                    if(containerType == 'S' || containerType == 'Q'){
                        cerr<<"Stack or queue can only be specified once\n";
                        exit(1);
                    }                    
                    containerType = 'Q';
                    break;
                    case 'o':
                    outputFormat = optarg;
                    break;
                    case 'h':
                    help = 'h';
                    break;
                    default:
                    cerr << "Error: invalid option\n";
                    exit(1); 
        }              
    }
}        

};




int main(int argc, char *argv[]){
    std::ios_base::sync_with_stdio(false);

    Info info(argc, argv);
    string outputFormat = info.outputFormat;
    char containerType = info.containerType;
    if(info.help){
        cerr<<"--stack or -s for stack\n--queue or -q for queue\n--output or -o, followed by M or L for output format\n";
        return 0;
    }
    if(containerType != 'Q' && containerType != 'S'){
        cerr<<"Stack or queue must be specified\n";
        return 1;
    }
 
    if(outputFormat != "M" && outputFormat != "L"){
        outputFormat = 'M';
    }

    Map map(std::cin);

    RoutingScheme routingScheme(map, info.containerType, outputFormat);
    routingScheme.move();   
    
}