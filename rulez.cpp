#include "rulez.h"
#include "predicate.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void rulez::set_rulezPredicate(vector <predicate> rulezPred){

        allrules = rulezPred;
}

string rulez::to_string(){


        stringstream ss;
        ss << allrules[0].to_string() << " :- " << allrules[1].to_string();
        for(unsigned i = 2; i < allrules.size(); i++){

                if(i == allrules.size() -1){

                        ss << allrules[i].to_string();
                }
                else{
                        ss << allrules[i].to_string() << ",";
                }
        }

        return ss.str();
}
