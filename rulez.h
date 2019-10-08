#pragma once
#ifndef RULEZ_H
#define RULEZ_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "predicate.h"

using namespace std;

class rulez {

public:
        rulez(){};

	void set_rulezPredicate(vector <predicate> rulezPred);
	string to_string();

private:

	vector <predicate> allrules;      

};
#endif

