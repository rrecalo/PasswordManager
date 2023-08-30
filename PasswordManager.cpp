//
//  StorageManager.cpp
//  PasswordManager
//
//  Created by Robert Recalo on 8/24/23.
//

#include <wx/wx.h>
#include <iostream>
#include <fstream>
//#include <bcrypt/BCrypt.hpp>
#include "EncryptionManager.cpp"


class PasswordManager {
    
public:
    static bool storeMasterPassword(wxString encryptedPassword){
        
        using namespace std;
        
        fstream new_file;
        new_file.open("master.dat", ios::out);
        if(!new_file){
            cout << "File creation Failed";
            new_file.close();
            return false;
        }
        else{
            new_file << encryptedPassword;
            //cout<< "New File created";
            new_file.close();
            return true;
        }
        
    };
    
    static bool masterPasswordExists(){
        
        using namespace std;
        fstream is;
        is.open("master.dat", ios::in);
        if(is)
        {
            //cout << "master.dat exists!" << endl;
            return true;
        }
        is.close();
        return false;
    };
    
    static bool compareMasterPassword(std::string password)
    {
        using namespace std;
        
        ifstream infile;

        string read_file_name("master.dat");

        infile.open(read_file_name);

        string sLine;

        while (!infile.eof())
        {
            infile >> sLine;
            cout << sLine.data() << endl;

        }

        infile.close();
        
        //sLine is read in from master.dat in its encrypted form!!!
        //cout << "existing password :: " << sLine << endl;
        //password entered is already encrypted!!!23
        //cout << "password entered :: " << password << endl;
        
        
        //cout << "existing password :: " << EncryptionManager::decrypt(sLine, "mykey") << endl;
        //is.close();
        return (password == sLine);
        //BCrypt::validatePassword("password", (std::string)password);
    };
};
