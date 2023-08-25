//
//  PasswordManagerGUI.h
//  PasswordManager
//
//  Created by Robert Recalo on 8/24/23.
//

#ifndef PasswordManagerGUI_h
#define PasswordManagerGUI_h


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
private:
    
    void onSubmitMasterPass(wxCommandEvent&);
    
    
    wxTextCtrl* masterPassEntryBox;
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(2, MyFrame::onSubmitMasterPass)
wxEND_EVENT_TABLE()

#endif /* PasswordManagerGUI_h */
