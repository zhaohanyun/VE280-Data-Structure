#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;

static bool list_equal(list_t l1, list_t l2)
    // EFFECTS: returns true iff l1 == l2.
{
    if(list_isEmpty(l1) && list_isEmpty(l2))
    {
        return true;
    }
    else if(list_isEmpty(l1) || list_isEmpty(l2))
    {
        return false;
    }
    else if(list_first(l1) != list_first(l2))
    {
        return false;
    }
    else
    {
        return list_equal(list_rest(l1), list_rest(l2));
    }    
}    

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

    list_print(insert_list(listA,listB,1441));
    cout << endl;

    chop(listA,3);
    list_print(listA);
    cout << endl;

    if(list_equal(listA, listA_answer) 
        && list_equal(listB, listB_answer))
    {
        cout << "Success!\n";
        return 0;
    }
    else
    {
        cout << "Failed\n";
        return -1;
    }
}
