#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>
#include <array>
#include <thread>
#include <chrono>

#include "user.h"

class ClientEnv {
    private:
        sf::TcpSocket socket;
        std::string ip;
        int port;
        void ReceiveMessage();
    public:
        bool connectedToServer;
        User user;
        ClientEnv();
        void connectServer();
        void initNetworkStream();
};

ClientEnv::ClientEnv() {
    ip = "127.0.0.1";
    port = 42069; 
    bool connected = false;
}

void ClientEnv::connectServer() {
    std::cout << "### Starting ChatKokaClient" << std::endl;
    std::cout << "### Connecting to server" << std::endl;
    while (socket.connect(ip, port) != sf::Socket::Status::Done) {
        std::cout << "!!! Retrying connection" << std::endl;
        socket.connect(ip, port);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    connectedToServer = true;
}

void ClientEnv::initNetworkStream() {
    if (connectedToServer) {
        std::thread worker(&ClientEnv::ReceiveMessage, this);
        worker.detach();
    } else {
        std::cout << "!!! Stopped Network stream" << std::endl;
        return;
    }
}

void ClientEnv::ReceiveMessage() {
    while(connectedToServer) {
        sf::Packet chatPacket;
        socket.receive(chatPacket);
        std::string message;
        chatPacket >> message;
        std::cout << message << std::endl;
        chatPacket.clear();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "!!! Stopped receieving messages" << std::endl;
    }
    std::cout << "!!! Stopped receieving messages" << std::endl;
    return;
}

int main() {

    ClientEnv env;
    env.connectServer();
    env.initNetworkStream();
    env.user.setDisplayName();
    while(env.connectedToServer) {
        
    }
    std::cout << "!!! Closed" << std::endl;
    return 0;
}


/*
class inputHandler {
    private:
        

    public:
        void update();
};

void inputHandler::update() {

}*/