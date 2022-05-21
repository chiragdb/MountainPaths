#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main() {
  // write behavior declarations here; define in elevation_dataset.cc.
  ElevationDataset data =
      ElevationDataset( "ex_input_data/map-input-w480-h480.dat", 480, 480 );
  // ElevationDataset data =
  //     ElevationDataset( "ex_input_data/all-tie-row1-2w-3h.dat", 2, 3 );
  // ElevationDataset data =
  //     ElevationDataset( "ex_input_data/map-input-w51-h55.dat", 51, 55 );
  GrayscaleImage g = GrayscaleImage( data );
  // g.to_ppm( "grayscale.ppm" );
  PathImage path_image = PathImage( g, data );
  path_image.to_ppm( "path.ppm" );
}
