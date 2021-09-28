//
// Created by Administrator on 2019/11/10.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "hand.h"
#include"player.h"

using namespace std;

class Simple_Player: public Player{
private:
    int count=0;

public:

//    explicit Simple_Player(int n){
//        bankroll=n;
//    }

    Simple_Player();;

    int bet(unsigned int bankroll, unsigned int minimum) override;

    bool draw(Card dealer,const Hand &player) override;

    void expose(Card c) override {};

    void shuffled() override;


    int get_count(){
        return count;
    }


    void set_count(int n){
        count=n;
    }
};


class Counting_Player : public Simple_Player{

public:

    void expose(Card c) override;

    void shuffled() override;

    int bet(unsigned int bankroll, unsigned int minimum) override;
//    void count();

};
int Simple_Player::bet(unsigned int bankroll, unsigned int minimum) {
    if (bankroll>=minimum) {
        return minimum;
    }
    else
        exit(1);
}

int Counting_Player::bet(unsigned int bankroll, unsigned int minimum) {
    // REQUIRES: bankroll >= minimum
    // EFFECTS: returns the player's bet, between minimum and bankroll
    // inclusive
    if (bankroll>=minimum){
        if (get_count()>=2 && bankroll>=2*minimum){
            return 2*minimum;
        }
        else {
            return minimum;
        }
    }
    else{
        exit(1);
    }
}

bool Simple_Player::draw(Card dealer, const Hand &player) {
    // EFFECTS: returns true if the player wishes to be dealt another
    // card, false otherwise.
    if  (!player.handValue().soft){
        if (player.handValue().count<=11){
            return true;
        }
        else if(player.handValue().count==12){
            return !(dealer.spot == 2 || dealer.spot == 3 || dealer.spot == 4);
        }
        else if (player.handValue().count>=13 && player.handValue().count<=16) {
            return !(dealer.spot >= 0 && dealer.spot <= 4);
        }
        else {
            return false;
        }
    }
    else{
        if (player.handValue().count<=17){
            return true;
        }
        else if (player.handValue().count==18){
            return !(dealer.spot==0||dealer.spot==5||dealer.spot==6);
        }
        else {
            return false;
        }
    }
}

Simple_Player::Simple_Player() = default;

void Simple_Player::shuffled() {}

//void Simple_Player::expose(Card c){}

void Counting_Player::expose(Card c){
    // EFFECTS: allows the player to "see" the newly-exposed card c.
    if (c.spot<=4){
        //2-6
        set_count(get_count()+1);
    }
    else if (c.spot>=8){
        //face card, 10 and ACE
        set_count(get_count()-1);
    }
}

void Counting_Player::shuffled() {
// EFFECTS: tells the player that the deck has been re-shuffled.
    set_count(0);
}


extern Player * get_Simple(){
    static Simple_Player s_p;
// EFFECTS: returns a pointer to a "simple player", as defined by the
// project specification
    return &s_p;
}


extern Player * get_Counting(){
// EFFECTS: returns a pointer to a "counting player", as defined by
// the project specification.
    static Counting_Player c_p;
    return &c_p;
}