#include "EncodeMessage.h"




// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {

}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions) {

    ImageMatrix encodedImage(img.get_height(),img.get_width());

    for(int i=0;i<img.get_height();i++){
        for(int j=0;j<img.get_width();j++){
            encodedImage.get_data()[i][j]= img.get_data()[i][j];


        }

    }

    std::string messageCopy= message;
    std::vector<int> primeNumbers;
    primeNumbers.push_back(2);
    for(int i=3;i<message.size();i++) {
        int check=0;
        for (int j = 2; j < i; j++) {
            if(i%j==0){
                check++;
                break;
            }


        }
        if(check==0) {
            primeNumbers.push_back(i);


        }
    }
    for(int i:primeNumbers){
        char letterAtPrime=message[i];
        unsigned char unsignedLetter = static_cast<unsigned char>(letterAtPrime);
        int asciiValue = static_cast<int>(unsignedLetter);
        int fibonacci = 1;
        for (int j = 1; j <= i; j++) {
            fibonacci = fibonacci* j;

        }
        int newAscii= asciiValue + fibonacci;//finding the chars at prime num positions and convert it o ascii and add fibo . then create a new char at that position
        if(newAscii<=32){
            newAscii+=33;
        }
        else if(newAscii>=127){
            newAscii=126;
        }
        char newLetter = static_cast<char>(newAscii);
        messageCopy[i]=newLetter;// this is the message after char changing



    }
    //shifting the message
    std::string shiftedMessage=messageCopy.substr(messageCopy.size()-messageCopy.size()/2 )+ messageCopy.substr(0,messageCopy.size()-messageCopy.size()/2);
    std::string binaryOfMessage;
    //finding binary representation of message to encode
    for(char c:shiftedMessage){
        unsigned char unsignedc = static_cast<unsigned char>(c);
        int asciiValue = static_cast<int>(unsignedc);
        int sevenBitValue = asciiValue % 128;  // Ensure it's within 7 bits
        std::string binaryOfChar="";

        for (int i = 6; i >= 0; i--) {
            binaryOfChar += ((sevenBitValue >> i) & 1);
        }
        binaryOfMessage+=binaryOfChar;//this is binary of message


    }
    int count=0;
    if(binaryOfMessage.size()>positions.size()){
        int size_difference=binaryOfMessage.size()-positions.size();
        binaryOfMessage = binaryOfMessage.substr(0,binaryOfMessage.size()-size_difference);

    }
    for(auto pair:positions){// going o edge of pic
        std::string binary="";
        int decimal= img.get_data()[pair.first][pair.second];//decimal value of pixel
        if (decimal == 0.0) {
            binary = "0";
        } else {
            while (decimal > 0) {
                int bit = static_cast<int>(decimal) % 2;
                binary = std::to_string(bit) + binary;//finding binary of pixel
                decimal = decimal / 2;
            }
        }
        binary[binary.size()-1]=binaryOfMessage[count];//changin pixel's binary's last bit
        count++;
        int lastdecimal = 0.0;//creating this to change binary to decimal again
        int power = 1.0; // Start with 2^0

        for (int i = binary.length() - 1; i >= 0; i--) {
            if (binary[i] == '1') {
                lastdecimal += power;
            }
            power *= 2;
        }


        encodedImage.get_data()[pair.first][pair.second]=lastdecimal;// changin pixel


    }

    


    return encodedImage;
}
