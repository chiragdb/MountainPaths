#include "elevation_dataset.hpp"

#include <limits>

ElevationDataset::ElevationDataset( const std::string& file,
                                    size_t width,
                                    size_t height ):
    width_( width ), height_( height ) {
  std::ifstream ifs( file );
  int current = 0;
  if ( !ifs.is_open() ) {
    throw std::runtime_error( "file is not open" );
  }
  bool b = true;
  while ( ifs.good() ) {
    if ( b == false ) {
      break;
    }
    for ( size_t row = 0; row < height_; ++row ) {
      if ( b == false ) {
        break;
      }
      std::vector<int> temp;
      for ( size_t col = 0; col < width_; ++col ) {
        ifs >> current;
        if ( ifs.bad() ) {
          throw std::runtime_error( "bad format for input file" );
        } else if ( ifs.fail() ) {
          ifs.clear();
          ifs.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        } else {
          temp.push_back( current );
        }
        if ( ifs.eof() ) {
          b = false;
          break;
        }
      }
      data_.push_back( temp );
    }
  }
  if ( data_.size() != height_ ) {
    data_.pop_back();
  }

  // bool b = true;
  // while ( ifs.good() ) {
  //   if ( !b ) {
  //     break;
  //   }
  //   for ( size_t row = 0; row < height_; ++row ) {
  //     if ( !b ) {
  //       break;
  //     }
  //     std::vector<int> temp;
  //     for ( size_t col = 0; col < width_; ++col ) {
  //       ifs >> current;
  //       // std::cout << current << std::endl;
  //       // if ( ifs.eof() ) {
  //       //   b = false;
  //       //   break;
  //       // }
  //       if ( ifs.bad() ) {
  //         throw std::runtime_error( "Bad format for input file" );
  //       } else if ( ifs.eof() ) {
  //         b = false;
  //         break;
  //       } else if ( ifs.fail() ) {
  //         ifs.clear();
  //         ifs.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
  //       } else {
  //         temp.push_back( current );
  //       }
  //     }
  //     if ( b ) {
  //       // std::cout << "pushback" << std::endl;
  //       data_.push_back( temp );
  //     }
  //     // data_.push_back( temp );
  //   }
  // }
  // if ( data_.size() != height_ ) {
  //   data_.pop_back();
  // }
  std::vector<int> max_and_min = data_.at( 0 );
  max_ele_ = max_and_min.at( 0 );
  min_ele_ = max_and_min.at( 0 );
  int data_size = data_.size();
  int num_elements = 0;
  for ( int i = 0; i < data_size; ++i ) {
    std::vector<int> vect = data_.at( i );
    int vect_size = vect.size();
    for ( int j = 0; j < vect_size; ++j ) {
      int comparison = vect.at( j );
      if ( comparison > max_ele_ ) {
        max_ele_ = comparison;
      } else if ( comparison < min_ele_ ) {
        min_ele_ = comparison;
      }
      num_elements = num_elements + 1;
    }
  }
  int num_expected_elements = int( width_ ) * int( height_ );
  // std::cout << "num elements counted: " << num_elements << std::endl;
  // std::cout << "num elements expected: " << num_expected_elements <<
  // std::endl;
  if ( num_elements != num_expected_elements ) {
    throw std::runtime_error(
        "# of elements does not match dimensions in parameter" );
  }
  // std::cout << width_ << std::endl;
  // std::cout << height_ << std::endl;
  // std::cout << max_ele_ << std::endl;
  // std::cout << min_ele_ << std::endl;
}

size_t ElevationDataset::width() const { return width_; }

size_t ElevationDataset::height() const { return height_; }

int ElevationDataset::max_ele() const { return max_ele_; }

int ElevationDataset::min_ele() const { return min_ele_; }

int ElevationDataset::datum_at( size_t row, size_t col ) const {
  return data_.at( row ).at( col );
}

const std::vector<std::vector<int>> ElevationDataset::get_data() const {
  return data_;
}
