#define JPEG_INTERNALS
#include "jinclude.h"
#include "jpeglib.h"

LOCAL(boolean) output_pass_setup JPP((j_decompress_ptr cinfo));

GLOBAL(long)
jmin (long a, long b)
{
  return a < b ? a : b;
}

GLOBAL(void)
jpeg_init_read_tile_scanline(j_decompress_ptr cinfo, huffman_index *index,
		     int *start_x, int *start_y, int *width, int *height)
{
  // Calculates the boundary of iMCU
  int lines_per_iMCU_row = cinfo->max_v_samp_factor * DCTSIZE;
  int lines_per_iMCU_col = cinfo->max_h_samp_factor * DCTSIZE;
  int row_offset = *start_y / lines_per_iMCU_row;
  int col_left_boundary = ((*start_x / lines_per_iMCU_col)
            / index->MCU_sample_size) * index->MCU_sample_size;
  int col_right_boundary =
                  jdiv_round_up(*start_x + *width, lines_per_iMCU_col);

  cinfo->coef->MCU_columns_to_skip =
      *start_x / lines_per_iMCU_col - col_left_boundary;

  *height = (*start_y - row_offset * lines_per_iMCU_row) + *height;
  *start_x = col_left_boundary * lines_per_iMCU_col;
  *start_y = row_offset * lines_per_iMCU_row;
  cinfo->image_width = jmin(cinfo->original_image_width,
          col_right_boundary * lines_per_iMCU_col) -
          col_left_boundary * lines_per_iMCU_col;
  cinfo->input_iMCU_row = row_offset;
  cinfo->output_iMCU_row = row_offset;

  // Updates JPEG decoder parameter
  jinit_color_deconverter(cinfo);
  jpeg_calc_output_dimensions(cinfo);
  jinit_upsampler(cinfo);
  (*cinfo->master->prepare_for_output_pass) (cinfo);
  if (cinfo->progressive_mode)
    (*cinfo->entropy->start_pass) (cinfo);
  else
    jpeg_decompress_per_scan_setup(cinfo);

  int sample_size = DCTSIZE / cinfo->min_DCT_scaled_size;

  *height = jdiv_round_up(*height, sample_size);
  *width = cinfo->output_width;
  cinfo->output_scanline = lines_per_iMCU_row * row_offset / sample_size;
  cinfo->inputctl->consume_input = cinfo->coef->consume_data;
  cinfo->inputctl->consume_input_build_huffman_index =
      cinfo->coef->consume_data_build_huffman_index;
  cinfo->entropy->index = index;
  cinfo->input_iMCU_row = row_offset;
  cinfo->output_iMCU_row = row_offset;
  cinfo->coef->MCU_column_left_boundary = col_left_boundary;
  cinfo->coef->MCU_column_right_boundary = col_right_boundary;
  cinfo->coef->column_left_boundary =
      col_left_boundary / index->MCU_sample_size;
  cinfo->coef->column_right_boundary =
      jdiv_round_up(col_right_boundary, index->MCU_sample_size);
}

GLOBAL(JDIMENSION)
jpeg_read_tile_scanline (j_decompress_ptr cinfo, huffman_index *index,
        JSAMPARRAY scanlines)
{
  // Calculates the boundary of iMCU
  int lines_per_iMCU_row = cinfo->max_v_samp_factor * DCTSIZE;
  int lines_per_iMCU_col = cinfo->max_h_samp_factor * DCTSIZE;
  int sample_size = DCTSIZE / cinfo->min_DCT_scaled_size;
  JDIMENSION row_ctr = 0;

  if (cinfo->progressive_mode) {
    (*cinfo->main->process_data) (cinfo, scanlines, &row_ctr, 1);
  } else {
    if (cinfo->output_scanline % (lines_per_iMCU_row / sample_size) == 0) {
      // Set the read head to the next iMCU row
      int iMCU_row_offset = cinfo->output_scanline /
            (lines_per_iMCU_row / sample_size);
      int offset_data_col_position = cinfo->coef->MCU_column_left_boundary /
            index->MCU_sample_size;
      huffman_offset_data offset_data =
          index->scan[0].offset[iMCU_row_offset][offset_data_col_position];
      (*cinfo->entropy->configure_huffman_decoder) (cinfo, offset_data);
    }
    (*cinfo->main->process_data) (cinfo, scanlines, &row_ctr, 1);
  }

  cinfo->output_scanline += row_ctr;
  return row_ctr;
}

GLOBAL(boolean)
jpeg_start_tile_decompress (j_decompress_ptr cinfo)
{
  if (cinfo->global_state == DSTATE_READY) {
    /* First call: initialize master control, select active modules */
    cinfo->tile_decode = TRUE;
    jinit_master_decompress(cinfo);
    if (cinfo->buffered_image) {
      cinfo->global_state = DSTATE_BUFIMAGE;
      return TRUE;
    }
    cinfo->global_state = DSTATE_PRELOAD;
  }
  if (cinfo->global_state == DSTATE_PRELOAD) {
    cinfo->output_scan_number = cinfo->input_scan_number;
  } else if (cinfo->global_state != DSTATE_PRESCAN)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  /* Perform any dummy output passes, and set up for the final pass */
  return output_pass_setup(cinfo);
}

LOCAL(boolean)
output_pass_setup (j_decompress_ptr cinfo)
{
  if (cinfo->global_state != DSTATE_PRESCAN) {
    /* First call: do pass setup */
    (*cinfo->master->prepare_for_output_pass) (cinfo);
    cinfo->output_scanline = 0;
    cinfo->global_state = DSTATE_PRESCAN;
  }
  /* Loop over any required dummy passes */
  while (cinfo->master->is_dummy_pass) {
#ifdef QUANT_2PASS_SUPPORTED
    /* Crank through the dummy pass */
    while (cinfo->output_scanline < cinfo->output_height) {
      JDIMENSION last_scanline;
      /* Call progress monitor hook if present */
      if (cinfo->progress != NULL) {
	cinfo->progress->pass_counter = (long) cinfo->output_scanline;
	cinfo->progress->pass_limit = (long) cinfo->output_height;
	(*cinfo->progress->progress_monitor) ((j_common_ptr) cinfo);
      }
      /* Process some data */
      last_scanline = cinfo->output_scanline;
      (*cinfo->main->process_data) (cinfo, (JSAMPARRAY) NULL,
				    &cinfo->output_scanline, (JDIMENSION) 0);
      if (cinfo->output_scanline == last_scanline)
	return FALSE;		/* No progress made, must suspend */
    }
    /* Finish up dummy pass, and set up for another one */
    (*cinfo->master->finish_output_pass) (cinfo);
    (*cinfo->master->prepare_for_output_pass) (cinfo);
    cinfo->output_scanline = 0;
#else
    ERREXIT(cinfo, JERR_NOT_COMPILED);
#endif /* QUANT_2PASS_SUPPORTED */
  }
  /* Ready for application to drive output pass through
   * jpeg_read_scanlines or jpeg_read_raw_data.
   */
  cinfo->global_state = cinfo->raw_data_out ? DSTATE_RAW_OK : DSTATE_SCANNING;
  return TRUE;
}
