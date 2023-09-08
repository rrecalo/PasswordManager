//
//  PasswordListWindow.hpp
//  PasswordManager
//
//  Created by Robert Recalo on 8/26/23.
//

#ifndef PasswordListWindow_hpp
#define PasswordListWindow_hpp

#include <stdio.h>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/splitter.h>
#include "Account.cpp"
#endif /* PasswordListWindow_hpp */
#pragma once

class PasswordListWindow : public wxFrame
{
public:
    PasswordListWindow(const wxString &title, const wxPoint &pos, const wxSize &size);
    void init();
    void onSubmitNewAccount(wxCommandEvent&);
    std::string encryptString(const std::string& plaintext, const std::string& pin);
    std::string decryptString(const std::string& encrypted, const std::string& pin);
    void handleError(const char *message);
private:
    void loadList(std::vector<Account> accounts);
    void updatePasswordList(std::string* account, std::string* login, std::string* pass);
    
    
    wxBoxSizer *sizer;
    wxListView *list;
    wxButton *submit;
    
    wxTextCtrl *accountInputField;
    wxTextCtrl *loginInputField;
    wxTextCtrl *passwordInputField;
    wxDECLARE_EVENT_TABLE();
};
