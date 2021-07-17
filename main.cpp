#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>
using namespace std;

uint32_t bin_file_to_data(char* my_file[]){
    FILE * bin_file;
    if ((bin_file = fopen(*my_file, "rb")) == NULL) {
      fputs("open error", stderr);
      exit(-1);
    }
    uint32_t network_buffer[1];

    size_t readlen = fread(network_buffer, 1, sizeof (uint32_t), bin_file);

    if (readlen != sizeof(uint32_t)){
        printf("fread return %lu\n", readlen);
        exit(-1);
    }
    uint32_t n = ntohl(*network_buffer);

    fclose(bin_file);

    return n;
}

int add(int a, int b){
    return a + b;
}

int main(int argc, char* argv[])
{
    if (argc == 3){
        u_int32_t n1 = bin_file_to_data(&argv[1]);
        u_int32_t n2 = bin_file_to_data(&argv[2]);

        printf("%d(0x%x) + %d(0x%x) = %d(0x%x) \n", n1, n1, n2, n2, add(n1,n2)
               , add(n1, n2));
    }

    else printf("input 2 files.");

    return 0;
}
