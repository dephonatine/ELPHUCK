#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include "elf.h"
/*
 * written by: doc
*/

Elf64_Phdr *ph_list[100];
Elf64_Phdr *sh_list[100];

void main(int argc, char *argv[]) { 
    FILE *fd = fopen(argv[1], "r+");
    fseek(fd, 0, SEEK_END);
    size_t sz = ftell(fd);
    rewind(fd);
    uint8_t *buf = malloc(sz);
    fread(buf, 1, sz, fd);

    Elf64_Ehdr *elf_header = get_elf_header(buf);
    build_ph_list(buf, elf_header);
    build_sh_list(buf, elf_header);

    uint8_t section_text = find_section(buf, elf_header, ".text");
    uint8_t section_plt = find_section(buf, elf_header, ".plt.got");

}
