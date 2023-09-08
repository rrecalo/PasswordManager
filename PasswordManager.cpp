//
//  StorageManager.cpp
//  PasswordManager
//
//  Created by Robert Recalo on 8/24/23.
//

#include <wx/wx.h>
#include <iostream>
#include <fstream>
#include "PasswordListWindow.hpp"
//#include "Account.cpp"
//#include <bcrypt/BCrypt.hpp>
#include "EncryptionManager.cpp"


class PasswordManager {
    
public:
    static bool storePasswordList(std::vector<Account> accList){
        using namespace std;
        remove("list.dat");
        fstream new_file;
        new_file.open("list.dat", ios::out);
        if(!new_file){
            cout << "File creation Failed";
            new_file.close();
            return false;
        }
        else{
            for (size_t i = 0; i < accList.size(); ++i) {
                new_file << accList[i].Serialize() << "\n";
                //std::cout << accList[i].toString() << " " << std::endl;
            }
            
            new_file.close();
            return true;
        }
        
        return true;
    }
    
    static std::vector<Account> retrievePasswordList(){
        using namespace std;
        vector<Account> accounts;
            ifstream file("list.dat");

            if (!file.is_open()) {
                throw runtime_error("Failed to open file for reading.");
            }

            string line;
            while (getline(file, line)) {
                accounts.push_back(Account::Deserialize(line));
            }

            file.close();
            return accounts;
//            for (size_t i = 0; i < accounts.size(); ++i) {
//                cout << accounts[i].toString() << "\n";
//
//                //std::cout << accList[i].toString() << " " << std::endl;
//            }
//        return true;
    }
    
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
        
        return (password == sLine);
    };
};
