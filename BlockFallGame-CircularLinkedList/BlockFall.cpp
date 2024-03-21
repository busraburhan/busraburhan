#include "BlockFall.h"
#include <fstream>
#include <iostream>
using namespace std;

BlockFall::BlockFall(string grid_file_name, string blocks_file_name, bool gravity_mode_on, const string &leaderboard_file_name, const string &player_name) : gravity_mode_on(
        gravity_mode_on), leaderboard_file_name(leaderboard_file_name), player_name(player_name) {
    initialize_grid(grid_file_name);
    read_blocks(blocks_file_name);
    leaderboard.read_from_file(leaderboard_file_name);
}

void BlockFall::read_blocks(const string &input_file) {
    std::ifstream inputFile(input_file);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        exit(-1) ; // Exit with an error code
    }

    else{
        Block* temp_block= new Block();
        initial_block=temp_block;
        active_rotation=temp_block;
        std::string line;
        while(std::getline(inputFile,line)){
            vector<bool> blockRow;
            if(line[0]=='[' && line.find(']')!=std::string::npos){
                for(char c:line) {
                    if(c=='0' || c=='1'){
                        blockRow.push_back(c=='1');
                    }


                }
                temp_block->shape.push_back(blockRow);
                if(temp_block->shape== rotation(temp_block->shape,true)){
                    temp_block->right_rotation=temp_block;
                    temp_block->left_rotation=temp_block;

                }
                else{
                    temp_block->right_rotation= new Block();
                    temp_block->right_rotation->left_rotation=temp_block;
                    temp_block->right_rotation->shape=rotation(temp_block->shape,true);
                    temp_block->right_rotation->next_block=temp_block->next_block;
                    if(rotation(temp_block->right_rotation->shape,true)==temp_block->shape){
                        temp_block->right_rotation->right_rotation=temp_block;
                        temp_block->left_rotation=temp_block->right_rotation;

                    }
                    else{
                        temp_block->left_rotation=new Block();
                        temp_block->left_rotation->shape= rotation(temp_block->shape,false);
                        temp_block->left_rotation->next_block=temp_block->next_block;
                        temp_block->left_rotation->right_rotation=temp_block;
                        temp_block->right_rotation->right_rotation= new Block();
                        temp_block->right_rotation->right_rotation->next_block=temp_block->next_block;
                        temp_block->right_rotation->right_rotation->shape= rotation(temp_block->right_rotation->shape,true);
                        temp_block->right_rotation->right_rotation->right_rotation=temp_block->left_rotation;
                        temp_block->left_rotation->left_rotation=temp_block->right_rotation->right_rotation;
                        temp_block->right_rotation->right_rotation->left_rotation=temp_block->right_rotation;


                    }
                }


                temp_block->next_block=new Block();
                temp_block=temp_block->next_block;

            }

            else if(line[0]=='[') {
                for(char c:line) {
                    if(c=='0' || c=='1') {
                        blockRow.push_back(c=='1');
                    }
                }
                temp_block->shape.push_back(blockRow);


            }
            else if (line.find(']')!=std::string::npos){
                for (char c: line) {
                    if(c=='0' || c=='1') {
                        blockRow.push_back(c == '1');
                    }
                }
                temp_block->shape.push_back(blockRow);
                temp_block->next_block=new Block();
                if(temp_block->shape== rotation(temp_block->shape,true)){
                    temp_block->right_rotation=temp_block;
                    temp_block->left_rotation=temp_block;

                }
                else{
                    temp_block->right_rotation= new Block();
                    temp_block->right_rotation->left_rotation=temp_block;
                    temp_block->right_rotation->shape=rotation(temp_block->shape,true);
                    temp_block->right_rotation->next_block=temp_block->next_block;
                    if(rotation(temp_block->right_rotation->shape,true)==temp_block->shape){
                        temp_block->right_rotation->right_rotation=temp_block;
                        temp_block->left_rotation=temp_block->right_rotation;

                    }
                    else{
                        temp_block->left_rotation=new Block();
                        temp_block->left_rotation->shape= rotation(temp_block->shape,false);
                        temp_block->left_rotation->next_block=temp_block->next_block;
                        temp_block->left_rotation->right_rotation=temp_block;
                        temp_block->right_rotation->right_rotation= new Block();
                        temp_block->right_rotation->right_rotation->next_block=temp_block->next_block;
                        temp_block->right_rotation->right_rotation->shape= rotation(temp_block->right_rotation->shape,true);
                        temp_block->right_rotation->right_rotation->right_rotation=temp_block->left_rotation;
                        temp_block->left_rotation->left_rotation=temp_block->right_rotation->right_rotation;
                        temp_block->right_rotation->right_rotation->left_rotation=temp_block->right_rotation;


                    }
                }

                temp_block=temp_block->next_block;





            }
            else if(line[0]=='1'|| line[0]=='0'){
                for(char c:line) {
                    if(c=='0' || c=='1') {
                        blockRow.push_back(c == '1');
                    }
                }
                temp_block->shape.push_back(blockRow);
            }


        }
        Block* current = initial_block;  // this deletes the unnecessary block has been created above.
        while (current->next_block->next_block != nullptr) {
            current = current->next_block;
        }

        delete current->next_block;
        current->next_block = nullptr;

        current = initial_block;  // this deletes the power up block from the linked list.
        while (current->next_block->next_block != nullptr) {
            current = current->next_block;
        }
        power_up =current->next_block->shape;

        delete current->next_block;
        current->next_block = nullptr;






        /*current = initial_block;
        while (current != nullptr) {
            for (const auto& row : current->shape) {
                for (bool value : row) {
                    std::cout << (value ? "1" : "0") << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "---now rotations---" << std::endl;
            while(current->right_rotation->operator!=(current)){
                for (const auto& row : current->right_rotation->shape) {
                    for (bool value : row) {
                        std::cout << (value ? "1" : "0") << " ";
                    }
                    std::cout << std::endl;
                }
                std::cout << "--rotation block end---" << std::endl;
                current->right_rotation=current->right_rotation->right_rotation;
            }
            std::cout<<"----------next block----------"<<endl;
            current = current->next_block;
        }
        std::cout<<"------powerup---------"<<endl;
        for(int i=0;i<power_up.size();i++){
            for(int j=0;j<power_up[0].size();j++){
                std::cout<<power_up[i][j]<<" ";
            }
            std::cout<<endl;
        }*/




    }

    inputFile.close();
    // TODO: Read the blocks from the input file and initialize "initial_block" and "active_rotation" member variables
    // TODO: For every block, generate its rotations and properly implement the multilevel linked list structure
    //       that represents the game blocks, as explained in the PA instructions.
    // TODO: Initialize the "power_up" member variable as the last block from the input file (do not add it to the linked list!)
}

