/**
 * @brief 
 * removeWhite__()  reomves the white space in the string.
 * 
 * [Detailed description of the function or class]
 * 
 * @param [str] [a reference to the string to be trimmed]
 * @return [string been trimmed] 
 * 
 * [Additional notes or information]
 * 
 * if it's recieves an empyt string its return the empty string 
 */

#ifndef TYPE_H 
#define TYPE_H 

#include<iostream>
#include<cctype>

using namespace std;

namespace Type
{
    string removewhite__(const string &str){
        std::string result;
        bool lastWasSpace = false;

        for (char ch : str) {
            if (std::isspace(ch)) {
                // Skip spaces to ensure only one space is added around operators
                lastWasSpace = true;
                
            } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' /*add your operator delimiter */)  {
                // Add spaces around operators
                if (!result.empty() && result.back() != ' ') {
                    result += ' ';
                }
                result += ch;
                result += ' ';
                lastWasSpace = false;
        } else {
                // Add non-space characters and reset space tracking
                if (lastWasSpace && !result.empty() && result.back() != ' ') {
                    result += ' ';
                }
                result += ch;
                lastWasSpace = false;
            }
        }

        // Trim trailing spaces
        while (!result.empty() && result.back() == ' ') {
            result.pop_back();
        }

        return result;
    }

}
// namespace Type
#endif

