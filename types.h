/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 Description: Defines common user-defined data types and enums used throughout the steganography project. Includes typedefs for unsigned integers, status
              codes for function results, and operation-type identifiers for selecting encoding or decoding modes.
------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#ifndef TYPES_H
#define TYPES_H

/* User defined types */
typedef unsigned int uint;

/* Status will be used in fn. return type */
typedef enum
{
    e_success,
    e_failure
} Status;

typedef enum
{
    e_encode,
    e_decode,
    e_unsupported
} OperationType;

#endif
