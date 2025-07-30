#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *f = fopen("main.wasm", "wb");
    if (!f) {
        perror("Erro ao criar o ficheiro");
        return 1;
    }

    printf("\033c\033[43;30m\nCriando ficheiro main.wasm...\n");

    // Cabeçalho wasm
    unsigned char filetype[]        = { 0x00, 'a', 's', 'm' };
    unsigned char version[]         = { 0x01, 0x00, 0x00, 0x00 };

    // Seção de tipos
    unsigned char sectiontype       = 0x01;
    unsigned char sectionsize       = 0x07;
    unsigned char numbertypes       = 0x01;
    unsigned char funcs             = 0x60;
    unsigned char parametrs         = 0x02;
    unsigned char parametrsid1      = 0x7f; // i32
    unsigned char parametrsid2      = 0x7f; // i32
    unsigned char numberofresults   = 0x01;
    unsigned char returnvalue       = 0x7f; // i32

    // Seção de funções
    unsigned char functionid        = 0x03;
    unsigned char sectionsize2      = 0x02;
    unsigned char numberoffunctions = 0x01;
    unsigned char indexcodes        = 0x00;

    // Seção de exportação
    unsigned char exports           = 0x07;
    unsigned char sectionsize3      = 0x07;
    unsigned char numberexports     = 0x01;
    unsigned char lenname           = 0x03;
    char funcname[]                 = "sum";
    unsigned char exportmode        = 0x00;
    unsigned char exportindex       = 0x00;

    // Seção de código
    unsigned char sectioncode       = 0x0A;
    unsigned char setioncodesize    = 0x09;
    unsigned char functioncount     = 0x01;
    unsigned char functionbodysize  = 0x07;
    unsigned char localdecl         = 0x00;

    // Instruções: local.get 0, local.get 1, i32.add, end
    unsigned char codes[] = { 0x20, 0x00, 0x20, 0x01, 0x6A, 0x0B };

    // Escrever todos os dados em ordem
    fwrite(filetype, sizeof(filetype), 1, f);
    fwrite(version, sizeof(version), 1, f);

    fwrite(&sectiontype, 1, 1, f);
    fwrite(&sectionsize, 1, 1, f);
    fwrite(&numbertypes, 1, 1, f);
    fwrite(&funcs, 1, 1, f);
    fwrite(&parametrs, 1, 1, f);
    fwrite(&parametrsid1, 1, 1, f);
    fwrite(&parametrsid2, 1, 1, f);
    fwrite(&numberofresults, 1, 1, f);
    fwrite(&returnvalue, 1, 1, f);

    fwrite(&functionid, 1, 1, f);
    fwrite(&sectionsize2, 1, 1, f);
    fwrite(&numberoffunctions, 1, 1, f);
    fwrite(&indexcodes, 1, 1, f);

    fwrite(&exports, 1, 1, f);
    fwrite(&sectionsize3, 1, 1, f);
    fwrite(&numberexports, 1, 1, f);
    fwrite(&lenname, 1, 1, f);
    fwrite(funcname, strlen(funcname), 1, f);
    fwrite(&exportmode, 1, 1, f);
    fwrite(&exportindex, 1, 1, f);

    fwrite(&sectioncode, 1, 1, f);
    fwrite(&setioncodesize, 1, 1, f);
    fwrite(&functioncount, 1, 1, f);
    fwrite(&functionbodysize, 1, 1, f);
    fwrite(&localdecl, 1, 1, f);
    fwrite(codes, sizeof(codes), 1, f);

    fclose(f);
    printf("Ficheiro main.wasm criado com sucesso!\n");
    return 0;
}

