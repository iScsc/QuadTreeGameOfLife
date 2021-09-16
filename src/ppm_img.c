#include "ppm_img.h"

void print_ppm_img(char name[],world W){
    FILE *p_img = NULL;

    int s = sizeof("out/.ppm")+sizeof(*name);
    char path[s];
    sprintf(path,"out/%s.ppm",name);

    p_img = fopen(path,"w");

    if (p_img == NULL) {
        fprintf(stderr, "Cannot write to file %s!\n",path);
        exit(EXIT_FAILURE);
    }

    fprintf(p_img,"P3\n%d %d\n%d\n",(int)pow(2,W.root->level),(int)pow(2,W.root->level),1);

    return;
}

//test