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
		
		data = "";

		return;
	}
	
	throw *(parsingTokens.begin());
}

void parser::scheme(){

	checkRemove("ID");
	checkRemove("LEFT_PAREN");
	checkRemove("ID");
	idList();
	checkRemove("RIGHT_PAREN");
}

void parser::fact(){

	checkRemove("ID");
        checkRemove("LEFT_PAREN");
	checkRemove("STRING");
        stringList();
        checkRemove("RIGHT_PAREN");
	checkRemove("PERIOD");
}

void parser::rule(){

	headPredicate();
	checkRemove("COLON_DASH");
	predicate();
	predicateList();
	checkRemove("PERIOD");
}

void parser::query(){

        predicate();
	checkRemove("Q_MARK");
}

void parser::schemeList(){

	while (parsingTokens.front().get_type() != "FACTS"){
		
		scheme();	
		schemeList();

	}
}

void parser::factList(){

	while (parsingTokens.front().get_type() != "RULES"){
		
		fact();		
                factList();

        }
}

void parser::ruleList(){

        while (parsingTokens.front().get_type() != "QUERIES"){
		
		rule();
                ruleList();

        }
}

void parser::queryList(){

        while (parsingTokens.front().get_type() != "EOF"){
		
		query();
                queryList();

        }
}

void parser::headPredicate(){

	checkRemove("ID");
        checkRemove("LEFT_PAREN");
	checkRemove("ID");
        idList();
        checkRemove("RIGHT_PAREN");
}

void parser::predicate(){

	checkRemove("ID");
        checkRemove("LEFT_PAREN");
        parameter();
	parameterList();
        checkRemove("RIGHT_PAREN");
}

void parser::predicateList(){
	
	while(parsingTokens.front().get_type() != "PERIOD"){
		
		checkRemove("COMMA");
		predicate();
		predicateList();
	}
}

void parser::parameterList(){

        while(parsingTokens.front().get_type() != "RIGHT_PAREN"){
		
		checkRemove("COMMA");
		parameter();	
                parameterList();
        }
}

void parser::stringList(){

        while(parsingTokens.front().get_type() != "RIGHT_PAREN"){
		
		checkRemove("COMMA");
		checkRemove("STRING");
                stringList();
        }
}

void parser::idList(){

        while(parsingTokens.front().get_type() != "RIGHT_PAREN"){
		
		checkRemove("COMMA");
		checkRemove("ID");
                idList();

        }
}
// DOUBLE CHECK THIS FUNCTION
void parser::parameter(){

	if(parsingTokens.front().get_type() == "STRING"){

		checkRemove("STRING");
		return;
	}
	else if(parsingTokens.front().get_type() == "ID"){

		checkRemove("ID");
		return;
	}
	else{
		expression();
	}
}

void parser::expression(){

	checkRemove("LEFT_PAREN");
	parameter();
	operate();
	parameter();
	checkRemove("RIGHT_PAREN");

}
// DOUBLE CHECK THIS FUNCTION
void parser::operate(){

	if(parsingTokens.front().get_type() == "ADD"){

                checkRemove("ADD");
                return;
        }
        else if(parsingTokens.front().get_type() == "MULTIPLY"){

                checkRemove("MULTIPLY");
                return;
        }

}
