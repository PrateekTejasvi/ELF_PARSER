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

bool elf_isvalid(FILE *file){
    unsigned char data[4];
    fseek(file,0L,SEEK_SET);
    fread(data,sizeof(data),1,file);
    return memcmp(data,MAGIC,4) == 0  ;
}

uint8_t getelf_class(FILE *file) {
  uint8_t data;
  fseek(file, 4L, SEEK_SET);
  fread(&data, sizeof(data), 1, file);
  return data;
}

SectionHeader *read_section_header(FILE *file, ELFHeader header) {
  SectionHeader *data = malloc(sizeof(SectionHeader) * header.e_shnum);
  for (int i = 0; i < header.e_shnum; i++) {
    uint64_t offset = header.e_shoff + (i * header.e_shentsize);
    fseek(file, offset, SEEK_SET);
    fread(&data[i], sizeof(SectionHeader), 1, file);
  }
  return data;
}
char *read_section_string(FILE *file, SectionHeader *section_headers,
                          ELFHeader header) {
  SectionHeader string_table_header = section_headers[header.e_shstrndx];
  uint64_t offset = string_table_header.sh_offset;
  uint64_t size = string_table_header.sh_size;
  char *data = malloc(sizeof(char) * size);
  fseek(file, offset, SEEK_SET);
  fread(data, size, 1, file);
  return data;
}

ELFHeader readheader(FILE *file) {
  ELFHeader data;
  fseek(file, 0L, SEEK_SET);
  fread(&data, sizeof(ELFHeader), 1, file);
  return data;
}
