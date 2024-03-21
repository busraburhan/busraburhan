#include "SpaceSectorLLRBT.h"

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    std::fstream  InputFile(filename);
    string line;
    getline(InputFile,line);
    while(getline(InputFile,line)){
        vector<string> lineVector=Sector::splitLine(line,',');
        insertSectorByCoordinates(stoi(lineVector[0]),stoi(lineVector[1]),stoi(lineVector[2]));

    }
    // TODO: read the sectors from the input file and insert them into the LLRBT sector map
    // according to the given comparison critera based on the sector coordinates.
}

// Remember to handle memory deallocation properly in the destructor.
SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    //destroying(this->root);
    // TODO: Free any dynamically allocated memory in this class.
}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    this->root= inserting(this->root, nullptr,x,y,z);
    root->color=false;

    // TODO: Instantiate and insert a new sector into the space sector LLRBT map 
    // according to the coordinates-based comparison criteria.
}

void SpaceSectorLLRBT::displaySectorsInOrder() {
    std::cout<<"Space sectors inorder traversal:"<<endl;
    inOrdering(this->root);
    std::cout<<endl;
    // TODO: Traverse the space sector LLRBT map in-order and print the sectors 
    // to STDOUT in the given format.
}

void SpaceSectorLLRBT::displaySectorsPreOrder() {
    std::cout<<"Space sectors preorder traversal:"<<endl;
    preOrdering(this->root);
    std::cout<<endl;
    // TODO: Traverse the space sector LLRBT map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
}

void SpaceSectorLLRBT::displaySectorsPostOrder() {
    std::cout<<"Space sectors postorder traversal:"<<endl;
    postOrdering(this->root);
    std::cout<<endl;
    // TODO: Traverse the space sector LLRBT map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;

    std::vector<Sector*> path_to_root1;
    Sector* found= findNode(this->root,sector_code);
    Sector* earth= findNode(root,"0SSS");

    if(found!=nullptr){
        Sector* temp=found;
        while(temp!= nullptr){
            path_to_root1.push_back(temp);
            temp=temp->parent;

        }



    }
    else{

        return path;
    }


    if(this->root->sector_code=="0SSS"){

        for (int i = path_to_root1.size() - 1; i >= 0; i--) {
            path.push_back(path_to_root1[i]);
        }
        return path;
    }


    std::vector<Sector*> path_to_root2;




    if(earth!=nullptr){
        Sector* temp=earth;
        while(temp!= nullptr){
            path_to_root2.push_back(temp);
            temp=temp->parent;
        }




    }




    Sector* commonSector= nullptr;
    for(auto& sec:path_to_root1){
        for(auto& sec2:path_to_root2){
            if(sec->sector_code==sec2->sector_code){
                commonSector=sec;
                break;
            }
        }
        if(commonSector!= nullptr){
            break;
        }
    }

    if(commonSector!= nullptr){

        while(earth!=commonSector){
            path.push_back(earth);
            earth=earth->parent;
        }
        vector<Sector*> temp;
        while(found!=commonSector){
            temp.push_back(found);
            found=found->parent;
        }
        path.push_back(commonSector);
        for(int i=temp.size()-1;i>=0;i--){
            path.push_back(temp[i]);

        }

    }




    return path;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    return path;
}

void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
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

