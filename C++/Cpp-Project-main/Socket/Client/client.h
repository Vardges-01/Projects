#include <iostream>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fstream>
#include <vector>
#include <string>

class client
{
private:
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

public:
    client(int arg1, char *arg2[]);
    void error(const char *msg);
    void menuClient();
    void Get();
    void Post();
    void Put();
    void Dell();

    ~client();
};

client::client(int arg1, char *arg2[])
{
    if (arg1 < 3)
    {
        std::cout << stderr << " usage hostname port\n"
                  << arg2[0];
        exit(0);
    }
    portno = atoi(arg2[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(arg2[1]);
    if (server == NULL)
    {
        std::cout << stderr << " ERROR, no such host\n";
        exit(0);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");
}

void client::menuClient()
{
    while (true)
    {
        std::cout << "$> ";
        bzero(buffer, 256);
        std::cin >> buffer;
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0)
            error("ERROR writing to socket");

        std::string comm = buffer;

        if (comm == "EXIT")
        {
            std::cout << "GOOD BYE :) " << std::endl;
            close(sockfd);
            return;
        }
        else if (comm == "Get")
        {
            Get();
        }
        else if (comm == "Post")
        {
            Post();
        }
        else if (comm == "Put")
        {
            Put();
        }
        else if (comm == "Dell")
        {
            Dell();
        }
        else
        {
            std::cout << "Command not found" << std::endl;
        }
    }
}

// Function Get
void client::Get()
{
    bzero(buffer, 256);
    std::cin >> buffer;
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");

    while (n > 0)
    {
        n = read(sockfd, buffer, 100);
        std::cout << buffer << std::endl;
        bzero(buffer, 100);
    }
}

// Function Post
void client::Post()
{
    char resultFile[30];
    bzero(buffer, 256);
    std::cin >> buffer;
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");

    n = read(sockfd, resultFile, 30);
    std::cout << resultFile << std::endl;
}

// Function Put
void client::Put()
{
    // std::cin.get();
    // bzero(buffer, 256);
    // std::cin >> buffer;
    // n = write(sockfd, buffer, strlen(buffer));
    // if (n < 0)
    //     error("ERROR writing to socket");

    // while (n > 0)
    // {
    //     std::cin.getline(buffer, 100);
    //     n = write(sockfd, buffer, 100);
    //     bzero(buffer, 100);
    //     std::cin.clear();
    // }
}

// Function Remove
void client::Dell()
{
    char resultFile[22];
    bzero(buffer, 256);
    std::cin >> buffer;
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");

    n = read(sockfd, resultFile, 30);
    std::cout << resultFile << std::endl;
}

// Error Messege
void client::error(const char *msg)
{
    perror(msg);
    exit(0);
}

client::~client()
{
}
