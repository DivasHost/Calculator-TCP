#ifndef MATHLAB_H
#define MATHLAB_H
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

using namespace std;

/* 
    MathLab  contains the definition of functions and constant used for server calculation of mathematical problems.
    The functions are defined in the mathLab namespace.

    Usage of functions:  

    all functions are defines as methods in a class defined [calculator] 

    * Add(int a, int b) : returns the sum of two integers
    * Subtract(int a, int b) : returns the difference of two integers
    * Multiply(int a, int b) : returns the product of two integers
    * Divide(int a, int b) : return the division of two integers
    * abs_(double value) : return the absolute value of a variable
    
    NB  :  Other function were include by develope
    
    NB : Additonal fucntions can be added to the class as needed

 */

void print_msg(const char* msg){
   perror("print_msg");
   exit(1);
}

namespace mathLab {
    // Function declarations and other definitions go here
    class calculator {
        public:
            void Add(double*  array_ptr ,  size_t size , double*  result);
            void Subtract(double* array_ptr, size_t size, double* result);
            void Multiply(double* array_ptr, size_t size, double* result);
            void Divide(double* array_ptr, size_t size, double* result);
            double abs_(double value);
            double ceil_(double value);
            double floor_(double value);
            double round_(double value);
            double truncate_(double value);
            double sqrt_(double value);
            double cbrt_(double value);
            double exp_(double value);
            double log_(double value);
            double log10_(double value);
            double log2_(double value);
            double sin_(double value);
            double cos_(double value);
            double asin_(double value);
            double tan_(double value);
            double acos_(double value);
            double atan_(double value);
            double sinh_(double value);
            double cosh_(double value);
            double tanh_(double value);
            double asinh_(double value);
            double acosh_(double value);
            double atanh_(double value);
            double erf_(double value);
            double tgamma_(double value);
            double lgamma_(double value);
            // functiom to add abs, ceil, floor, round,trunc,fmod, sqrt,cbrt,exp,log,log10,log2,sin,cos,asin,tan,acos,atan,sinh,cosh,tanh,asinh,acosh,atanh,erf,tgamma,lgamma
            // other functions goes here

    };

    void calculator::Add(double*  array_ptr ,  size_t size , double*  result) {
        if (size == 0) {
            print_msg("System hass passed an empyt array to the Add function");
        }; // Handle empty array case

        double sum = array_ptr[0];
        for (size_t i = 1; i < size; i++) {
            sum += array_ptr[i];
        }
        *result = sum;    
    }

    void calculator::Subtract(double* array_ptr, size_t size, double* result) {
        if (size == 0) {
            print_msg("System hass passed an empyt array to the Substract function");
        } // Handle empty array case

        double difference = array_ptr[0];
        for (size_t i = 1; i < size; i++) {
            difference -= array_ptr[i];
        }
        *result = difference;
    }

    void calculator::Multiply(double* array_ptr, size_t size, double* result) {
        if (size == 0) {
            print_msg("System hass passed an empyt array to the Multiply function");
        } // Handle empty array case

        double product = 1.0;
        for (size_t i = 0; i < size; i++) {
            product *= array_ptr[i];
        }
        *result = product;
    }

    void calculator::Divide(double* array_ptr, size_t size, double* result) {
        if (size == 0) {
            print_msg("System hass passed an empyt array to the Divide function");
        } // Handle empty array case

        double quotient = array_ptr[0];
        for (size_t i = 1; i < size; i++) {
            if (array_ptr[i] == 0) {

            } // Handle division by zero
            quotient /= array_ptr[i];
        }
        *result = quotient;
    }

    // Other functions and definitions go here
    double calculator::abs_(double value){
        // result get the value absolute
        return  abs(value);
    }
    double  calculator::ceil_(double value){
        // result get the value ceil values
        return ceil(value);
    }
    double calculator::floor_(double value){
        // result get the value floor values
        return floor(value);
    }
    double calculator::round_(double value){
        // result get the value round values
        return round(value);
    }
    double calculator::truncate_(double value){
        // result get the value truncate values
        return trunc(value);
    }
    double calculator::sqrt_(double value){
        // result get the value square root
        return sqrt(value);
    }
    double calculator::cbrt_(double value){
        // result get the value cube root
        return cbrt(value);
    }
    double calculator::exp_(double value){
        // result get the value exponential
        return exp(value);
    }
    double calculator::log_(double value){
        // result get the value natural logarithm
        return log(value);
    }
    double calculator::log10_(double value){
        // result get the value logarithm base 10
        return log10(value);
    }
    double calculator::log2_(double value){
        // result get the value logarithm base 2
        return log2(value);
    }
    double calculator::sin_(double value){
        // result get the value sine
        double rad =  value *  (PI / 180);
        return sin(rad);
    }
    double calculator::cos_(double value){
        // result get the value cosine
        double rad =  value *  (PI / 180);
        return cos(rad);
    }
    double calculator::tan_(double value){
        double rad =  value *  (PI / 180);
        return tan(rad);
    }
    double calculator::acos_(double value){
        // result get the value arccosine
        double rad =  acos_(value);
        return rad * (180 / PI);
    }

    double calculator::asin_(double value){
        // result get the value arcsine
        double rad =  asin_(value);
        return rad * (180 / PI);
    }
    double calculator::atan_(double value){
        // result get the value arctangent
        double rad =  atan_(value);
        return rad * (180 / PI);
    }
    double calculator::sinh_(double value){
        // result get the value hyperbolic sine
        return sinh(value);
    }
    double calculator::cosh_(double value){
        // result get the value hyperbolic cosine
        return cosh(value);
    }
    double calculator::tanh_(double value){
        // result get the value hyperbolic tangent
        return tanh(value);
    }
    double calculator::asinh_(double value){
        // result get the value inverse hyperbolic sine
        return asinh(value);
    }
    double calculator::acosh_(double value){
        // result get the value inverse hyperbolic cosine
        return acosh(value + 1.0);
    }
    double calculator::atanh_(double value){
        // result get the value inverse hyperbolic tangent
        return atanh(value);
    }
    double calculator::erf_(double value){
        // result get the value error function
        return erf(value);
    }
    double calculator::tgamma_(double value){
        // result get the value gamma function
        return tgamma(value);
    }
    double calculator::lgamma_(double value){
        // result get the value logarithm of the gamma function
        return lgamma(value);
    }
    // Other functions and definitions go here
}

#endif // MATHLAB_H

/* "abs", "ceil", "floor", "round","trunc", "sqrt","cbrt","exp","log","log10","log2","sin","cos","asin","tan","acos","atan","sinh","cosh","tanh","asinh","acosh","atanh","erf","tgamma","lgamma"}; //add  */