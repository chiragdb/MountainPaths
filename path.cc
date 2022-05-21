#include "path.hpp"

#include "path_image.hpp"

Path::Path( size_t length, size_t starting_row ):
    length_( length ), starting_row_( starting_row ) {
  for ( size_t i = 0; i < length_; ++i ) {
    path_.push_back( 0 );
  }
}

size_t Path::length() const { return length_; }

size_t Path::starting_row() const { return starting_row_; }

unsigned int Path::ele_change() const { return ele_change_; }

void Path::inc_ele_change( unsigned int value ) {
  ele_change_ = ele_change_ + value;
}

const std::vector<size_t>& Path::path() const { return path_; }

void Path::set_loc( size_t col, size_t row ) { path_.at( col ) = row; }
