#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 

// void SendConfirmation(int clientSocket) {
//   const char *msg = "RECIEVED";
//   send(clientSocket, msg, strlen(msg), 0);
// }

void GetUsername(int clientSocket) {
  while (true) {
    std::cout << "Please enter a username:\n";
    std::string username;
    std::cin >> username;

    char msg[1024] = {'\0'};
    sprintf(msg, "1|%s", username.c_str());
    // std::cout << "Sending " << msg << "\n\n\n";
    send(clientSocket, msg, strlen(msg), 0);

    char conf[1024];
    int read = recv(clientSocket, conf, sizeof(conf), 0);
    conf[read] = '\0';
    // std::cout << "Message received " << conf << "\n";
    int status = -1;
    sscanf(conf, "%d|", &status);
    if (status == 2) {
      char msg[1024];
      sscanf(conf, "2|%[^|]", &msg);
      puts(msg);
      puts("-----------------------------------");
      break;
    }
    else {
      std::cout << "Username already in use or not appropriate.\n";
    }
  }
}

void RunGame(int clientSocket) {
  while (true) {
    char buffer[1024] = {'\0'}; 
    int buff_read = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[buff_read] = '\0';
    // std::cout << "" << "Message from client: " << buffer 
    //         << std::endl;
    int msg_type;
    sscanf(buffer, "%d|", &msg_type);
    // std::cout << "Msg Type : " << msg_type << "\n";
    switch (msg_type)
    {
    case 2: {
      char msg[1024];
      sscanf(buffer, "2|%[^|]", &msg);
      puts(msg);
      puts("-----------------------------------");
      break;
    }
    case 3: {

      break;
    }
    
    default:
      break;
    }
  }
}

int main(int agrc, char ** argv){

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
    fprintf(stderr, "Could not connect to server, exiting...\n");
    return EXIT_FAILURE;
  } 

  char intro[1024] = {'\0'};
  sprintf(intro, "1|%s", code.c_str());
  send(clientSocket, intro, strlen(intro), 0);
  
  char buffer[1024] = {'\0'}; 
  int buff_read = recv(clientSocket, buffer, sizeof(buffer), 0); 
  buffer[buff_read] = '\0';

  int pos;
  sscanf(buffer, "%d|", &pos);
  // SendConfirmation();
  if (pos == 1) {
    std::cout << "Creating new game (CODE: " << code << ")\n";
    std::cout << "How many players would you like to set the limit to (4-13):\n";
    int tgt; std::cin >> tgt;
    char tgt_send[1024] = {'\0'};
    sprintf(tgt_send, "%d", tgt);
    // std::cout << "Sending " << tgt_send << "\n";
    send(clientSocket, tgt_send, strlen(tgt_send), 0);
  }
  GetUsername(clientSocket);
  RunGame(clientSocket);

  // closing socket 
  close(clientSocket); 

  return EXIT_SUCCESS;
}