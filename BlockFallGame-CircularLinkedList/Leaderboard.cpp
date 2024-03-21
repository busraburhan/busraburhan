#include "Leaderboard.h"

void Leaderboard::insert_new_entry(LeaderboardEntry * new_entry) {
    if(head_leaderboard_entry== nullptr|| new_entry->score>head_leaderboard_entry->score){
        new_entry->next_leaderboard_entry=head_leaderboard_entry;
        head_leaderboard_entry=new_entry;
    }
    else {
        LeaderboardEntry *temp;
        temp = head_leaderboard_entry;
        while(temp->next_leaderboard_entry!=nullptr&&temp->next_leaderboard_entry->score>=new_entry->score){
            temp=temp->next_leaderboard_entry;
        }
        new_entry->next_leaderboard_entry=temp->next_leaderboard_entry;
        temp->next_leaderboard_entry=new_entry;
        temp=nullptr;

    }
    LeaderboardEntry* temp;
    temp=head_leaderboard_entry;
    int size=0;
    while(temp!=nullptr){
        size++;
        if(size>10){
            delete temp->next_leaderboard_entry;
            temp->next_leaderboard_entry=nullptr;
            break;


        }
        else{
            temp=temp->next_leaderboard_entry;
        }


    }





    // TODO: Insert a new LeaderboardEntry instance into the leaderboard, such that the order of the high-scores
    //       is maintained, and the leaderboard size does not exceed 10 entries at any given time (only the
    //       top 10 all-time high-scores should be kept in descending order by the score).
}

void Leaderboard::write_to_file(const string& filename) {
    // TODO: Write the latest leaderboard status to the given file in the format specified in the PA instructions
}

void Leaderboard::read_from_file(const string& filename) {
    // TODO: Read the stored leaderboard status from the given file such that the "head_leaderboard_entry" member
    //       variable will point to the highest all-times score, and all other scores will be reachable from it
    //       via the "next_leaderboard_entry" member variable pointer.
}


void Leaderboard::print_leaderboard() {
    // TODO: Print the current leaderboard status to the standard output in the format specified in the PA instructions
}

Leaderboard::~Leaderboard() {
    LeaderboardEntry* current = head_leaderboard_entry;
    LeaderboardEntry* nextPlayer;

    while (current != nullptr) {
        nextPlayer = current->next_leaderboard_entry;
        delete current;
        current = nextPlayer;
    }

    head_leaderboard_entry = nullptr;
}

    // TODO: Free dynamically allocated memory used for storing leaderboard entries




