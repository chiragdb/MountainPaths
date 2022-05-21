#include "path_image.hpp"

#include "path.hpp"

PathImage::PathImage( const GrayscaleImage& image,
                      const ElevationDataset& dataset ):
    width_( dataset.width() ), height_( dataset.height() ) {
  path_image_ = image.get_image();
  std::vector<std::vector<int>> elevation_data = dataset.get_data();
  for ( size_t rows = 0; rows < height_; ++rows ) {
    size_t current_row = rows;
    Path p = Path( width_, current_row );
    for ( size_t cols = 0; cols < width_; ++cols ) {
      path_image_[current_row][cols] = Color( 252, 25, 63 );
      p.set_loc( cols, current_row );
      if ( cols >= width_ - 1 ) {
        break;
      }
      int top_diff;
      int middle_diff;
      int bottom_diff;
      int current = dataset.datum_at( current_row, cols );
      if ( current_row == 0 ) {
        middle_diff =
            abs( current - dataset.datum_at( current_row, cols + 1 ) );
        bottom_diff =
            abs( current - dataset.datum_at( current_row + 1, cols + 1 ) );
        if ( bottom_diff < middle_diff ) {
          current_row = current_row + 1;
          p.inc_ele_change( bottom_diff );
        } else if ( middle_diff < bottom_diff ) {
          p.inc_ele_change( middle_diff );
        } else {
          p.inc_ele_change( middle_diff );
        }
      } else if ( current_row == height_ - 1 ) {
        top_diff =
            abs( current - dataset.datum_at( current_row - 1, cols + 1 ) );
        middle_diff =
            abs( current - dataset.datum_at( current_row, cols + 1 ) );
        if ( top_diff < middle_diff ) {
          current_row = current_row - 1;
          p.inc_ele_change( top_diff );
        } else if ( middle_diff < top_diff ) {
          p.inc_ele_change( middle_diff );
        } else {
          p.inc_ele_change( middle_diff );
        }
      } else {
        top_diff =
            abs( current - dataset.datum_at( current_row - 1, cols + 1 ) );
        middle_diff =
            abs( current - dataset.datum_at( current_row, cols + 1 ) );
        bottom_diff =
            abs( current - dataset.datum_at( current_row + 1, cols + 1 ) );
        if ( top_diff < middle_diff && top_diff < bottom_diff ) {
          current_row = current_row - 1;
          p.inc_ele_change( top_diff );
        } else if ( bottom_diff < top_diff && bottom_diff < middle_diff ) {
          current_row = current_row + 1;
          p.inc_ele_change( bottom_diff );
        } else if ( middle_diff < top_diff && middle_diff < bottom_diff ) {
          p.inc_ele_change( middle_diff );
        } else if ( bottom_diff < middle_diff && top_diff < middle_diff &&
                    bottom_diff == top_diff ) {
          current_row = current_row + 1;
          p.inc_ele_change( bottom_diff );
        } else {
          p.inc_ele_change( middle_diff );
        }
      }
      // std::cout << "next row: " << current_row << std::endl;
      // p.path().push_back( current_row );
      // std::vector<size_t> v = p.path();
      // p.path().push_back( current_row );
    }
    paths_.push_back( p );
  }
  Path min = paths_.at( 0 );
  int paths_size = paths_.size();
  for ( int i = 0; i < paths_size; ++i ) {
    Path current = paths_.at( i );
    if ( current.ele_change() < min.ele_change() ) {
      min = current;
    }
  }
  // std::cout << min.starting_row() << std::endl;
  // std::cout << min.path().size() << std::endl;
  int min_path_size = min.path().size();
  for ( int j = 0; j < min_path_size; ++j ) {
    int row = min.path().at( j );
    path_image_[row][j] = Color( 31, 253, 13 );
  }
}

size_t PathImage::width() const { return width_; }

size_t PathImage::height() const { return height_; }

unsigned int PathImage::max_color_value() const { return max_color_value_; }

const std::vector<Path>& PathImage::paths() const { return paths_; }

const std::vector<std::vector<Color>>& PathImage::path_image() const {
  return path_image_;
}

void PathImage::to_ppm( const std::string& name ) const {
  std::ofstream ofs{ name };
  ofs << "P3" << '\n';
  ofs << width_ << " " << height_ << '\n';
  ofs << max_color_value_ << '\n';
  for ( size_t rows = 0; rows < height_; ++rows ) {
    for ( size_t cols = 0; cols < width_; ++cols ) {
      // Color c = color_at( rows, cols );
      Color c = path_image_.at( rows ).at( cols );
      if ( cols == width_ - 1 ) {
        ofs << c.red() << " " << c.green() << " " << c.blue() << '\n';
      } else {
        ofs << c.red() << " " << c.green() << " " << c.blue() << " ";
      }
    }
  }
}
