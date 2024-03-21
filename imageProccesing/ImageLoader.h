//
// Created by Büşra Burhan on 24.10.2023.
//

#ifndef ASSIGNMENT1_IMAGELOADER_H
#define ASSIGNMENT1_IMAGELOADER_H
#include <string>
#include <vector>

class ImageLoader {
public:
    ImageLoader(const std::string& filepath); // Constructor for loading image from file
    ImageLoader(const ImageLoader &other); // copy constructor
    ImageLoader& operator=(const ImageLoader &other); // copy assignment operator

    // Destructor
    ~ImageLoader();


    int getHeight() const;
    int getWidth() const;
    double** getImageData() const;

private:
    int height;
    int width;
    double** imageData;
};





#endif //ASSIGNMENT1_IMAGELOADER_H
