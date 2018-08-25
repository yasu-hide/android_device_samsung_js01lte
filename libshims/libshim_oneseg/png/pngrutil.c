
#define PNG_INDEX_SUPPORTED
#include "pngpriv.h"

#ifdef PNG_READ_SUPPORTED
void /* PRIVATE */
png_set_interlaced_pass(png_structp png_ptr, int pass)
{
   /* Arrays to facilitate easy interlacing - use pass (0 - 6) as index */

   /* Start of interlace block */
   PNG_CONST int png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};

   /* Offset to next interlace block */
   PNG_CONST int png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};

   /* Start of interlace block in the y direction */
   PNG_CONST int png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};

   /* Offset to next interlace block in the y direction */
   PNG_CONST int png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};

   png_ptr->pass = pass;
   png_ptr->iwidth = (png_ptr->width +
         png_pass_inc[png_ptr->pass] - 1 -
         png_pass_start[png_ptr->pass]) /
      png_pass_inc[png_ptr->pass];
}
#endif
