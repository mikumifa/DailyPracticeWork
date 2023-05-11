#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "color.hpp"
#include "path.hpp"
#include "path_image.hpp"
#include "path.hpp"
#include <cstdlib>  // for size_t
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
    const string& filename = "input.txt";
    const string& savename = "./ElevationDataset.txt";
    const string& save_pathimage = "./save_pathimage.txt";
    size_t width = 480;
    size_t height =480;
    ElevationDataset ed = ElevationDataset(filename, width, height);
    GrayscaleImage gi = GrayscaleImage(ed);
    gi.ToPpm(savename);
    PathImage pi = PathImage(gi, ed);
    pi.ToPpm(save_pathimage);
}