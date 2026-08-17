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
uint8_t getelf_data(FILE *file){
    uint8_t elf_data;
    fseek(file,5L,SEEK_SET);
    fread(&elf_data,sizeof(elf_data),1,file);
    return elf_data;
}

int main(int argc,char **argv) {
    if(argc != 2){
        printf("usage: %s <elf-file>\n",argv[0]);
        return EXIT_FAILURE;
    }
       FILE *file = fopen(argv[1],"rb");
       if(file == NULL){
           perror("Error opening file");
           return EXIT_FAILURE;
       }
       uint8_t buffer[BUFFER_SIZE];
       size_t bytesRead = fread(buffer,sizeof(uint8_t),BUFFER_SIZE,file);
       if (bytesRead < 4) {
           printf("File too small to be an ELF file\n");
           fclose(file);
           return EXIT_FAILURE;
       }
       if(elf_isvalid(buffer)){
           printf("file is a valid elf\n");
       }
       else{
           printf("file is not a valid elf file\n");
       }
       printf("elf_class:%d\n",getelf_class(file));
       printf("elf_data:%d\n",getelf_data(file));//TODO:do not need this technically because we have already loaded the first 16 bytes of the file into the buffer
       printf("elf_version:%d\n",buffer[6]);
       fclose(file);
    return 0;
}
