#include <stddef.h>
#include <stdint.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include"elf.h"

#define BUFFER_SIZE 16

bool elf_isvalid(const uint8_t *data){
    return (memcmp(data, MAGIC, 4)==0);
}

uint8_t getelf_class(FILE *file){
    uint8_t data;
    fseek(file, 4L,SEEK_SET);
    fread(&data,sizeof(data),1,file);
    return data;
}
ELFHeader readheader(FILE *file){
    ELFHeader data;
    fseek(file,0L,SEEK_SET);
    fread(&data,sizeof(ELFHeader),1,file);
    return data;
    }
int main(int argc,char **argv) {
    if(argc != 2){
        printf("usage: %s <elf-file>\n",argv[0]);
        return EXIT_FAILURE;
    }
       FILE *file = fopen(argv[1],"rb");
       if(getelf_class(file)==1){
           printf("ELF32 not supported!\n");
           return EXIT_FAILURE;
       }
       if(file == NULL){
           perror("Error opening file");
           return EXIT_FAILURE;
       }
       ELFHeader header = readheader(file);
       printf("%zu\n",sizeof(ELFHeader));
       printf("Type: %u\n", header.e_type);
       printf("Machine: %u\n", header.e_machine);
       printf("Version: %u\n", header.e_version);
       printf("Entry: 0x%llx\n", (unsigned long long)header.e_entry);
       printf("Program Header Offset: 0x%llx\n",
              (unsigned long long)header.e_phoff);
       printf("Section Header Offset: 0x%llx\n",
              (unsigned long long)header.e_shoff);
       fclose(file);
    return 0;
}
