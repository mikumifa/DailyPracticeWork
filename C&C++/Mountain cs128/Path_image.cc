#include <fstream>
#include <limits>
#include "path_image.hpp"

int my_min(int x, int y, int z) {
    return (x < y) ? ((x < z) ? x : z) : ((y < z) ? y : z);
}

PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset) : height_(dataset.Height()),
                                                                                     width_(dataset.Width()),
                                                                                     path_image_(image.GetImage()) {
    const Color kRed(252, 25, 63);
    const Color kGreen(31, 253, 13);
    Path min_path(width_, 0);
    unsigned int min = INT32_MAX;
    for (size_t i = 0; i < height_; ++i) {
        Path path(width_, i);
        path.SetLoc(0, i);
        size_t pre_row = i;
        for (size_t j = 1; j < width_; j++) {


            int upper = abs(dataset.DatumAt(pre_row - 1, j) - dataset.DatumAt(pre_row, j - 1));
            int mid = abs(dataset.DatumAt(pre_row, j) - dataset.DatumAt(pre_row, j - 1));
            int lower = abs(dataset.DatumAt(pre_row + 1, j) - dataset.DatumAt(pre_row, j - 1));

            if (mid <= lower && mid <= upper) {
                path.SetLoc(j, pre_row);

            } else if (lower <= mid && lower <= upper) {
                path.SetLoc(j, pre_row + 1);
                pre_row++;
            } else if (upper < mid && upper < lower) {
                path.SetLoc(j, pre_row - 1);
                pre_row--;
            }
            path.IncEleChange(my_min(mid,lower,upper));
        }
        paths_.push_back(path);
        if (min > path.EleChange()) {
            min = path.EleChange();
            min_path = path;
        }
    }

    for (size_t i = 0; i < height_; i++) {
        for (size_t col = 0; col < width_; col++) {
            if (i != min_path.StartingRow())
                path_image_[paths_[i].GetPath()[col]][col] = kRed;
        }
    }

    for (size_t col = 0; col < width_; col++) {
        path_image_[paths_[min_path.StartingRow()].GetPath()[col]][col] = kGreen;
    }

}

size_t PathImage::Width() const {
    return width_;
}

size_t PathImage::Height() const {
    return height_;
}

unsigned int PathImage::MaxColorValue() const {
    return kMaxColorValue;
}

const std::vector<Path> &PathImage::Paths() const {
    return paths_;
}

const std::vector<std::vector<Color>> &PathImage::GetPathImage() const {
    return path_image_;
}

void PathImage::ToPpm(const std::string &name) const {
    std::ofstream out(name);
    out << "P3\n"
        << width_ << " " << height_ << "\n"
        << kMaxColorValue << "\n";
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            out << path_image_[i][j].Red() << " " << path_image_[i][j].Green() << " " << path_image_[i][j].Blue()
                << " ";
        }
        out << std::endl;
    }
    out.close();
}
