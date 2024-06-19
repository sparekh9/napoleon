#include <iostream> 
#include <string>
#include <cstring> 
#include <unordered_map>
#include <memory>
#include <mutex>
#include <thread>
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include "../include/game.h"

using namespace napoleon;

std::unordered_map<std::string, std::shared_ptr<Game>> games;

void serveClient(int clientSocket) {
  char buffer[1024] = {'\0'}; 
  recv(clientSocket, buffer, sizeof(buffer), 0); 
  std::cout << "" << "Message from client: " << buffer 
            << std::endl;
  char username[80];
  char code[8];
  sscanf(buffer, "1|%[^|\n]|%[^|\n]", username, code);
  // std::cout << "Username: " << username << "\n";
  // std::cout << "Code: " << code << "\n";
  
  //CODE NOT FOUND, Creating new game
  if (games.find(code) == games.end()) {
    std::cout << "Initialising new game...\n";
    char req_n[1024] = {'\0'};
    sprintf(req_n, "1|");
    send(clientSocket, req_n, strlen(req_n), 0);

    std::shared_ptr<Game> new_game = std::make_shared<Game>(Game());
    Player player = Player(clientSocket, username);
    games.insert(std::make_pair(code, new_game));

    memset(buffer, 0, strlen(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    int tgt; sscanf(buffer, "%d", &tgt);
    std::cout << "Waiting for " << tgt << " players...\n";

  }
  else {
    
  }


  std::cout << "Disconnecting from client.\n";
  close(clientSocket);
}

int main(int agrc, char ** argv){
    
  // creating socket 
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0); 

  // specifying the address 
  sockaddr_in serverAddress; 
  serverAddress.sin_family = AF_INET; 
  serverAddress.sin_port = htons(7072); 
  serverAddress.sin_addr.s_addr = INADDR_ANY; 

  // binding socket. 
  bind(serverSocket, (struct sockaddr*)&serverAddress, 
        sizeof(serverAddress)); 

  // listening to the assigned socket 
  listen(serverSocket, 5); 

  while (true) {
    // accepting connection request 
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    std::thread t1(serveClient, clientSocket);
    t1.detach();
  }
  

  return EXIT_SUCCESS;
}