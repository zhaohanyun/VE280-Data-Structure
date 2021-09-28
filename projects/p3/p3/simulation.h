//
// Created by Administrator on 2019/10/18.
//

#ifndef P3_SIMULATION_H
#define P3_SIMULATION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "world_type.h"
using namespace std;

void read_spe_summary(world_t &world,string);
void read_world(world_t &world,string);
void read_file(int argc, char *argv[],world_t &my_world);
//EFFECT: run read_spe_summary and read_world function, and collect the errors when reading files.

void check(int argc, char *argv[]);


void state_print(world_t world);

void play(world_t my_world, int argc, char* argv[]);
//EFFECT:run the turns of the world
#endif //P3_SIMULATION_H
