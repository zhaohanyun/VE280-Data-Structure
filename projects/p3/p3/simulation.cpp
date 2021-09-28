//
// Created by Administrator on 2019/10/18.
//
#include <iostream>
#include <fstream>
#include "simulation.h"
#include "world_type.h"
using namespace std;

void op_helper(instruction_t & inst_temp, string& inst){
    //EFFECT:set the op value for following four instruction
    int i=0;
    for (i=0;i<9;i++){
        if (inst==opName[i]) {
            inst_temp.op = (opcode_t) i;
            break;
        }
    }
    if (i==9){
        cout<<"Error: Instruction "<<inst<<" is not recognized!"<<endl;
        cout<<endl;
        exit(6);
    }
}

void direction_helper(direction_t &direction, const string &direction_temp){
    int i;
    for (i=0;i<4;i++) {
        if (direction_temp==directName[i]) {
            direction = (direction_t) i;
            break;
        }
    }
    if (i==4){
        cout<<"Error: Direction "<<direction_temp<<" is not recognized!"<<endl;
        cout<<endl;
        exit(9);
    }
}

void check_num_species(int num_species){
    if ((unsigned int)num_species>MAXSPECIES)
    {
        cout<<"Error: Too many species!"<<endl;
        cout<<"Maximal number of species is "<<MAXSPECIES<<"."<<endl;
        cout<<endl;
        exit(4);
    }
}

void check_inst_num(string& species,int inst_counter){
    if ((unsigned int)inst_counter>MAXPROGRAM){
        cout<<"Error: Too many instructions for species "<<species<<"!"<<endl;
        cout<<"Maximal number of instructions is "<<MAXPROGRAM<<"."<<endl;
        cout<<endl;
        exit(5);
    }
}

void check_crea_num(int creature_counter){
    if ((unsigned int)creature_counter>MAXCREATURES){
        cout<<"Error: Too many creatures!"<<endl;
        cout<<"Maximal number of creatures is "<<MAXCREATURES<<"."<<endl;
        cout<<endl;
        exit(7);
    }
}

void check_crea_name(const world_t& world, string* species_in_file, int num_species){
    int i,j;
    for (i=0;(unsigned int)i<world.numSpecies;i++){
        for (j=0;j<num_species;j++){
            if (world.creatures[i].species->name==species_in_file[j]){
                break;
            }
        }
        if(j==num_species){
            cout<<"Error: Species "<<world.creatures[i].species->name<<" not found!"<<endl;
            cout<<endl;
            exit(8);
        }
    }
}

void check_height(int height){
    if (height<1||(unsigned int)height>MAXHEIGHT){
        cout<<"Error: The grid height is illegal!"<<endl;
        cout<<endl;
        exit(10);
    }
}

void check_width(int width){
    if (width<1||(unsigned int)width>MAXWIDTH){
        cout<<"Error: The grid width is illegal!"<<endl;
        cout<<endl;
        exit(11);
    }
}

void check_in_boundary(creature_t creature, int height, int width){
    if (creature.location.c+1>height||creature.location.r+1>width ||creature.location.c<0 ||creature.location.r<0){
        cout<<"Error: Creature ("<<creature.species->name<<" "<<directName[creature.direction]<<" "<<creature.location.r<<" "<<creature.location.c<<") is out of bound!"<<endl;
        cout<<"The grid size is "<<height<<"-by-"<<width<<"."<<endl;
        cout<<endl;
        exit(12);
    }
}

void init_squares(world_t& world){
    int i,j;
    for (i=0;(unsigned int)i<MAXHEIGHT-1;i++){
        for(j=0;(unsigned int)j<MAXWIDTH-1;j++){
            world.grid.squares[i][j]= nullptr;
        }
    }
}

