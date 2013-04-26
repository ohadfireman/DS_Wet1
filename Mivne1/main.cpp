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
    int root=12, step1=8,step2=15,step3=6,step4=10;
    int step5=14,step6=24,step7=4,step8=11,step9=13;
    int step10=20,step11=29,step12=19,step13=18;
    T.Insert(&root);
    T.Insert(&step1);
    T.Insert(&step2);
    T.Insert(&step3);
    T.Insert(&step4);
    T.Insert(&step5);
    T.Insert(&step6);
    T.Insert(&step7);
    T.Insert(&step8);
    T.Insert(&step9);
    T.Insert(&step10);
    T.Insert(&step11);
    T.Insert(&step12);
    T.Insert(&step13);
    return 0;
}

