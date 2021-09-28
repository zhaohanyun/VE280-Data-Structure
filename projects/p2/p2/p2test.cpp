//
// Created by Administrator on 2019/10/11.
//
#include <iostream>
#include "recursive.h"
#include "p2.h"
#include <stdlib.h>
using namespace std;
int main()
{
    list_t listA=list_make(),listB=list_make();
    int i;
    for (i=1;i<=10;i++)
    {
        listA=list_make(i,listA);
    }
    list_print(listA);
    cout << endl;

    for(i=5;i>=1;i--)
    {
        listB=list_make(i,listB);
    }
    list_print(listB);
    cout << endl;

    list_print(insert_list(listA,listB,4));
    cout << endl;


    list_print( chop(listA,3));
    cout << endl;

  //  list_print(filter_odd(listA));
    list_print(filter_even(listA));
    cout << endl;
//
//    tree_t left_temp=tree_make(),right_temp=tree_make();
//    int i,n;
//    tree_t big_tree=tree_make(12,left_temp,right_temp);
//    //tree_print(big_tree);
//    for (i=1;i<=10;i++)
//    {
//        if (rand()%2==1)
//        {
//            big_tree=insert_tree(i,big_tree);
//        }
//        else
//            big_tree=insert_tree(i,big_tree);
//    }
//    tree_print(big_tree);
//
////    cout<<depth(big_tree)<<endl;
//
//tree_t small_tree=tree_make();
//    small_tree=insert_tree(1,small_tree);
//for (i=2;i<=7;i++)
//{
//    small_tree=insert_tree(i,small_tree);
//}
//tree_print(small_tree);
////if(contained_by(small_tree,big_tree))
//if(tree_search(big_tree,7))
//{
//    cout<<"yes"<<endl;
//}
//else
//{
//    cout<<"no"<<endl;
//}
//cout<<tree_min(big_tree);
    return 0;
}