Sector *SpaceSectorLLRBT::inserting(Sector *root, Sector *parent, int x, int y, int z) {
    if(root == nullptr){
        Sector* sector=new Sector(x,y,z);
        sector->parent=parent;
        return sector;
    }

    if (x == root->x && y == root->y && z == root->z) {
        return root;

    }

    if (x < root->x || (x == root->x && y < root->y) || (x == root->x && y == root->y && z <root->z)) {
        root->left = inserting(root->left,root, x, y, z);
    }
        // Recursively insert into the right subtree if the coordinates are greater
    else {
        root->right = inserting(root->right,root, x, y, z);
    }


    if (isRed(root -> right) &&
        !isRed(root -> left))
    {

        // Left rotate the node to make it into
        // valid structure.
        root = rotateLeft(root);

        // Swap the colors as the child node
        // should always be red
        swapColors(root, root-> left);
    }

    // case 2
    // when left child as well as left grand
    // child in Red
    if (isRed(root -> left) &&
        isRed(root-> left -> left))
    {

        // Right rotate the current node to make
        // it into a valid structure.
        root = rotateRight(root);
        swapColors(root, root -> right);
    }

    // case 3
    // when both left and right child are Red in color.
    if (isRed(root -> left) && isRed(root -> right))
    {

        // Invert the color of node as well
        // it's left and right child.
        root -> color = !root -> color;

        // Change the color to black.
        root -> left -> color = false;
        root -> right -> color = false;
    }

    return root;
}

Sector *SpaceSectorLLRBT::rotateRight(Sector *sector) {
    Sector* x = sector->left;
    sector->left = x->right;

    if (x->right != nullptr)
        x->right->parent = sector;

    x->parent = sector->parent;

    if (sector->parent == nullptr)
        root = x;
    else if (sector == sector->parent->left)
        sector->parent->left = x;
    else
        sector->parent->right = x;

    x->right = sector;
    sector->parent = x;
    return x;
}

Sector *SpaceSectorLLRBT::rotateLeft(Sector *sector) {
    Sector* y = sector->right;
    sector->right = y->left;

    if (y->left != nullptr)
        y->left->parent = sector;

    y->parent = sector->parent;

    if (sector->parent == nullptr)
        root = y;
    else if (sector == sector->parent->left)
        sector->parent->left = y;
    else
        sector->parent->right = y;

    y->left = sector;
    sector->parent = y;

    return y;
}

void SpaceSectorLLRBT::swapColors(Sector *sector1, Sector *sector2) {
    bool temp = sector1 -> color;
    sector1 -> color = sector2 -> color;
    sector2 -> color = temp;

}

bool SpaceSectorLLRBT::isRed(Sector *sector) {
    if (sector == NULL)
        return 0;

    return (sector -> color == true);
}

void SpaceSectorLLRBT::inOrdering(Sector *currentNode) {
    if (currentNode != nullptr) {
        inOrdering(currentNode->left);
        if(currentNode->color==true){
            std::cout<<"RED sector: ";
        }
        else{
            std::cout<<"BLACK sector: ";
        }
        std::cout << currentNode->sector_code << endl;
        inOrdering(currentNode->right);
    }


}

void SpaceSectorLLRBT::postOrdering(Sector *currentNode) {
    if (currentNode != nullptr) {
        postOrdering(currentNode->left);
        postOrdering(currentNode->right);
        if(currentNode->color==true){
            std::cout<<"RED sector: ";
        }
        else{
            std::cout<<"BLACK sector: ";
        }
        std::cout << currentNode->sector_code << endl;
    }



}

void SpaceSectorLLRBT::preOrdering(Sector *currentNode) {
    if (currentNode != nullptr) {
        if(currentNode->color==true){
            std::cout<<"RED sector: ";
        }
        else{
            std::cout<<"BLACK sector: ";
        }
        std::cout << currentNode->sector_code << endl;

        preOrdering(currentNode->left);
        preOrdering(currentNode->right);
    }


}

Sector *SpaceSectorLLRBT::findNode(Sector *root, std::string target) {
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

void SpaceSectorLLRBT::destroying(Sector *root) {
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

Sector *SpaceSectorLLRBT::findLCA(Sector *root, Sector *node1, Sector *node2) {
    if (root == nullptr || root == node1 || root == node2) {
        return root;
    }

    Sector* leftLCA = findLCA(root->left, node1, node2);
    Sector* rightLCA = findLCA(root->right, node1, node2);

    if (leftLCA != nullptr && rightLCA != nullptr) {
        return root; // Current node is the LCA
    }

    return (leftLCA != nullptr) ? leftLCA : rightLCA;
}
