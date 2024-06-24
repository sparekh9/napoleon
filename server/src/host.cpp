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

std::string GetUsername(std::shared_ptr<Game> game, int clientSocket) {
  char username[80];
  while (true) {

    char buffer[1024];
    int read = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[read] = '\0';

    // std::cout << "Msg rec : " << buffer << "\n";
    sscanf(buffer, "1|%[^|\n]", username);
    // std::cout << "Parsed usr: " << username << "\n";
    
    if (game->ValidUsr(username)) {
      std::cout << "Username accepted \n";
      break;
    } 
    else {
      char conf[1024] = {'\0'};
      sprintf(conf, "1|0");
      send(clientSocket, conf, strlen(conf), 0);
      memset(username, 0, strlen(username));
    }
  }
  return username;
}

void serveClient(int clientSocket) {
  char buffer[1024] = {'\0'}; 
  int buff_read = recv(clientSocket, buffer, sizeof(buffer), 0);
  buffer[buff_read] = '\0';
  // std::cout << "" << "Message from client: " << buffer 
  //           << std::endl;
  char username[80];
  char code[8];
  sscanf(buffer, "1|%[^|\n]", code);
  // std::cout << "Username: " << username << "\n";
  // std::cout << "Code: " << code << "\n";
  
  // Creating new game
  if (games.find(code) == games.end()) {
    std::cout << "Initializing new game...\n";
    char req_n[1024] = {'\0'};
    sprintf(req_n, "1|");
    send(clientSocket, req_n, strlen(req_n), 0);

    std::shared_ptr<Game> new_game = std::make_shared<Game>(Game(code));
    games.insert(std::make_pair(code, new_game));
    

    memset(buffer, 0, strlen(buffer));
    buff_read = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[buff_read] = '\0';
    int tgt; sscanf(buffer, "%d", &tgt);
    new_game->SetTarget(tgt);

    std::string username = GetUsername(new_game, clientSocket);

    Player player = Player(clientSocket, username);
    new_game->AddPlayer(player);
  }
  else {
    char req_n[1024] = {'\0'};
    sprintf(req_n, "2|");
    send(clientSocket, req_n, strlen(req_n), 0);

    std::shared_ptr<Game> game = games[code];

    std::string username = GetUsername(game, clientSocket);
    Player new_player = Player(clientSocket, username);
    game->AddPlayer(new_player);

    if(game->Ready()) {
      game->Init();
      game->Run();
    }
  }
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