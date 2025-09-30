#ifndef SPECIAL_H
#define SPECIAL_H
#include <iostream>
#include <regex>
#include <vector>
#include <string>
#include "mathLab.h"
#include <cmath>

//2x^2 - 4x - 5 dig_x2_dig_x_dig
// 3x^2 - 4x = -5 dig_2_digx__dig_
// 3x^2 = - 4 + 4x; dig_x2__dig__digx

using namespace std;
using namespace mathLab;

namespace special {
    typedef enum  {
        quadratic_equation,
        // polynomial_equation,
        // cubic_equation,
        // linear_equation,
        Not_Equation
    }equations;

    typedef enum  {
        dig_x2_dig_x_dig,
        dig_2_digx__dig_,
        dig_x2__dig__digx,
        Null____
        // polynomial_equation,
        // linear_equation,
        // quadratic_equation,
        // cubic_equation,

        // add more cummutation of quadratic equations
    }quadratic_type;

    equations equation_check(const string& str){
        regex Quad_exp("^(([\\+\\-]?([[:digit:]]+)?)([a-z])\\^2[[:space:]]*([\\+\\-][[:space:]]*[[:digit:]]*)\\4[[:space:]]*([\\-\\+][[:space:]]*[[:digit:]]*)|(([\\-\\+]?[[:digit:]]+)([a-z])\\^2[[:space:]]*([\\-\\+][[:space:]]*[[:digit:]]+)\\8[[:space:]]*\\=[[:space:]]*([\\-\\+]?[[:space:]]*[[:digit:]]+))|(([\\-\\+]?[[:digit:]]+)([a-z])\\^2[[:space:]]*\\=[[:space:]]*([\\-\\+]?[[:space:]]*[[:digit:]]+)[[:space:]]*([\\-\\+][[:space:]]*[[:digit:]]+)\\13))$",  regex_constants::icase); //add expression with | () before  tha parentheses, Definition should be testes befor added

        // define equation expression here

        if(regex_match(str, Quad_exp)){
            return quadratic_equation;
        }else  {
            return Not_Equation;
        }

        // add your key word regex here
    }

    quadratic_type idenity_qudratice_equation(const string& str){
        smatch match;
        regex exp1("^(([\\+\\-]?([[:digit:]]+)?)([a-z])\\^2[[:space:]]*([\\+\\-][[:space:]]*[[:digit:]]*)\\4[[:space:]]*([\\-\\+]?[[:space:]]*[[:digit:]]*)|(([\\-\\+]?[[:digit:]]+)))$",  regex_constants::icase);
        regex exp2("(([\\-\\+]?[[:digit:]]+)([a-z])\\^2[[:space:]]*([\\-\\+][[:space:]]*[[:digit:]]+)\\3[[:space:]]*\\=[[:space:]]*([\\-\\+]?[[:space:]]*[[:digit:]]+))", regex_constants::icase);
        regex exp3("(([\\-\\+]?[[:digit:]]+)([x])\\^2[[:space:]]*\\=[[:space:]]*([\\-\\+]?[[:space:]]*[[:digit:]]+)[[:space:]]*([\\-\\+][[:space:]]*[[:digit:]]+)[x])",  regex_constants::icase);
        // add your regular expression here and define with the @def with @details exp...;

        if(regex_search(str, match, exp1)){
            return dig_x2_dig_x_dig;
        }else if(regex_search(str, match, exp2)){
            return dig_2_digx__dig_;
        }else if(regex_search(str, match, exp3) ) {
            return dig_x2__dig__digx;
        }else {
            return Null____;
        }
    }

    // get_parameter
    vector<string> get_parameter(const string &str,  regex rg){
        smatch match;
        vector<string> params;

        if(regex_search(str, match, rg)){
            for(size_t i = 1; i < match.size(); ++i){
                params.push_back(match[i].str());
            }
        }
        return params;
    }

    // remove the white space in character
    string removeAllSpaces(const std::string &str) {
        std::string result;
        for (char ch : str) {
            if (!std::isspace(ch)) { // Add only non-space characters
                result += ch;
            }
        }
        return result;
    }

    class equation
    {
        public:
            /* data */
            public: 
            vector<string> params;
            vector<double> d_params;

            public:
            vector<double> ans;
            string var; // contain the varibale used 
            
        public:
            equation(const string& string);
    };
    
