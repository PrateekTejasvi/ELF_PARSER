//
// Created by PrateekTejasvi on 14/08/26.
//

#ifndef ELF_PARSER_ELF_H
#define ELF_PARSER_ELF_H
#include <stdint.h>
#include<stdio.h>
#include<stdbool.h>

 //ELF_PARSER_ELF_H
#define EI_NIDENT 16
typedef uint32_t Address; //depending on elf class can either be 32 bit or 64 bit
typedef uint16_t HalfWord;
typedef uint32_t Offset;
typedef uint32_t Word;
/*
 * for e_type
 * ET_NONE 0 = No file type
 * ET_REL 1 = Relocatable file
 * ET_Exec 2 = exectuable file will not support ASLR (address space layout randomization)
 * ET_DYN 3 = shared file
 * ET_CORE 4 = core file
 */
static unsigned char MAGIC[4] = {0x7f,'E','L','F'};
bool elf_isvalid(const uint8_t *data);

uint8_t getelf_class(FILE* file);
uint8_t getelf_data(FILE *file);

typedef struct ELFHeader {
    unsigned char e_ident[EI_NIDENT];
    HalfWord e_type;//type of the elf file
    HalfWord e_machine;//machine type
    Word e_version;//version always 1
    Address e_entry;//entry point for the exectuables
    Offset e_phoff;//program headers offset
    Offset e_shoff;//section headers offset
    Word e_flags;
    HalfWord e_ehsize;//size
    HalfWord e_phentsize;//size per program header
    HalfWord e_phnum;//number of program headers
    HalfWord e_shentsize;
    HalfWord e_shnum;
    HalfWord e_shstrndx;

}ELFHeader;

#endif
