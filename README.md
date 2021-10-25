# QuadTreeGameOfLife

In this directory, you'll find an implementation of Conway's Game of Life (GoL). The simulation is written in C language and uses SDL graphic library.

## Table Of Content.
- [1. ](https://github.com/Supaero-Computer-Science-Club/QuadTreeGameOfLife) Project Presentation
- [2. ](https://github.com/Supaero-Computer-Science-Club/QuadTreeGameOfLife) Structure 
- [3. ](https://github.com/Supaero-Computer-Science-Club/QuadTreeGameOfLife) Run the Code

## 1 Project Presentation. [[toc](https://github.com/Supaero-Computer-Science-Club/QuadTreeGameOfLife)]
This project aims to implement the GoL using **QuadTree** to store cells and the whole universe. The final goal is to compare it to implementations which use arrays (naive implementation), linked-list or others type of structure, at different scale and universe density in terms of **computing duration** and **computing cost**. Every implementation must be in C to compare the effectiveness of the structure not the one of the language.

## 2 Structure. [[toc](https://github.com/Supaero-Computer-Science-Club/QuadTreeGameOfLife)]
The interesting aspect of the project is the way the Conway's Universe is stored.
Indeed it uses QuadTree, a classic tree implementation but with 4 children and **only not-uniform branches** are developed which allow to reduce the needed memory to store the universe while preserving a quick access to a cell ( O(log(n)) ). See an example here:
| ![quadtree.png](https://github.com/Supaero-Computer-Science-Club/QuadTreeGameOfLife/res/quadtree.png) | 
|:--:| 
| *A Quadtree to store and sort points* |
The structure of the cells used is :
```C
struct cell{ //origin top left, y increasing down, x incr. right 
    int level;
    int x;
    int y;
    bool alive;
    cell** children; //children is either NULL or a 4 not-NULL-pointers array, can't be [NULL,cell,cell,NULL]
    //format: [top left, tr , bl , br ]
    //coord : [   0 0  , 1 0, 0 1, 1 1]
};
```
Remarks:
- ONLY cells of level 0 are real Conway's cells
- a cell of level n has a size of 2^n in the universe but needs the same memory space that a lvl 0
- **level** of the root increases as the universe expands, at any time the size of the universe is 2^root.level
- the **alive** variable is taken into account only if the cell hasn't any children, then the value of **alive** is associated to the whole cell and its non-existing children.
- A cell where level != 0 has a size != 1 so can't have real coordinates. So the coord of a level n cell are the coord of its first child (top left).
## 3 Run the code. [[toc](https://github.com/Supaero-Computer-Science-Club/QuadTreeGameOfLife)]
To run the program you'll need the `gcc` compiler and the `SDL` library. You can install both with `sudo apt install gcc` and `sudo apt install libsdl2-dev` on Ubuntu 20.04 LTS.
Then, run `make app` in the root folder of the project.
*NB: to re-run the program just type `./out/app`, files are already compiled.*
To clean the repository you can run `make clean`.

