//
// Created by Administrator on 2019/12/6.
//
#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "dlist.h"

using namespace std;

enum STATUS{
    PLATINUM=0,GOLD,SILVER,REGULAR
};

const string status_name[]={"platinum","gold","silver","regular"};

typedef struct PASSENGER {
    int timestamp{};//the time the call come in
    string name;
    STATUS status;
    int duration{};
    //int order{};//show the order in the input file if multiple calls appears at the same tick
} passenger;


void callfrom(Dlist<passenger>& p_1status,Dlist<passenger> &Agent){//passenger of one particular status
    //EFFECT: remove the passengers from a particular status and add to the queue of the agent
    passenger* pass_call1,*pass_call2,*pass_prio;Dlist<passenger> Agent_temp;
    while (!p_1status.isEmpty()) {
        pass_call1 = p_1status.removeFront();
        while(!Agent.isEmpty()) {
            pass_call2 = Agent.removeFront();//if 1 and 2 are of same status, 2 comes earlier than 1
            pass_prio=pass_call1->status<pass_call2->status?pass_call1:pass_call2;

            pass_call1=pass_call1->status>=pass_call2->status?pass_call1:pass_call2;//less prior one
            Agent_temp.insertBack(pass_prio);
        }
        Agent_temp.insertBack(pass_call1);
        Agent=Agent_temp;
    }

}

void answer(Dlist<passenger>& Agent){
    //EFFECT: make the agent to answer to the passengers
    passenger* pass_now;
    if (!Agent.isEmpty()){
        pass_now=Agent.removeFront();
        if (pass_now->duration>0){//begin a new passenger
            cout<<"Answering call from "<<pass_now->name<<endl;
            pass_now->duration--;
            pass_now->duration*=(-1);//negeative number shows this passenger is already in progress
           // Agent.insertFront(pass_now);
        }
        else{//<0
            pass_now->duration++;
           // Agent.insertFront(pass_now);
        }
        if (pass_now->duration==0){
            delete pass_now;
        }
        else{
            Agent.insertFront(pass_now);
        }

    }
}

void play(){
    Dlist<passenger> call;//record the order in the input file if multiple calls appears at the same tick
    Dlist<passenger> Agent;
    Dlist<passenger> platinum;
    Dlist<passenger> gold;
    Dlist<passenger> silver;
    Dlist<passenger> regular;
     int event=0;int i;int tick=0;string temp_status;
     int agent=0;//show how many ticks of work there are to do
    cin>>event;
    if (event ==0){
        cout<<"Starting tick 0"<<endl;
    }
    else {
        for (i = 0; i < event; i++) {
            auto *temp_pass = new passenger;
            cin >> temp_pass->timestamp >> temp_pass->name >> temp_status >> temp_pass->duration;
            if (temp_status == "platinum") {
                temp_pass->status = PLATINUM;
                //platinum.insertBack(temp_pass);
            } else if (temp_status == "silver") {
                temp_pass->status = SILVER;
                //silver.insertBack(temp_pass);
            } else if (temp_status == "gold") {
                temp_pass->status = GOLD;
                //gold.insertBack(temp_pass);
            } else {//(temp_status=="regular")
                temp_pass->status = REGULAR;
                //regular.insertBack(temp_pass);
            }
            call.insertBack(temp_pass);
        }
        while (!call.isEmpty() || agent != 0) {
            cout << "Starting tick #" << tick << endl;
            if (agent > 0) agent--;
            passenger *pass_call;
            if (!call.isEmpty()) {
                pass_call = call.removeFront();
                while (pass_call->timestamp == tick) {//input the call at this tick into their own status queue
                    cout << "Call from " << pass_call->name << " a " << status_name[pass_call->status] << " member"
                         << endl;
                    if (pass_call->status == 0) {
                        platinum.insertBack(pass_call);
                    } else if (pass_call->status == 1) {
                        gold.insertBack(pass_call);
                    } else if (pass_call->status == 2) {
                        silver.insertBack(pass_call);
                    } else { //(pass_call->status==3
                        regular.insertBack(pass_call);
                    }
                    agent += pass_call->duration;
                    pass_call = nullptr;
                    if (!call.isEmpty()) {
                        pass_call = call.removeFront();
                    } else {
                        break;
                    }
                }
                if (pass_call) {
                    call.insertFront(
                            pass_call);//insert the last element that is examined, which is bounded not to be the tick's call
                }
            }
            if (!platinum.isEmpty()) callfrom(platinum, Agent);
            if (!gold.isEmpty()) callfrom(gold, Agent);
            if (!silver.isEmpty())callfrom(silver, Agent);
            if (!regular.isEmpty())callfrom(regular, Agent);
            answer(Agent);
            tick++;
        }
    }
}


int main(){
 play();
}