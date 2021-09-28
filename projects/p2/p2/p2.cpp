//
// Created by Administrator on 2019/10/4.
//
#include <iostream>
#include <cstdlib>
#include "p2.h"
#include "recursive.h"
static int add(int a, int b)
{
    return  a+b;
}

static int product(int a , int b)
{
    return a*b;
}

int size(list_t list)
/*
// EFFECTS: Returns the number of elements in "list".
//          Returns zero if "list" is empty.
*/

{
    if (!list_isEmpty(list))
        return 1+size(list_rest(list));
    else
        return 0;
}

int sum(list_t list)
/*
// EFFECTS: Returns the sum of each element in "list".
//          Returns zero if "list" is empty.
*/
{
    return accumulate(list,add,0);
}

int product(list_t list)
/*
// EFFECTS: Returns the product of each element in "list".
//          Returns one if "list" is empty.
*/
{
    return accumulate(list,product,1);
}

int accumulate(list_t list, int (*fn)(int, int), int base)
/*
// REQUIRES: "fn" must be associative.
//
// EFFECTS: Returns "base" if "list" is empty.
//          Returns fn(list_first(list),
//                      accumulate(list_rest(list), fn, base) otherwise.
*/
{
    if(!list_isEmpty(list))
    {
        return fn(list_first(list), accumulate(list_rest(list), fn, base));
    }
    else
        return base;
}

static list_t reverse_helper(list_t list, list_t list_new)
/*
 //EFFECTS: receive two lists, one is we are about to reverse, one is empty.
 //Take out the element from the target list one by one and put them into the very beginning of the empty list.
 */
{
    if (!list_isEmpty(list))
    {
        list_new=list_make(list_first(list),list_new);
        return reverse_helper(list_rest(list),list_new);
    }
    else
    {
        return list_new;
    }
}
list_t reverse(list_t list)
/*
// EFFECTS: Returns the reverse of "list".
*/

{
    return reverse_helper(list,list_make());
}


list_t append(list_t first, list_t second)
/*
// EFFECTS: Returns the list (first second).
*/
{
    if (!list_isEmpty(first))
        return list_make(list_first(first),append(list_rest(first),second));
    else
        return second;
}

list_t filter_odd(list_t list)
/*
// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are odd in value,
//          in the order in which they appeared in list.
*/
{
    if (!list_isEmpty(list))
    {
        if (list_first(list)%2==1)
            return list_make(list_first(list),filter_odd(list_rest(list)));
        else
            return filter_odd(list_rest(list));
    }
    else
    {
        return list_make();
    }
}


list_t filter_even(list_t list)
/*
// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are even in value,
//          in the order in which they appeared in list.
*/

{
    if (!list_isEmpty(list))
    {
        if (list_first(list)%2==0)
            return list_make(list_first(list),filter_even(list_rest(list)));
        else
            return filter_even(list_rest(list));
    }
    else
    {
        return list_make();
    }
}

list_t filter(list_t list, bool (*fn)(int))
/*
// EFFECTS: Returns a list containing precisely the elements of "list"
//          for which the predicate fn() evaluates to true, in the
//          order in which they appeared in list.
*/
{
    if (!list_isEmpty(list))
    {
        if (fn(list_first(list)))
        {
            return list_make(list_first(list), filter(list_rest(list), fn));
        }
        else
        {
            return filter(list_rest(list), fn);
        }
    }
    else
    {
        return list_make();
    }
}

static list_t chop_helper1(list_t list, unsigned int n) //the original n is the new size of the chopped list
//EFFECTS: return the part before the node (used in both insert and chop)
{
    if (n>0)
        return list_make(list_first(list),chop_helper1(list_rest(list),n-1));
    else
        return list_make();
}

static list_t chop_helper2(list_t list,unsigned int n) //the original n is the new size of the chopped list
//EFFECTS: return the part after the node (used in insert)
{
    if (n>0)
        return chop_helper2(list_rest(list),n-1);
    else
        return list;
}

list_t insert_list(list_t first, list_t second, unsigned int n)
/*
// REQUIRES: n <= the number of elements in "first".
//
// EFFECTS: Returns a list comprising the first n elements of
//          "first", followed by all elements of "second",
//           followed by any remaining elements of "first".
*/
{
   return append(append(chop_helper1(first,n),second),chop_helper2(first,n));
}


list_t chop(list_t list, unsigned int n)
{
    return chop_helper1(list,size(list)-n);
}


//tree
//
//


int tree_sum(tree_t tree)
/*
// EFFECTS: Returns the sum of all elements in "tree".
//          Returns zero if "tree" is empty.
*/
{
    if (!tree_isEmpty(tree))
        return tree_sum(tree_left(tree))+tree_sum(tree_right(tree))+tree_elt(tree);
    else
        return 0;
}



