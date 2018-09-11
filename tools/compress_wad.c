#include "miniz.h"
#include <stdio.h>

#define SRC_SIZE 8 * 1024 * 1024

unsigned char src_data[SRC_SIZE];

int main(int argc, char * argv[])
{
    puts("Opening file");
    FILE * fp = fopen("res/doom1.wad", "r+b");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    puts("Reading file");
    size_t src_len = fread(src_data, sizeof src_data[0], SRC_SIZE, fp);
    if (!src_len)
    {
        printf("Error reading file.\n");
        fclose(fp);
        return 1;
    }
    puts("Closing file");
    fclose(fp);
    size_t cmp_len = SRC_SIZE;
    unsigned char * cmp_data = (unsigned char *) malloc(cmp_len);
    puts("Compressing");
    int status = compress(cmp_data, &cmp_len, src_data, src_len);
    if (status != Z_OK)
    {
        printf("Compresion failed!\n");
        printf("Error: %s\n", zError(status));
        free(cmp_data);
        return 1;
    }
    puts("Opening destination file");
    fp = fopen("res/doom1.zlib", "w+b");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    puts("Writing destination file");
    size_t count = fwrite(cmp_data, sizeof cmp_data[0], cmp_len, fp);
    puts("Done writing");
    if (count < cmp_len)
    {
        printf("Error writing file\n");
        fflush(stdout);
        free(cmp_data);
        fclose(fp);
        return 1;
    }
    free(cmp_data);
    puts("Closing destination file");
    fclose(fp);
    return 0;
}
