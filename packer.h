/* elf header offsets */
#define     OFF_IDENT           0
#define     OFF_TYPE            16
#define     OFF_MACHINE         18
#define     OFF_VERSION         20
#define     OFF_ENTRY           24
#define     OFF_PHOFF           32
#define     OFF_SHOFF           40
#define     OFF_FLAGS           48
#define     OFF_EHSIZE          52
#define     OFF_PHENTSIZE       54
#define     OFF_PHNUM           56
#define     OFF_SHENTSIZE       58
#define     OFF_SHNUM           60
#define     OFF_SHSTRNDX        62

/* section header offsets */
#define     LOC_NAME            0
#define     LOC_TYPE            4
#define     LOC_FLAGS           8
#define     LOC_ADDR            16
#define     LOC_OFFSET          24
#define     LOC_SIZE            32
#define     LOC_LINK            40
#define     LOC_INFO            44
#define     LOC_ADDRALIGN       48
#define     LOC_ENTSIZE         56

/* program header offsets */
#define     P_TYPE              0
#define     P_FLAGS             P_TYPE + 4
#define     P_OFFSET            P_FLAGS + 4
#define     P_VADDR             P_OFFSET + 8
#define     P_PADDR             P_VADDR + 8
#define     P_FILESZ            P_PADDR + 8
#define     P_MEMSZ             P_FILESZ + 8
#define     P_ALIGN             P_MEMSZ + 8

/* program segment types */
#define     PT_NULL             0
#define     PT_LOAD             1
#define     PT_DYNAMIC          2
#define     PT_INTERP           3
#define     PT_NOTE             4

/* program segment flags */
#define     PF_X                0x1
#define     PF_W                0x2
#define     PF_R                0x4

#define SHT_STRTAB      3

extern Elf64_Phdr *ph_list[100];
extern Elf64_Shdr *sh_list[100];