void grid_pointer(world_t &world,creature_t *crea_to_place){
    //EFFECT: check overlap and set the pointer of a grid
    creature_t *crea_ptr1;
    crea_ptr1=world.grid.squares[crea_to_place->location.r][crea_to_place->location.c];
        if (crea_ptr1!= nullptr){
        cout<<"Error: Creature ("<<crea_to_place->species->name<<" "<<directName[crea_to_place->direction]<<" "<<crea_to_place->location.r<<" "<<crea_to_place->location.c<<") overlaps with creature ("<<crea_ptr1->species->name<<" "<<directName[crea_ptr1->direction]<<" "<<crea_ptr1->location.r<<" "<<crea_ptr1->location.c<<")!"<<endl;
        cout<<endl;
        exit(13);
        }
        else{
        world.grid.squares[crea_to_place->location.r][crea_to_place->location.c]=crea_to_place;
        }


}

void read_spe_summary(world_t &world, string species_summary_file){
//REQUIRES:
//EFFECTS:
    ifstream iFile(species_summary_file,ios::in);
    if (!iFile)
        throw ("species_summary_file");
    string dir_of_species; //the directory where the program files are stored
    getline(iFile, dir_of_species);
    string species_in_file[MAXSPECIES];
    unsigned int num_species=0;
    while (getline(iFile,species_in_file[num_species])){
        num_species++;
    }
    check_crea_name(world, species_in_file, num_species);
    world.numSpecies=num_species;
    check_num_species(num_species);
    //after the loop, num_species is the size of species, as well as the number of species
    iFile.close();
    iFile.clear();
    //now all the contents in SPECIES file are recorded.

    string instruction_temp;
    string instruction_line;
    string DIR;
    istringstream iStream;
    unsigned int address_temp;
    for (int i=0;(unsigned int)i<num_species;i++)
    {
        int inst_counter=0;
        DIR=dir_of_species+"/"+species_in_file[i];
        ifstream iFile2(DIR,ios::in);
        if (!iFile2)
            throw (DIR);
        world.species[i].name=species_in_file[i];
        address_temp=0;
        //the function with no address will be set as 0
        getline(iFile2,instruction_line);
        while (instruction_line.length()!=0)
        {
            iStream.str(instruction_line);
            iStream >> instruction_temp >> address_temp;
            op_helper(world.species[i].program[inst_counter], instruction_temp);
            //assign the op name

            world. species[i].program[inst_counter].address=address_temp;
            //assign the op value (enum)
            inst_counter++;
            iStream.clear();
            getline(iFile2,instruction_line);

        }
        iFile2.close();
        iFile2.clear();
        world.species[i].programSize=(unsigned int)inst_counter;
        check_inst_num(species_in_file[i],inst_counter);

        int j;
        for(j=0;(unsigned int)j<world.numCreatures;j++) {

            if (world.creatures[j].species->name == world.species[i].name) {
                *world.creatures[j].species=world.species[i];
                //enable the pointer
            }
        }

    }

}

void read_world(world_t &world, string world_file){
    ifstream iFile(world_file,ios::in);
    if (!iFile)
        throw (world_file);
    string height,width,line;

    getline(iFile,height);
    istringstream iStream;
    iStream.str(height);
    iStream>>world.grid.height;
    check_height(world.grid.height);
    iStream.clear();

    getline(iFile,width);
    iStream.str(width);
    iStream>>world.grid.width;
    check_width(world.grid.width);
    iStream.clear();


    int creature_counter=0;
    string direction_temp;
    while (getline(iFile,line)){
        *world.creatures[creature_counter].species=world.species[creature_counter];
        iStream.str(line);
        iStream>>world.creatures[creature_counter].species->name>>direction_temp>>world.creatures[creature_counter].location.r>>world.creatures[creature_counter].location.c;
        direction_helper(world.creatures[creature_counter].direction,direction_temp);
        check_in_boundary(world.creatures[creature_counter],world.grid.height,world.grid.width);
        creature_t* creature_pointer=&world.creatures[creature_counter];
        grid_pointer(world,creature_pointer);
        world.creatures[creature_counter].programID=1;


        creature_counter++;
        iStream.clear();
    }
    iFile.close();
    iFile.clear();
    check_crea_num(creature_counter);
    world.numCreatures=(unsigned int)creature_counter;
}

