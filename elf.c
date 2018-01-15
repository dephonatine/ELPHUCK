#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "elf.h"
#include "packer.h"

/* elf data/manipulation library */
/* author: doc */

typedef union { 
    Elf64_Ehdr *header;
    Elf32_Ehdr *header;
}


Elf64_Ehdr *get_elf_header(void *buf) { 
    Elf64_Ehdr *header = malloc(sizeof(Elf64_Ehdr));
    memcpy(header, buf, sizeof(Elf64_Ehdr));
//   printf("%s\n", header->e_ident);
    if(memcmp(ELFMAG, header->e_ident, 4)) { 
        printf("Not a valid ELF file. Aborting.\n");
        exit(1);
    }
    return header;
}

Elf64_Phdr *get_program_header(void *ptr) {
    Elf64_Phdr *header = malloc(sizeof(Elf64_Phdr));
    memcpy(header, ptr, sizeof(Elf64_Phdr));
    return header;
}

Elf64_Shdr *get_section_header(void *ptr) { 
    Elf64_Shdr *header = malloc(sizeof(Elf64_Shdr));
    memcpy(header, ptr, sizeof(Elf64_Shdr));
    return header;
}

void build_ph_list(void *buf, Elf64_Ehdr *elf) { 
    void *ptr = (buf + elf->e_phoff);
    for(int i = 0; i < elf->e_phnum; i++) { 
        ph_list[i] = get_program_header(ptr);
        ptr += elf->e_phentsize;
    }
}

void build_sh_list(void *buf, Elf64_Ehdr *elf) {
    void *ptr = (buf + elf->e_shoff);
    for(int i = 0; i < elf->e_shnum; i++) {
        sh_list[i] = get_section_header(ptr);
        ptr += elf->e_shentsize;
    }
}

uint8_t find_section(void *buf, Elf64_Ehdr *elf, uint8_t *section) { 
    uint8_t index = 0;
    uint64_t base = 0;
    for(int i = 0; i < elf->e_shnum; i++) {
        if (sh_list[i]->sh_type == SHT_STRTAB && !sh_list[i]->sh_flags && 
            (sh_list[i]->sh_offset > sh_list[i+1]->sh_offset)) {
                index = i;
                base = sh_list[index]->sh_offset;
                break;      
        }
    }

    for(int i = 0; i < elf->e_shnum; i++) { 
        if(!strcmp((char *)(buf + base + sh_list[i]->sh_name), section)) {
            printf("[^] Found %s\n", section);
            return i;
        }

    }
}
