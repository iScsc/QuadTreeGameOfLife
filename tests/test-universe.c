#include "universe.h"
#include "ppm_img.h"

int main(int argc, char* argv[]){
    world W = {new_cell(1,0,0,false),{0,0,1,1}};

    display_cell(*W.root);
    printf(" # Adding children to Cell (0,0) lvl 1\n------------------\n");
    
    W.root->children = make_children(*W.root);
    display_cell(*W.root);
    display_cell(*W.root->children[0]);
    display_cell(*W.root->children[1]);
    display_cell(*W.root->children[2]);
    display_cell(*W.root->children[3]);

    display_universe(W);

    //print_ppm_img("test",W);
    return 0;
}