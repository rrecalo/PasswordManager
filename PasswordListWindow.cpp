//
//  PasswordListWindow.cpp
//  PasswordManager
//
//  Created by Robert Recalo on 8/26/23.
//

#include <wx/wxprec.h>
#include <string>
#include <sstream>
#include <wx/wx.h>
#include <wx/listctrl.h>
#ifndef WX_PRECOMP
#include "PasswordListWindow.hpp"
#include "PasswordManager.cpp"
#include <gcrypt.h>
//#include "PasswordManagerGUI.h"
#pragma once
#endif




wxBEGIN_EVENT_TABLE(PasswordListWindow, wxFrame)
    EVT_BUTTON(56, PasswordListWindow::onSubmitNewAccount)
wxEND_EVENT_TABLE()

PasswordListWindow::PasswordListWindow(const wxString &title, const wxPoint &pos, const wxSize &size) :
    wxFrame(nullptr, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{};

void PasswordListWindow::init(){
    sizer = new wxBoxSizer(wxVERTICAL);
    list = new wxListView(this, wxID_ANY, wxDefaultPosition, wxSize(680, 300));
    //list->SetSingleStyle(wxRESIZE_BORDER, false);
    //list->SetMaxSize(wxSize(500, 300));
    PasswordListWindow::loadList(PasswordManager::retrievePasswordList());
    
    list->SetColumnWidth(0, GetSize().GetWidth() * 0.5);
    list->SetColumnWidth(1, GetSize().GetWidth() * 0.5);
    
    
    //wxPanel *inputPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 100));
    wxBoxSizer *inputSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *accountSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *usernameSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *passwordSizer = new wxBoxSizer(wxVERTICAL);
    
    wxStaticText *accountInputLabel = new wxStaticText(this, wxID_ANY, "Account Domain", wxDefaultPosition, wxSize(200, 25), wxALL , "");
    accountInputField = new wxTextCtrl(this, 5, "", wxDefaultPosition, wxSize(200, 25));
    accountInputField->SetHint("What is this login used for...");
    accountInputField->Fit();
    
    wxStaticText *loginInputLabel = new wxStaticText(this, wxID_ANY, "Username", wxDefaultPosition, wxSize(200, 25), wxALL , "");
    loginInputField = new wxTextCtrl(this, 5, "", wxDefaultPosition, wxSize(200, 25));
    loginInputField->SetHint("Enter username here...");
    
    
    wxStaticText *passwordInputLabel = new wxStaticText(this, wxID_ANY, "Password", wxDefaultPosition, wxSize(200, 25), wxALL , "");
    passwordInputField = new wxTextCtrl(this, 6, "", wxDefaultPosition, wxSize(200, 25), wxTE_PASSWORD );
    passwordInputField->SetHint("Enter password here...");
    //passwordInputField->SetBackgroundColour(wxColor(200, 100, 100));
    //inputSizer->AddStretchSpacer();
    
    accountSizer->Add(accountInputLabel);
    accountSizer->Add(accountInputField);
    usernameSizer->Add(loginInputLabel);
    usernameSizer->Add(loginInputField);
    passwordSizer->Add(passwordInputLabel);
    passwordSizer->Add(passwordInputField);
    
    
    inputSizer->AddSpacer(20);
    inputSizer->Add(accountSizer, wxALIGN_CENTER_VERTICAL);
    inputSizer->AddSpacer(20);
    inputSizer->Add(usernameSizer, wxALIGN_CENTER_VERTICAL);
    inputSizer->AddSpacer(20);
    inputSizer->Add(passwordSizer, wxALIGN_CENTER_VERTICAL);
    inputSizer->AddSpacer(20);

    submit = new wxButton(this, 56, "Add Account", wxDefaultPosition, wxSize(150, 40));
    //submit->Fit();
    

    
    
    
    //inputSizer->AddStretchSpacer();
    sizer->Add(inputSizer, 1, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM | wxTOP, 10);
    sizer->Add(submit, 1, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM | wxTOP, 10);
    
    //sizer->Add(inputPanel);
    sizer->Add(list, 0);
    sizer->SetMinSize(500, 300);
    this->SetSizerAndFit(sizer);
};

void PasswordListWindow::onSubmitNewAccount(wxCommandEvent &commandEvent){
    
    std::string accountField = (std::string)accountInputField->GetValue();
    std::string loginField = (std::string)loginInputField->GetValue();
    std::string passwordField = (std::string)passwordInputField->GetValue();
    
    if(!loginField.empty() && !passwordField.empty()){
        
        std::string input = passwordField;
        std::string pin = "1234"; // Replace with your 4-digit PIN

        std::string encrypted = PasswordListWindow::encryptString(input, pin);
        //std::cout << "Encrypted: " << encrypted.size() << std::endl;


        std::string decrypted = PasswordListWindow::decryptString(encrypted, pin);

        if (decrypted.empty()) {
            //std::cerr << "Decryption failed." << std::endl;
        } else {
            //std::cout << "Decrypted: " << decrypted << std::endl;
        }

        std::string ps = "********";

        PasswordListWindow::updatePasswordList(&accountField, &loginField, &ps);
        
    }
    
    
};

// Function to encrypt a string using AES in CBC mode
std::string PasswordListWindow::encryptString(const std::string& input, const std::string& pin) {
    // Initialize the libgcrypt library
     if (!gcry_check_version(GCRYPT_VERSION)) {
         std::cerr << "libgcrypt version mismatch" << std::endl;
         exit(1);
     }

     gcry_cipher_hd_t handle;
     gcry_error_t error;

     // Define the encryption algorithm and mode (e.g., AES-256, CBC)
     const int key_length = 32; // AES-256 key length

     // Initialize the cipher handle
        
     error = gcry_cipher_open(&handle, GCRY_CIPHER_AES256, GCRY_CIPHER_MODE_CBC, 0);
     if (error) {
         std::cerr << "Failed to initialize cipher: " << gcry_strerror(error) << std::endl;
         exit(1);
     }

     // Set the encryption key (PIN)
     error = gcry_cipher_setkey(handle, pin.c_str(), key_length);
     if (error) {
         std::cerr << "Failed to set encryption key: " << gcry_strerror(error) << std::endl;
         gcry_cipher_close(handle);
         exit(1);
     }

     // Get the block length for the IV
     const size_t block_length = gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES256);
     if (block_length == 0) {
         std::cerr << "Failed to get block length" << std::endl;
         gcry_cipher_close(handle);
         exit(1);
     }

     // Generate an IV (Initialization Vector)
     unsigned char iv[block_length];
     gcry_create_nonce(iv, block_length);
     //gcry_randomize(iv, sizeof(iv), GCRY_STRONG_RANDOM);

    /** padding code start*/
    size_t padding_length = block_length - (input.size() % block_length);
    std::string padded = input;
    for (size_t i = 0; i < padding_length; ++i) {
        padded.push_back(static_cast<char>(padding_length));
    }
    /** padding code end*/
    
    std::string input2 = padded;
    // Allocate memory for the encrypted data (make sure it's a multiple of block_length)
    std::string encrypted(input2.size(), '\0');
    
    // Set the IV
    error = gcry_cipher_setiv(handle, iv, block_length);
    if (error) {
        std::cerr << "Failed to set IV: " << gcry_strerror(error) << std::endl;
        gcry_cipher_close(handle);
        exit(1);
    }

    // Encrypt the data
    error = gcry_cipher_encrypt(handle, reinterpret_cast<unsigned char*>(&encrypted[0]), encrypted.size(), input2.c_str(), input2.size());
    if (error) {
        std::cerr << "Failed to encrypt data: " << gcry_strerror(error) << std::endl;
        gcry_cipher_close(handle);
        exit(1);
    }

    // Cleanup and finalize
    gcry_cipher_close(handle);

    // Encode the IV and encrypted data as a Base64 string
    std::string result;
    result += std::string(reinterpret_cast<char*>(iv), block_length);
    result += encrypted;

    return result;
 }

