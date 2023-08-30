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
#endif /* PasswordListWindow_hpp */
#pragma once

class PasswordListWindow : public wxFrame
{
public:
    PasswordListWindow(const wxString &title, const wxPoint &pos, const wxSize &size);
    void init();
    void onSubmitNewAccount(wxCommandEvent&);
private:
    
    void updatePasswordList(std::string* account, std::string* login, std::string* pass);
    //bool PasswordListWindow::onSubmitNewAccount(wxCommandEvent &commandEvent)
    wxBoxSizer *sizer;
    wxListView *list;
    wxButton *submit;
    
    wxTextCtrl *accountInputField;
    wxTextCtrl *loginInputField;
    wxTextCtrl *passwordInputField;
    wxDECLARE_EVENT_TABLE();
};
////
//wxBEGIN_EVENT_TABLE(PasswordListWindow, wxFrame)
//    EVT_BUTTON(56, PasswordListWindow::onSubmitNewAccount)
//wxEND_EVENT_TABLE()
