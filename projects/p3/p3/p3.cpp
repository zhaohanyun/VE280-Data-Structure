#include <iostream>
#include "world_type.h"
#include "simulation.h"
using namespace std;

int main(int argc, char* argv[]) {
    world_t my_world;
    check(argc,argv);
//    read_spe_summary(my_world,argv[1]);
//    read_world(my_world,argv[2]);

    read_file(argc, argv, my_world);
    play(my_world, argc, argv);
}