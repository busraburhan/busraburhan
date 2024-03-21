// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>

#include "EdgeDetector.h"
#include <cmath>
#include <iostream>
using namespace std;

// Default constructor
EdgeDetector::EdgeDetector() {



}

// Destructor
EdgeDetector::~EdgeDetector() {

}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
    double **GxArray;
    GxArray = new double *[3];
    for (int i = 0; i < 3; i++) {
        GxArray[i] = new double[3];
    }
    GxArray[0][0] = -1.0;
    GxArray[0][1] = 0.0;
    GxArray[0][2] = 1.0;
    GxArray[1][0] = -2.0;
    GxArray[1][1] = 0.0;
    GxArray[1][2] = 2.0;
    GxArray[2][0] = -1.0;
    GxArray[2][1] = 0.0;
    GxArray[2][2] = 1.0;

    double **GyArray;
    GyArray = new double *[3];
    for (int i = 0; i < 3; i++) {
        GyArray[i] = new double[3];
    }
    GyArray[0][0] = -1.0;
    GyArray[0][1] = -2.0;
    GyArray[0][2] = -1.0;
    GyArray[1][0] = 0.0;
    GyArray[1][1] = 0.0;
    GyArray[1][2] = 0.0;
    GyArray[2][0] = 1.0;
    GyArray[2][1] = 2.0;
    GyArray[2][2] = 1.0;

    Convolution Gx(GxArray,3,3,1,1);
    Convolution Gy(GyArray,3,3,1,1);
    for (int i = 0; i < 3; ++i) {
        delete[] GxArray[i];
        delete[] GyArray[i];

    }
    delete[] GxArray;
    GxArray= nullptr;
    delete[] GyArray;
    GyArray= nullptr;



    int height = input_image.get_height();
    int width = input_image.get_width();
    double **Ix;
    Ix = new double *[height];
    for (int i = 0; i < height; i++) {
        Ix[i] = new double[width];
    }
    double **Iy;
    Iy = new double *[height];
    for (int i = 0; i < height; i++) {
        Iy[i] = new double[width];
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Ix[i][j] = Gx.convolve(input_image).get_data()[i][j];
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Iy[i][j] = Gy.convolve(input_image).get_data()[i][j];
        }
    }

    double **magnitude ;
    magnitude=new double *[input_image.get_height()];

    // Create arrays for each row
    for (int i = 0; i < height; i++) {
        magnitude[i] = new double[width];
    }

    double magnitudeValue = 0.00;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            magnitude[i][j] = sqrt((Ix[i][j] * Ix[i][j]) + (Iy[i][j] * Iy[i][j]));
            magnitudeValue += magnitude[i][j];
        }
    }

    double threshold = magnitudeValue / (height * width);

    vector<pair<int, int>> pairsAboveAvarage;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(magnitude[i][j]> threshold){
                pairsAboveAvarage.push_back(make_pair(i, j));

            }
        }
    }
    if (Ix != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] Ix[i];

        }
        delete[] Ix;
        Ix= nullptr;
    }
    if (Iy != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] Iy[i];

        }
        delete[] Iy;
        Iy= nullptr;
    }
    if (magnitude != nullptr) {
        for (int i = 0; i < height; ++i) {

            delete[]  magnitude[i];
        }
        delete[] magnitude;
        magnitude= nullptr;
    }


    return pairsAboveAvarage;



}