    equation::equation(const string& str)
    {
        // pass the string to check if it an equation
        equations equate = special::equation_check(str);

        if(equate == quadratic_equation){
            quadratic_type type = special::idenity_qudratice_equation(str);
            if(type == dig_x2_dig_x_dig){
                // implementation for dig_x2_dig_x_dig equation  2x^2 - 4x - 5
                regex exp1("^(([\\+\\-]?([[:digit:]]+)?)([a-z])\\^2[[:space:]]*([\\+\\-][[:space:]]*[[:digit:]]*)\\4[[:space:]]*([\\-\\+]?[[:space:]]*[[:digit:]]*)|(([\\-\\+]?[[:digit:]]+)))$",  regex_constants::icase);
                params =  get_parameter(str, exp1);
                regex int_var("[\\-\\+]?[[:digit:]]+");
                calculator calculate;
                for(int i = 0; i < params.size(); i++) {
                    params[i] = special::removeAllSpaces(params[i]);
                }
                vector <string>  group;
                group.push_back(params[1]);
                group.push_back(params[4]);

                if(!group[0].empty()){
                    if(group[0].size() ==  1){
                        if(isdigit(group[0][0])){
                            string var  =  group[0];
                            params[1] =  var;
                        }else {
                            string var  =  group[0];
                            if(var[0] == '+' || var[0] == '-'){
                                var.append("1");
                                params[1] =  var;
                            }
                        }
                     }
                }else  {
                    string str  =  group[0];
                    str.append("1");
                    params[1] = str;
                }

                if(group[1].size() == 1){
                    if(!isdigit(group[1][0])){
                        string var  =  group[1];
                        if(var == "-" || var == "+"){
                            var.append("1");
                            group[1] = var;
                            params[4] = group[1];
                        }
                    } 
                }           


                // erase the 3 postions in params
                // params.erase(params.begin() + 2);
                // convert parameters to double 
                for(int i = 0; i < params.size(); i++){
                    if(regex_match(params[i], int_var)){
                        string n =  params[i];
                        d_params.push_back(stod(n));
                    }else {
                        continue;
                    }
                }

                // carry quadratic expression
                // check if the d_params is greater than avg (3)
                double x1, x2;
                if(d_params.size() >  3){
                    double derivative = (pow(d_params[2], 2) - (4*d_params[0]*d_params[3]));
                    double deriv;
                    // check if derivative is greeter than 0 
                    if(derivative > 0){
                        // equation is positive
                        deriv =  calculate.sqrt_(derivative);
                    } else {
                        deriv = -calculate.sqrt_(abs(derivative));
                    }
                    // get roots of equation
                    x1 =  (-d_params[2] + deriv) / (2*d_params[0]);
                    x2 =  (-d_params[2] - deriv) / (2*d_params[0]);
                }else  {
                    double derivative = (pow(d_params[1], 2) - (4*d_params[0]*d_params[2]));
                    double deriv;
                    // check if derivative is greeter than 0 
                    if(derivative > 0){
                        // equation is positive
                        deriv =  calculate.sqrt_(derivative);
                    } else {
                        deriv = -calculate.sqrt_(abs(derivative));
                    }
                    // get roots of equation
                    x1 =  (-d_params[1] + deriv) / (2*d_params[0]);
                    x2 =  (-d_params[1] - deriv) / (2*d_params[0]);
                }
                ans.push_back(x1);  // check if correct cux of wrong accession 
                ans.push_back(x2);
                this->var =  params[3];
 

            } else if(type == dig_2_digx__dig_){
                // implementation for dig_2_digx__dig_ equation  3x^3 - 4x = -5  
                regex exp2("(([\\-\\+]?[[:digit:]]+)([a-z])\\^2[[:space:]]*([\\-\\+][[:space:]]*[[:digit:]]+)\\3[[:space:]]*\\=[[:space:]]*([\\-\\+]?[[:space:]]*[[:digit:]]+))", regex_constants::icase);
                params =  get_parameter(str, exp2);
                for(int i = 0; i < params.size(); i++) {
                    params[i] = special::removeAllSpaces(params[i]);
                }
                regex int_var("[\\-\\+]?[[:digit:]]+");
                for(int i = 0; i < params.size(); i++) {
                    params[i] = special::removeAllSpaces(params[i]);
                }
                for(int i = 0; i < params.size(); i++){
                    if(regex_match(params[i], int_var)){
                        string n =  params[i];
                        d_params.push_back(stod(n));
                    }else {
                        continue;
                    }
                }
            } else if(type == dig_x2__dig__digx){
                // implementation for dig_x2__dig__digx equation   3x^3 = - 4 + 4x
                regex exp3("(([\\-\\+]?[[:digit:]]+)([x])\\^2[[:space:]]*\\=[[:space:]]*([\\-\\+]?[[:space:]]*[[:digit:]]+)[[:space:]]*([\\-\\+][[:space:]]*[[:digit:]]+)[x])",  regex_constants::icase);
                params =  get_parameter(str, exp3);
                for(int i = 0; i < params.size(); i++) {
                    params[i] = special::removeAllSpaces(params[i]);
                }
                regex int_var("[\\-\\+]?[[:digit:]]+");
                for(int i = 0; i < params.size(); i++) {
                    params[i] = special::removeAllSpaces(params[i]);
                }
                for(int i = 0; i < params.size(); i++){
                    if(regex_match(params[i], int_var)){
                        string n =  params[i];
                        d_params.push_back(stod(n));
                    }else {
                        continue;
                    }
                }
            }
        }else {
            ans.push_back(0); // do nothing
        }

        // add your keyword defintion and syntax
    }
    
}


#endif // SPECIAL_H