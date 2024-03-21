#include "SpaceSectorBST.h"

using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    //destroying(this->root);
    // Free any dynamically allocated memory in this class.
}

void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
    std::fstream  InputFile(filename);
    string line;
    getline(InputFile,line);
    while(getline(InputFile,line)){
        vector<string> lineVector=Sector::splitLine(line,',');
        insertSectorByCoordinates(stoi(lineVector[0]),stoi(lineVector[1]),stoi(lineVector[2]));

    }





    // TODO: read the sectors from the input file and insert them into the BST sector map
    // according to the given comparison critera based on the sector coordinates.
}

void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    this->root=insert(SpaceSectorBST::root,nullptr,x,y,z);


    // Instantiate and insert a new sector into the space sector BST map according to the 
    // coordinates-based comparison criteria.
}

void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    this->root=deletion(this->root,sector_code);
    // TODO: Delete the sector given by its sector_code from the BST.
}

void SpaceSectorBST::displaySectorsInOrder() {
    std::cout<<"Space sectors inorder traversal:"<<endl;
    inOrdering(this->root);

    // TODO: Traverse the space sector BST map in-order and print the sectors 
    // to STDOUT in the given format.
}

void SpaceSectorBST::displaySectorsPreOrder() {
    std::cout<<"Space sectors preorder traversal:"<<endl;
    preOrdering(this->root);
    // TODO: Traverse the space sector BST map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
}

void SpaceSectorBST::displaySectorsPostOrder() {

    std::cout<<"Space sectors postorder traversal:"<<endl;
    postOrdering(this->root);
    // TODO: Traverse the space sector BST map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    std::vector<Sector*> path_temp;
    Sector* found= findNode(this->root,sector_code);
    if(found!=nullptr) {
        Sector *temp = found;
        while (temp != nullptr) {
            path_temp.push_back(temp);
            temp = temp->parent;

        }


        for (int i = path_temp.size() - 1; i >= 0; i--) {
            path.push_back(path_temp[i]);
        }



    }

    return path;



    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    return path;
}

void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
    if(!path.empty()) {
        std::cout << "The stellar path to Dr. Elara: ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i]->sector_code;

            // Print a hyphen after each element (except the last one)
            if (i < path.size() - 1) {
                std::cout << "->";
            }
        }
    }
    else{
        std::cout<<"A path to Dr. Elara could not be found.";
    }

    std::cout << std::endl;
    // TODO: Print the stellar path obtained from the getStellarPath() function 
    // to STDOUT in the given format.
}

Sector *SpaceSectorBST::insert(Sector* root,Sector* parent ,int x ,int y,int z) {
    if(root == nullptr){
        Sector* sector=new Sector(x,y,z);
        sector->parent=parent;

        return sector;
    }

    if (x == root->x && y == root->y && z == root->z) {
        return root;

    }

    if (x < root->x || (x == root->x && y < root->y) || (x == root->x && y == root->y && z <root->z)) {
        root->left = insert(root->left,root, x, y, z);
    }
        // Recursively insert into the right subtree if the coordinates are greater
    else {
        root->right = insert(root->right,root, x, y, z);
    }

    return root;


}

Sector *SpaceSectorBST::deletion(Sector* root,string sector_code) {

    Sector* toDelete= findNode(root,sector_code);
    if(toDelete==nullptr){
        return root;

    }

    if(toDelete->left== nullptr&&toDelete->right== nullptr){

        if (toDelete->parent != nullptr) {
            if (toDelete->parent->left == toDelete) {
                toDelete->parent->left = nullptr;
            } else {

                toDelete->parent->right = nullptr;
            }
        }

        delete toDelete;

        return root;
    }


    if(toDelete->right!= nullptr&& toDelete->left==nullptr){
        Sector* child = toDelete->right;
        if (toDelete->parent != nullptr) {
            if (toDelete->parent->left == toDelete) {
                toDelete->parent->left = child;
            } else {
                toDelete->parent->right = child;
            }
            child->parent = toDelete->parent;
        } else {
            // If toDelete is the root
            root = child;
            child->parent = nullptr;
        }
        delete toDelete;
        return root;




    }
    if(toDelete->right== nullptr&& toDelete->left!=nullptr){
        Sector* child = toDelete->left;
        if (toDelete->parent != nullptr) {
            if (toDelete->parent->left == toDelete) {
                toDelete->parent->left = child;
            } else {
                toDelete->parent->right = child;
            }
            child->parent = toDelete->parent;
        } else {
            // If toDelete is the root
            root = child;
            child->parent = nullptr;
        }
        delete toDelete;
        return root;



    }
    if(toDelete->right!= nullptr&& toDelete->left!=nullptr){
        Sector* toPut = min(toDelete->right);

        // Copy the data from the in-order successor to the node to be deleted
        toDelete->x = toPut->x;
        toDelete->y = toPut->y;
        toDelete->z = toPut->z;
        toDelete->distance_from_earth = toPut->distance_from_earth;
        string code =toPut->sector_code;
        //toDelete->sector_code = toPut->sector_code;


        // Recursively delete the in-order successor
        root= deletion(root, toPut->sector_code);
        toDelete->sector_code=code;


        return root;


    }
    return nullptr;



}

Sector* SpaceSectorBST::min(Sector* root) {
    Sector* temp=root;
    while(temp->left!=nullptr){
        temp=temp->left;

    }
    return temp;

}

Sector *SpaceSectorBST::max(Sector *root) {
    Sector* temp1=root;
    while(temp1->right!=nullptr){
        temp1=temp1->right;

    }
    return temp1;

}

void SpaceSectorBST::inOrdering(Sector *currentNode) {

    if (currentNode != nullptr) {
        inOrdering(currentNode->left);
        std::cout << currentNode->sector_code << endl;
        inOrdering(currentNode->right);
    }

}

void SpaceSectorBST::preOrdering(Sector *currentNode) {

    if (currentNode != nullptr) {
        std::cout << currentNode->sector_code << endl;
        preOrdering(currentNode->left);
        preOrdering(currentNode->right);
    }


}

void SpaceSectorBST::postOrdering(Sector *currentNode) {

    if (currentNode != nullptr) {
        postOrdering(currentNode->left);
        postOrdering(currentNode->right);
        std::cout << currentNode->sector_code << endl;
    }


}

Sector *SpaceSectorBST::findNode(Sector *root, string target) {
    if (root == nullptr || root->sector_code == target) {
        return root;
    }

    // Recursive case: search in the left and right subtrees
    Sector* inLeftSubtree = findNode(root->left, target);
    if (inLeftSubtree != nullptr) {
        return inLeftSubtree;
    }

    return findNode(root->right, target);

}

void SpaceSectorBST::destroying(Sector *root) {
    if (root == nullptr) {
        return;
    }
    if(root->left!= nullptr){
        destroying(root->left);
    }
    if(root->right!= nullptr) {
        destroying(root->right);
    }
    delete root;

}




