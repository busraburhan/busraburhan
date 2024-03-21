#include <iostream>

#include "Convolution.h"

// Default constructor
Convolution::Convolution() {
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad){
    kernel = new double*[kh];
    for (int i = 0; i < kh; ++i) {
        kernel[i] = new double[kw];
    }
    for (int i = 0; i < kh; ++i) {
        for (int j = 0; j < kw; j++) {
            kernel[i][j] = customKernel[i][j];
        }
    }
    height=kh;
    width=kw;
    stride=stride_val;
    padding=pad;

}

// Destructor
Convolution::~Convolution() {
    if (kernel != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] kernel[i];
        }
        delete[] kernel;
    }
    kernel= nullptr;
}

// Copy constructor
Convolution::Convolution(const Convolution &other){
    height= other.height;
    width= other.width;
    kernel = new double*[other.height];
    for (int i = 0; i < other.height; ++i) {
        kernel[i] = new double[other.width];
    }
    for (int i = 0; i < other.height; ++i) {
        for (int j = 0; j < other.width; j++) {
            kernel[i][j] = other.kernel[i][j];
        }
    }




}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other) {
        return *this;
    }
    else {
        // Free existing memory
        if (kernel != nullptr) {
            for (int i = 0; i < height; ++i) {
                delete[] kernel[i];
            }
            delete[] kernel;
        }

        // Copy data from 'other' to 'this'
        height = other.height;
        width = other.width;
        stride = other.stride;
        padding = other.padding;

        kernel = new double *[height];
        for (int i = 0; i < height; ++i) {
            kernel[i] = new double[width];
            for (int j = 0; j < width; ++j) {
                kernel[i][j] = other.kernel[i][j];
            }
        }

        return *this;
    }
}




// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    if(padding){
        int newNumRows = input_image.get_height() + 2;
        int newNumCols = input_image.get_width() + 2;

        double** newArray ;
        newArray= new double*[newNumRows];
        for (int i = 0; i < newNumRows; i++) {
            newArray[i] = new double[newNumCols];
        }

        // Copy values from original array to the center of the new array
        for (int i = 0; i < input_image.get_height(); i++) {
            for (int j = 0; j < input_image.get_width(); j++) {
                newArray[i + 1][j + 1] = input_image.get_data()[i][j];
            }
        }

        // Fill the edges with zeros
        for (int i = 0; i < newNumRows; i++) {
            newArray[i][0] =0.0;
            newArray[i][newNumCols - 1] = 0.0;
        }
        for (int j = 0; j < newNumCols; j++) {
            newArray[0][j] = 0.0;
            newArray[newNumRows - 1][j] = 0.0;
        }







        int result_Height = (newNumRows - height) / stride + 1;
        int result_Width = (newNumCols - width) / stride + 1;

        /*double **resultMatrix = new double *[result_Height];
        for (int i = 0; i < result_Height; i++) {
            resultMatrix[i] = new double[result_Width];
        }*/
        ImageMatrix convolveMatrix(result_Height,result_Width);





        for (int i = 0; i < result_Height; i++) {
            for (int j = 0; j < result_Width; j++) {
                for (int m = 0; m < height; m++) {
                    for (int n = 0; n < width; n++) {
                        convolveMatrix.get_data()[i][j] =convolveMatrix.get_data()[i][j]+ newArray[i * stride + m][j * stride + n] * kernel[m][n];

                    }
                }
            }
        }


        if (newArray != nullptr) {
            for (int i = 0; i < newNumRows; i++) {
                delete[] newArray[i];
            }
            delete[] newArray;
        }
        newArray= nullptr;

        return convolveMatrix;




    }

    else {
        int result_Height = (input_image.get_height() - height) / stride + 1;
        int result_Width = (input_image.get_width() - width) / stride + 1;

        ImageMatrix convolveMatrix(result_Height,result_Width);


        for (int i = 0; i < result_Height; i++) {
            for (int j = 0; j < result_Width; j++) {
                for (int m = 0; m < height; m++) {
                    for (int n = 0; n < width; n++) {
                        convolveMatrix.get_data()[i][j] += input_image.get_data()[i * stride + m][j * stride + n] * kernel[m][n];
                    }
                }
            }
        }




        return convolveMatrix;
    }
}
