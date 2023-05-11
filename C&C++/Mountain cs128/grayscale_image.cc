#include <cmath>
#include <fstream>
#include "grayscale_image.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset &dataset) : height_(dataset.Height()), width_(dataset.Width()) {
    for (size_t i = 0; i < height_; ++i) {
        std::vector<Color> buffer;
        for (size_t j = 0; j < width_; ++j) {
            int shade_of_gray = std::round(
                    double(dataset.DatumAt(i, j) - dataset.MinEle()) / (dataset.MaxEle() - dataset.MinEle()) *
                    kMaxColorValue);
            buffer.emplace_back(Color(shade_of_gray, shade_of_gray, shade_of_gray));
        }
        image_.emplace_back(buffer);
    }
}

GrayscaleImage::GrayscaleImage(const std::string &filename, size_t width, size_t height) : height_(height),
                                                                                           width_(width) {
    ElevationDataset dataset(filename, width, height);
    for (size_t i = 0; i < height_; ++i) {
        std::vector<Color> buffer;
        for (size_t j = 0; j < width_; ++j) {
            int shade_of_gray = std::round(
                    double(dataset.DatumAt(i, j) - dataset.MinEle()) / (dataset.MaxEle() - dataset.MinEle()) *
                    kMaxColorValue);
            buffer.emplace_back(Color(shade_of_gray, shade_of_gray, shade_of_gray));
        }
        image_.emplace_back(buffer);
    }

}

size_t GrayscaleImage::Width() const {
    return width_;
}

size_t GrayscaleImage::Height() const {
    return height_;
}

unsigned int GrayscaleImage::MaxColorValue() const {
    return kMaxColorValue;
}

const Color &GrayscaleImage::ColorAt(int row, int col) const {
    return image_[row][col];
}

const std::vector<std::vector<Color> > &GrayscaleImage::GetImage() const {
    return image_;
}

void GrayscaleImage::ToPpm(const std::string &name) const {
    std::ofstream out(name);
    out << "P3\n" << width_ << " " << height_ << "\n" << kMaxColorValue << "\n";
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            out << image_[i][j].Red() << " " << image_[i][j].Green() << " " << image_[i][j].Blue() << " ";

        }
        out << std::endl;
    }
    out.close();
}