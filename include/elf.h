//
// Created by PrateekTejasvi on 14/08/26.
//

#ifndef ELF_PARSER_ELF_H
#define ELF_PARSER_ELF_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// ELF_PARSER_ELF_H
#define EI_NIDENT 16
/*
 * for e_type
 * ET_NONE 0 = No file type
 * ET_REL 1 = Relocatable file
 * ET_Exec 2 = exectuable file will not support ASLR (address space layout
 * randomization) ET_DYN 3 = shared file ET_CORE 4 = core file
 */
const static unsigned char MAGIC[4] = {0x7f, 'E', 'L', 'F'};
bool elf_isvalid(const uint8_t *data);


typedef struct ELFHeader {
  unsigned char e_ident[EI_NIDENT];
  uint16_t e_type;    // type of the elf file
  uint16_t e_machine; // machine type
  uint32_t e_version;     // version always 1
  uint64_t e_entry;    // entry point for the exectuables
  uint64_t e_phoff;     // program headers offset
  uint64_t e_shoff;     // section headers offset
  uint32_t e_flags;
  uint16_t e_ehsize;    // size
  uint16_t e_phentsize; // size per program header
  uint16_t e_phnum;     // number of program headers
  uint16_t e_shentsize;
  uint16_t e_shnum;
  uint16_t e_shstrndx;

} ELFHeader;

#endif
