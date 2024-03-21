#include "GameController.h"
#include <fstream>
#include <iostream>
#include "LeaderboardEntry.h"
bool GameController::play(BlockFall& game, const string& commands_file) {


    std::fstream inputFile(commands_file);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        exit(-1); // Exit with an error code
    }
    else {

        std::vector<pair<int,int>> activeIndexes;
        int activeColumnStart=0;
        int activeColumnEnd=0;
        for (int i = 0; i < game.active_rotation->shape.size(); i++) {
            for (int j = 0; j < game.active_rotation->shape[i].size(); j++) {
                game.grid[i][j] = game.active_rotation->shape[i][j];
                activeIndexes.push_back(make_pair(i,j));
                activeColumnEnd=j;


            }
        }



        std::string line;
        while(std::getline(inputFile,line)){
            if(line=="PRINT_GRID"){
                std::cout<<"Score: "<<game.current_score<<endl;
                std::cout<<"High Score: "<<endl;
                for(int i=0;i<game.grid.size();i++) {
                    for (int j = 0; j < game.grid[0].size(); j++) {
                        if (game.grid[i][j] == 1) {
                            std::cout << occupiedCellChar<<" " ;
                        } else {
                            std::cout << unoccupiedCellChar <<" ";

                        }
                    }
                    std::cout << endl;
                }

            }

            else if(line=="MOVE_RIGHT"){
                if(activeColumnEnd!=game.grid[0].size()-1) {
                    int checkNext=0;
                    for (int i=0;i<game.active_rotation->shape.size();i++) {
                        if(game.grid[i][activeColumnEnd]==1&&game.grid[i][activeColumnEnd+1]==1){
                            checkNext++;


                        }
                    }

                    if(checkNext==0) {

                        for (auto it = activeIndexes.rbegin(); it != activeIndexes.rend(); ++it) {
                            // Access the pair using (*it)
                            game.grid[(*it).first][(*it).second + 1] = game.grid[(*it).first][(*it).second];
                            game.grid[(*it).first][(*it).second] = 0;
                            (*it).second++;


                        }
                        activeColumnStart++;
                        activeColumnEnd++;
                    }
                }


            }
            else if(line=="MOVE_LEFT"){
                if(activeColumnStart!=0){
                    int checkNext=0;
                    for (int i=0;i<game.active_rotation->shape.size();i++) {
                        if(game.grid[i][activeColumnStart]==1&&game.grid[i][activeColumnStart-1]==1){
                            checkNext++;


                        }
                    }
                    if(checkNext==0) {
                        for (auto &it:activeIndexes) {
                            // Access the pair using (*it)
                            game.grid[it.first][it.second-1]=game.grid[it.first][it.second];
                            game.grid[it.first][it.second]=0;
                            it.second--;



                        }
                        activeColumnStart--;
                        activeColumnEnd--;
                    }

                }



            }
            else if(line=="ROTATE_RIGHT"){
                vector<vector<int>> temp_grid=game.grid;

                for(auto pair:activeIndexes){
                    temp_grid[pair.first][pair.second]=0;

                }
                if(activeColumnStart+game.active_rotation->right_rotation->shape[0].size()<=game.grid[0].size()) {
                    int check = 0;
                    for (int i = 0; i < game.active_rotation->right_rotation->shape.size(); i++) {
                        for (int j = 0; j < game.active_rotation->right_rotation->shape[0].size(); j++) {
                            if (game.active_rotation->right_rotation->shape[i][j] == 1 &&temp_grid[i][j + activeColumnStart] == 1) {
                                check++;
                            }

                        }
                    }
                    if (check == 0) {

                        for (auto pair: activeIndexes) {
                            game.grid[pair.first][pair.second] = 0;

                        }
                        activeIndexes.clear();

                        for (int i = 0; i < game.active_rotation->right_rotation->shape.size(); i++) {
                            for (int j = 0; j < game.active_rotation->right_rotation->shape[0].size(); j++) {
                                game.grid[i][activeColumnStart+j] = game.active_rotation->right_rotation->shape[i][j];
                                activeIndexes.push_back(make_pair(i,activeColumnStart+j));


                            }
                        }
                        game.active_rotation=game.active_rotation->right_rotation;
                        activeColumnEnd=activeColumnStart+game.active_rotation->right_rotation->shape[0].size();
                    }
                }
            }
            else if(line=="ROTATE_LEFT"){
                vector<vector<int>> temp_grid=game.grid;

                for(auto pair:activeIndexes){
                    temp_grid[pair.first][pair.second]=0;

                }
                if(activeColumnStart+game.active_rotation->left_rotation->shape[0].size()<=game.grid[0].size()){
                    int check = 0;
                    for (int i = 0; i < game.active_rotation->left_rotation->shape.size(); i++) {
                        for (int j = 0; j < game.active_rotation->left_rotation->shape[0].size(); j++) {
                            if (game.active_rotation->left_rotation->shape[i][j] == 1 &&temp_grid[i][j + activeColumnStart] == 1) {
                                check++;
                            }

                        }
                    }
                    if(check==0){
                        for (auto pair: activeIndexes) {
                            game.grid[pair.first][pair.second] = 0;

                        }
                        activeIndexes.clear();
                        for (int i = 0; i < game.active_rotation->left_rotation->shape.size(); i++) {
                            for (int j = 0; j < game.active_rotation->left_rotation->shape[0].size(); j++) {
                                game.grid[i][activeColumnStart+j] = game.active_rotation->left_rotation->shape[i][j];
                                activeIndexes.push_back(make_pair(i,activeColumnStart+j));


                            }
                        }
                        game.active_rotation=game.active_rotation->left_rotation;
                        activeColumnEnd=activeColumnStart+game.active_rotation->left_rotation->shape[0].size();

                    }

                }


            }
            else if(line=="DROP") {
                if (game.gravity_mode_on==false) {
                    int toFall = 0;
                    vector<int> tempOnes;
                    for(auto i:activeIndexes){
                        tempOnes.push_back(game.grid[i.first][i.second]);
                        game.grid[i.first][i.second]=0;
                    }
                    for(int i=1;i<game.grid.size()-game.active_rotation->shape.size()+1;i++){
                        int check=0;
                        int count=0;
                        for(auto pair:activeIndexes){
                            if(game.grid[pair.first+i][pair.second]==1 && tempOnes[count]==1){
                                check++;
                            }
                            count++;
                        }
                        if(check!=0){
                            break;

                        }
                        else{
                            toFall=i;
                        }

                    }
                    int count=0;
                    for(auto i:activeIndexes){
                        game.grid[i.first][i.second]=tempOnes[count];
                        count++;
                    }

                    for(auto it = activeIndexes.rbegin(); it != activeIndexes.rend(); ++it){
                        if(game.grid[it->first][it->second]==1) {
                            game.grid[it->first + toFall][it->second] = game.grid[it->first][it->second];
                        }
                        game.grid[it->first][it->second]=0;

                    }
                    int howManyCell=0;
                    for(int i=0;i<game.active_rotation->shape.size();i++){
                        for(int j=0;j<game.active_rotation->shape[0].size();j++){
                            if(game.active_rotation->shape[i][j]==1){
                                howManyCell++;
                            }
                        }
                    }
                    game.current_score+=(toFall*howManyCell);

                    int rowToDelete=0;
                    for(int i=game.grid.size()-1;i>=0;i--){
                        int check=0;
                        for(int j=0;j<game.grid[0].size();j++){
                            if(game.grid[i][j]==0){
                                check++;
                            }


                        }
                        if(check==0){
                            rowToDelete++;
                            for(int k=0;k<game.grid[0].size();k++){
                                game.grid[i][k]=0;
                            }
                            for(int k=i-1;k>=0;k--){
                                for(int j=0;j<game.grid[0].size();j++){
                                    game.grid[k+1][j]=game.grid[k][j];
                                }
                            }

                        }
                    }
                    game.current_score+=(game.grid[0].size()*rowToDelete);
                    //start
                     rowToDelete=0;
                    for(int i=game.grid.size()-1;i>=0;i--){
                        int check=0;
                        for(int j=0;j<game.grid[0].size();j++){
                            if(game.grid[i][j]==0){
                                check++;
                            }


                        }
                        if(check==0){
                            rowToDelete++;
                            for(int k=0;k<game.grid[0].size();k++){
                                game.grid[i][k]=0;
                            }
                            for(int k=i-1;k>=0;k--){
                                for(int j=0;j<game.grid[0].size();j++){
                                    game.grid[k+1][j]=game.grid[k][j];
                                }
                            }

                        }
                    }
                    game.current_score+=(game.grid[0].size()*rowToDelete);

                    if(game.active_rotation->next_block!= nullptr) {
                        game.active_rotation = game.active_rotation->next_block;
                        activeIndexes.clear();
                        activeColumnStart = 0;
                        activeColumnEnd = 0;
                        int checking=0;
                        for (int i = 0; i < game.active_rotation->shape.size(); i++) {
                            for (int j = 0; j < game.active_rotation->shape[i].size(); j++) {
                                if(game.grid[i][j]==1&&game.active_rotation->shape[i][j]==1){
                                    checking++;
                                }
                            }
                        }
                        if(checking==0) {
                            for (int i = 0; i < game.active_rotation->shape.size(); i++) {
                                for (int j = 0; j < game.active_rotation->shape[i].size(); j++) {
                                    game.grid[i][j] = game.active_rotation->shape[i][j];
                                    activeIndexes.push_back(make_pair(i, j));
                                    activeColumnEnd = j;


                                }
                            }
                        }
                        else{
                            std::cout<<"GAME OVER!\n"
                                       "Next block that couldn't fit:"<<endl;

                            for(int i=0;i<game.active_rotation->shape.size();i++){
                                for(int j=0;j<game.active_rotation->shape[0].size();j++){
                                    if (game.active_rotation->shape[i][j] == 1) {
                                        std::cout << occupiedCellChar << " ";
                                    } else {
                                        std::cout << unoccupiedCellChar << " ";

                                    }

                                }
                                std::cout<<endl;
                            }
                            std::cout<<"Final grid and score:"<<endl<<endl;
                            std::cout<<"Score: "<<game.current_score<<endl;
                            std::cout<<"High Score: "<<game.current_score<<endl;
                            for(int i=0;i<game.grid.size();i++) {
                                for (int j = 0; j < game.grid[0].size(); j++) {
                                    if (game.grid[i][j] == 1) {
                                        std::cout << occupiedCellChar << " ";
                                    } else {
                                        std::cout << unoccupiedCellChar << " ";

                                    }
                                }
                                std::cout << endl;
                            }
                            LeaderboardEntry player(game.current_score,std::time(nullptr),game.player_name);


                            return false;

                        }
                    }
                    else{
                        activeIndexes.clear();
                        std::cout<<"YOU WIN!\n"
                                   "No more blocks.\n"
                                   "Final grid and score:"<<endl;

                        std::cout<<"Score: "<<game.current_score<<endl;
                        std::cout<<"High Score: "<<game.current_score<<endl;
                        for(int i=0;i<game.grid.size();i++) {
                            for (int j = 0; j < game.grid[0].size(); j++) {
                                if (game.grid[i][j] == 1) {
                                    std::cout << occupiedCellChar << " ";
                                } else {
                                    std::cout << unoccupiedCellChar << " ";

                                }
                            }
                            std::cout << endl;
                        }
                        LeaderboardEntry player(game.current_score,std::time(nullptr),game.player_name);
                        return true;


                    }








                }
                else {
                    vector<int> smallerFall;

                    for (auto pair = activeIndexes.rbegin(); pair != activeIndexes.rend(); ++pair) {
                        if (game.grid[(*pair).first][(*pair).second] == 1) {
                            int rowToPut=0;
                            for(int k=pair->first+1;k<game.grid.size();k++){
                                if(game.grid[k][pair->second]==0){
                                    rowToPut=k;
                                }
                            }

                            if(rowToPut!=0){
                                game.grid[rowToPut][(*pair).second]=game.grid[(*pair).first][(*pair).second];
                                game.grid[(*pair).first][(*pair).second]=0;
                            }
                            smallerFall.push_back(rowToPut-(*pair).first);

                        }
                    }

                    int minElement = smallerFall[0];

                    // Iterate through the vector to find the minimum element
                    for (int i = 1; i < smallerFall.size(); ++i) {
                        if (smallerFall[i] < minElement) {
                            minElement = smallerFall[i];
                        }
                    }
                    int howManyCell=0;
                    for(int i=0;i<game.active_rotation->shape.size();i++){
                        for(int j=0;j<game.active_rotation->shape[0].size();j++){
                            if(game.active_rotation->shape[i][j]==1){
                                howManyCell++;
                            }
                        }
                    }

                    game.current_score+=(minElement*howManyCell);
                    int powerup=1;
                    for(int i=0;i<game.grid.size()-game.power_up.size()+1;i++){
                        for(int j=0;j<game.grid[0].size()-game.power_up[0].size()+1;j++){
                            int check=0;
                            for (int k=0;k<game.power_up.size(); k++ ){
                                for(int h=0;h<game.power_up[0].size();h++){
                                    if(game.grid[i+k][j+h]!=game.power_up[k][h]){
                                        check++;
                                    }


                                }

                            }
                            if(check==0){
                                powerup=0;


                            }
                        }
                    }
                    if(powerup==0){
                        int point=0;
                        for(int i=0;i<game.grid.size();i++){
                            for(int j=0;j<game.grid[0].size();j++){
                                game.grid[i][j]=0;

                            }
                        }
                        game.current_score+=1000;

                    }

                    int rowToDelete=0;
                    for(int i=game.grid.size()-1;i>=0;i--){
                        int check=0;
                        for(int j=0;j<game.grid[0].size();j++){
                            if(game.grid[i][j]==0){
                                check++;
                            }


                        }
                        if(check==0){
                            rowToDelete++;
                            for(int k=0;k<game.grid[0].size();k++){
                                game.grid[i][k]=0;
                            }
                            for(int k=i-1;k>=0;k--){
                                for(int j=0;j<game.grid[0].size();j++){
                                    game.grid[k+1][j]=game.grid[k][j];
                                }
                            }

                        }
                    }
                    game.current_score+=(game.grid[0].size()*rowToDelete);
                    //start
                    rowToDelete=0;
                    for(int i=game.grid.size()-1;i>=0;i--){
                        int check=0;
                        for(int j=0;j<game.grid[0].size();j++){
                            if(game.grid[i][j]==0){
                                check++;
                            }


                        }
                        if(check==0){
                            rowToDelete++;
                            for(int k=0;k<game.grid[0].size();k++){
                                game.grid[i][k]=0;
                            }
                            for(int k=i-1;k>=0;k--){
                                for(int j=0;j<game.grid[0].size();j++){
                                    game.grid[k+1][j]=game.grid[k][j];
                                }
                            }

                        }
                    }
                    game.current_score+=(game.grid[0].size()*rowToDelete);


                    if(game.active_rotation->next_block!= nullptr) {
                        game.active_rotation = game.active_rotation->next_block;
                        activeIndexes.clear();
                        activeColumnStart = 0;
                        activeColumnEnd = 0;
                        int checking=0;
                        for (int i = 0; i < game.active_rotation->shape.size(); i++) {
                            for (int j = 0; j < game.active_rotation->shape[i].size(); j++) {
                                if(game.grid[i][j]==1&&game.active_rotation->shape[i][j]==1){
                                    checking++;
                                }
                            }
                        }

                        if(checking==0) {
                            for (int i = 0; i < game.active_rotation->shape.size(); i++) {
                                for (int j = 0; j < game.active_rotation->shape[i].size(); j++) {
                                    game.grid[i][j] = game.active_rotation->shape[i][j];
                                    activeIndexes.push_back(make_pair(i, j));
                                    activeColumnEnd = j;


                                }
                            }
                        }
                        else{
                            std::cout<<"GAME OVER!\n"
                                       "Next block that couldn't fit:"<<endl;

                            for(int i=0;i<game.active_rotation->shape.size();i++){
                                for(int j=0;j<game.active_rotation->shape[0].size();j++){
                                    if (game.active_rotation->shape[i][j] == 1) {
                                        std::cout << occupiedCellChar << " ";
                                    } else {
                                        std::cout << unoccupiedCellChar << " ";

                                    }

                                }
                                std::cout<<endl;
                            }
                            std::cout<<"Final grid and score:"<<endl<<endl;
                            std::cout<<"Score: "<<game.current_score<<endl;
                            std::cout<<"High Score: "<<game.current_score<<endl;
                            for(int i=0;i<game.grid.size();i++) {
                                for (int j = 0; j < game.grid[0].size(); j++) {
                                    if (game.grid[i][j] == 1) {
                                        std::cout << occupiedCellChar << " ";
                                    } else {
                                        std::cout << unoccupiedCellChar << " ";

                                    }
                                }
                                std::cout << endl;
                            }
                            LeaderboardEntry player(game.current_score,std::time(nullptr),game.player_name);


                            return false;

                        }
                    }
                    else{
                        activeIndexes.clear();
                        std::cout<<"YOU WIN!\n"
                                   "No more blocks.\n"
                                   "Final grid and score:"<<endl;

                        std::cout<<"Score: "<<game.current_score<<endl;
                        std::cout<<"High Score: "<<game.current_score<<endl;
                        for(int i=0;i<game.grid.size();i++) {
                            for (int j = 0; j < game.grid[0].size(); j++) {
                                if (game.grid[i][j] == 1) {
                                    std::cout << occupiedCellChar << " ";
                                } else {
                                    std::cout << unoccupiedCellChar << " ";

                                }
                            }
                            std::cout << endl;
                        }
                        LeaderboardEntry player(game.current_score,std::time(nullptr),game.player_name);
                        return true;


                    }




                }

            }
            else if(line=="GRAVITY_SWITCH") {
                if (!game.gravity_mode_on) {
                    vector<int> temp_block;
                    for (auto pair: activeIndexes) {
                        temp_block.push_back(game.grid[pair.first][pair.second]);
                        game.grid[pair.first][pair.second] = 0;
                    }
                    game.gravity_mode_on = !(game.gravity_mode_on);
                    for (int i = game.grid.size() - 2; i >= 0; i--) {
                        for (int j = 0; j < game.grid[0].size(); j++) {
                            if (game.grid[i][j] == 1) {

                                int rowToPut = 0;
                                for(int k=i+1;k<game.grid.size();k++){
                                    if(game.grid[k][j]==0){
                                        rowToPut=k;
                                    }
                                }



                                if (rowToPut != 0) {
                                    game.grid[rowToPut][j] = game.grid[i][j];
                                    game.grid[i][j] = 0;
                                }

                            }
                        }
                    }
                    int powerup=1;
                    for(int i=0;i<game.grid.size()-game.power_up.size()+1;i++){
                        for(int j=0;j<game.grid[0].size()-game.power_up[0].size()+1;j++){
                            int check=0;
                            for (int k=0;k<game.power_up.size(); k++ ){
                                for(int h=0;h<game.power_up[0].size();h++){
                                    if(game.grid[i+k][j+h]!=game.power_up[k][h]){
                                        check++;
                                    }


                                }

                            }
                            if(check==0){
                                powerup=0;


                            }
                        }
                    }
                    if(powerup==0){
                        int point=0;
                        for(int i=0;i<game.grid.size();i++){
                            for(int j=0;j<game.grid[0].size();j++){
                                game.grid[i][j]=0;

                            }
                        }
                        game.current_score+=1000;

                    }
                    int rowToDelete=0;
                    for(int i=game.grid.size()-1;i>=0;i--){
                        int check=0;
                        for(int j=0;j<game.grid[0].size();j++){
                            if(game.grid[i][j]==0){
                                check++;
                            }


                        }
                        if(check==0){
                            rowToDelete++;
                            for(int k=0;k<game.grid[0].size();k++){
                                game.grid[i][k]=0;
                            }
                            for(int k=i-1;k>=0;k--){
                                for(int j=0;j<game.grid[0].size();j++){
                                    game.grid[k+1][j]=game.grid[k][j];
                                }
                            }

                        }
                    }
                    game.current_score+=(game.grid[0].size()*rowToDelete);
                    //start
                    rowToDelete=0;
                    for(int i=game.grid.size()-1;i>=0;i--){
                        int check=0;
                        for(int j=0;j<game.grid[0].size();j++){
                            if(game.grid[i][j]==0){
                                check++;
                            }


                        }
                        if(check==0){
                            rowToDelete++;
                            for(int k=0;k<game.grid[0].size();k++){
                                game.grid[i][k]=0;
                            }
                            for(int k=i-1;k>=0;k--){
                                for(int j=0;j<game.grid[0].size();j++){
                                    game.grid[k+1][j]=game.grid[k][j];
                                }
                            }

                        }
                    }
                    game.current_score+=(game.grid[0].size()*rowToDelete);
                    int count = 0;
                    for (auto pair: activeIndexes) {
                        game.grid[pair.first][pair.second] = temp_block[count];
                        count++;
                    }

                }
                else{
                    game.gravity_mode_on=!(game.gravity_mode_on);
                }
            }
            else{
                std::cout<<"Unknown command: "<<line<<endl;

            }

        }
        for(auto pair:activeIndexes){
            game.grid[pair.first][pair.second]=0;
        }
        LeaderboardEntry player(game.current_score,std::time(nullptr),game.player_name);
        Leaderboard leaderboard;

        return true;
    }




    // TODO: Implement the gameplay here while reading the commands from the input file given as the 3rd command-line
    //       argument. The return value represents if the gameplay was successful or not: false if game over,
    //       true otherwise.
    inputFile.close();
    return false;
}


