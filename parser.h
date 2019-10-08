#pragma once
#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Tokens.h"
#include "predicate.h"
#include "rulez.h"

using namespace std;

class parser {

public:
	parser();

	void startParser(){
		datalogProgram();
	}

	void setvector(vector <Tokens> Tokens){

		parsingTokens = Tokens; 

	}


private:

	vector <Tokens> parsingTokens;

	void checkRemove(string);
	void datalogProgram();
	void schemeList();
	void factList();
	void ruleList();
	void queryList();
	void scheme();
	void fact();
	void rule();
	void query();
	void headPredicate();
	void predicate();
	void predicateList();
	void parameterList();
	void stringList();
	void idList();
	void parameter();
	void expression();
	void operate();


};

#endif

