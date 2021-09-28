//
// Created by Administrator on 2019/12/3.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "dlist.h"

using namespace std;

void command(const string &s, Dlist<int>& calculator){
//EFFECTS:distinguish the operator and complete the operations
    int* a,* b;
    if(s=="+"||s=="-"||s=="*"||s=="/"||s=="r"){
        if (!calculator.isEmpty()){
            a=calculator.removeFront();
            if(!calculator.isEmpty()){//has enough operants
                b=calculator.removeFront();
            }
            else{//has just one element
                cout << "Not enough operands\n";
                calculator.insertFront(a);
                return;
            }
        }
        else{//empty list
            cout << "Not enough operands\n";
            return;
        }
        //till now, two operatants a and b are poped out
        if (s=="+"){
            int * temp_ptr= new int;
            *temp_ptr=*a+*b;
            calculator.insertFront(temp_ptr);
            delete a;
            delete b;
        }
        else if (s=="-"){
            int * temp_ptr= new int;
            *temp_ptr=*b-*a;
            calculator.insertFront(temp_ptr);
            delete a;
            delete b;
        }
        else if(s=="*"){
            int * temp_ptr= new int;
            *temp_ptr=(*a)*(*b);
            calculator.insertFront(temp_ptr);
            delete a;
            delete b;
        }
        else if(s=="/"&& *a!=0){
            int * temp_ptr= new int;
            *temp_ptr=(*b)/(*a);
            calculator.insertFront((temp_ptr));
            delete a;
            delete b;
        }
        else if(s=="r"){
            calculator.insertFront(a);
            calculator.insertFront(b);
        }
        else{
            cout << "Divide by zero\n";
            calculator.insertFront(a);
            calculator.insertFront(b);

            return;
        }

    }
    else if (s=="n"||s=="d"||s=="p"){
        if (calculator.isEmpty()){//empty list
            cout << "Not enough operands\n";
            return;
        }
        else {

            a=calculator.removeFront();
            if (s=="n"){
                int * temp_ptr= new int;
                *temp_ptr=(*a)*(-1);
                calculator.insertFront(temp_ptr);
                delete a;
            }
            else if(s=="d"){
                int * a_ =new int(*a);
                calculator.insertFront(a);
                calculator.insertFront(a_);
            }
            else{//p
                cout<<*a<<"\n";
                calculator.insertFront(a);
            }

        }

    }
    else if(s=="c"){
        while (!calculator.isEmpty()){
            int* temp=calculator.removeFront();
            delete temp;
        }
    }
    else if(s=="a"){
        Dlist<int> calculator_temp(calculator);
        while(!calculator_temp.isEmpty()){
            a=calculator_temp.removeFront();
            cout<<*a<<" ";
            delete a;
        }
        cout<<endl;
    }
//    else if(s=="q"){
//        exit(0);
//    }
    else {
        cout << "Bad input\n";
        return;
    }
}

void play(){
    Dlist<int> calculator;
    int num,temp_num;
    string s;

    while (cin >> s) {
        temp_num=strtol(s.c_str(), nullptr, 10); //try to convert s into long
        if (to_string(temp_num)==s ||"0"+to_string(temp_num)==s || "-0"+to_string(-temp_num)==s || "-"+to_string(temp_num)==s){ //normal numbers, positive and negative number start with 0, and -0
            num = temp_num;
            int* ip=new int(num);
            calculator.insertFront(ip);
        }
        else if(s=="q"){
            break;
        }
        else {
            command(s, calculator);
        }
        cin.clear();
    }
}
int main() {
    play();
    return 0;


}