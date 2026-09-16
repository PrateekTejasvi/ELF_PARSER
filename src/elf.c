#include"elf.h"
#include<stdlib.h>
#include<string.h>

ELF_FILE *elf_open(FILE *file){
    ELF_FILE *elf = malloc(sizeof(ELF_FILE));
    elf->file = file;
    elf->header = readheader(file);
    elf->section_header = read_section_header(file,elf->header);
    elf->section_string_table = read_section_string(file, elf->section_header, elf->header);
    return elf;
}
void elf_close(ELF_FILE *elf){
    free(elf->section_string_table);
    free(elf->section_header);
    free(elf);
}
bool readAt(FILE *file,uint64_t offset,void *buffer,size_t size){
    if(fseek(file,offset,SEEK_SET) != 0) return false;
    return fread(buffer,1,size,file) == size;
}

bool elf_isvalid(FILE *file){
    unsigned char data[4];
    readAt(file,0L,&data,sizeof(data));
    return memcmp(data,MAGIC,4) == 0  ;
}
uint8_t getelf_class(FILE *file) {
  uint8_t data;
  readAt(file,4L,&data,sizeof(data));
  return data;
}

SectionHeader *read_section_header(FILE *file, ELFHeader header) {
  SectionHeader *data = malloc(sizeof(SectionHeader) * header.e_shnum);
  for (int i = 0; i < header.e_shnum; i++) {
    uint64_t offset = header.e_shoff + (i * header.e_shentsize);
    readAt(file,offset,&data[i],header.e_shentsize);
  }

  return data;
}
char *read_section_string(FILE *file, SectionHeader *section_headers,
                          ELFHeader header) {
  SectionHeader string_table_header = section_headers[header.e_shstrndx];
  uint64_t offset = string_table_header.sh_offset;
  uint64_t size = string_table_header.sh_size;
  char *data = malloc(sizeof(char) * size);
  readAt(file, offset, data, size);
  return data;
}

ELFHeader readheader(FILE *file) {
  ELFHeader data;
  readAt(file,0L,&data,sizeof(data));
  return data;
}
