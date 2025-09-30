#include "mathLab.h"
#include "type.h"
#include "signRule.h"
#include "speciall.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <unistd.h>  
#include <algorithm>
#include <iomanip>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h> 
#include <string.h>
#include <regex>


//namespace declaration
using namespace std;
using namespace mathLab;
using namespace Type;
using namespace Sign;
using namespace special;

#define MAX_CLIENTS 3
#define Num_Operation  2 // number of operation that can be done by the server

typedef enum {
     Quadratic_Equation =  1,
     Linear_Equation = 2,
     Polynomial_Equation = 3,
     Cubi_Equation = 4 //add equation here
}formular;


// regression text
bool regex_test(string &keyword_Name, const string &strings){
     string patterns =  keyword_Name + R"(\((\d+(\.\d+)?)\))";
     regex regexPattern(patterns);
     return regex_search(strings, regexPattern);
}

std::string extractValueInSqrt(const string &key,const std::string& str) {
    // Regular expression to match sqrt(<digits>) and capture the digits
    std::regex pattern ( key  + R"(\((\d+(\.\d+)?)\))");
    std::smatch match;

    // Search for the pattern in the input string
    if (std::regex_search(str, match, pattern)) {
        // The first capture group (digits inside the parentheses) is in match[1]
        return match[1].str();
    }

    // Return an empty string if no match is found
    return "";
}

/*Declaration of sockaddr_in */
struct sockaddr_in server, client;
socklen_t  addrlen; 

void error(const char* message){
    perror(message);
    exit(1);
}

