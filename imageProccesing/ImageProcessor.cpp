#include "ImageProcessor.h"
#include <iostream>

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}
ImageSharpening sharpening;
EdgeDetector edgeDetector;
DecodeMessage decoder;
EncodeMessage encoder;

std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {

    ImageMatrix sharpened_Image = sharpening.sharpen(img,2.0);
    std::vector<std::pair<int, int>> edge_vector=edgeDetector.detectEdges(sharpened_Image);
    std::string hidden_message=decoder.decodeFromImage(sharpened_Image,edge_vector);
    return hidden_message;


}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {

    ImageMatrix sharpened_img = sharpening.sharpen(img,2);

    std::vector<std::pair<int, int>> edgess=edgeDetector.detectEdges(sharpened_img);

    ImageMatrix encodedmatrix=encoder.encodeMessageToImage(img,message,edgess);
    return encodedmatrix;

}
