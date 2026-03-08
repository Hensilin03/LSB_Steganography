# Image Steganography in C (LSB Method)

This project **hides secret messages inside BMP images using the Least Significant Bit (LSB) method**.

The program **hides a secret text file inside a BMP image** and **later allows the hidden data to be extracted from the image**. It operates through the command line and uses a technique called **Least Significant Bit (LSB)** steganography to embed the secret information. By modifying the least significant bits of the image's byte data, the program stores the hidden message without causing noticeable changes to the image. As a result, the image appears visually unchanged while secretly containing the embedded text.

## What the Program Does

### 1. Encoding
* Choose a `.bmp` image and a `.txt` file
* The program embeds the text file inside the image
* A new image called the **stego image** is created

### 2. Decoding
* Provide the stego image
* The program extracts the hidden text file from it

## How Encoding Works

1. **Open Files**     – Load the source `.bmp` image and the secret `.txt` file.
2. **Capacity Check** – Ensure the image has enough space (8 image bytes store 1 secret byte).
3. **Copy Header**    – Copy the 54-byte BMP header to keep the output image valid.
4. **Magic String**   – Encode a small identifier (`#*`) to mark that hidden data exists.
5. **Store Metadata** – Encode the file extension and secret file size.
6. **Hide Data**      – Embed the secret file bits into the **least significant bits (LSB)** of image bytes.
7. **Finalize**       – Copy the remaining image data to complete the stego image.

## Decoding Process

1. **Skip Header**         – Move past the 54-byte BMP header.
2. **Verify Magic String** – Check if `#*` exists to confirm hidden data.
3. **Read Metadata**       – Decode the file extension and stored file size.
4. **Extract Data**        – Reconstruct the secret file by reading LSBs from the image bytes.
5. **Write Output**        – Save the recovered data into a new output file.

## Project Files
```
common.h      → Magic string definition
encode.c      → Encoding logic
encode.h      → Encode structures and prototypes
decode.c      → Decoding logic
decode.h      → Decode structures and prototypes
types.h       → Custom data types and enums
test_encode.c → Main program (handles encode/decode)
```

## How to Compile

Compile using GCC:
```
gcc *.c -o stego
```

## How to Run

### Encoding
```
./stego -e beautiful.bmp secret.txt stego.bmp
```

If the output image name is not provided, the program creates **stego.bmp** by default.

### Decoding
```
./stego -d stego.bmp decoded.txt
```

This extracts the hidden message and saves it to `decoded.txt`.

## Concepts Used
While working on this project I practiced:

* File handling in C
* Bitwise operations
* Understanding basic BMP file structure
* Command line arguments
* Structures
* Modular programming

## Notes
* The program currently supports **BMP images only**
* The secret file is expected to be a **.txt file**
* The LSB method changes image data slightly, but visually the image remains the same

## Author
**Hensilin Rithista S**
B.Tech Electronics and Communication Engineering
