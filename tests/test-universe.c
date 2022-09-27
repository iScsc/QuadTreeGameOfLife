#include "universe.h"
#include "ppm_img.h"

int main(int argc, char* argv[]){
    world W = {new_cell(2,0,0,false),{0,0,3,3}};

    display_cell(*W.root);
    printf(" # Adding children to Cell (0,0) lvl 2\n------------------\n");
    
    W.root->children = make_children(*W.root);
    display_cell(*W.root);
    display_cell(*W.root->children[0]);
    display_cell(*W.root->children[1]);
    display_cell(*W.root->children[2]);
    display_cell(*W.root->children[3]);

    display_universe(W);

    print_ppm_img("Univ0",W);

    printf(" # Adding children to Cell (1,0) lvl 1 and getting some alive\n------------------\n");

    cell* newly_alive_cell = W.root->children[1];
    newly_alive_cell->alive = true;
    newly_alive_cell->children = make_children(*newly_alive_cell);
    newly_alive_cell->children[3]->alive = false;

    print_ppm_img("Univ1",W);

    return 0;
}