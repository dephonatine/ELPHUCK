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
	Elf ## BITS ## _Phdr *get_program_header ## BITS (void *ptr){ \
        Elf ## BITS ## _Phdr *header = malloc(sizeof(Elf ## BITS ## _Phdr)+1); \
        memcpy(header, ptr, sizeof(Elf ## BITS ## _Phdr)); \
        return header; \
}

#define DEF_GET_SH(BITS) \
	Elf ## BITS ## _Shdr *get_section_header ## BITS (void *ptr){ \
        Elf ## BITS ## _Shdr *header = malloc(sizeof(Elf ## BITS ## _Shdr)+1); \
        memcpy(header, ptr, sizeof(Elf ## BITS ## _Shdr)); \
        return header; \
}


#define DEF_BUILD_SH(BITS) \
	Elf ## BITS ## _Shdr *build_sh_list ## BITS (void *buf, Elf ## BITS ## _Ehdr *elf){ \
        void *ptr = (buf + elf->e_shoff); \
        for(int i = 0; i < elf->e_shnum; i++) { \
            sh_list ## BITS [i] = get_section_header ## BITS (ptr); \
            ptr += elf->e_shentsize; \
        } \       
}


#define DEF_BUILD_PH(BITS) \
	Elf ## BITS ## _Phdr *build_ph_list ## BITS (void *buf, Elf ## BITS ## _Ehdr *elf){ \
        void *ptr = (buf + elf->e_phoff); \
        for(int i = 0; i < elf->e_phnum; i++) { \
            ph_list ## BITS [i] = get_program_header ## BITS (ptr); \
            ptr += elf->e_phentsize; \
        } \       
}


#define DEF_BUILD_EH(BITS) \
	Elf ## BITS ## _Ehdr *get_elf_header ## BITS (void *ptr){ \
        Elf ## BITS ## _Ehdr *header = malloc(sizeof(Elf ## BITS ## _Ehdr)+1); \
        memcpy(header, ptr, sizeof(Elf ## BITS ## _Ehdr)); \
        return header; \
}


DEF_GET_PH(32)
DEF_GET_PH(64)
DEF_GET_SH(32)
DEF_GET_SH(64)
DEF_BUILD_SH(32)
DEF_BUILD_SH(64)
DEF_BUILD_PH(32)
DEF_BUILD_PH(64)
DEF_BUILD_EH(32)
DEF_BUILD_EH(64)
    
void identify_arch(Elf_Data *elf) {
    Elf_Ehdr header;
    header.header64 = (Elf64_Ehdr *)elf->data;
    switch(header.header64->e_ident[EI_CLASS]) {
        case ELFCLASS32:
            elf->arch = EM_386;
            break;
        case ELFCLASS64:
            elf->arch = EM_X86_64;
            break;
    }

}

    
/*
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
