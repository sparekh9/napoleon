#include <cstring> 
#include <iostream> 
#include <chrono>
#include <thread>
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <arpa/inet.h>

using namespace std::chrono_literals;
  
int main() 
{ 
    // creating socket 
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0); 
  
    // specifying address 
    sockaddr_in serverAddress; 
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(8080); 
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    // serverAddress.sin_addr.s_addr = inet_addr("10.0.0.242");
    
    std::cout << "Connecting to server\n";

    // sending connection request 
    connect(clientSocket, (struct sockaddr*)&serverAddress, 
            sizeof(serverAddress)); 
  
    // sending data 
    const char* message = "Hello, server!"; 
    send(clientSocket, message, strlen(message), 0); 

    std::this_thread::sleep_for(200ms);

    char buffer[1024] = { 0 }; 
    recv(clientSocket, buffer, sizeof(buffer), 0); 
    std::cout << "Message from client: " << buffer 
              << std::endl; 
  
    // closing socket 
    close(clientSocket); 
  
    return 0; 
}

