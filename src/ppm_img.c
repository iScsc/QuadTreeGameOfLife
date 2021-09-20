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

    for (int j = W.limits.y0; j < W.limits.y1; j++) {
        for(int i = W.limits.x0; i<W.limits.x1; i++){
            int color = 1;
            if(get_state(W,i,j)==1){
                color = 0;
            }
            fprintf(p_img, "%3d %3d %3d ", color,color,color);
        }
        fprintf(p_img,"\n");

    }

    fclose(p_img);

    p_img = NULL;

    return;
}

//test