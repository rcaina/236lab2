#pragma once
#ifndef PREDICATE_H
#define PREDICATE_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class predicate {

public:
        predidcate(){}
        predicate() {}


private:

	vector <Schemes> schemes;
	vector <Facts> facts;
	vector <Queries> queries;
	vector <Rules> rules;


};
#endif

