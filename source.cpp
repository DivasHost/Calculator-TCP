#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <netdb.h>
#include <typeinfo>
#include <vector>
#include <iomanip>
#include <iomanip>
#include <sstream>

#define Num_Keyword 20 // number of keyword should be change if neccesary

using namespace std;

/* 
    Client section :  client connext to the server to send requests to the server in form of string and message it out to the cleint screen
*/

void error(const char* message){
    perror(message);
    exit(1);
}


bool isFloat(const string &input) {
    try {
        stod(input); // Try converting to floating-point
        return true;
    } catch (...) {
        return false;
    }
}

int main(int argc, char* argv[]) {
        // Your code here

        /*Make sure that the user set the criteria for connectin to serverr*/
    if(argc < 3){
            fprintf(stderr,  "Failuere in putting the complete criteria for connection\n");
            exit(1);
    }

    /*Declaration*/
    int client_socket;
    int num__of_index;
    int  byte_sent ,  byte_received;
    char client_[256], client_send[256];
    char* client_recv[Num_Keyword];
    struct sockaddr_in client;
    struct  hostent *host;
    socklen_t  addrlen;

    /*Create a socket for the client and check if it's created successfully*/
    client_socket  =  socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket <  0)  {
            error("Error opening socket");  
    }

    int port_no  =  atoi(argv[2]);
    host = gethostbyname(argv[1]);

    if(host == NULL) {
        fprintf(stderr, "Error, no such host\n");
        exit(0);
    }

    /*clearing any value in client*/
    memset(&client,  0, sizeof(char));

    /*Initialize  value to client*/
    client.sin_family  = AF_INET;

    /*copying the value in sin_addr.s_addr  to the h_addr */
    bcopy((char *) host->h_addr,  (char *) &client.sin_addr.s_addr, sizeof(client));
    client.sin_port  = htons(port_no);

    /*Connect to the server*/
    if(connect(client_socket,  (struct sockaddr *)&client, sizeof(client)) <  0) {
        error("Failed to connect to server");
    }else {
        cout << "Connected to server: " <<  endl;
        
    }

    cout << "\n\n" << setw(50) <<  "CALCULATOR" << endl;
    
    /*Client is in operation wtih server*/
    while (true)
    {
        /* code */
        memset(client_send, 0, 256);
        cout  <<  "\n<<<<<  :  ";
        fgets(client_send, 255, stdin);

        /*Send message to the server*/
        byte_sent = send(client_socket, client_send, strlen(client_send), 0);

        if(byte_sent  <  0 ) error("ERROR IN SENDING TO SERVER");

        // set all memory to zero
        memset(client_, 0, 256);
        // get the data in form of an array
        
        byte_received = recv(client_socket, client_, 255, 0);
        
        if(byte_received < 0) error("ERROR IN RECEIVING FROM SERVER");

        // check if it is a special message
        string message = client_;
        vector<string> tokens;
        if(isFloat(message)){
            cout << "\n>>>>>  :  " << client_ << endl;
        }else  {
            // split the meesage 
            if(message.find("Math Error") !=  string::npos){
                cout << "\n>>>>>  :  " << client_ << endl;
            }else {
                string str;
                stringstream cliv_stream(message);
                while(getline(cliv_stream, str, '|')){
                    tokens.push_back(str);
                }
                
                // display to the client list of special 
                cout << "\n>>>>> : " ;
                ssize_t comma_ctrl =  1;
                ssize_t index =  0;
                for(int i = 1; i < tokens.size() - 1; i+=2) {
                    if(i == tokens.size() - 2) {
                        cout << "[ " <<  i <<"." << tokens[i] << " ]" << "\n";
                        break;
                    }

                    if(i  < tokens.size() - 1) {
                        cout << "[ " << (i)  <<"." << tokens[i] << " , " << (i + 1) <<"." <<  tokens[i + 1] << " ]" << "\n" << setw(10);
                    }
                }



                // recv from client
                memset(client_, 0, 256);
                cout  <<  "\n<<<<< [INDEX]  :  ";
                fgets(client_send, 255, stdin);

                byte_sent = send(client_socket, client_send, strlen(client_send), 0);
                if(byte_sent  <  0 ) error("ERROR IN SENDING TO SERVER");

                // recv from server
                byte_received = recv(client_socket, client_, 255, 0);
                if(byte_received < 0) error("ERROR IN RECEIVING FROM SERVER");


                // check if the string contains not a number or this feature underdevelopment

                string restrict  =  client_;
                if(restrict.find("Out of option")  !=  string::npos|| restrict.find("This feature is under development") !=  string::npos ||  restrict.find("Not a number") != string::npos){
                    cout << "\n>>>>> :  " << client_ << endl;
                }else  {
                    // recv from client
                    memset(client_,  0, sizeof(client_));
                    cout  <<  "\n<<<<< " << "[Operation] :  ";
                    fgets(client_send, 255, stdin);

                    // send to server 
                    byte_sent = send(client_socket, client_send, strlen(client_send), 0);
                    if(byte_sent  <  0 ) error("ERROR IN SENDING TO SERVER");

                    // recv from server
                    byte_received = recv(client_socket, client_, 255, 0);
                    if(byte_received < 0) error("ERROR IN RECEIVING FROM SERVER");

                    cout << "\n>>>>> :  " << client_ << endl;
                }
            }
        }
    }

    close(client_socket);
    return 0;
}