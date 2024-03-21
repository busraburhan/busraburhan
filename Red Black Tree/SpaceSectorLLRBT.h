#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

class SpaceSectorLLRBT {
public:
    Sector* root;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
    Sector* inserting(Sector* root,Sector* parent ,int x ,int y,int z);
    bool isRed(Sector* sector);
    Sector* rotateRight(Sector* sector);
    Sector* rotateLeft(Sector* sector);
    void swapColors(Sector* sector1,Sector* sector2);
    void inOrdering(Sector* currentNode);
    void preOrdering(Sector* currentNode);
    void postOrdering(Sector* currentNode);
    Sector* findNode(Sector* root, std::string target);
    void destroying(Sector* root);
    Sector* findLCA(Sector* root, Sector* node1, Sector* node2) ;

};

#endif // SPACESECTORLLRBT_H
