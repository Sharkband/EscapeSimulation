#include "defs.h"

//Purpose: to set up the client and receive messages and print out the received message to the terminal
//parameter: ip is an in paramter to set up the server socket with the given ip
//no return value
void viewEscape(char *ip){

 int clientSocket;
 setupClientSocket(&clientSocket, ip);

 char buffer[MAX_BUFF];

 while(1){

  if(buffer[strlen(buffer)-2]=='t'){
   break;
  }

  rcvData(clientSocket, buffer);

  printf("%s", buffer);

 }

 close(clientSocket);

}


