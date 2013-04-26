//
//  main.cpp
//  Mivne1
//
//  Created by Aviad Rom on 4/19/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#include <iostream>
#include "AVLTree.h"

int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    AVLTree<int> T;
    int data=4,b=5,c=3,d=1;
    T.Insert(&data);
    T.Insert(&b);
    T.Insert(&c);
    T.Insert(&d);
    return 0;
}

