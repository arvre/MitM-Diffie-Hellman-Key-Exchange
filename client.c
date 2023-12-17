#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define SERVER_IP "127.0.0.1"

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
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(PORT);

    // Connect to Bob
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("Connected to Bob.\n");

    // Perform Diffie-Hellman key exchange
    int base = 2; // base g
    int modulus = 23; // prime modulus p

    int alicePrivateKey = 6; // private key a
    int alicePublicKey = (int)(mod_pow(base, alicePrivateKey, modulus));

    printf("Alice's public key: %d\n", alicePublicKey);

    // Send public key to Bob
    send(clientSocket, &alicePublicKey, sizeof(alicePublicKey), 0);

    // Close socket
    close(clientSocket);

    return 0;
}
