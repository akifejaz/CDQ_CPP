// Server side C/C++ program to demonstrate Socket
// programming

#include "inc/server.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void userFunctions(char *);
void parseUserArguemnts(json &data);
void userLogin(string ="", string ="", string ="", string ="");
void parseFuncArguments(json &data);
void functionChoice(string ="NAN");
void performFunction(json &data);
json parseToJson(char *);
void loginFailedDetails();
int parseJsonToText(json &response);

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

int main(int argc, char const* argv[])
{	
	cout << "Welcome to the Employee Management System" << endl;

	if(connection()==-1){ 
		response["Response"]["ConnectionFailedServer"] = "true";
		return 0; 
	}
	response["response"]["ConnectionEstablish"] = "true";
	json data;

	while(true){
		if(f == ForceExit){
			//loginFailedDetails();
			response["response"]["ProgramExit"] = "true";
			cout << "Thank you for using our system ! " << endl;
            return 0;
		}
		else {
			valread = read(new_socket, buffer, 1024);
			data = parseToJson(buffer);

			parseUserArguemnts(data);
			userLogin(userDetails.userName, userDetails.userPass, userDetails.ip, userDetails.port);
			if(f == ForceExit){
				response["response"]["UserNameOrPassIncorrect"] = "true";
				cout<<"Thank you for using our system ! ";
				return 0;}

			parseFuncArguments(data);
			performFunction(data);
			
			int s = parseJsonToText(response);
			//cout<<output;
			
			send(new_socket, output, s, 0);
			
			f = ForceExit;
		}
	}
	
	// closing the connected socket
	close(new_socket);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
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
	
	if(fun == updateDatabase){
		//updateDatabase(arr);
		//cout << "updateDatabase Called " <<endl;
		response["response"]["updateFunction"] = "Called";
	}
	else if(fun == searchDatabase){
		//searchDatabase(arr);
		//cout << "searchDatabase Called "<<endl;
		response["response"]["searchFunction"] = "Called";
	}
	else if(fun == deleteFromDatabase){
		//deleteFromDatabase(arr);
		//cout << "deleteFromDatabase Called "<<endl;
		response["response"]["deleteFunction"] = "Called";
	}
	else if(fun == displayDatabase){
		//displayDatabase(arr);
		// cout << "displayDatabase Called "<<endl;
		// c_db.displayDatabase();
		response["response"]["displayFunction"] = "Called";
	}
	else if(fun == addToDatabase){
		//cout << "addToDatabase Called "<<endl;
	}
	else{
		f = ForceExit;
		//cout << "Error Performing Function : Try Again " << endl;
		response["response"]["InvalidFunction"] = "Error";
	}

	
}

json parseToJson(char *arr){
    json data;
	
	data = json::parse(arr);
	return data;
}


void loginFailedDetails(){

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

int parseJsonToText(json &data){

	
	std::string s = data.dump();
    
    output = new char[s.length()];
    strcpy(output, s.c_str());

    return s.length() + 1;
}