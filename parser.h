#pragma once
#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Tokens.h"

using namespace std;

class parser {

public:
	parser(){}
	parser();

	void parse();
	Datalog parse();
	void parseFact();
	void parseQueries();
	void parseRules();
	void parseSchemes();
};

#endif

