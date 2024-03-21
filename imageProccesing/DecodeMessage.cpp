// DecodeMessage.cpp

#include "DecodeMessage.h"

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}


std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    std::string binaryString ;
    for (auto pair: edgePixels) {
        int i = pair.first;
        int j = pair.second;
        double num = image.get_data()[i][j];
        int lsb = static_cast<int>(num) & 1;
        binaryString += std::to_string(lsb);


    }
    if (binaryString.size() % 7 != 0) {
        // Calculate how many '0's to add
        int zerosToAdd = 7 - (binaryString.size() % 7);

        // Add the '0's to the beginning of the string
        binaryString = std::string(zerosToAdd, '0') + binaryString;
    }

    std::string asciiResult;

    // Process the binary string in chunks of 7 bits
    for (size_t i = 0; i < binaryString.size(); i += 7) {
        std::string chunk = binaryString.substr(i, 7);
        int decimal = 0;
        int power = 1;

        // Iterate through the binary string in reverse
        for (int i = chunk.size() - 1; i >= 0; --i) {
            if (chunk[i] == '1') {
                decimal += power; // Add 2^position to the decimal value
            }
            power *= 2; // Multiply power by 2 for the next position
        }
        if (decimal<=32){
            decimal+=33;
        }
        else if(decimal>=127){
            decimal=126;
        }
        asciiResult.push_back(static_cast<char>(decimal));


    }
    return asciiResult;



}