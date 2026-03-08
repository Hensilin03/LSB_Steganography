/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 Description: Implements the full decoding workflow. Handles validation of input arguments, opening of the stego image, and extraction of embedded data 
              such as the magic string, file extension, file size, and secret file contents. Uses LSB-based decoding to rebuild the original hidden file and write it to the output.
------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "types.h"
#include "common.h"

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo){
    if (argv[2] == NULL)
        return e_failure;

    // stego file must be .bmp 
    if (strcmp(strstr(argv[2], "."), ".bmp") != 0)
        return e_failure;

    decInfo->stego_image_fname = argv[2];

    // optional output file 
    if (argv[3] != NULL)
        decInfo->output_fname = argv[3];
    else
        decInfo->output_fname = NULL;  // advance option - create after reading extension

    return e_success;
}

Status open_files_decode(DecodeInfo *decInfo){
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "r");
    
    if (decInfo->fptr_stego_image == NULL)
        return e_failure;

    //wait until extension decode 

    return e_success;
}

// lsb extract 1 byte
char decode_byte_from_lsb(const char *buffer){
    char ch = 0;
    for (int i = 0; i < 8; i++)
    {
        ch = (ch << 1) | (buffer[i] & 1);
    }
    return ch;
}

// lsb extract 4 bytes integer (32 bits) 
uint decode_size_from_lsb(const char *buffer){
    uint val = 0;
    for (int i = 0; i < 32; i++)
    {
        val = (val << 1) | (buffer[i] & 1);
    }
    return val;
}

Status decode_magic_string(DecodeInfo *decInfo){
    // skip 54 byte header 
    fseek(decInfo->fptr_stego_image, 54, SEEK_SET);

    char buff[8];
    int len = strlen(MAGIC_STRING);

    for (int i = 0; i < len; i++){
        fread(buff, 8, sizeof(char), decInfo->fptr_stego_image);
        decInfo->decoded_magic_string[i] = decode_byte_from_lsb(buff);
    }
    decInfo->decoded_magic_string[len] = '\0';

    if (strcmp(decInfo->decoded_magic_string, MAGIC_STRING) != 0)
        return e_failure;

    return e_success;
}

Status decode_extn_size(DecodeInfo *decInfo){
    char buff[32];
    fread(buff, 32, sizeof(char), decInfo->fptr_stego_image);

    decInfo->decoded_ext_size = decode_size_from_lsb(buff);
    return e_success;
}

Status decode_extension(DecodeInfo *decInfo){
    char buff[8];

    for (int i = 0; i < decInfo->decoded_ext_size; i++){
        
        fread(buff, 8, sizeof(char), decInfo->fptr_stego_image);
        decInfo->decoded_ext[i] = decode_byte_from_lsb(buff);
    }
    decInfo->decoded_ext[decInfo->decoded_ext_size] = '\0';

    // advanced option: create output file now if not provided 
    if (decInfo->output_fname == NULL){
       
        decInfo->output_fname = decInfo->decoded_ext;  // name = ".txt"
    }

    decInfo->fptr_output = fopen(decInfo->output_fname, "w");
    
    if (decInfo->fptr_output == NULL)
        return e_failure;

    return e_success;
}

Status decode_secret_file_size(DecodeInfo *decInfo){
    
    char buff[32];
    fread(buff, 32, sizeof(char), decInfo->fptr_stego_image);

    decInfo->decoded_file_size = decode_size_from_lsb(buff);
    return e_success;
}

Status decode_secret_file_data(DecodeInfo *decInfo){
    
    char buff[8];
    char ch;

    for (int i = 0; i < decInfo->decoded_file_size; i++){
        
        fread(buff, 8, sizeof(char), decInfo->fptr_stego_image);
        ch = decode_byte_from_lsb(buff);
        fwrite(&ch, 1, 1, decInfo->fptr_output);
    }

    return e_success;
}

Status do_decoding(DecodeInfo *decInfo){
    
    if (open_files_decode(decInfo) == e_failure)
        return e_failure;

    if (decode_magic_string(decInfo) == e_failure){
        
        printf("Not a secret message. MAGIC_STRING mismatch.\n");
        return e_failure;
    }

    decode_extn_size(decInfo);
    decode_extension(decInfo);
    decode_secret_file_size(decInfo);
    decode_secret_file_data(decInfo);

    printf("Decoded successfully.\n");
    return e_success;
}
