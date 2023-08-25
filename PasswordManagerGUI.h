//
//  PasswordManagerGUI.h
//  PasswordManager
//
//  Created by Robert Recalo on 8/24/23.
//

#ifndef PasswordManagerGUI_h
#define PasswordManagerGUI_h
#pragma once


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
private:
    
    void onSubmitMasterPass(wxCommandEvent&);
    void onDebugButtonClicked(wxCommandEvent&);
    void signIn();
    bool validatePinInput();
    bool createdMasterPassword = false;
    bool signedIn = false;
    
    wxTextCtrl* masterPassEntryBox;
    wxStaticText *signInPrompt;
    wxButton *submitButton;
    wxBoxSizer *sizer;
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(2, MyFrame::onSubmitMasterPass)
EVT_BUTTON(3, MyFrame::onDebugButtonClicked)
wxEND_EVENT_TABLE()

#endif /* PasswordManagerGUI_h */
