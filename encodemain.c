// encodemain.c
#include "compress.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Usage: %s -c|-d filename\n", argv[0]);
        return 1;
    }

    if(strcmp(argv[1], "-c") == 0) {
        // Compress file
    } else if(strcmp(argv[1], "-d") == 0) {
        // Decompress file
    } else {
        printf("Invalid option. Use -c for compress and -d for decompress.\n");
        return 1;
    }

    return 0;
}
