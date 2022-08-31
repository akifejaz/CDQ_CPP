#if !defined(MACRO_SERVER_H)
#define MACRO_SERVER_H
#include "database.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int connection();
void functionChoice(string str);


/* Variables For Connection Rec & Create */
#define PORT 8080
int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);

struct UserDetails{
	string userName;
	string userPass;
	string ip;
	string port;

}userDetails;

static char buffer[1024] = { 0 };
char * output;

json response = json::parse( R"(
    {
        "Response": {
            "ConnectionFailedServer": "",
            "ConnectionEstablish": "",
            "UserNameOrPassIncorrect":  "",
            "InvalidFunction": "",
            "displayFunction": "",
            "deleteFunction": "",
			"updateFunction" : ""
        }
    }
    )"
);
/* Variables For Connection Rec & Create */


//this function is for creating the connection b/w client and server
int connection(){
	
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))
		== 0) {
		perror("socket failed"); 
		exit(EXIT_FAILURE);
		return -1;
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
		return -1;
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
		return -1;
	}
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
		return -1;
	}
	if ((new_socket
		= accept(server_fd, (struct sockaddr*)&address,
				(socklen_t*)&addrlen))
		< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
		return -1;
	}

	return 0;
}


void parseUserArguemnts(json &data){

	//here we will parse the request that we received from the client
	//also perform certain actions based on the request
	//first of all parse the first 4 parameters : userName, userPass, ip, port & store then in struct

	userDetails.userName = data["Input"]["userName"];
	userDetails.userPass = data["Input"]["userPass"];
	userDetails.ip = data["Input"]["ip"];
	userDetails.port = data["Input"]["port"];

	// cout<<userDetails.userName;
	// cout<<userDetails.userPass;
	// cout<<userDetails.port;
	// cout<<userDetails.ip;
}

void userLogin(string username, string password, string ip, string port){

    if(username == "user" && password == "user" && ip == "localhost" && port == "8080"){
		f = user;
		l = loginSuccess;
		cout<<"User Loged In : "<<endl;
	}	
	else if(username == "admin" && password == "admin" && ip == "localhost" && port == "8080"){
		f = admin;
		l = loginSuccess;
		cout<<"Admin Loged In : "<<endl;
	}
	else{
		
		f = ForceExit;
		l = loginFailed;
		cout<<"Force Stop : Error Usrname Pass "<<endl;
	}		
}

void parseFuncArguments(json &data){

	//here we will parse the next arguments and store in the struct
	//nlohmann::json j = nlohmann::json::parse(arr);

	//cout<<data<<endl;
	string fun = data["Input"]["fun"];
	functionChoice(fun);
}

void functionChoice(string str){
	if(str == "updateDatabase"){
		fun = updateDatabase;
	}
	else if(str == "searchDatabase"){
		fun = searchDatabase;
	}
	else if(str == "deleteFromDatabase"){
		fun = deleteFromDatabase;
	}
	else if(str == "displayDatabase"){
		fun = displayDatabase;
	}
	else if(str == "addToDatabase"){
		fun = addToDatabase;
	}
	else{
		f = ForceExit;
		lfd = invalidFunction;
	}
}

void performFunction(json &data){
	
	//Note : Incomplete Function, Basically Here we will call the databse functions and performe oprations
	// as requested by client

	if(fun == updateDatabase){
	
		response["response"]["updateFunction"] = "Called";
	}
	else if(fun == searchDatabase){
		
		response["response"]["searchFunction"] = "Called";
	}
	else if(fun == deleteFromDatabase){

		response["response"]["deleteFunction"] = "Called";
	}
	else if(fun == displayDatabase){
		//displayDatabase(arr);
		// cout << "displayDatabase Called "<<endl;
		// c_db.displayDatabase();
		response["response"]["displayFunction"] = "Called";
	}
	else if(fun == addToDatabase){
		
	}
	else{
		f = ForceExit;
		response["response"]["InvalidFunction"] = "Error";
	}
}

json parseToJson(char *arr){  //converts text (char *) to Json object
    json data;
	
	data = json::parse(arr);
	return data;
}


void loginFailedDetails(){ //RC's Checker In case Failaer we will show error using this

    //enum lfd = {socketCreated, serverConnFailed, socketCreationFailed, userNameIncorrect, passwordIncorrect}; //flags for login
    if(lfd== serverConnFailed){
        cout<< "Server Conn Failed"<<endl;
    }
    else if(lfd==socketCreationFailed){
        cout<< "Socket Creation Failed"<<endl;
    }
    else if(lfd==userNameIncorrect){
        cout<< "Username Incorrect"<<endl;
    }
    else if(lfd==passwordIncorrect){
        cout<< "Password Incorrect"<<endl;
    }
}

int parseJsonToText(json &data){      //jason to char* 

	
	std::string s = data.dump();
    
    output = new char[s.length()];
    strcpy(output, s.c_str());

    return s.length() + 1;
}

#endif // MACRO


