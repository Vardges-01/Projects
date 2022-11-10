#include <iostream>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fstream>
#include <vector>
#include <string>

class SokServer
{
private:
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    std::vector<std::string> fileNames;
    std::fstream fs;
    void setfiles();
    void uploadfiles();
    bool findFile();
    void error(const char *msg);

public:
    SokServer(int argc, char *argv[]);
    void myServ();
    void Get();  // Reade file
    void Post(); // Create file
    void Put();  // Uplade file
    void Dell(); // Delete file

    ~SokServer();
};

SokServer::SokServer(int arg1, char *arg2[])
{
    // Socket
    if (arg1 < 2)
    {
        std::cout << stderr << " ERROR, no port provided\n";
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(arg2[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *)&cli_addr,
                       &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");

    setfiles();
}

// Main Server
void SokServer::myServ()
{
    while (true)
    {
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 10);
        if (n < 0)
            error("ERROR reading from socket");
        std::cout << buffer << std::endl;
        std::string comm = buffer;

        if (comm == "EXIT")
        {
            std::cout << "GOOD BYE :) " << std::endl;
            uploadfiles();
            close(newsockfd);
            return;
        }
        else if (comm == "Get")
        {
            Get();
            std::cout << "Get" << std::endl;
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

// Set Files name in Vector
void SokServer::setfiles()
{
    std::string fnam;
    std::fstream fs("fileName.txt");
    while (std::getline(fs, fnam))
    {
        fileNames.push_back(fnam);
    }
}

// Find file
bool SokServer::findFile()
{
    if (std::find(fileNames.begin(), fileNames.end(), buffer) != fileNames.end())
    {
        return true;
    }
    return false;
}

// Function Upload file names
void SokServer::uploadfiles()
{
    std::ofstream of("fileName.txt");
    for (auto x : fileNames)
    {
        of << x << std::endl;
    }
    of.close();
}

// Error Messege
void SokServer::error(const char *msg)
{
    perror(msg);
    exit(1);
}

// Function Get
void SokServer::Get()
{
    char line[100];
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 10);
    std::ifstream fs(buffer);
    if (fs.is_open())
    {
        while (!fs.eof())
        {
            memset(line, 0, 100);
            fs.getline(line, 100);
            write(newsockfd, line, 100);
            std::cout << line << std::endl;
        }
    }
    else
        error("File not found");
    fs.close();
}

// Function Post
void SokServer::Post()
{
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 10);
    if (!findFile())
    {
        fileNames.push_back(buffer);
        std::ofstream of(buffer);
        of.close();
        write(newsockfd, "Your file has created", 22);
    }
    else
    {
        write(newsockfd, "Such a file already exists", 30);
    }
    fs.close();
}

// Function Put
void SokServer::Put()
{
    bzero(buffer, 256);
    n = read(newsockfd, buffer, strlen(buffer));
    std::fstream fs;
    if (findFile())
    {
        fs.open(buffer, std::fstream::app);
        while (n > 0)
        {
            char line[100];
            bzero(buffer, 256);
            n = read(newsockfd, buffer, 100);
            fs << buffer;
        }
        fs.close();
    }
}

// Function Dellete
void SokServer::Dell()
{
    bzero(buffer, 256);
    read(newsockfd, buffer, 10);
    auto it = std::find(fileNames.begin(), fileNames.end(), buffer);
    if (it != fileNames.end())
    {
        remove(buffer);
        fileNames.erase(it);
        uploadfiles();
        write(newsockfd, "Your file has Deleted", 22);
    }
    else
    {
        bzero(buffer, 256);
        n = write(newsockfd, "File not Found", 15);
        return;
    }
}

SokServer::~SokServer()
{
}
