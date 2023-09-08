//
//  Account.cpp
//  PasswordManager
//
//  Created by Robert Recalo on 9/8/23.
//

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>

class Account {
public:
    Account(std::string d, std::string l, std::string p){
        domain = d;
        login = l;
        plaintextpass = p;
    }

    // Serialize the object to a string
    std::string Serialize() const {
        std::stringstream ss;
        ss << domain << "," << login << "," << plaintextpass;
        return ss.str();
    }

    // Deserialize a string back into the object
    static Account Deserialize(const std::string& data) {
        std::stringstream ss(data);
        std::string domain, login, plaintextpass;
        //read from the stringstream but stop at the delimiter of ','
        getline(ss, domain, ',');
        getline(ss, login, ',');
        getline(ss, plaintextpass);
//        std::cout << "d : " << domain << " | ";
//        std::cout << "l : " << login << " | ";
//        std::cout << "p : " << plaintextpass << "\n";
        return Account(domain, login, plaintextpass);
    }
    
    std::string toString(){
        return domain + " | " + login + " | " + plaintextpass;
    }
    

    std::string domain;
    std::string login;
    std::string plaintextpass;
private:
    
};
