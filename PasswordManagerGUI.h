//
//  PasswordManagerGUI.h
//  PasswordManager
//
//  Created by Robert Recalo on 8/24/23.
//

#include "PasswordListWindow.hpp"

#ifndef PasswordManagerGUI_h
#define PasswordManagerGUI_h
#pragma once

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    void initLoginScreen();
    PasswordListWindow *passwordList;
private:
    
    void onSubmitMasterPin(wxCommandEvent&);
    void onDebugButtonClicked(wxCommandEvent&);

    void signIn();
    bool validatePinInput(std::string input);
    void createMasterPin(std::string input);
    void attemptSignIn(std::string input);
    void displayIncorrectPassword();
    void displayNewPinCreated();
    void displayInvalidInput();
    bool masterPinExists;
    bool signedIn = false;
    
    wxTextCtrl* masterPassEntryBox;
    wxStaticText *signInPrompt;
    wxButton *submitButton;
    wxBoxSizer *sizer;
    wxBoxSizer *passwordViewSizer;
    wxDECLARE_EVENT_TABLE();
};



#endif /* PasswordManagerGUI_h */
