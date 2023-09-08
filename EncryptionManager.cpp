//
//  Encryption.cpp
//  PasswordManager
//
//  Created by Robert Recalo on 8/24/23.
//
#include <wx/wx.h>
#include <list>
//#include <bcrypt/BCrypt.hpp>
#pragma once



class EncryptionManager {

public:
    EncryptionManager(){};
    
    static std::string encryptPassword(wxString password)
    {
        using namespace std;

        
        std::string encryptedPass = encrypt((string)password, "mykey");
        
        return std::string(encryptedPass);
    }
    static std::string encrypt(std::string msg, std::string key)
    {
        // Make sure the key is at least as long as the message
        std::string tmp(key);
        while (key.size() < msg.size())
            key += tmp;
        
        // And now for the encryption part
        for (std::string::size_type i = 0; i < msg.size(); ++i)
            msg[i] ^= key[i];
        return msg;
    };

    // Rewritten to use const& on both parameters
    static std::string decrypt(std::string const& msg, std::string const& key)
    {
        return encrypt(msg, key); // lol
    };

private:

    
};





