#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 

// using namespace napoleon;

// void InitGame(ENetPeer* peer) {
//   puts("Welcome to Napoleon!\nPlease enter the number of players (2 - 13):");
//   int n; std::cin >> n;
//   char send_data[1024] = {'\0'};
//   sprintf(send_data, "1|%d", n);
//   SendPacket(peer, send_data);
// }
void RunGame(int clientSocket) {
  while (true) {
    char buffer[1024] = {'\0'}; 
    recv(clientSocket, buffer, sizeof(buffer), 0);
    int msg_type;
    sscanf(buffer, "%d|", &msg_type);
    switch (msg_type)
    {
    case 2: {
      char msg[1024];
      sscanf(buffer, "2|%[^|\n]", &msg);
      puts(msg);
      break;
    }
    
    default:
      break;
    }
  }
}

int main(int agrc, char ** argv){

  std::cout << "Please enter a username:\n";
  std::string username;
  std::cin >> username;

  std::cout << "Please enter a game code:\n";
  std::string code;
  std::cin >> code;
  
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0); 
  
  // specifying address 
  sockaddr_in serverAddress; 
  serverAddress.sin_family = AF_INET; 
  serverAddress.sin_port = htons(7072); 
  serverAddress.sin_addr.s_addr = INADDR_ANY; 

  // sending connection request 
  if (connect(clientSocket, (struct sockaddr*)&serverAddress, 
          sizeof(serverAddress)) < 0) {
    fprintf(stderr, "Could not connect to server, exiting...");
    return EXIT_FAILURE;
  } 

  char intro[1024] = {'\0'};
  sprintf(intro, "1|%s|%s", username.c_str(), code.c_str()); 
  send(clientSocket, intro, strlen(intro), 0);
  
  char buffer[1024] = {'\0'}; 
  recv(clientSocket, buffer, sizeof(buffer), 0); 
  int pos;
  sscanf(buffer, "%d|", &pos);
  if (pos == 1) {
    std::cout << "Creating new game (CODE: " << code << ")\n";
    std::cout << "How many players would you like to set the limit to (4-13):\n";
    int tgt; std::cin >> tgt;
    char tgt_send[1024] = {'\0'};
    sprintf(tgt_send, "%d", tgt);
    std::cout << "Sending " << tgt_send << "\n";
    send(clientSocket, tgt_send, strlen(tgt_send), 0);
    RunGame(clientSocket);
  }

  // closing socket 
  close(clientSocket); 

  return EXIT_SUCCESS;
}