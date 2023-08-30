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
    list->InsertColumn(0, "Account");
    list->InsertColumn(1, "Login");
    list->InsertColumn(2, "Hashed Password");
    list->InsertItem(0, "google.com");
    list->SetItem(0, 1, "websitelogin@email.com");
    list->SetItem(0, 2, "password12");
    
    list->SetColumnWidth(0, GetSize().GetWidth() * 0.5);
    list->SetColumnWidth(1, GetSize().GetWidth() * 0.5);
    //list->SetBackgroundColour(wxColour(200, 25, 25));
    
    //wxBoxSizer *passSizer = new wxBoxSizer(wxVERTICAL);
    
    


    
    
    //wxPanel *inputPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 100));
    wxBoxSizer *inputSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *accountSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *usernameSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *passwordSizer = new wxBoxSizer(wxVERTICAL);
    
    wxStaticText *accountInputLabel = new wxStaticText(this, wxID_ANY, "Account Type", wxDefaultPosition, wxSize(200, 25), wxALL , "");
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
    
    
    
    //std::cout << "login field : " << !loginField.empty() << "\n\n";
    
    if(!loginField.empty() && !passwordField.empty()){
//        char const *s = passwordField.c_str();
//        unsigned char *x;
//        unsigned i;
//        unsigned int l = gcry_md_get_algo_dlen(GCRY_MD_SHA256); /* get digest length (used later to print the result) */
//        gcry_md_hd_t h;
//        gcry_md_open(&h, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE); /* initialise the hash context */
//        gcry_md_write(h, s, strlen(s)); /* hash some text */
//        x = gcry_md_read(h, GCRY_MD_SHA256); /* get the result */
//
//        std::string hashedPass;
//        for (size_t i = 0; i < l; ++i) {
//            hashedPass += char("0123456789ABCDEF"[x[i] >> 4]);
//            hashedPass += char("0123456789ABCDEF"[x[i] & 0x0F]);
//        }

        // Clean up resources
        //gcry_md_close(sha256);
        std::string hashedPass = hashWithSHA256(passwordField);

        updatePasswordList(&accountField, &loginField, &hashedPass);
    }
    
    
};

void PasswordListWindow::updatePasswordList(std::string *account, std::string *login, std::string *pass){
    //std::cout << "pass : " << *pass << std::endl;
    list->InsertItem(0, *account);
    list->SetItem(0, 1, *login);
    list->SetItem(0, 2, *pass);
};

std::string PasswordListWindow::hashWithSHA256(const std::string &input) {
    // Initialize the libgcrypt library
    if (!gcry_check_version(GCRYPT_VERSION)) {
        std::cerr << "Libgcrypt version mismatch" << std::endl;
        return "";
    }

    // Initialize the SHA-256 algorithm
    gcry_md_hd_t sha256;
    if (gcry_md_open(&sha256, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE) != 0) {
        std::cerr << "SHA-256 initialization failed" << std::endl;
        return "";
    }

    // Feed the input data to the hash algorithm
    gcry_md_write(sha256, input.c_str(), input.length());

    // Finalize the hash computation
    const unsigned char *hashBytes = gcry_md_read(sha256, 0);
    const size_t hashSize = gcry_md_get_algo_dlen(GCRY_MD_SHA256);
    
    // Convert the hash bytes to a hexadecimal string
    std::string hashResult;
    for (size_t i = 0; i < hashSize; ++i) {
        hashResult += char("0123456789ABCDEF"[hashBytes[i] >> 4]);
        hashResult += char("0123456789ABCDEF"[hashBytes[i] & 0x0F]);
    }

    // Clean up resources
    gcry_md_close(sha256);

    return hashResult;
};
