/**
 * @brief 
 * 
 * @class Sign
 * Rule class contructor.
 * 
 * [Detailed description of the function or class]
 * 
 * @param [operators :  this is the operator for the operation]
 * @return [no return values] 
 * 
 * [Additional notes or information]
 * 
 * Note  : Developer should open the @dir Documents/MacPack_Project/Project/MathLab.h to implement the rule set at the signRule. Data should not be added to this file only when necessary.
 * 
 * @details Signal info
 * #  404 -  "Additon operetor"
 * #  401 -  "Substraction operetor"
 */


#ifndef SIGNRULE_H
#define SIGNRULE_H
#include <iostream>
#include <string> 
#include "mathLab.h"

#define Num_Operation  2

using namespace mathLab;
using namespace std;

typedef enum  {
    ADD, 
    SUB, 
    MUL,
    DIV,
}Operators;

void reverse_array(double* array, int size) {
    int start = 0;
    int end = size - 1;
    while (start < end) {
        double temp = array[start];
        array[start] = array[end];
        array[end] = temp;
        start++;
        end--;
    }
}


Operators op;
calculator calculate;
namespace Sign {
    // Your code goes here
    class  Rule
    {
        protected:
        int sig; // signal container
        int cot; // operator control

        private:
        double* result;
        
        public:
            Rule(string operators);
            void  __rule__set(double* array_ptr,   string  next__operator,  double* result);
            string get_result();

    };
    
    Rule:: Rule(string operators)
    {    
        if(operators == "+") {
            this->sig  =  404;
        }else if(operators == "-"){
            this->sig  =  401;
        }else  {
            this->sig = 000;
        }
    }

    void Rule::__rule__set(double* array_ptr,   string  next__operator, double* ans) {
        // Your code goes here
        /* 
            This would've implied  on other  operator as next_operator if only signal is 404 or the 402 for the follwoing to execute 

            data1 and data2  arguments recieves each stack of operation and base on the signal of first variable if been an operator the value get evaluated irrespective of the operator count
        */

        //check the opereator
        if(next__operator.find("+") !=  string::npos) op = ADD;
        if(next__operator.find("-") != string::npos) op = SUB;
        if(next__operator.find("*") != string::npos) op = MUL;
        if(next__operator.find("/") != string::npos) op  = DIV;


        switch (op)
        {
            case ADD: 
                // Addition operation
                if(this->sig ==  404) {
                    calculate.Add(array_ptr, Num_Operation,  ans);
                    this->result =  ans;
                }else if(this->sig == 401) {
                    if(array_ptr[0] >=  array_ptr[1])  {  
                        calculate.Subtract(array_ptr, Num_Operation,  ans);
                        this->result =  ans;
                        this->cot =  -1;
                    }else  {
                        reverse_array(array_ptr,  Num_Operation);
                        calculate.Subtract(array_ptr, Num_Operation, ans);
                        this->result =  ans;
                        this->cot =  1;
                    }
                }else  {
                        calculate.Add(array_ptr, Num_Operation,  ans);
                        this->result =  ans;
                        this->cot =  1;
                }
            break;

            case SUB: 
                // Subtraction operation
                if(this->sig ==  404){
                    calculate.Subtract(array_ptr, Num_Operation,  ans);
                    this->result =  ans;
                    this->cot  =  1;
                }else if(this->sig  ==  401){
                    calculate.Add(array_ptr, Num_Operation,  ans);
                    this->result =  ans;
                    this->cot  =  -1;
                }else  {
                    calculate.Subtract(array_ptr, Num_Operation,  ans);
                    this->result =  ans;
                    this->cot  =  1;
                }
            break;

            case MUL:
                 // Multiplication operation
                 if(this->sig  ==  404){
                    calculate.Multiply(array_ptr, Num_Operation,  ans);
                    this->result =  ans;
                    this->cot  =  1;
                 }else  if(this->sig == 401){
                    calculate.Multiply(array_ptr, Num_Operation,  ans);
                    this->result =  ans;
                    this->cot  =  -1;
                 }else  {
                    calculate.Multiply(array_ptr, Num_Operation,  ans);
                    this->result =  ans;
                    this->cot  =  1;
                 }
            break;

            case DIV:
                 // Division operation
                 if(this->sig == 404) {
                    calculate.Divide(array_ptr, Num_Operation,  ans);
                    this->result =  ans;
                    this->cot  =  1;
                 }else if(this->sig == 401){
                    calculate.Divide(array_ptr, Num_Operation,  ans);
                    this->result =  ans;
                    this->cot  =  -1;
                 }else {
                    calculate.Divide(array_ptr, Num_Operation,  ans);
                    this->result =  ans;
                    this->cot  =  1;
                 }
            break;
        }
    }

    string Rule::get_result() {
        if(this->cot  <  0) {
            return "-" + to_string(*result);
        }else  {
            return to_string(*result);
        }
    }
}

#endif // SIGNRULE_H