void read_file(int argc, char *argv[],world_t &my_world){
    int i;
    for(i=0;(unsigned int)i<MAXCREATURES;i++){
        my_world.creatures[i].species=new species_t;
    }
    try
    {
        init_squares(my_world);
        read_world(my_world, argv[2]);
        read_spe_summary(my_world, argv[1]);

    }
    catch (string& error_file)
    {
        cout<<"Error: Cannot open file "<<error_file<<"!"<<endl;
        cout<<endl;
        exit(3);
    }
}

void check_argnum(int argc, char *argv[]){
        if (argc<4)
        {
            cout << "Missing arguments!" << endl;
            cout<<"Usage: ./";
            for (int i=0;i<argc;i++)
            {
                cout<<argv[i];
            }
            cout<<flush;
            exit(1);
        }
}

void check_neg_rounds(char* argv[]){
    if (stoi(argv[3])<0)
        cout<<"Error: Number of simulation rounds is negative!"<<endl;
}

void check(int argc, char *argv[]){
    check_argnum(argc, argv);
    check_neg_rounds(argv);

}

//void game(){
//    species_t species[MAXSPECIES];
//    read_spe_summary(world);
//}

void print_state(world_t world){
    int i,j;
    for (i=0;(unsigned int)i<world.grid.height;i++){
        for(j=0;(unsigned int)j<world.grid.width;j++){
            if (world.grid.squares[i][j]== nullptr){
                cout<<"____ ";
            }
            else{
                cout<<world.grid.squares[i][j]->species->name[0]<<world.grid.squares[i][j]->species->name[1]<<"_"<<directName[world.grid.squares[i][j]->direction][0]<<" ";
        }
        }
        cout<<endl;
    }
}

point_t adjacentPoint(point_t pt, direction_t dir) {
    // EFFECTS: Returns a point that results from moving one square
// in the direction "dir" from the point "pt"
//does not handle the wall
    point_t point_next=pt;
    switch (dir){
        case NORTH:
            point_next.r--;
            break;
        case WEST:
            point_next.c--;
            break;
        case SOUTH:
            point_next.r++;
            break;
        case EAST:
            point_next.c++;
            break;
    }
    return point_next;
}

unsigned int next_ID(unsigned current_ID, int programsize){
    if (1<=current_ID&&current_ID<(unsigned int)programsize){
        return (current_ID+1);
    }
    else if(current_ID==(unsigned int)programsize){
        return 1;
    }
    else{
        cout<<"programID error!"<<endl;
        exit(-1);
    }
}

