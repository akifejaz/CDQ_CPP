// Client side C/C++ program to demonstrate Socket
// programming
#include "inc/api.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

char *input;
using namespace std;
int parseJsonFile(json d);

/*
    updateDatabase
    searchDatabase
    deleteFromDatabase
    displayDatabase
    addToDatabase

*/

json data ;

int main(int argc, char const* argv[])
{   
    if(argc!=11){
        cout<<"Usage: ./CQD_DB -u <username> -p <password> -ip <ip> -po <port> -f <function>"<<endl;
        return 0;
    }

    for(int i=1; i<argc; i++){
        //cout<<"Here\n";
        if(strcmp(argv[i], "-u")==0){
            
            data["Input"]["userName"] = argv[i+1];
            i++;
            //cout<<argv[i];
        }
        else if(strcmp(argv[i], "-p")==0){
            data["Input"]["userPass"] = argv[i+1];
            i++;
            //cout<<argv[i];
        }
        else if(strcmp(argv[i], "-ip")==0){
            data["Input"]["ip"] = argv[i+1];
            i++;
            //cout<<argv[i];
        }
        else if(strcmp(argv[i], "-po")==0){
            data["Input"]["port"] = argv[i+1];
            i++;
            //cout<<argv[i];
        }
        else if(strcmp(argv[i], "-f")==0){
            data["Input"]["fun"] = argv[i+1];
            i++;
            //cout<<argv[i];
        }    
    }

	if(connection()==-1){return 0;}
    int sizeOfArr = parseJsonFile(data);
    send(sock, input, sizeOfArr,0);
	printf("--- Json Request Sent --- \n");

    char response[1024];
    read(sock, response, 1024);
    std::cout << std::setw(4) << response << std::endl;
    printf("--- Json Response Received --- \n");
	// closing the connected socket
	close(client_fd);
	return 0;
}

int parseJsonFile(json data){

    //data = json::parse(arr);
    std::string s = data.dump();
    
    input = new char[s.length()];
    strcpy(input, s.c_str());

    return s.length() + 1;
}