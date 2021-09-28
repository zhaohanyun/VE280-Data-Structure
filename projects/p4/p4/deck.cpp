//
// Created by Administrator on 2019/11/10.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "card.h"
#include "deck.h"

using namespace std;

Deck::Deck(){
    // EFFECTS: constructs a "newly opened" deck of cards:  first the
    // spades from 2-A, then the hearts, then the clubs, then the
    // diamonds.  The first card dealt should be the 2 of Spades.
    next=0;
    for (int i=0;i<4;i++){
        for (int j=0;j<13;j++){
            deck[i*13+j].spot=(enum Spot)j;
            deck[i*13+j].suit=(enum Suit)i;
        }
    }
}

void Deck::reset(){
    // EFFECTS: resets the deck to the state of a "newly opened" deck
    // of cards:
    next=0;
    for (int i=0;i<4;i++){
        for (int j=0;j<13;j++){
            deck[i*13+j].spot=(enum Spot)j;
            deck[i*13+j].suit=(enum Suit)i;
        }
    }
}

void Deck::shuffle(int n) {
    // REQUIRES: "n" is between 0 and 52, inclusive.
    // MODIFIES: this
    Deck Deck_pre = *this;
    for (int i = 0; i < n && i < 52 - n; i++) {
        this->deck[2 * i] = Deck_pre.deck[n + i];
        this->deck[2 * i + 1] = Deck_pre.deck[i];
    }
    //So far, at least one pile has been used up
    int j = abs(52 - 2 * n);
    while (j > 0) {
        if (n <= 26) {
            this->deck[52 - j] = Deck_pre.deck[52 - j];
        } else {
            this->deck[52 - j] = Deck_pre.deck[n - j];
        }
        j--;
    }
    this->next = 0;

}

Card Deck::deal() {
    // MODIFIES: this

    // EFFECTS: deals the "next" card and returns that card. If no cards
    // remain, throws an instance of DeckEmpty.
    next++;
    return deck[next-1];
}

int Deck::cardsLeft() {
    // EFFECTS: returns the number of cards in the deck that have not
    // been dealt since the last reset/shuffle.
    return 52-next;
}