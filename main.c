#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct auheader {
    char magic_number[4];
    char data_offset[4];
    char data_size[4];
    char coding[4];
    char sample_rate[4];
    char channels[4];
    char info[4];
};

int main()
{
    printf("Opening au file...\n");
    FILE *ptr_aufile;
    struct auheader my_auheader;
    ptr_aufile = fopen("/tmp/Xylo.au", "rb");
    if (!ptr_aufile)
    {
        printf("Could not open file.");
    }
    else
    {
        printf("Reading header...\n");
        fread(&my_auheader, sizeof(struct auheader), 1, ptr_aufile);
        printf("magic_number = %s\n", my_auheader.magic_number);
        int data_offset = my_auheader.data_offset[0] * 16777216 + my_auheader.data_offset[1] * 65536 + my_auheader.data_offset[2] * 265 + my_auheader.data_offset[3];
        printf("data_offset = %d\n", data_offset);
        int data_size = my_auheader.data_size[0] * 16777216 + my_auheader.data_size[1] * 65536 + my_auheader.data_size[2] * 265 + my_auheader.data_size[3];
        printf("data_size = %d\n", data_size);
        int coding = my_auheader.coding[0] * 16777216 + my_auheader.coding[1] * 65536 + my_auheader.coding[2] * 265 + my_auheader.coding[3];
        printf("coding = %d\n", coding);
        if (coding != 3)
        {
            printf("I am sorry, I only support 16 bit linear PCM by now.");
            return 0;
        }
        int sample_rate = my_auheader.sample_rate[0] * 16777216 + my_auheader.sample_rate[1] * 65536 + my_auheader.sample_rate[2] * 265 + my_auheader.sample_rate[3];
        printf("sample_rate = %d\n", sample_rate);
        int channels = my_auheader.channels[0] * 16777216 + my_auheader.channels[1] * 65536 + my_auheader.channels[2] * 265 + my_auheader.channels[3];
        printf("channels = %d\n", channels);
    }
    fclose(ptr_aufile);
    return 0;
}