bool tree_search(tree_t tree, int key)
/*
// EFFECTS: Returns true if there exists any element in "tree"
//          whose value is "key". Otherwise, return "false".
*/
{
    if(!tree_isEmpty(tree)) //check the element at the top of the input tree
    {
        if (tree_elt(tree)!=key)
        {
            return tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key);
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false; //find the exact element
    }
}

int depth(tree_t tree)
/*
// EFFECTS: Returns the depth of "tree", which equals the number of
//          layers of nodes in the tree.
//          Returns zero is "tree" is empty.
*/
{
    if(!tree_isEmpty(tree_left(tree))&&!tree_isEmpty(tree_right(tree))) //both of the children are not empty
    {
        return (depth(tree_left(tree)) > depth(tree_right(tree)) ? (depth(tree_left(tree)) + 1) : (
                depth(tree_right(tree)) + 1));
    }
    else if (!tree_isEmpty(tree_left(tree))||!tree_isEmpty(tree_right(tree))) //either of the children is not empty
    {
        return (tree_isEmpty(tree_left(tree))?(depth(tree_right(tree))+1):(depth(tree_left(tree))+1));
    }
    else // reach the leaf of the tree
    {
        return 1; //it's the "ground floor" of the subtree
    }
}

int tree_min(tree_t tree)
/*
// REQUIRES: "tree" is non-empty.
// EFFECTS: Returns the smallest element in "tree".
*/
{
    int min_helper;
    if(!tree_isEmpty(tree_left(tree))&&!tree_isEmpty(tree_right(tree))) //both of the children are not empty
    {
        min_helper = (tree_min(tree_left(tree)) > tree_min(tree_right(tree)) ? tree_min(tree_right(tree)) : tree_min(
                tree_left(tree))); //compare the min of left and right tree
        return (min_helper > tree_elt(tree) ? tree_elt(tree)
                                            : min_helper); //compare the min of the children's and the elt
    }
    else if (!tree_isEmpty(tree_left(tree))||!tree_isEmpty(tree_right(tree))) //either of the children is not empty
    {
        if(tree_isEmpty(tree_left(tree)) )
        {
            return (tree_min(tree_right(tree))<tree_elt(tree)? tree_min(tree_right(tree)):tree_elt(tree));
        }
        else
        {
            return (tree_min(tree_left(tree))<tree_elt(tree)? tree_min(tree_left(tree)):tree_elt(tree));
        }
    }
    else //reach the leaf of the tree
    {
        return tree_elt(tree);
    }
}

list_t traversal(tree_t tree)
{
    if(!tree_isEmpty(tree))
        return append(traversal(tree_left(tree)),list_make(tree_elt(tree),traversal(tree_right(tree))));
    else
        return list_make();
}

bool tree_hasPathSum(tree_t tree, int sum)
{
    if(!tree_isEmpty(tree))
    {
        if (sum > tree_elt(tree)&&(!tree_isEmpty(tree_left(tree))||!tree_isEmpty(tree_right(tree))))
        {
            return !(!tree_hasPathSum(tree_left(tree), sum - tree_elt(tree)) &&
                     !tree_hasPathSum(tree_right(tree), sum - tree_elt(tree)));
        }
        else
        {
            return sum == tree_elt(tree) && tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree));
        }
    }
    else
    {
        return false;
    }
}


bool covered_by(tree_t A, tree_t B)
/*
// EFFECTS: Returns true if tree A is covered by tree B.
*/
{
    if(tree_isEmpty(A))
    {
        return true;
    }
    else
    {
        if (tree_elt(A)!= tree_elt(B))
        {
            return false;
        }
        else
        {
            return covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B));
        }
    }
}

bool contained_by(tree_t A, tree_t B)
/*
// EFFECTS: Returns true if tree A is covered by tree B
//          or a subtree of B.
*/

{
    return (!covered_by(A, B) || !covered_by(A, tree_left(B)) || !covered_by(A, tree_right(B)));
}

tree_t insert_tree(int elt, tree_t tree)
/*
// REQUIRES: "tree" is a sorted binary tree.
//
// EFFECTS: Returns a new tree with elt inserted at a leaf such that
//          the resulting tree is also a sorted binary tree.
*/
{
    if(!tree_isEmpty(tree))
        return (elt<tree_elt(tree))?tree_make(tree_elt(tree),insert_tree(elt,tree_left(tree)),tree_right(tree)):tree_make(tree_elt(tree),tree_left(tree),insert_tree(elt,tree_right(tree)));
    else
        return tree_make(elt,tree_make(),tree_make());
}