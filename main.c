#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct auheader {
    unsigned char magic_number[4];
    unsigned char data_offset[4];
    unsigned char data_size[4];
    unsigned char coding[4];
    unsigned char sample_rate[4];
    unsigned char channels[4];
    unsigned char info[4];
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

        unsigned int data_offset = (unsigned int)my_auheader.data_offset[0] << 24
            | (unsigned int)my_auheader.data_offset[1] << 16
            | (unsigned int)my_auheader.data_offset[2] << 8
            | (unsigned int)my_auheader.data_offset[3];
        printf("data_offset = %d\n", data_offset);

        unsigned int data_size = (unsigned int)my_auheader.data_size[0] << 24
            | (unsigned int)my_auheader.data_size[1] << 16
            | (unsigned int)my_auheader.data_size[2] << 8
            | (unsigned int)my_auheader.data_size[3];
        printf("data_size = %d\n", data_size);

        unsigned int coding = (unsigned int)my_auheader.coding[0] << 24
            | (unsigned int)my_auheader.coding[1] << 16
            | (unsigned int)my_auheader.coding[2] << 8
            | (unsigned int)my_auheader.coding[3];
        printf("coding = %d\n", coding);
        if (coding != 3)
        {
            printf("I am sorry, I only support 16 bit linear PCM by now.");
            return 0;
        }

        unsigned long sample_rate = (unsigned int)my_auheader.sample_rate[0] << 24
            | (unsigned long)my_auheader.sample_rate[1] << 16
            | (unsigned long)my_auheader.sample_rate[2] << 8
            | (unsigned long)my_auheader.sample_rate[3];
        printf("sample_rate = %u\n", sample_rate);

        unsigned long channels = (unsigned int)my_auheader.channels[0] << 24
            | (unsigned long)my_auheader.channels[1] << 16
            | (unsigned long)my_auheader.channels[2] << 8
            | (unsigned long)my_auheader.channels[3];
        printf("channels = %d\n", channels);

        unsigned char original_stream[data_size];
        unsigned char reversed_stream[data_size];

        fread(&original_stream, data_size,1, ptr_aufile);
        for (int i = 0; i < 16; i++)
            printf("byte #%i = %i\n", i, original_stream[i]);
    }
    fclose(ptr_aufile);
    return 0;
}
