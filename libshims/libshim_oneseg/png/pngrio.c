#define PNG_INTERNAL
#define PNG_NO_PEDANTIC_WARNINGS
#define PNG_INDEX_SUPPORTED
#include "pngpriv.h"

#ifdef PNG_INDEX_SUPPORTED
void /* PRIVATE */
png_seek_data(png_structp png_ptr, png_uint_32 offset)
{
   if (png_ptr->seek_data_fn != NULL)
      (*(png_ptr->seek_data_fn))(png_ptr, offset);
   else
      png_error(png_ptr, "Call to NULL seek function");
}
#endif

#ifdef PNG_READ_SUPPORTED
void PNGAPI
png_set_seek_fn(png_structp png_ptr, png_seek_ptr seek_data_fn)
{
   if (png_ptr == NULL)
      return;
   png_ptr->seek_data_fn = seek_data_fn;
}
#endif
