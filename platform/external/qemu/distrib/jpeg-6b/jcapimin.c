/*
 * jcapimin.c
 *
 * Copyright (C) 1994-1998, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains application interface code for the compression half
 * of the JPEG library.  These are the "minimum" API routines that may be
 * needed in either the normal full-compression case or the transcoding-only
 * case.
 *
 * Most of the routines intended to be called directly by an application
 * are in this file or in jcapistd.c.  But also see jcparam.c for
 * parameter-setup helper routines, jcomapi.c for routines shared by
 * compression and decompression, and jctrans.c for the transcoding case.
 */

#define JPEG_INTERNALS
#include "jinclude.h"
#include "jpeglib.h"



GLOBAL(void)
jpeg_CreateCompress (j_compress_ptr cinfo, int version, size_t structsize)
{
  int i;

  
  cinfo->mem = NULL;		
  if (version != JPEG_LIB_VERSION)
    ERREXIT2(cinfo, JERR_BAD_LIB_VERSION, JPEG_LIB_VERSION, version);
  if (structsize != SIZEOF(struct jpeg_compress_struct))
    ERREXIT2(cinfo, JERR_BAD_STRUCT_SIZE, 
	     (int) SIZEOF(struct jpeg_compress_struct), (int) structsize);

  {
    struct jpeg_error_mgr * err = cinfo->err;
    void * client_data = cinfo->client_data; 
    MEMZERO(cinfo, SIZEOF(struct jpeg_compress_struct));
    cinfo->err = err;
    cinfo->client_data = client_data;
  }
  cinfo->is_decompressor = FALSE;

  
  jinit_memory_mgr((j_common_ptr) cinfo);

  
  cinfo->progress = NULL;
  cinfo->dest = NULL;

  cinfo->comp_info = NULL;

  for (i = 0; i < NUM_QUANT_TBLS; i++)
    cinfo->quant_tbl_ptrs[i] = NULL;

  for (i = 0; i < NUM_HUFF_TBLS; i++) {
    cinfo->dc_huff_tbl_ptrs[i] = NULL;
    cinfo->ac_huff_tbl_ptrs[i] = NULL;
  }

  cinfo->script_space = NULL;

  cinfo->input_gamma = 1.0;	

  
  cinfo->global_state = CSTATE_START;
}



GLOBAL(void)
jpeg_destroy_compress (j_compress_ptr cinfo)
{
  jpeg_destroy((j_common_ptr) cinfo); 
}



GLOBAL(void)
jpeg_abort_compress (j_compress_ptr cinfo)
{
  jpeg_abort((j_common_ptr) cinfo); 
}


/*
 * Forcibly suppress or un-suppress all quantization and Huffman tables.
 * Marks all currently defined tables as already written (if suppress)
 * or not written (if !suppress).  This will control whether they get emitted
 * by a subsequent jpeg_start_compress call.
 *
 * This routine is exported for use by applications that want to produce
 * abbreviated JPEG datastreams.  It logically belongs in jcparam.c, but
 * since it is called by jpeg_start_compress, we put it here --- otherwise
 * jcparam.o would be linked whether the application used it or not.
 */

GLOBAL(void)
jpeg_suppress_tables (j_compress_ptr cinfo, boolean suppress)
{
  int i;
  JQUANT_TBL * qtbl;
  JHUFF_TBL * htbl;

  for (i = 0; i < NUM_QUANT_TBLS; i++) {
    if ((qtbl = cinfo->quant_tbl_ptrs[i]) != NULL)
      qtbl->sent_table = suppress;
  }

  for (i = 0; i < NUM_HUFF_TBLS; i++) {
    if ((htbl = cinfo->dc_huff_tbl_ptrs[i]) != NULL)
      htbl->sent_table = suppress;
    if ((htbl = cinfo->ac_huff_tbl_ptrs[i]) != NULL)
      htbl->sent_table = suppress;
  }
}



