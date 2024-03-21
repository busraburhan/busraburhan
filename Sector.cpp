#include "Sector.h"
#include <cmath>
#include <iostream>


// Constructor implementation

Sector::Sector(int x, int y, int z) : x(x), y(y), z(z), left(nullptr), right(nullptr), parent(nullptr), color(RED) {
    this->distance_from_earth = std::sqrt((x*x)+(y*y)+(z*z));
    int forCode=static_cast<int>(this->distance_from_earth);
    string code= to_string(forCode);
    if(x==0){
        code+="S";
    }
    else if(x>0){
        code+="R";
    }
    else{
        code+="L";
    }


    if(y==0){
        code+="S";
    }
    else if(y>0){
        code+="U";
    }
    else{
        code+="D";
    }



    if(z==0){
        code+="S";
    }
    else if(z>0){
        code+="F";
    }
    else{
        code+="B";
    }

    this->sector_code=code;


        // TODO: Calculate the distance to the Earth, and generate the sector code
}

Sector::~Sector() {
    // TODO: Free any dynamically allocated memory if necessary
}

Sector& Sector::operator=(const Sector& other) {
    this->x=other.x;
    this->y=other.y;
    this->z=other.z;
    this->distance_from_earth=other.distance_from_earth;
    this->color=other.color;
    this->left=other.left;
    this->right=other.right;
    this->parent=other.parent;

    // TODO: Overload the assignment operator
    return *this;
}

bool Sector::operator==(const Sector& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Sector::operator!=(const Sector& other) const {
    return !(*this == other);
}

vector<std::string> Sector::splitLine(string line, char splitCharacter) {
    vector<std::string> splitted_line;
    string word="";
    for(char s: line){
        if(splitCharacter==s){
            splitted_line.push_back(word);
            word="";


        }
        else{
            word+=s;
        }
    }
    splitted_line.push_back(word);
    return splitted_line;

}
