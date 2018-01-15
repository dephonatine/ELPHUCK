#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include "elf.h"
/*
 * written by: doc
*/

Elf64_Phdr *ph_list64[100];
Elf64_Shdr *sh_list64[100];
Elf32_Phdr *ph_list32[100];
Elf32_Shdr *sh_list32[100];

void main(int argc, char *argv[]) {
    Elf_Data *elf = malloc(sizeof(Elf_Data));
    FILE *fd = fopen(argv[1], "r+");
    fseek(fd, 0, SEEK_END);
    size_t sz = ftell(fd);
    rewind(fd);
    uint8_t *buf = malloc(sz);
    fread(buf, 1, sz, fd);
    elf->data = buf;
    identify_arch(elf);
    switch(elf->arch) {
        case EM_X86_64:
            Elf64_Ehdr *header = get_elf_header64(buf);
            break;


    }

}
