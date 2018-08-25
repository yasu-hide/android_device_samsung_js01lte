
#define PNG_INDEX_SUPPORTED
#include "pngpriv.h"

#if defined(PNG_SIMPLIFIED_READ_SUPPORTED) && defined(PNG_STDIO_SUPPORTED)
#  include <errno.h>
#endif

#ifdef PNG_INDEX_SUPPORTED
#define IDAT_HEADER_SIZE 8

/* Set the png read position to a new position based on idat_position and
 * offset.
 */
void
png_set_read_offset(png_structp png_ptr,
      png_uint_32 idat_position, png_uint_32 bytes_left)
{
   png_seek_data(png_ptr, idat_position);
   png_ptr->idat_size = png_read_chunk_header(png_ptr);

   // We need to add back IDAT_HEADER_SIZE because in zlib's perspective,
   // IDAT_HEADER in PNG is already stripped out.
   png_seek_data(png_ptr, idat_position + IDAT_HEADER_SIZE + png_ptr->idat_size - bytes_left);
   png_ptr->idat_size = bytes_left;
}

/* Configure png decoder to decode the pass starting from *row.
 * The requested row may be adjusted to align with an indexing row.
 * The actual row for the decoder to start its decoding will be returned in
 * *row.
 */
void PNGAPI
png_configure_decoder(png_structp png_ptr, int *row, int pass)
{
   png_indexp index = png_ptr->index;
   int n = *row / index->step[pass];
   png_line_indexp line_index = index->pass_line_index[pass][n];

   // Adjust row to an indexing row.
   *row = n * index->step[pass];
   png_ptr->row_number = *row;

#ifdef PNG_READ_INTERLACING_SUPPORTED
   if (png_ptr->interlaced)
      png_set_interlaced_pass(png_ptr, pass);
#endif

   long row_byte_length =
      PNG_ROWBYTES(png_ptr->pixel_depth, png_ptr->iwidth) + 1;

   inflateEnd(&png_ptr->zstream);
   inflateCopy(&png_ptr->zstream, line_index->z_state);

   // Set the png read position to line_index.
   png_set_read_offset(png_ptr, line_index->stream_idat_position,
         line_index->bytes_left_in_idat);
   memcpy(png_ptr->prev_row, line_index->prev_row, row_byte_length);
   png_ptr->zstream.avail_in = 0;
}

/* Build the line index and store the index in png_ptr->index.
 */
void PNGAPI
png_build_index(png_structp png_ptr)
{
   // number of rows in a 8x8 block for each interlaced pass.
   int number_rows_in_pass[7] = {1, 1, 1, 2, 2, 4, 4};

   int ret;
   png_uint_32 i, j;
   png_bytep rp;
   int p, pass_number = 1;

#ifdef PNG_READ_INTERLACING_SUPPORTED
   pass_number = png_set_interlace_handling(png_ptr);
#endif

   if (png_ptr == NULL)
      return;

   png_read_start_row(png_ptr);

#ifdef PNG_READ_INTERLACING_SUPPORTED
   if (!png_ptr->interlaced)
#endif
   {
      number_rows_in_pass[0] = 8;
   }

   // Allocate a buffer big enough for any transform.
   rp = png_malloc(png_ptr, PNG_ROWBYTES(png_ptr->maximum_pixel_depth, png_ptr->width));

   png_indexp index = png_malloc(png_ptr, sizeof(png_index));
   png_ptr->index = index;

   index->stream_idat_position = png_ptr->total_data_read - IDAT_HEADER_SIZE;

   // Set the default size of index in each pass to 0,
   // so that we can free index correctly in png_destroy_read_struct.
   for (p = 0; p < 7; p++)
      index->size[p] = 0;

   for (p = 0; p < pass_number; p++)
   {
      // We adjust the index step in each pass to make sure each pass
      // has roughly the same size of index.
      // This way, we won't consume to much memory in recording index.
      index->step[p] = INDEX_SAMPLE_SIZE * (8 / number_rows_in_pass[p]);
      const png_uint_32 temp_size =
         (png_ptr->height + index->step[p] - 1) / index->step[p];
      index->pass_line_index[p] =
         png_malloc(png_ptr, temp_size * sizeof(png_line_indexp));

      // Get the row_byte_length seen by the filter. This value may be
      // different from the row_byte_length of a bitmap in the case of
      // color palette mode.
      int row_byte_length =
         PNG_ROWBYTES(png_ptr->pixel_depth, png_ptr->iwidth) + 1;

      // Now, we record index for each indexing row.
      for (i = 0; i < temp_size; i++)
      {
         png_line_indexp line_index = png_malloc(png_ptr, sizeof(png_line_index));
         index->pass_line_index[p][i] = line_index;

         line_index->z_state = png_malloc(png_ptr, sizeof(z_stream));
         inflateCopy(line_index->z_state, &png_ptr->zstream);
         line_index->prev_row = png_malloc(png_ptr, row_byte_length);
         memcpy(line_index->prev_row, png_ptr->prev_row, row_byte_length);
         line_index->stream_idat_position = index->stream_idat_position;
         line_index->bytes_left_in_idat = png_ptr->idat_size + png_ptr->zstream.avail_in;

         // increment the size now that we have the backing data structures.
         // This prevents a crash in the event that png_read_row fails and
         // we need to cleanup the partially constructed png_index_struct;
         index->size[p] += 1;

         // Skip the "step" number of rows to the next indexing row.
         for (j = 0; j < index->step[p] &&
               i * index->step[p] + j < png_ptr->height; j++)
         {
            png_read_row(png_ptr, rp, NULL);
         }
      }
   }
   png_free(png_ptr, rp);
}
#endif
