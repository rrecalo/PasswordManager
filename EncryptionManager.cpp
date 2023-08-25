//
//  Encryption.cpp
//  PasswordManager
//
//  Created by Robert Recalo on 8/24/23.
//
#include <wx/wx.h>

class EncryptionManager {

public:
    EncryptionManager(){};
    static wxString encryptPassword(wxString password)
    {
        return password + "encrypted!!";
    }

private:

    
};


