#include "SFML/Network.hpp"
#include "SFML/Window.hpp"

#include <iostream>
#include <string>
#include <array>
#include <thread>
#include <chrono>

#include "user.h"

void sendMessage() {
    std::string input;
    std::cout << "You said: ";
    std::cin >> input;
}

void receieveMessage() {

}

int main() {

    std::cout << "### Starting ChatKokaClient" << std::endl;

    std::cout << "### Connecting to server" << std::endl;
    sf::TcpSocket client;

    while (client.connect("127.0.0.1", 42069) != sf::Socket::Status::Done) {
        std::cout << "!!! Retrying connection" << std::endl;
        client.connect("127.0.0.1", 42069);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    User primaryUser;
    primaryUser.setDisplayName();

    return 0;
}