// compress.c
#include "compress.h"
#include <stdio.h>
#include <stdlib.h>

// Function to reverse bits in a byte
unsigned char reverseBits(unsigned char num) {
    unsigned char NO_OF_BITS = sizeof(num) * 8;
    unsigned char reverse_num = 0;
    int i;
    for (i = 0; i < NO_OF_BITS; i++) {
        if((num & (1 << i)))
           reverse_num |= 1 << ((NO_OF_BITS - 1) - i);  
    }
    return reverse_num;
}

void compressFile(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "wb");
    int digit;
    unsigned char buffer = 0;
    int bitsFilled = 0;

    if (!inputFile || !outputFile) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while ((digit = fgetc(inputFile)) != EOF) {
        if (digit >= '0' && digit <= '9') {
            unsigned char encoded = reverseBits((digit - '0')) >> 4;
            buffer = (buffer << 4) | encoded;
            bitsFilled += 4;

            if (bitsFilled == 8) {
                fwrite(&buffer, 1, 1, outputFile);
                buffer = 0;
                bitsFilled = 0;
            }
        }
    }

    if (bitsFilled > 0) { // Pad the last digit with 4 zeros if needed
        buffer = buffer << (8 - bitsFilled);
        fwrite(&buffer, 1, 1, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}

void decompressFile(const char *inputFileName, const char *outputFileName) {
    FILE *inputFile = fopen(inputFileName, "rb");
    FILE *outputFile = fopen(outputFileName, "w");
    unsigned char buffer;
    int bytesRead;

    if (!inputFile || !outputFile) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while ((bytesRead = fread(&buffer, 1, 1, inputFile)) > 0) {
        for (int i = 7; i >= 0; i -= 4) {
            unsigned char digit = (buffer >> i) & 0xF;
            digit = reverseBits(digit) >> 4;
            if (i == 7 || (i == 3 && bytesRead * 8 - 4 > i)) { // Do not decode padding
                fputc('0' + digit, outputFile);
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}
