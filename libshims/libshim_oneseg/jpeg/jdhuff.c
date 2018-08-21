#define JPEG_INTERNALS
#include "jinclude.h"
#include "jpeglib.h"
#include "jdhuff.h"

GLOBAL(void)
jpeg_create_huffman_index(j_decompress_ptr cinfo, huffman_index *index)
{
  int i, s;
  index->scan_count = 1;
  index->total_iMCU_rows = cinfo->total_iMCU_rows;
  index->scan = (huffman_scan_header*)malloc(index->scan_count
          * sizeof(huffman_scan_header));
  index->scan[0].offset = (huffman_offset_data**)malloc(cinfo->total_iMCU_rows
          * sizeof(huffman_offset_data*));
  index->scan[0].prev_MCU_offset.bitstream_offset = 0;
  index->MCU_sample_size = DEFAULT_MCU_SAMPLE_SIZE;

  index->mem_used = sizeof(huffman_scan_header)
      + cinfo->total_iMCU_rows * sizeof(huffman_offset_data*);
}

GLOBAL(void)
jpeg_destroy_huffman_index(huffman_index *index)
{
    int i, j;
    for (i = 0; i < index->scan_count; i++) {
        for(j = 0; j < index->total_iMCU_rows; j++) {
            free(index->scan[i].offset[j]);
        }
        free(index->scan[i].offset);
    }
    free(index->scan);
}

GLOBAL(void)
jset_input_stream_position(j_decompress_ptr cinfo, int offset)
{
  if (cinfo->src->seek_input_data) {
    cinfo->src->seek_input_data(cinfo, offset);
  } else {
    cinfo->src->bytes_in_buffer = cinfo->src->current_offset - offset;
    cinfo->src->next_input_byte = cinfo->src->start_input_byte + offset;
  }
}