int main(int argc, char* argv[]) {
    /*Make sure that the user set the port number for the server*/
     if(argc < 2){
          fprintf(stderr, "Error in command line argument\n");
          exit(1);
     }

     /*Declaration*/
     int port = atoi(argv[1]); // convert port code to string
     char user_recv[266];
     int  byte_recv , byte_send; 
     stringstream srv_streem ;
     const char* delimiter[] =  {"+","-", "*", "/"}; //add delimiter here
     const char* special_kewords[] =  {"abs", "ceil", "floor", "round","trunc", "sqrt","cbrt","exp","log","log10","log2","sin","cos","asin","tan","acos","atan","sinh","cosh","tanh","asinh","acosh","atanh","erf","tgamma","lgamma"}; //add your keyword here
     const char* equations[] =  {"Quadratic Equation", "Linear Equation", "Polynomial Equation", "Cubi Equation"}; //add your equation here key word NB : default equation should not be earsed or changed
     size_t equation_size = sizeof(equations) /  sizeof(equations[0]);
     size_t size  =  sizeof(delimiter)/sizeof(delimiter[0]);
     size_t spec_size =  sizeof(special_kewords) / sizeof(special_kewords[0]);
     int increment = 0,  size_of_number =  0;
     char math_erro[] =  "Math Error";
     char nan[] = "Not a number";
     char out_option[] =  "Out of option";
     char not_available[] = "This feature is under development";
     char in_option[] = "in option";
     string srv_operation;
     string srv_strings;
     string srv_standard_formats;
     string ans;
     deque<string> srv_string_token;
     deque<double> srv_deque;
     vector<string> client_sen_operator;
     vector<int> positon;
     double array[Num_Operation];
     double result;
     string srv_result;
     srv_string_token.clear();
     calculator calculate;
     const char* keyword =  "ls";

     /*Create a socket for the server and check if it's created successfully*/
     int srv_socket  =  socket(AF_INET, SOCK_STREAM, 0);
     

     /*Check if the socket was created successfully*/
     if(srv_socket <  0)  {
          error("Error opening socket");  
     }else{ 
          cout << "Socket created successfully\n" << endl;
     }

          
     /*make sure there is no value in the server by set it to zero*/
     memset(&server ,  0 , sizeof(server)); 
     /*Initialize the sockaddr sin_family, port and addr*/
     server.sin_family =  AF_INET;
     server.sin_port = htons(port);
     server.sin_addr.s_addr = INADDR_ANY;

     /*Bind the socket to the server address and port*/
     int binding = ::bind(srv_socket, (struct sockaddr *)&server, sizeof(server));

     if(binding  <  0) { 
          error("Error binding socket\n");
     }else   {
          cout <<  "Connect\n" <<  endl;
     }

     /*Listen for incoming connections*/
     if(listen(srv_socket, MAX_CLIENTS) <  0) error("Error listening") ;
     addrlen = sizeof(client);

     /*Accept a new client connection and handle it*/
     int new_srv_socket = accept(srv_socket, (struct sockaddr*)&server, &addrlen);

     /*Check if the client was accepted successfully*/
     if(new_srv_socket < 0) {
          error("Unable to connect\n");
     }else  {
          cout << "\n\n" << setw(50) <<  "CALCULATOR" << endl;
     }

     /*Server is in operation wtih client*/
     while (true)
     {    
          memset(user_recv, 0, 266);
          byte_recv = recv(new_srv_socket, user_recv, 265, 0);

          /*Check if the message was received successfully*/
          if(byte_recv < 0) error("ERROR IN RECEIVING FROM CLIENT");

          cout  <<  ">>>>> : " << user_recv << endl;

          // get the data stored in srv_strings
          srv_strings.append(user_recv);
          
          // check if it was successful in appending
          if(srv_strings.size() ==  0) error("ERROR IN APPENDING DATA");
          

          // check condition if  user send a keyword case
          if(srv_strings.find(keyword) != string::npos)  {
          // for special function 
               stringstream s_s;
               string ans_s;
               srv_streem << keyword << " | ";
               // get all equation command char* into a stream
               for(size_t i  = 0;  i <  equation_size; i++){
                    srv_streem <<  " " << equations[i] << " | " << flush;
               }
               // check if the stream is not empty
               if(srv_streem.bad()) error("bad stream");

               //define srv_strings to srv_stream
               srv_strings =  srv_streem.str();
               // send to the server 
               byte_send  =  send(new_srv_socket, srv_strings.c_str(),  strlen(srv_strings.c_str()),  0);
               // check if successful
               if(byte_send <  0) error("ERROR SENDING TO CLIENT");

               // recv from server  
               memset(user_recv, 0 , sizeof(user_recv));
               byte_recv = recv(new_srv_socket, user_recv, 265, 0);
               // check if successful
               if(byte_recv <  0) error("ERROR IN RECEIVING FROM CLIENT");

               int convert;
               string convert_string =  user_recv;

               try
               {
                    // convert string to number 
                    convert =  stoi(convert_string);
                    if(!convert){
                         throw 404;
                    }else  {
                         //send to the client a message
                         formular form =  Quadratic_Equation;
                         formular form2 =  Linear_Equation;
                         formular form3 =  Polynomial_Equation;
                         formular form4 =  Cubi_Equation;
                         // add your formala defined as form5

                         if(convert  ==  form){
                              // send to client message fo this is not available
                              byte_send  =  send(new_srv_socket, in_option,  strlen(in_option),  0);
                              // check if successful
                              if(byte_send <  0) error("ERROR SENDING TO CLIENT");

                              // recv from cleint 
                              memset(user_recv, 0, sizeof(user_recv));
                              byte_recv = recv(new_srv_socket, user_recv, 265, 0);
                              // check if successful
                              if(byte_recv <  0) error("ERROR IN RECEIVING FROM CLIENT");

                              // evaluate the expression
                              string equation_expression  = user_recv;
                              string modified =  removeAllSpaces(equation_expression);
                              equation expression(modified);

                              // check if it is a valid expression
                              if(expression.ans.size() == 1){
                                   // send to server
                                   byte_send =  send(new_srv_socket,  "Not a Quadratic Expression",  strlen("Not a Quadratic Expression"), 0);

                                   // check if successful
                                   if(byte_send <  0) error("ERROR SENDING TO CLIENT");

                              }else  {
                                   // convert ans to string and send i to the client  
                                   // cleare s_s 
                                   s_s.clear();
                                   ans_s.clear();
                                   s_s << expression.var << "1  : " << expression.ans[0] << "\t" << expression.var <<"2  : "<< expression.ans[1] <<  flush ;

                                   // check if stream was successfully
                                   if(s_s.bad()) error("bad stream");

                                   // define srv_string
                                   ans_s =  s_s.str();
                                   // send to the server
                                   byte_send =  send(new_srv_socket, ans_s.c_str(),  strlen(ans_s.c_str()),  0);

                                   // check if successful
                                   if(byte_send <  0) error("ERROR SENDING TO CLIENT");

                              }

                         }else if(convert ==  form2){
                              // send to client  message fo this is not available
                              byte_send  =  send(new_srv_socket, not_available,  strlen(not_available),  0);
                              // check if successful
                              if(byte_send <  0) error("ERROR SENDING TO CLIENT");
                         }else if(convert ==  form3) {
                              // send to client message fo this is not available
                              byte_send  =  send(new_srv_socket, not_available,  strlen(not_available),  0);
                              // check if successful
                              if(byte_send <  0) error("ERROR SENDING TO CLIENT");
                         }else if(convert ==  form4){
                              // send to client message fo this is not available
                              byte_send  =  send(new_srv_socket, not_available,  strlen(not_available),  0);
                              // check if successful
                              if(byte_send <  0) error("ERROR SENDING TO CLIENT");
                         }else {
                              // send to client meessage of out of option
                              byte_send  =  send(new_srv_socket, out_option,  strlen(out_option),  0);
                              // check if successful
                              if(byte_send <  0) error("ERROR SENDING TO CLIENT");
                         }

                         // add your form definiton
                         // clear s_s streem;
                         s_s.clear();
                    }
               }
               catch(...)
               {
                    // send to customer of no a number character;
                     byte_send  =  send(new_srv_socket, nan,  strlen(nan),  0);
                     // check if successful
                     if(byte_send <  0) error("ERROR SENDING TO CLIENT");
               }
                   
               
          } else {


               // get the srv_string to be rearranged by the removewhite__() function to bring it to standard format
               srv_standard_formats =  removewhite__(srv_strings);

               // add the string to the stream
               srv_streem.write(srv_standard_formats.c_str(), srv_standard_formats.size());

               // check if the streem is not empty
               if(srv_streem.bad()) error("bad stream");

               // eneter loop to stream and push back string to the srv_string_token
               while (getline(srv_streem,  srv_operation,  ' '))
               {
                    /* code */
                    srv_string_token.push_back(srv_operation);
               }
               
               // check if srv_string_token is empty
               if(srv_string_token.size() == 0)  error("error at spliting the sting");

               // set the Rule class  to of operator
               Rule rule(srv_string_token[0]);

               // first condtion if the first variable is an operator
               if(srv_string_token[0] == "+" ||  srv_string_token[0] == "-") {
                    srv_string_token.pop_front();
               }

               // check for special keyword 
               // loop through all srv_string_token to check for special tokens  and set thier posistion with a new index

               for(int i =  0; i < srv_string_token.size(); i++) {
                    // check if the string is a special keyword
                    for(int j = 0; j < spec_size; j++) {
                         string key  =  special_kewords[j];
                         if(regex_test(key, srv_string_token[i])) {
                              // solve the expression
                              string str_values  =  extractValueInSqrt(key, srv_string_token[i]);
                              double value =  stod(str_values); //convert to double
                              if(key.find("abs") !=  string::npos) {
                                   value = calculate.abs_(value);
                                   srv_string_token[i] = to_string(value); // push back the value back to the pacticular position and convert to string 
                              }else if(key.find("ceil") !=  string::npos) {
                                   value = calculate.ceil_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("floor") != string::npos) {
                                   value = calculate.floor_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("round") !=  string::npos) {
                                   value = calculate.round_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("sqrt") !=  string::npos) {
                                   value = calculate.sqrt_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("cbrt") != string::npos) {
                                   value = calculate.cbrt_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("exp") != string::npos) {
                                   value = calculate.exp_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("log") != string::npos) {
                                   value = calculate.log_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("sin") != string::npos) {
                                   value = calculate.sin_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("cos") != string::npos) {
                                   value = calculate.cos_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("tan") != string::npos) {
                                   value = calculate.tan_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("asin") != string::npos) {
                                   value = calculate.asin_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("acos") != string::npos) {
                                   value = calculate.acos_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("atan") != string::npos) {
                                   value = calculate.atan_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("log2") != string::npos) {
                                   value = calculate.log2_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("log10") != string::npos) {
                                   value = calculate.log10_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("sinh") != string::npos) {
                                   value = calculate.sinh_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("cosh") != string::npos) {
                                   value = calculate.cosh_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("tanh") != string::npos) {
                                   value = calculate.tanh_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("asinh") != string::npos) {
                                   value = calculate.asinh_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("acosh") != string::npos) {
                                   value = calculate.acosh_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("atanh") != string::npos) {
                                   value = calculate.atanh_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("erf") != string::npos) {
                                   value = calculate.erf_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("tgamma") != string::npos) {
                                   value = calculate.tgamma_(value);
                                   srv_string_token[i] = to_string(value);
                              }else if(key.find("lgamma") != string::npos) {
                                   value = calculate.lgamma_(value);
                                   srv_string_token[i] = to_string(value);
                              }

                              // add your keyword here

                         }
                    }    
               }

               // get the number of intiger and operator in the srv_string_token
               for(size_t i = 0; i < srv_string_token.size(); i++) {
                    if(isdigit(srv_string_token[i][0])) {
                         srv_deque.push_back(stod(srv_string_token[i]));
                         size_of_number++; // increment if a number
                    } else {
                         client_sen_operator.push_back(srv_string_token[i]); // push back operator to client_sen_operator
                    increment++; // increment if operator 
                    }
               }
               
               // if size of number (n-1) is equal to the size of operator
               if((size_of_number - 1) ==  increment || size_of_number ==  1 ){
                    //(n-1)  is equal to the size of operator
                    //get the number of operation done in the array 

                    // check if size of number is 0
                    if(size_of_number ==  1) {
                         // send to client  
                         string  one_ans =  to_string(srv_deque[0]);
                         byte_send =  send(new_srv_socket,  one_ans.c_str(),  250,  0);
                         if(byte_send == 0) error("ERROR  IN SENDING TO SERVER");
                    }else{

                         for(size_t i = 0; i < Num_Operation; i++) {
                              array[i] =  srv_deque[i];
                         } 

                         // operation array sequence in 2 array size , as they are passed to the caluclate class to evaluate with the operator
                         for(size_t i  = 0; i  <  client_sen_operator.size() ;  i++ ){
                              // if operator is + , - , * , /
                              rule.__rule__set(array, client_sen_operator[i], &result);

                              // removing the 2 first elements in the srv_dwque 
                              srv_deque.pop_front();
                              srv_deque.pop_front();
                              // add the result in the srv_deque
                              srv_deque.push_front(result);

                              if(srv_deque.size() == 1) {
                                   break;
                              }

                              // update the array operation with a new  variable
                              /* the date in the array get modefiel and would need to update our data from the array operation */

                              array[0] =  result;
                              for(int i = 1; i < Num_Operation; i++) {
                                   array[i] = srv_deque[i];
                              }

                         }  

                         ans =  rule.get_result();

                         // send the message back to the client

                         byte_send =  send(new_srv_socket, ans.c_str(),  250,  0);

                         if(byte_send == 0) error("ERROR  IN SENDING TO SERVER");
                    }

               }else{
                    byte_send =  send(new_srv_socket,  math_erro,  strlen(math_erro),  0);

                    // check if the client recieved successfully
                    if(byte_send <  0) error("ERROR IN SENDING TO CLIENT");
               }  
          }
          
          // clear the deque and vector for next iteration
          srv_deque.clear();
          srv_string_token.clear();
          client_sen_operator.clear();
          srv_strings.clear();
          srv_streem.str("");
          srv_streem.clear();
          ans.clear();
          increment = 0;
          size_of_number = 0;
          result = 0; 
          memset(user_recv, 0, 266);

     }

     // Close the socket
     close(new_srv_socket);
     close(srv_socket);
     return 0;
}