std::string PasswordListWindow::decryptString(const std::string& encrypted, const std::string& pin) {
    // Initialize the libgcrypt library
    if (!gcry_check_version(GCRYPT_VERSION)) {
        std::cerr << "libgcrypt version mismatch" << std::endl;
        exit(1);
    }

    gcry_cipher_hd_t handle;
    gcry_error_t error;

    // Define the encryption algorithm and mode (e.g., AES-256, CBC)
    const int key_length = 32; // AES-256

    // Initialize the cipher handle
    error = gcry_cipher_open(&handle, GCRY_CIPHER_AES256, GCRY_CIPHER_MODE_CBC, 0);
    if (error) {
        std::cerr << "Failed to initialize cipher: " << gcry_strerror(error) << std::endl;
        exit(1);
    }

    // Set the encryption key (PIN)
    error = gcry_cipher_setkey(handle, pin.c_str(), key_length);
    if (error) {
        std::cerr << "Failed to set encryption key: " << gcry_strerror(error) << std::endl;
        gcry_cipher_close(handle);
        exit(1);
    }

    // Get the block length for the IV
    const size_t block_length = gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES256);
    if (block_length == 0) {
        std::cerr << "Failed to get block length" << std::endl;
        gcry_cipher_close(handle);
        exit(1);
    }

    if (encrypted.size() <= block_length) {
        std::cerr << "Invalid encrypted data" << std::endl;
        gcry_cipher_close(handle);
        exit(1);
    }

    // Extract the IV from the encrypted data
    unsigned char iv[block_length];
    std::memcpy(iv, encrypted.c_str(), block_length);

    // Allocate memory for the decrypted data
    std::string decrypted(encrypted.size() - block_length, '\0');

    // Set the IV
    error = gcry_cipher_setiv(handle, iv, block_length);
    if (error) {
        std::cerr << "Failed to set IV: " << gcry_strerror(error) << std::endl;
        gcry_cipher_close(handle);
        exit(1);
    }

    // Decrypt the data
    error = gcry_cipher_decrypt(handle, reinterpret_cast<unsigned char*>(&decrypted[0]), decrypted.size(), encrypted.c_str() + block_length, encrypted.size() - block_length);
    if (error) {
        std::cerr << "Failed to decrypt data: " << gcry_strerror(error) << std::endl;
        gcry_cipher_close(handle);
        exit(1);
    }

    // Cleanup and finalize
    gcry_cipher_close(handle);

    
    size_t pad_length = decrypted[decrypted.size() - 1];
    if (pad_length > decrypted.size()) {
        // Invalid padding
        return "";
    }
    return decrypted.substr(0, decrypted.size() - pad_length);
}

