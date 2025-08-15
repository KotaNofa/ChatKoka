#include "user.h"

User::User() {
    displayname = "";
    userID = "";
}

void User::setDisplayName() {
    std::cout << "--- Set a username" << std::endl;
    std::string input;
    std::cin >> input;
    std::cout << "### Username set" << std::endl;
}

std::string User::getDisplayName() {
    return displayname;
}