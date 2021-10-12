#include "universe.h"
#include "ppm_img.h"

int main(int argc, char* argv[]){

    //constructing a World via universe.c
    world W = {new_cell(2,0,0,false),{0,0,3,3}};
    //W : root lvl 2, no children
    display_cell(*W.root);

    printf(" # Adding children to Cell (0,0) lvl 2\n------------------\n");
    //added children lvl 1

    W.root->children = make_children(*W.root);
    display_cell(*W.root);
    display_cell(*W.root->children[0]);
    display_cell(*W.root->children[1]);
    display_cell(*W.root->children[2]);
    display_cell(*W.root->children[3]);

    //display universe boundaries and root lvl
    display_universe(W);

    printf(" # Adding children to Cell (1,0) lvl 1 and getting some alive\n------------------\n");

    cell* newly_alive_cell = W.root->children[1];
    newly_alive_cell->alive = true;
    newly_alive_cell->children = make_children(*newly_alive_cell);
    display_cell(*newly_alive_cell);


    //Test find_cell
    printf("\n # Testing find_cell and killing (3,1)\n");
    cell* dying_cell = find_cell(W,3,1);
    dying_cell->alive =false;
    display_cell(*dying_cell);

    print_ppm_img("W_rlvl2_lvl0_alive",W);

    //Tests off_limits
    printf("\nTesting off_limits (W boundaries are 0 3 0 3 (root lvl 2))\n");
    printf("Point (0,0): %d\nPoint (-1,0): %d\nPoint (5,1): %d\n",
    off_limits(W,0,0),off_limits(W,-1,0),off_limits(W,5,1));

    printf("\nTesting get_state (W boundaries are 0 3 0 3 (root lvl 2))\n");
    printf("Point (0,0): %d\nPoint (-1,0): %d\nPoint (2,1): %d\n",
    get_state(W,0,0),get_state(W,-1,0),get_state(W,2,1));
    printf("------------------\n # Testing change_state on existing cells\n");
    change_state(W,0,3,true);
    change_state(W,1,1,true);
    change_state(W,3,0,false);
    
    printf(" Printing .ppm...\n");

    print_ppm_img("W_rlvl2_test_change_state",W);

    printf(" ... printed\n");

    printf("------------------\n # Testing change_state on NON-existing cells\n");

    

    return 0;
}