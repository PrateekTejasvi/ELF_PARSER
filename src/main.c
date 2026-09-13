#include "elf.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
  if (argc != 2) {
    printf("usage: %s <elf-file>\n", argv[0]);
    return EXIT_FAILURE;
  }
  FILE *file = fopen(argv[1], "rb");
  if (file == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }
  if (getelf_class(file) == 1) {
    printf("ELF32 not supported!\n");
    return EXIT_FAILURE;
  }
  ELFHeader header = readheader(file);
  SectionHeader *section_header = read_section_header(file,header);
  // NOTE:the outputs here are actually in decimal
/*   for (int i = 0; i < header.e_shnum; i++) {
    printf("Section %d\n", i);
    printf("  Name: %u\n", section_header[i].sh_name);
    printf("  Type: %u\n", section_header[i].sh_type);
    printf("  Flags: 0x%lx\n", (unsigned long)section_header[i].sh_flags);
    printf("  Address: 0x%lx\n", (unsigned long)section_header[i].sh_addr);
    printf("  Offset: 0x%lx\n", (unsigned long)section_header[i].sh_offset);
    printf("  Size: %lu\n", (unsigned long)section_header[i].sh_size);
    printf("  Link: %u\n", section_header[i].sh_link);
    printf("  Info: %u\n", section_header[i].sh_info);
    printf("  Address alignment: %lu\n",
           (unsigned long)section_header[i].sh_addralign);
    printf("  Entry size: %lu\n\n",
           (unsigned long)section_header[i].sh_entsize);
  } */
  char *read_string = read_section_string(file, section_header, header);
  for(int i=1;i<header.e_shnum;i++){
      printf("[%d]:%s\n",i,&read_string[section_header[i].sh_name]);
  }//section0 is the NULL section

  free(section_header);
  free(read_string);
  /*        printf("Type: %u\n", header.e_type);
         printf("Machine: %u\n", header.e_machine);
         printf("Version: %u\n", header.e_version);
         printf("Entry: 0x%llx\n", (unsigned long long)header.e_entry);
         printf("Program Header Offset: 0x%llx\n",
                (unsigned long long)header.e_phoff);
         printf("Section Header Offset: 0x%llx\n",
                (unsigned long long)header.e_shoff);
         printf("Size of one program header:%d\n",header.e_phentsize);
         printf("Number of program headers%d\n",header.e_phnum);
         printf("size of one section header:%d\n",header.e_shentsize);
         printf("Number of section headers:%d\n",header.e_shnum);
         printf("section header string table index:0x%d\n",header.e_shstrndx);
   */
  fclose(file);
  return 0;
}
