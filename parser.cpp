#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctype.h>
#include "parser.h"
#include "Tokens.h"

using namespace std;

parser::parser(){

	

}

/*			SCHEMES COLON scheme schemeList
		        FACTS COLON factList
		        RULES COLON ruleList
			QUERIES COLON query queryList */

void parser::datalogProgram(){

	try{
		checkRemove("SCHEMES");
		checkRemove("COLON");
		scheme();
		schemeList();
		checkRemove("FACTS");
		checkRemove("COLON");
		factList();
		checkRemove("RULES");
		checkRemove("COLON");
		ruleList();
		checkRemove("QUERIES");
		checkRemove("COLON");
		query();
		queryList();
		checkRemove("EOF");

		cout << "success" << endl;
	}
	catch(Tokens F){

		cout << "Failure\n  " << F.toString();
	}


}


void parser::checkRemove(string data){

	if(parsingTokens.front().get_type() == data){

		parsingTokens.erase(parsingTokens.begin());

		return;
	}
	
	throw parsingTokens.begin();

}