void BlockFall::initialize_grid(const string &input_file) {
    std::ifstream inputFile(input_file);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        exit(-1); // Exit with an error code
    }
    if(inputFile.is_open()){
        std::string line;
        while(std::getline(inputFile,line)){
            grid.push_back(splitLine(line,' '));

        }
        rows=grid.size();
        cols=grid[0].size();


    }


    // TODO: Initialize "rows" and "cols" member variables
    // TODO: Initialize "grid" member variable using the command-line argument 1 in main
}




BlockFall::~BlockFall() {
    while(initial_block!= nullptr){
        if(initial_block->right_rotation!=initial_block){
            if(initial_block->right_rotation->right_rotation!=initial_block){
                delete initial_block->right_rotation->right_rotation;
                delete initial_block->right_rotation;
                delete initial_block->left_rotation;

            }
            else{
                delete initial_block->right_rotation;

            }
        }
        Block* temp=initial_block;
        initial_block=initial_block->next_block;
        delete temp;

    }
    // TODO: Free dynamically allocated memory used for storing game blocks
}

vector<int> BlockFall::splitLine(string line, char splitCharacter) {
    vector<int> splitted_line;
    string word="";
    for(char s: line){
        if(splitCharacter==s){
            splitted_line.push_back(stoi(word));
            word="";


        }
        else{
            word+=s;
        }
    }
    splitted_line.push_back(stoi(word));
    return splitted_line;


}

vector<vector<bool>> BlockFall::rotation(vector<vector<bool>> inputVector, bool trueIfRight) {
    int rows = inputVector.size();
    int cols = inputVector[0].size();

    // Initialize newVector with the correct size
    vector<vector<bool>> newVector(cols, vector<bool>(rows));

    if(trueIfRight){
        for(int i=0; i<inputVector.size();i++){
            for(int j=0; j<newVector.size();j++){
                newVector[j][inputVector.size()-i-1]=inputVector[i][j];

            }


        }
    }
    else{
        for(int i=0;i<inputVector.size();i++){
            for(int j=newVector.size()-1;j>=0;j--){
                newVector[newVector.size()-j-1][i]=inputVector[i][j];
            }
        }
    }
    return newVector;

}

vector<bool> BlockFall::split(string line, char splitCharacter) {
    vector<bool> splitted_line;
    string word="";
    for(char s: line){
        if(splitCharacter==s){
            splitted_line.push_back(word=="1");
            word="";


        }
        else{
            word+=s;
        }
    }
    splitted_line.push_back(word=="1");
    return splitted_line;

}

