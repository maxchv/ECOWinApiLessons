// UsingStaticLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <MyMath.h>

int main()
{
	MySpace::MyMath m;
	cout << m.Add(2, 2) << endl;

    return 0;
}

