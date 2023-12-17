#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define SERVER_IP "127.0.0.1"

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(PORT);

    // Connect to Bob as if Mallory is Alice
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("Connected to Bob as Alice (Mallory).\n");

    // Intercept and manipulate public key
    int interceptedPublicKey = 10; // replace with the manipulated value
    printf("Intercepted and manipulated public key sent to Bob: %d\n", interceptedPublicKey);

    // Send manipulated public key to Bob
    send(clientSocket, &interceptedPublicKey, sizeof(interceptedPublicKey), 0);

    // Close socket
    close(clientSocket);

    return 0;
}
