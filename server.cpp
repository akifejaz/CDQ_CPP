// Server side C/C++ program to demonstrate Socket
// programming

#include "inc/server.h"

/* Function Declarations : Define in Header */
void userFunctions(char *);
void parseUserArguemnts(json &data);
void userLogin(string ="", string ="", string ="", string ="");
void parseFuncArguments(json &data);
void functionChoice(string ="NAN");
void performFunction(json &data);
json parseToJson(char *);
void loginFailedDetails();
int parseJsonToText(json &response);



int main(int argc, char const* argv[])
{	
	cout << "Welcome to the Employee Management System" << endl;

	if(connection()==-1){ 
		response["Response"]["ConnectionFailedServer"] = "true";
		return 0; 
	}
	response["response"]["ConnectionEstablish"] = "true";
	
	json data;   //for input request from client
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

			parseUserArguemnts(data); //this function gets the userName,Pass etc for login 
			userLogin(userDetails.userName, userDetails.userPass, userDetails.ip, userDetails.port);
			if(f == ForceExit){
				response["response"]["UserNameOrPassIncorrect"] = "true";
				cout<<"Thank you for using our system ! ";
				return 0;
				}

			parseFuncArguments(data); //this function extract the function user wants to performe
			performFunction(data);    //calls the functions of databse

			int s = parseJsonToText(response);  //generate response for client
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
