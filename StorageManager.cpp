//
//  StorageManager.cpp
//  PasswordManager
//
//  Created by Robert Recalo on 8/24/23.
//

#include "StorageManager.hpp"
#include <wx/wx.h>
#include<iostream>
#include <fstream>

class StorageManager {
    
public:
    static void storePassword(wxString encryptedPassword){
        using namespace std;
        fstream new_file;
        new_file.open("file.txt", ios::out);
        if(!new_file){
            cout<< "File creation Failed";
        }
        else{
            new_file<<encryptedPassword;
            cout<< "New File created";
            new_file.close();
        }
        
    };
};
