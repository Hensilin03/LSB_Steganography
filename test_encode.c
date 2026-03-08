/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 Description: Acts as the driver program for both encoding and decoding operations. Determines the requested mode (-e or -d), validates command-line
              arguments, initializes the appropriate structures, and invokes either the encoding or decoding workflow. Provides basic status messages and
              usage guidance for incorrect input.
------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "encode.h"
#include "types.h"
#include "decode.h"

int main(int argc, char *argv[]) {
   
    //check operation type (encoding or decoding)
    if(check_operation_type(argv) == e_encode){

        EncodeInfo encInfo;
        printf("Selected Encoding.\n");
        //validate i/p arg for encoding (2 files .bmp & .txt are mandatory)
        if (read_and_validate_encode_args(argv, &encInfo) == e_success){
           
            printf("Read and validate input arguments is successful!\n");
            
            if(do_encoding(&encInfo) == e_success){
                printf("Completed Encoding.\n");
            }
            else{
                printf("Failed to do the encoding!\n");
            }
        }
        else{
            printf("Failed to validate the input arguments!\n");
        }
    }
    else if(check_operation_type(argv) == e_decode){
        //declare a structure var -- pass by reference
        printf("Selected Decoding.\n");
        //validate the decoding arguments
        //call de decoding
        DecodeInfo decInfo;

        if (read_and_validate_decode_args(argv, &decInfo) == e_success){

            if(do_decoding(&decInfo) == e_success)
                printf("Successfully completed Decoding!\n");
            else
                printf("Failed to decode!\n");
        }
        else{
            printf("Failed to validate decoding arguments!\n");
        }
    }
    else{
        printf("Invalid Option.\n");
        printf("**********************Usage**********************\n");
        printf("Encoding: ./a.out -e beautiful.bmp secret.txt stego.bmp\n");
        printf("Decoding: ./a.out -d stego.bmp decoded.txt\n");
    }

    return 0;
}

OperationType check_operation_type(char *argv[]){

    //./a.out -e beautiful.bmp secret.txt stego.bmp
    if(strcmp(argv[1], "-e") == 0){
        return e_encode;
    }
    else if (strcmp(argv[1], "-d") == 0){
        return e_decode;
    }
    else{
        return e_unsupported;
    }
}