void simulate_creatures(creature_t &creature, grid_t &grid, const bool verbose){
    point_t point_next=adjacentPoint(creature.location,creature.direction);
    creature_t* crea_ptr=&creature;
    switch (creature.species->program[creature.programID-1].op){
        case HOP:
            if(verbose) {
                cout << "Instruction " << creature.programID << ": "
                     << opName[creature.species->program[creature.programID - 1].op] << endl;
            }
            else{
                cout<<opName[creature.species->program[creature.programID - 1].op]<<endl;
            }

            if(creature.direction==NORTH&&creature.location.r!=0&& grid.squares[point_next.r][point_next.c]== nullptr){
                grid.squares[creature.location.r][creature.location.c]= nullptr;

                grid.squares[creature.location.r-1][creature.location.c]=crea_ptr;
                creature.location.r--;
            }
            else if(creature.direction==SOUTH&&(unsigned int)creature.location.r!=grid.height-1&& grid.squares[point_next.r][point_next.c]== nullptr) {
                grid.squares[creature.location.r][creature.location.c] = nullptr;
                grid.squares[creature.location.r+1][creature.location.c] = crea_ptr;
                creature.location.r++;
            }
            else if(creature.direction==WEST&&creature.location.c!=0&& grid.squares[point_next.r][point_next.c]== nullptr) {
                grid.squares[creature.location.r][creature.location.c] = nullptr;
                grid.squares[creature.location.r][creature.location.c-1] = crea_ptr;
                creature.location.c--;
            }
            else if(creature.direction==EAST&&(unsigned int)creature.location.c!=grid.width-1&& grid.squares[point_next.r][point_next.c]== nullptr) {
                grid.squares[creature.location.r][creature.location.c] = nullptr;
                grid.squares[creature.location.r][creature.location.c+1] = crea_ptr;
                creature.location.c++;
            }

            creature.programID=next_ID(creature.programID,creature.species->programSize);
            break;

        case LEFT:
            if(verbose) {
                cout << "Instruction " << creature.programID << ": "
                     << opName[creature.species->program[creature.programID - 1].op] << endl;
            }
            else{
                cout<<opName[creature.species->program[creature.programID - 1].op]<<endl;
            }
            if (creature.direction==NORTH) {
                creature.direction = WEST;
                grid.squares[creature.location.r][creature.location.c]->direction = WEST;
            }
            else if(creature.direction==WEST){
                creature.direction=SOUTH;
                grid.squares[creature.location.r][creature.location.c]->direction = SOUTH;
            }
            else if(creature.direction==SOUTH) {
                creature.direction=EAST;
                grid.squares[creature.location.r][creature.location.c]->direction = EAST;
            }
            else if(creature.direction==EAST) {
                creature.direction=NORTH;
                grid.squares[creature.location.r][creature.location.c]->direction = NORTH;
            }
            creature.programID=next_ID(creature.programID,creature.species->programSize);
            break;

        case RIGHT:
            if(verbose) {
                cout << "Instruction " << creature.programID << ": "
                     << opName[creature.species->program[creature.programID - 1].op] << endl;
            }
            else{
                cout<<opName[creature.species->program[creature.programID - 1].op]<<endl;
            }
            if (creature.direction==NORTH) {
                creature.direction = EAST;
                grid.squares[creature.location.r][creature.location.c]->direction = EAST;
            }
            else if(creature.direction==WEST) {
                creature.direction = NORTH;
                grid.squares[creature.location.r][creature.location.c]->direction = NORTH;
            }
            else if(creature.direction==SOUTH) {
                creature.direction = WEST;
                grid.squares[creature.location.r][creature.location.c]->direction = WEST;
            }
            else if(creature.direction==EAST) {
                creature.direction = SOUTH;
                grid.squares[creature.location.r][creature.location.c]->direction = SOUTH;
            }
            creature.programID=next_ID(creature.programID,creature.species->programSize);
            break;

        case INFECT:
            if(verbose) {
                cout << "Instruction " << creature.programID << ": "
                     << opName[creature.species->program[creature.programID - 1].op] << endl;
            }
            else{
                cout<<opName[creature.species->program[creature.programID - 1].op]<<endl;
            }
            if(0<=point_next.r&&(unsigned int)point_next.r<=grid.height-1 && 0<=point_next.c&&(unsigned int)point_next.c<=grid.width-1 && grid.squares[point_next.r][point_next.c]!= nullptr && grid.squares[point_next.r][point_next.c]->species!=grid.squares[creature.location.r][creature.location.c]->species) {
                //the next position is within the wall, has some creature on it and is different, then infect
                grid.squares[point_next.r][point_next.c]->species=grid.squares[creature.location.r][creature.location.c]->species;
                grid.squares[point_next.r][point_next.c]->programID=1;

            }
            creature.programID=next_ID(creature.programID,creature.species->programSize);
            break;

        case IFEMPTY:
            if (verbose) {
                cout << "Instruction " << creature.programID << ": "
                     << opName[creature.species->program[creature.programID - 1].op] << " "
                     << creature.species->program[creature.programID - 1].address << endl;
            }

            if(0<=point_next.r&&(unsigned int)point_next.r<=grid.height-1 && 0<=point_next.c&&(unsigned int)point_next.c<=grid.width-1  && grid.squares[point_next.r][point_next.c]== nullptr){
                creature.programID=creature.species->program[creature.programID-1].address;
                simulate_creatures(creature, grid,verbose);
            }
            else {
                creature.programID=next_ID(creature.programID,creature.species->programSize);
                simulate_creatures(creature, grid,verbose);
            }
            break;

        case IFWALL:
            if (verbose) {
                cout << "Instruction " << creature.programID << ": "
                     << opName[creature.species->program[creature.programID - 1].op] << " "
                     << creature.species->program[creature.programID - 1].address << endl;
            }

            if (0>point_next.r || (unsigned int)point_next.r> grid.height-1 || 0>point_next.c || (unsigned int)point_next.c>grid.width-1){
                creature.programID=creature.species->program[creature.programID-1].address;
                simulate_creatures(creature, grid,verbose);
            }
            else {
                creature.programID=next_ID(creature.programID,creature.species->programSize);
                simulate_creatures(creature, grid,verbose);
            }
            break;

        case IFSAME:
            if (verbose){
                cout<<"Instruction "<<creature.programID<<": "
                    <<opName[creature.species->program[creature.programID-1].op]<<" "
                    <<creature.species->program[creature.programID-1].address<<endl;
            }

            if (0<=point_next.r&&(unsigned int)point_next.r<=grid.height-1 && 0<=point_next.c&&(unsigned int)point_next.c<=grid.width-1 && grid.squares[point_next.r][point_next.c]!= nullptr && grid.squares[point_next.r][point_next.c]->species==grid.squares[creature.location.r][creature.location.c]->species){
                creature.programID=creature.species->program[creature.programID-1].address;
                simulate_creatures(creature, grid,verbose);
            }
            else {
                creature.programID=next_ID(creature.programID,creature.species->programSize);
                simulate_creatures(creature, grid,verbose);
            }
            break;

        case IFENEMY:
            if (verbose){
                cout<<"Instruction "<<creature.programID<<": "
                    <<opName[creature.species->program[creature.programID-1].op]<<" "
                    <<creature.species->program[creature.programID-1].address<<endl;
            }
            if(0<=point_next.r&&(unsigned int)point_next.r<=grid.height-1 && 0<=point_next.c&&(unsigned int)point_next.c<=grid.width-1 && grid.squares[point_next.r][point_next.c]!= nullptr && grid.squares[point_next.r][point_next.c]->species!=grid.squares[creature.location.r][creature.location.c]->species){
                creature.programID=creature.species->program[creature.programID-1].address;
                simulate_creatures(creature, grid,verbose);
            }
            else {
                creature.programID=next_ID(creature.programID,creature.species->programSize);
                simulate_creatures(creature, grid,verbose);
            }
            break;

        case GO:
            if (verbose){
                cout<<"Instruction "<<creature.programID<<": "
                    <<opName[creature.species->program[creature.programID-1].op]<<" "
                    <<creature.species->program[creature.programID-1].address<<endl;
            }
            creature.programID=creature.species->program[creature.programID-1].address;
            simulate_creatures(creature, grid,verbose);
            break;

        default:
            break;
    }

}

