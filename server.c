#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

// Function to compute (base^exp) % mod
int mod_pow(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        exp = exp >> 1;
        base = (base * base) % mod;
    }

    return result;
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Listen for incoming connections
    listen(serverSocket, 1);
    printf("Bob is waiting for Alice...\n");

    // Accept connection from Alice
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
    printf("Connection established with Alice.\n");

    // Generate server's private key
    int serverPrivateKey = 15; 
    int modulus = 23; // prime modulus p

    // Receive public key from Alice
    int alicePublicKey;
    recv(clientSocket, &alicePublicKey, sizeof(alicePublicKey), 0);
    printf("Received public key from Alice: %d\n", alicePublicKey);

    // Compute shared secret
    int sharedSecret = mod_pow(alicePublicKey, serverPrivateKey, 23);

    printf("Shared secret with Alice: %d\n", sharedSecret);

    // Close sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
