//
//  StorageManager.cpp
//  PasswordManager
//
//  Created by Robert Recalo on 8/24/23.
//

#include <wx/wx.h>
#include <iostream>
#include <fstream>

class PasswordManager {
    
public:
    static bool storeMasterPassword(wxString encryptedPassword){
        
        using namespace std;
        
        fstream new_file;
        new_file.open("master.dat", ios::out);
        if(!new_file){
            cout<< "File creation Failed";
            return false;
        }
        else{
            new_file<<encryptedPassword;
            //cout<< "New File created";
            new_file.close();
            return true;
        }
        
    };
    
    static bool masterPasswordExists(){
        
        using namespace std;
        
        if(fstream("master.dat"))
        {
            cout << "master.dat exists!" << endl;
            return true;
        }
        return false;
    };
    
    static void makeMasterPassword(wxString password){
        
    }
};
