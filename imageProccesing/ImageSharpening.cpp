#include "ImageSharpening.h"
#include "iostream"

// Default constructor
ImageSharpening::ImageSharpening() {


}

ImageSharpening::~ImageSharpening(){

}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    // getting a blured image
    double **bluringkernel;
    bluringkernel = new double *[3];
    for (int i = 0; i < 3; i++) {
        bluringkernel[i] = new double[3];
    }
    bluringkernel[0][0] = 1.0;
    bluringkernel[0][1] = 1.0;
    bluringkernel[0][2] = 1.0;
    bluringkernel[1][0] = 1.0;
    bluringkernel[1][1] = 1.0;
    bluringkernel[1][2] = 1.0;
    bluringkernel[2][0] = 1.0;
    bluringkernel[2][1] = 1.0;
    bluringkernel[2][2] = 1.0;

    Convolution bluring(bluringkernel,3,3,1,true);


    ImageMatrix bluredImage=bluring.convolve(input_image)*(1/9.0);
    ImageMatrix step1= input_image-bluredImage;
    ImageMatrix step2= step1*k;
    ImageMatrix sharpenedImage= input_image +step2;

    for(int i=0;i<sharpenedImage.get_height();++i){
        for(int j=0; j<sharpenedImage.get_width();++j){
            if(sharpenedImage.get_data()[i][j]<0.0){
                sharpenedImage.get_data()[i][j]= 0.0;
            }
            else if(sharpenedImage.get_data()[i][j]>255.0 ){
                sharpenedImage.get_data()[i][j]= 255.0;

            }
        }
    }
    if (bluringkernel != nullptr) {
        for (int i = 0; i < 3; i++) {
            delete[] bluringkernel[i];
        }
        delete[] bluringkernel;
        bluringkernel= nullptr;
    }

    return sharpenedImage;


}
