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
  // NOTE:the outputs here are actually in decimal

  ELF_FILE *open = elf_open(file);
  elf_close(open);

  fclose(file);
  return 0;
}
