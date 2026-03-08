/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 Description: Declares all structures and function prototypes required for the decoding phase. Provides the DecodeInfo structure to store stego image details 
              and decoded output data, along with helpers for reading magic string, extension, file size, and extracting secret data using LSB-based decoding.
------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#ifndef DECODE_H
#define DECODE_H

#include <stdio.h>
#include "types.h"
#include "common.h"

#define MAX_DECODED_EXT 8
#define MAX_MAGIC_LEN 3   // "#*" + '\0'

typedef struct _DecodeInfo{
    // stego image 
    char *stego_image_fname;
    FILE *fptr_stego_image;

    // output file 
    char *output_fname;
    FILE *fptr_output;

    // decoded data containers 
    char decoded_magic_string[MAX_MAGIC_LEN];
    uint decoded_ext_size;
    char decoded_ext[MAX_DECODED_EXT];
    long decoded_file_size;

} DecodeInfo;

/* read & validate decode args */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* open files for decoding */
Status open_files_decode(DecodeInfo *decInfo);

/* perform decoding */
Status do_decoding(DecodeInfo *decInfo);

// decode helpers 
Status decode_magic_string(DecodeInfo *decInfo);
Status decode_extn_size(DecodeInfo *decInfo);
Status decode_extension(DecodeInfo *decInfo);
Status decode_secret_file_size(DecodeInfo *decInfo);
Status decode_secret_file_data(DecodeInfo *decInfo);

// lsb helpers 
char decode_byte_from_lsb(const char *image_buffer);
uint decode_size_from_lsb(const char *image_buffer);

#endif
