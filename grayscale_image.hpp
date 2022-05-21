#ifndef GRAYSCALE_IMAGE_H
#define GRAYSCALE_IMAGE_H

#include <cmath>
#include <cstdlib>  // for size_t
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"

class GrayscaleImage {
public:
  GrayscaleImage( const ElevationDataset& dataset );
  GrayscaleImage( const std::string& path, size_t width, size_t height );
  size_t width() const;
  size_t height() const;
  unsigned int max_color_value() const;
  const Color& color_at( int row, int col ) const;
  const std::vector<std::vector<Color>>& get_image() const;
  void to_ppm( const std::string& name ) const;

private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> image_;
  static const int max_color_value_ = 255;
};

#endif