#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bmp.h"

int main(int argc, char *argv[]) {
    char openfile[] = "./pictures/01.bmp";
    #if defined(VERSION4)
    char savefile[] = "./pictures/01_version4.bmp";
    #elif defined(VERSION5)
    char savefile[] = "./pictures/01_version5.bmp";	
    #else
    char savefile[] = "./pictures/01_after.bmp";
    #endif
    BMP *bmp = (BMP*) malloc(sizeof(BMP));
    clock_t start = 0;
    clock_t end = 0;
    int loop = 50;
    int i;

    /* Load the image and print the infomation */
    bmpLoad(bmp, openfile);
    long stride = bmp->width * 4;
    // bmpPrint(bmp);

    /* RGBA to BW */
    printf("RGBA to BW is in progress....\n");
    #if defined(ORIGIN)
        printf("[Original version]\n");
        start = clock();
        for(i = 0; i < loop; i++){
            rgbaToBw(bmp->data, bmp->width, bmp->height, stride);
        }
        end = clock();
    #endif

    #if defined(VERSION1)
        printf("[Version 1 : using RGB table]\n");
        generateRGBTable();
        start = clock();
        for(i = 0; i < loop; i++){
            rgbaToBw_v1(bmp->data, bmp->width, bmp->height, stride);
        }
        end = clock();
    #endif

    #if defined(VERSION2)
        printf("[Version 2 : using pointer]\n");
        start = clock();
        for(i = 0; i < loop; i++){
            rgbaToBw_v2(bmp->data, bmp->width, bmp->height, stride);
        }
        end = clock();
    #endif

    #if defined(VERSION3)
        printf("[Version 3] : versoin1 + versoin2`\n");
        generateRGBTable();
        start = clock();
        for(i = 0; i < loop; i++){
            rgbaToBw_v3(bmp->data, bmp->width, bmp->height, stride);
        }
        end = clock();
    #endif
	
    #if defined(VERSION4)
        printf("[Version 4] : NEON\n");
        start = clock();
        for(i = 0; i < loop; i++){
            rgbaToBw_v4(bmp->data, bmp->width, bmp->height, stride);
        }
        end = clock();
    #endif
	
    #if defined(VERSION5)
        printf("[Version 4] : NEON (unroll loop + PLD)\n");
        start = clock();
        for(i = 0; i < loop; i++){
            rgbaToBw_v5(bmp->data, bmp->width, bmp->height, stride);
        }
        end = clock();
    #endif	

    printf("Execution time of rgbaToBw() : %lf \n", ((double) (end - start)) / CLOCKS_PER_SEC / loop);
    bmpSave(bmp, savefile);

    return 0;
}
