#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>  /* define socket */
#include <netinet/in.h>  /* define internet socket */
#include <netdb.h>       /* define internet socket */
using namespace std;
#define SERVER_PORT 8333     /* define a server port number */

int main(int argc, char* argv[]) {
  int sd;
  struct sockaddr_in server_addr = { AF_INET, htons(SERVER_PORT)};
  string test;
  char* buf;
  struct hostent *hp;

  if(argc != 2) {
    cout << "Usage: " << argv[0] << " hostname" << endl;
    exit(1);
  }

  // Get the host
  if((hp = gethostbyname(argv[1])) == NULL) {
    cout << argv[0] << ": " << argv[1] << " unknown host" << endl;
    exit(1);
  }

  bcopy(hp->h_addr_list[0], (char*)&server_addr.sin_addr, hp->h_length);

  // Create a socket
  if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    cout << "Client: Socket failed." << endl;
    exit(1);
  }

  if(connect(sd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    cout << "Client: Connect failed." << endl;
    exit(1);
  }

  cout << "connect() successful! Will send a message to server." << endl;
  cout << "Input a string: ";
  cin >> test;

  write(sd, const_cast<char*>(test.c_str()), sizeof(test));
  read(sd, const_cast<char*>(test.c_str()), sizeof(test));
  cout << "SERVER ECHOED: " << test << endl;

  close(sd);

  return 0;
}
