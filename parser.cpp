#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctype.h>
#include "parser.h"
#include "Tokens.h"
#include "predicate.h"
#include "rulez.h"
#include <algorithm>

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

		cout << "Success!" << endl;
	}
	catch(Tokens F){

		cout << "Failure\n  " << F.toString();
	}
	
	cout << "Schemes(" << schemes.size() << ")" << endl;

	for(unsigned i = 0; i < schemes.size(); i++){

		cout << "  " <<schemes[i].to_string() << endl;
	}

	cout << "Facts(" << facts.size() << ")" << endl;

	for(unsigned i = 0; i < facts.size(); i++){

                cout << "  " << facts[i].to_string() << "."<< endl;
        }
	
	cout << "Rules(" << rules.size() << ")" << endl;

	for(unsigned i = 0; i < rules.size(); i++){

                cout << "  " << rules[i].to_String() << "?" << endl;
        }

	cout << "Queries(" << queries.size() << ")" << endl;

	for(unsigned i = 0; i < queries.size(); i++){

                cout << "  " << queries[i].to_string() << "?" << endl;
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

	string item = "";

	item = parsingTokens.front().get_symbol();
	checkRemove("ID");
	current.set_name(item);
	checkRemove("LEFT_PAREN");
	item = parsingTokens.front().get_symbol();
	checkRemove("ID");
	current.set_item(item);
	idList();
	checkRemove("RIGHT_PAREN");
	schemes.push_back(current);
	current.clear();
}

void parser::fact(){

	string item = "";

        item = parsingTokens.front().get_symbol();
	checkRemove("ID");
	current.set_name(item);
        checkRemove("LEFT_PAREN");
	item = parsingTokens.front().get_symbol();
	checkRemove("STRING");
	current.set_item(item);
        stringList();
        checkRemove("RIGHT_PAREN");
	checkRemove("PERIOD");
	facts.push_back(current);
        current.clear();

}

void parser::rule(){
//create new empty rule
	headPredicate();
//pushback new head predicate into empty rule
	currentrule.set_head(current);        	
	checkRemove("COLON_DASH");
	newPredicate();
	currentrule.add_predicate(current);	
	predicateList();
//push vector of predicate into rule
	checkRemove("PERIOD");
	rules.push_back(currentrule);
	currentrule.clearCurrentRule();
//pushback rule into rule vector
}

void parser::query(){

        newPredicate();
	checkRemove("Q_MARK");
	queries.push_back(current);
        current.clear();

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

	string item = "";
	item = parsingTokens.front().get_symbol();
	checkRemove("ID");
	current.set_name(item);
        checkRemove("LEFT_PAREN");
	item = parsingTokens.front().get_symbol();
	checkRemove("ID");
	current.set_item(item);
        idList();
        checkRemove("RIGHT_PAREN");
	
}

void parser::newPredicate(){
	
	string item = "";
	item = parsingTokens.front().get_symbol();
	checkRemove("ID");
	current.set_name(item);
        checkRemove("LEFT_PAREN");
        parameter();
	parameterList();
        checkRemove("RIGHT_PAREN");
}

void parser::predicateList(){
	
	while(parsingTokens.front().get_type() != "PERIOD"){
		
		checkRemove("COMMA");
		newPredicate();
		currentrule.add_predicate(current);
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
		string item = parsingTokens.front().get_symbol();
		checkRemove("STRING");
		current.set_item(item);
                stringList();
        }
}

void parser::idList(){

        while(parsingTokens.front().get_type() != "RIGHT_PAREN"){
		
		checkRemove("COMMA");
		string item = parsingTokens.front().get_symbol();
		checkRemove("ID");
		current.set_item(item);
                idList();

        }
}

void parser::parameter(){

	string item = "";

	if(parsingTokens.front().get_type() == "STRING"){

       	 	item = parsingTokens.front().get_symbol();
		checkRemove("STRING");
		current.set_item(item);
		return;
	}
	else if(parsingTokens.front().get_type() == "ID"){

		item = parsingTokens.front().get_symbol();
                checkRemove("ID");
                current.set_item(item);
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