GLOBAL(void)
jpeg_finish_compress (j_compress_ptr cinfo)
{
  JDIMENSION iMCU_row;

  if (cinfo->global_state == CSTATE_SCANNING ||
      cinfo->global_state == CSTATE_RAW_OK) {
    
    if (cinfo->next_scanline < cinfo->image_height)
      ERREXIT(cinfo, JERR_TOO_LITTLE_DATA);
    (*cinfo->master->finish_pass) (cinfo);
  } else if (cinfo->global_state != CSTATE_WRCOEFS)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  
  while (! cinfo->master->is_last_pass) {
    (*cinfo->master->prepare_for_pass) (cinfo);
    for (iMCU_row = 0; iMCU_row < cinfo->total_iMCU_rows; iMCU_row++) {
      if (cinfo->progress != NULL) {
	cinfo->progress->pass_counter = (long) iMCU_row;
	cinfo->progress->pass_limit = (long) cinfo->total_iMCU_rows;
	(*cinfo->progress->progress_monitor) ((j_common_ptr) cinfo);
      }
      if (! (*cinfo->coef->compress_data) (cinfo, (JSAMPIMAGE) NULL))
	ERREXIT(cinfo, JERR_CANT_SUSPEND);
    }
    (*cinfo->master->finish_pass) (cinfo);
  }
  
  (*cinfo->marker->write_file_trailer) (cinfo);
  (*cinfo->dest->term_destination) (cinfo);
  
  jpeg_abort((j_common_ptr) cinfo);
}



GLOBAL(void)
jpeg_write_marker (j_compress_ptr cinfo, int marker,
		   const JOCTET *dataptr, unsigned int datalen)
{
  JMETHOD(void, write_marker_byte, (j_compress_ptr info, int val));

  if (cinfo->next_scanline != 0 ||
      (cinfo->global_state != CSTATE_SCANNING &&
       cinfo->global_state != CSTATE_RAW_OK &&
       cinfo->global_state != CSTATE_WRCOEFS))
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);

  (*cinfo->marker->write_marker_header) (cinfo, marker, datalen);
  write_marker_byte = cinfo->marker->write_marker_byte;	
  while (datalen--) {
    (*write_marker_byte) (cinfo, *dataptr);
    dataptr++;
  }
}


GLOBAL(void)
jpeg_write_m_header (j_compress_ptr cinfo, int marker, unsigned int datalen)
{
  if (cinfo->next_scanline != 0 ||
      (cinfo->global_state != CSTATE_SCANNING &&
       cinfo->global_state != CSTATE_RAW_OK &&
       cinfo->global_state != CSTATE_WRCOEFS))
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);

  (*cinfo->marker->write_marker_header) (cinfo, marker, datalen);
}

GLOBAL(void)
jpeg_write_m_byte (j_compress_ptr cinfo, int val)
{
  (*cinfo->marker->write_marker_byte) (cinfo, val);
}


/*
 * Alternate compression function: just write an abbreviated table file.
 * Before calling this, all parameters and a data destination must be set up.
 *
 * To produce a pair of files containing abbreviated tables and abbreviated
 * image data, one would proceed as follows:
 *
 *		initialize JPEG object
 *		set JPEG parameters
 *		set destination to table file
 *		jpeg_write_tables(cinfo);
 *		set destination to image file
 *		jpeg_start_compress(cinfo, FALSE);
 *		write data...
 *		jpeg_finish_compress(cinfo);
 *
 * jpeg_write_tables has the side effect of marking all tables written
 * (same as jpeg_suppress_tables(..., TRUE)).  Thus a subsequent start_compress
 * will not re-emit the tables unless it is passed write_all_tables=TRUE.
 */

GLOBAL(void)
jpeg_write_tables (j_compress_ptr cinfo)
{
  if (cinfo->global_state != CSTATE_START)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);

  
  (*cinfo->err->reset_error_mgr) ((j_common_ptr) cinfo);
  (*cinfo->dest->init_destination) (cinfo);
  
  jinit_marker_writer(cinfo);
  
  (*cinfo->marker->write_tables_only) (cinfo);
  
  (*cinfo->dest->term_destination) (cinfo);
}