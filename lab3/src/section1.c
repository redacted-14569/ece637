
#include <math.h>
#include "tiff.h"
#include "allocate.h"
#include "randlib.h"
#include "typeutil.h"
#include "area_fill.h"

void error(char *name);

int main (int argc, char **argv) 
{
  FILE *fp;
  struct TIFF_img input_img;
  unsigned int **seg;
  struct pixel s;
  double T;
  int connectedNum,  i, j;
  int ClassLabel=1;
  char image_name[100];


//   if ( argc != 4) error( argv[0] );

  /* open image file */
  if ( ( fp = fopen ( argv[1], "rb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file %s\n", argv[1] );
    exit ( 1 );
  }

  /* read image */
  if ( read_TIFF ( fp, &input_img ) ) {
    fprintf ( stderr, "error reading file %s\n", argv[1] );
    exit ( 1 );
  }

  /* close image file */
  fclose ( fp );

  /* check the type of image data */
  if ( input_img.TIFF_type != 'g' ) {
    fprintf ( stderr, "error:  image must be gray scale\n" );
    exit ( 1 );
  }

  seg = (unsigned int **)get_img(input_img.width,input_img.height,sizeof( unsigned int));

  sscanf(argv[2], "%d", &(s.m));
  sscanf(argv[3], "%d", &(s.n));
  sscanf(argv[4], "%lf", &T);
  printf("in main loop %d, %d \n", s.m,s.n);
  ConnectedSet(s, T, input_img.mono, input_img.width, input_img.height, ClassLabel, seg, &connectedNum);

  for (i=0; i<input_img.height; i++){
    for (j=0; j<input_img.width; j++){
        // printf("%d \n", seg[i][j]);
        if (seg[i][j]==ClassLabel){
            input_img.mono[i][j]=0;
        }
        else{
            input_img.mono[i][j]=255;
        }
    }
  }

  free_img( (void**)seg );

  sprintf(image_name, "seg%f.tif",T);
  /* open output image file */
  if ( ( fp = fopen ( image_name, "wb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file output.tif\n");
    exit ( 1 );
  }

  /* write output image */
  if ( write_TIFF ( fp, &input_img) ) {
    fprintf ( stderr, "error writing TIFF file \n" );
    exit ( 1 );
  }

  /* close green image file */
  fclose ( fp );
    

  /* de-allocate space which was used for the images */
  free_TIFF ( &(input_img) );
  

  return(0);
}

void error(char *name)
{
    printf("usage:  %s  image.tiff \n\n",name);
    printf("this program reads in a 24-bit color TIFF image.\n");
    printf("It then horizontally filters the green component, adds noise,\n");
    printf("and writes out the result as an 8-bit image\n");
    printf("with the name 'green.tiff'.\n");
    printf("It also generates an 8-bit color image,\n");
    printf("that swaps red and green components from the input image");
    exit(1);
}