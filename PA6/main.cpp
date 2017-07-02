#include <iostream>
#include <fstream>
#include <stdlib.h> // NULL
#include <stdio.h>  // srand, rand
#include <time.h>   // time for random numbers
#include "classes.cpp"

using namespace std;

int main()
{
    BST my_tree1, my_tree2;
    int user_input, user_input2, random;
    int tree1_size = 0;
    int tree2_size = 0;
    int index;

    srand(time(NULL));

    while(true)
    {
        random = rand() % 200 + 1;
        if(!my_tree1.contains(random))
        {
            my_tree1.add(random);
            tree1_size++;
        }
        if(tree1_size == 10)
        {
            break;
        }
    }

    while(true)
    {
        random = rand() % 200 + 1;
        if(!my_tree2.contains(random) && my_tree1.contains(random))
        {
            my_tree2.add(random);
            tree2_size++;
        }
        if(tree2_size == 3)
        {
            break;
        }
    }

    // print data to terminal
    cout << "Height of tree 1: " << my_tree1.get_height() << endl;

    cout << "Inorder traversal of Tree 1: ";
    my_tree1.inorder_traversal();
    cout << endl;

    cout << "Preorder traversal of Tree 1: " ;
    my_tree1.preorder_traversal();
    cout << endl;

    cout << "Height of tree 2: " << my_tree2.get_height() << endl;

    cout << "Inorder traversal of Tree 2: " ;
    my_tree2.inorder_traversal();
    cout << endl;

    cout << "Preorder traversal of Tree 2: " ;
    my_tree2.preorder_traversal();
    cout << endl;

    cout << "Postorder traversal of Tree 2: " ;
    my_tree2.postorder_traversal();
    cout << endl;

    for(index = 1; index <= 200; index++)
    {
        if(my_tree2.contains(index))
        {
            my_tree1.remove(index);
            cout << "After removing " << index << endl;
            my_tree1.preorder_traversal();
            cout << endl;
        }
    }

    cout << "Modified inorder traversal of Tree 1: ";
    my_tree1.inorder_traversal();
    cout << endl;

    return 0;
}
