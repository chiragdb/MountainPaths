#include "grayscale_image.hpp"

#include <cmath>

#include "elevation_dataset.hpp"

GrayscaleImage::GrayscaleImage( const ElevationDataset& dataset ):
    width_( dataset.width() ), height_( dataset.height() ) {
  std::vector<std::vector<int>> data = dataset.get_data();
  int max_elevation = dataset.max_ele();
  int min_elevation = dataset.min_ele();
  double difference = max_elevation - min_elevation;
  int shade_of_gray = 0;
  for ( size_t rows = 0; rows < height_; ++rows ) {
    std::vector<int> temp = data.at( rows );
    std::vector<Color> temp_color;
    for ( size_t cols = 0; cols < width_; ++cols ) {
      int current_height = temp.at( cols );
      double val = ( current_height - min_elevation ) / difference;
      val = 255 * val;
      shade_of_gray = round( val );
      if ( min_elevation == max_elevation ) {
        shade_of_gray = 0;
      }
      Color c = Color( shade_of_gray, shade_of_gray, shade_of_gray );
      temp_color.push_back( c );
    }
    image_.push_back( temp_color );
  }
}

GrayscaleImage::GrayscaleImage( const std::string& path,
                                size_t width,
                                size_t height ):
    width_( width ), height_( height ) {
  ElevationDataset e = ElevationDataset( path, width, height );
  std::vector<std::vector<int>> data = e.get_data();
  int max_elevation = e.max_ele();
  int min_elevation = e.min_ele();
  double difference = max_elevation - min_elevation;
  int shade_of_gray = 0;
  for ( size_t rows = 0; rows < height_; ++rows ) {
    std::vector<int> temp = data.at( rows );
    std::vector<Color> temp_color;
    for ( size_t cols = 0; cols < width_; ++cols ) {
      int current_height = temp.at( cols );
      double val = ( current_height - min_elevation ) / difference;
      val = 255 * val;
      shade_of_gray = round( val );
      if ( min_elevation == max_elevation ) {
        shade_of_gray = 0;
      }
      Color c = Color( shade_of_gray, shade_of_gray, shade_of_gray );
      temp_color.push_back( c );
    }
    image_.push_back( temp_color );
  }
}

size_t GrayscaleImage::width() const { return width_; }

size_t GrayscaleImage::height() const { return height_; }

unsigned int GrayscaleImage::max_color_value() const {
  return max_color_value_;
}

const Color& GrayscaleImage::color_at( int row, int col ) const {
  return image_.at( row ).at( col );
}

const std::vector<std::vector<Color>>& GrayscaleImage::get_image() const {
  return image_;
}

void GrayscaleImage::to_ppm( const std::string& name ) const {
  std::ofstream ofs{ name };
  ofs << "P3" << '\n';
  ofs << width_ << " " << height_ << '\n';
  ofs << max_color_value_ << '\n';
  for ( size_t rows = 0; rows < height_; ++rows ) {
    for ( size_t cols = 0; cols < width_; ++cols ) {
      Color c = color_at( rows, cols );
      if ( cols == width_ - 1 ) {
        ofs << c.red() << " " << c.green() << " " << c.blue() << '\n';
      } else {
        ofs << c.red() << " " << c.green() << " " << c.blue() << " ";
      }
    }
  }
}
