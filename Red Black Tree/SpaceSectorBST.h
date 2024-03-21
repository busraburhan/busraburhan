#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>

#include "Sector.h"

class SpaceSectorBST {
  
public:
    Sector *root;
    SpaceSectorBST();
    ~SpaceSectorBST();
    void readSectorsFromFile(const std::string& filename); 
    void insertSectorByCoordinates(int x, int y, int z);
    void deleteSector(const std::string& sector_code);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
    Sector* insert(Sector* root,Sector* parent ,int x ,int y,int z);
    Sector* deletion(Sector* root, string sector_code);
    Sector* min(Sector* root);
    Sector* max(Sector* root);
    void inOrdering(Sector* currentNode);
    void preOrdering(Sector* currentNode);
    void postOrdering(Sector* currentNode);
    Sector* findNode(Sector* root, std::string target);
    void destroying(Sector* root);


};

#endif // SPACESECTORBST_H
