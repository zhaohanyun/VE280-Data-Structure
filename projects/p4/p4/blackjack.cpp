#include <iostream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "hand.h"
#include"player.h"
#include "deck.h"
#include "rand.h"

using namespace std;

void play(Player*, int bankroll,int hand);

void play(Player* player,int bankroll, const int hand){
    Deck deck=Deck();
    const int minimum=5;
    int thishand=0;
    int cut;
    Hand player_hand=Hand();
    Hand dealer_hand=Hand();
    Card card_temp{}, dealer_card{}, hole_card{};
    //bool winner=false;
    cout << "Shuffling the deck\n";
    for (int i=0;i<7;i++){
        cut=get_cut();
        deck.shuffle(cut);

        cout << "cut at " << cut << endl;
    }

    while (bankroll>=minimum && thishand<hand){
        thishand++;
        cout << "Hand " << thishand << " bankroll " << bankroll << endl;
        if (deck.cardsLeft()<20){
            cout << "Shuffling the deck\n";
            for (int i=0;i<7;i++){
                cut=get_cut();
                deck.shuffle(cut);

                cout << "cut at " << cut << endl;
            }
            player->shuffled();
        }
        int wager=player->bet((unsigned int)bankroll,minimum);

        cout << "Player bets " << wager << endl;

        //draw the card at the beginning of a hand
        card_temp=deck.deal();
        player_hand.addCard(card_temp);
        cout<<"Player dealt "<<SpotNames[card_temp.spot]<<" of "<<SuitNames[card_temp.suit]<<endl; //what is suitname?
        player->expose(card_temp);

        dealer_card=deck.deal();
        dealer_hand.addCard(dealer_card);
        cout<<"Dealer dealt "<<SpotNames[dealer_card.spot]<<" of "<<SuitNames[dealer_card.suit]<<endl;
        player->expose(dealer_card);


        card_temp=deck.deal();
        player_hand.addCard(card_temp);
        cout<<"Player dealt "<<SpotNames[card_temp.spot]<<" of "<<SuitNames[card_temp.suit]<<endl;
        player->expose(card_temp);

        hole_card=deck.deal();
        dealer_hand.addCard(hole_card);


        if (player_hand.handValue().count==21){
            bankroll+=(wager*3-(wager*3)%2)/2;
            cout<< "Player dealt natural 21\n";
        }
        else{
            while(player->draw(dealer_card,player_hand)){
                card_temp=deck.deal();
                player_hand.addCard(card_temp);
                cout<<"Player dealt "<<SpotNames[card_temp.spot]<<" of "<<SuitNames[card_temp.suit]<<endl;
                player->expose(card_temp);
            }
            cout << "Player's total is " << player_hand.handValue().count<< endl;
            if (player_hand.handValue().count>21){
                cout << "Player busts\n";
                bankroll-=wager;
            }
            else{
                cout<<"Dealer's hole card is "<<SpotNames[hole_card.spot]<<" of "<<SuitNames[hole_card.suit]<<endl;
                player->expose(hole_card);
                while (dealer_hand.handValue().count<17){
                    card_temp=deck.deal();
                    dealer_hand.addCard(card_temp);
                    cout<<"Dealer dealt "<<SpotNames[card_temp.spot]<<" of "<<SuitNames[card_temp.suit]<<endl;
                    player->expose(card_temp);
                }
                cout << "Dealer's total is " << dealer_hand.handValue().count << endl;
                if (dealer_hand.handValue().count >21){
                    cout << "Dealer busts\n";
                    bankroll+=wager;
                }
                else {
                    if(player_hand.handValue().count > dealer_hand.handValue().count){
                        cout << "Player wins\n";
                        bankroll+=wager;
                    }
                    else if(player_hand.handValue().count < dealer_hand.handValue().count){
                        cout << "Dealer wins\n";
                        bankroll-=wager;
                    }
                    else{
                        cout << "Push\n";
                    }
                }
            }
        }
        player_hand.discardAll();
        dealer_hand.discardAll();

    }
    cout << "Player has " << bankroll << " after " << thishand << " hands\n";
}

int main(int argc, char* argv[]) {
    int bankroll=strtol(argv[1], nullptr,10);
    int hand = strtol(argv[2], nullptr,10);
    string A=argv[3];
    Player *player;
    if (A=="simple"){
       player=get_Simple();
    }
    else if (A=="counting"){
        player=get_Counting();
    }
    else{
        cout<<"error!"<<endl;
        exit(0);
    }
    play(player,bankroll, hand);
}

