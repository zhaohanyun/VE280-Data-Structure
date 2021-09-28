//
// Created by Administrator on 2019/11/10.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "card.h"
#include "hand.h"

using namespace std;


Hand::Hand(){
    // EFFECTS: establishes an empty blackjack hand.
    curValue.count=0;
    curValue.soft=false;

}

void Hand::discardAll() {
    // MODIFIES: this
    // EFFECTS: discards any cards presently held, restoring the state
    // of the hand to that of an empty blackjack hand.
    curValue.count=0;
    curValue.soft=false;

}

int spot_helper(Card c){
    if (c.spot>=0&&c.spot<=8){
        //digital card
        return c.spot+2;
    }
    else{
        return 10;
    }
}
void Hand::addCard(Card c){
    // MODIFIES: this
    // EFFECTS: adds the card "c" to those presently held.
    if (c.spot!=ACE){
        curValue.count+=spot_helper(c);
        if(curValue.soft && curValue.count>10){
            //waste the ACE, including changing the soft state and let the origin double edged sward becomes a regular "ONE"
            curValue.soft=false;
            curValue.count++;
        }
    }
    else{
        if (!curValue.soft && handValue().count<=10) {
            //if this is the first ACE, then chnage the state to soft and DO NOT change the cruvalue
            curValue.soft = true;
        }
        else{
            //if one is so lucky to draw a second ACE, then it is bounded to be counted as 1
            curValue.count+=1;
        }
    }
}

HandValue Hand::handValue() const {
    // EFFECTS: returns the present value of the blackjack hand.  The
    // count field is the highest blackjack total possible without
    // going over 21.  The soft field should be true if and only if at
    // least one ACE is present, and its value is counted as 11 rather
    // than 1.  If the hand is over 21, any value over 21 may be returned.
    //
    Hand Hand_temp=*this;
    if (this->curValue.soft) {
        //one have at least one ACE
//        if (Hand_temp.curValue.count > 10){
//            Hand_temp.curValue.count + 1;
//            this->curValue.soft=false;
//        }
        Hand_temp.curValue.count =
                Hand_temp.curValue.count > 10 ? Hand_temp.curValue.count + 1 : Hand_temp.curValue.count + 11;
        //cout<<Hand_temp.curValue.count<<endl;

        return Hand_temp.curValue;

    }
    else{
        return this->curValue;
    }
}


//  if (this->curValue.soft){
//one have at least one ACE
//return this->curValue.count>21?this->curValue.count+1:this->curValue.count+11;