std::string pkcs7Unpad(const std::string& input) {
    size_t pad_length = input[input.size() - 1];
    if (pad_length > input.size()) {
        // Invalid padding
        return "";
    }
    return input.substr(0, input.size() - pad_length);
}

void PasswordListWindow::updatePasswordList(std::string *account, std::string *login, std::string *pass){
    //std::cout << "pass : " << *pass << std::endl;
    list->InsertItem(0, *account);
    list->SetItem(0, 1, *login);
    list->SetItem(0, 2, *pass);
    std::vector<Account> accounts;
    
    for(int i = 0; i < list->GetItemCount(); ++i){
        Account newAccount(std::string(list->GetItemText(i, 0)), std::string(list->GetItemText(i, 1)), std::string(list->GetItemText(i, 2)));
        accounts.push_back(newAccount);
    }
    PasswordManager::storePasswordList(accounts);
    
};

void PasswordListWindow::loadList(std::vector<Account> accounts){
    list->InsertColumn(0, "Domain");
    list->InsertColumn(1, "Login");
    list->InsertColumn(2, "Password");
    for(size_t i = 0; i < accounts.size(); ++i){
        list->InsertItem(0, accounts[i].domain);
        list->SetItem(0, 1, accounts[i].login);
        list->SetItem(0, 2, accounts[i].plaintextpass);
    }
}

void PasswordListWindow::handleError(const char *message) {
    std::cerr << "Error: " << message << std::endl;
    exit(1);
}
