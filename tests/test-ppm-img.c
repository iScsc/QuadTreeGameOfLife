#include "ppm_img.h"

int main(int argc, char const *argv[]){
    world W = {new_cell(2,0,0,false),{0,0,3,3}};
    W.root->children = make_children(*W.root);

    print_ppm_img("Univ0",W);

    cell* newly_alive_cell = W.root->children[1];
    newly_alive_cell->alive = true;
    newly_alive_cell->children = make_children(*newly_alive_cell);
    newly_alive_cell->children[3]->alive = false;

    print_ppm_img("Univ1",W);
    return 0;
}
