#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
    private:
        std::string displayname;
        std::string userID;
    public:
        User();
        void setDisplayName();
        void sendMessage();
        std::string getDisplayName();
};

#endif