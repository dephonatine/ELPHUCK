#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "elf.h"
#include "packer.h"

/* elf data/manipulation library */
/* 32-bit support coming later */
/* author: doc */

extern Elf64_Phdr *ph_list64[100];
extern Elf64_Shdr *sh_list64[100];
extern Elf32_Phdr *ph_list32[100];
extern Elf32_Shdr *sh_list32[100];


#define DEF_GET_PH(BITS) \
	Elf ## BITS ## _Phdr *get_program_header(void *ptr){ \
        Elf ## BITS ## _Phdr *header = malloc(sizeof(Elf ## BITS ## _Phdr)); \
        memcpy(header, ptr, sizeof(Elf ## BITS ## _Phdr); \
        return header; \
    }
DEF_GET_PH(32)
#define DEF_GET_SH(BITS) \
    Elf ## BITS ## _Shdr *get_section_header(void *ptr) { \
        Elf ## BITS ## _Shdr *header = malloc(sizeof(Elf ## BITS ## _Shdr)); \
        memcpy(header, ptr, sizeof(ELF ## BITS ## _Shdr)); \
        return header; \
    }
/*
#define DEF_BUILD_PH(BITS) \
    void build_ph_list(void *buf, Elf_Ehdr *elf) { \
        void *ptr = (buf + elf.header ## BITS ## ->e_phoff); \
        for(int i = 0; i < elf.header ## BITS ## ->e_phnum; i++) {\
            ph_list ## BITS ## [i] = get_program_header(ptr); \
            ptr += elf.header ## BITS ## ->e_phentsize; \
        } \
    }

#define DEF_BUILD_SH(BITS) \
    void build_sh_list(void *buf, Elf_Ehdr *elf) { \
        void *ptr = (buf + elf.header ## BITS ## ->e_shoff); \
        for(int i = 0; i < elf.header ## BITS ## ->e_shnum; i++) {\
            sh_list ## BITS ## [i] = get_program_header(ptr); \
            ptr += elf.header ## BITS ## ->e_shentsize; \
        } \
    }
*/



Elf_Ehdr *get_elf_header(Elf_Data *elf) {
    Elf_Ehdr header;
    uint8_t bits;
    header.header64 = (Elf64_Ehdr *)elf->data;
    switch(header.header64->e_ident[EI_CLASS]) { 
        case ELFCLASS32:
            bits = 32;
            break;
        case ELFCLASS64:
            bits = 64;
            break;
        default:
            bits = 0;
    }
}

/*
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
*/