void play(world_t world, int argc, char*argv[]){
    string verbose1="verbose";string verbose2="v";
    int round;int crea_index;
    cout<<"Initial state"<<endl;
    print_state(world);
    if(stoi(argv[3])>=1) {
        bool verbose=(argc>=5 && (argv[4] == verbose1 || argv[4] == verbose2));
        for (round = 1;round<=stoi(argv[3]);round++) {
            cout<<"Round "<<round<<endl;
            for (crea_index=0;(unsigned int)crea_index<world.numCreatures;crea_index++){
                world.creatures[crea_index]=*world.grid.squares[world.creatures[crea_index].location.r][world.creatures[crea_index].location.c];
                cout<<"Creature ("<<world.creatures[crea_index].species->name<<" "
                    <<directName[world.creatures[crea_index].direction]<<" "<<world.creatures[crea_index].location.r<<" "
                    <<world.creatures[crea_index].location.c<<") takes action: ";
                if (verbose)
                    cout<<endl;

                //cout<<"Instruction "<<world.creatures[crea_index].programID<<": "<<opName[world.creatures[crea_index].species->program[world.creatures[crea_index].programID].op]<<" "<<world.creatures[crea_index].species->program[world.creatures[crea_index].programID].address<<endl;
                //cout<<world.creatures[crea_index].species->name;
                simulate_creatures(world.creatures[crea_index],world.grid,verbose);

                cout.clear();
                if(verbose){
                    print_state(world);
                }
            }
            if (!verbose){
                print_state(world);
            }
        }

    }
}