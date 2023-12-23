#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "netpbm.h"

int main(int argc, char * argv[])
{
  netpbm image;
  netpbm target_image;
  int err = open_image("CM1.pgm", &image);
  if (err != 0) {
    printf("Unable to open source image: %d\n", -err);
    return 0;
  }
  err = empty_image("CM1-edited.pgm", &target_image, image.width, image.height);
  if (err != 0) {
    printf("Unable to open target image: %d\n", -err);
    return 0;
  }
  for (int y = 0; y < image.height; y++) {
    for (int x = 0; x < image.width; x++) {
      char * c = pixel_at(&image, x, y);
      if (c == NULL) {
	printf("Error at x = %d y = %d\n", x, y);
      }
      char * cdest = pixel_at(&target_image, x, y);
      *cdest = 255 - *c;
      // Also to try:
      /* char * cdest = pixel_at(&target_image, */
      /* 			      target_image.width - x - 1, */
      /* 			      target_image.height - y - 1); */
      /* *cdest = *c; */
    }
  }
  close_image(&image);
  close_image(&target_image);
  return 0;
}
