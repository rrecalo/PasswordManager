// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include <string>
#include <regex>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/splitter.h>
#include "PasswordManagerGUI.h"
#include "EncryptionManager.cpp"
#include "PasswordManager.cpp"
#include <fstream>
#include <iostream>
#include <cstdio>
#endif

class MyApp : public wxApp
{
    
public :
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);





bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Password Manager", wxDefaultPosition, wxDefaultSize);
    //frame->SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX));
    frame->Refresh();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) :
    wxFrame(nullptr, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    
    
//    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 200));
//    panel->SetBackgroundColour(wxColor(100, 100, 200));
    
    wxStaticText *text = new wxStaticText(this, -1, "Welcome to Password Manager!", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    //wxFont font = text->GetFont();
    //font.SetPointSize( 24 );
    //text->SetFont(font);
    text->SetFont(text->GetFont().Scale(1.5));
    
    signInPrompt = new wxStaticText(this, 1, "Please create a 4-digit master pin", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    
    masterPassEntryBox = new wxTextCtrl(this, 1, "");
    masterPassEntryBox->SetMinSize(wxSize(300, 25));
    masterPassEntryBox->SetHint("Enter your master pin here...");
    
    submitButton = new wxButton(this, 2, "Create Pin", wxDefaultPosition, wxDefaultSize);
    submitButton->Fit();
    
    wxButton *debugButton = new wxButton(this, 3, "DEBUG CLEAR PIN", wxDefaultPosition, wxDefaultSize);
    debugButton->Fit();

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->SetMinSize(500, 300);

    sizer->Add(text, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    sizer->Add(signInPrompt, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT |  wxTOP | wxBOTTOM, 10);
    sizer->Add(masterPassEntryBox, 0.5, wxALIGN_CENTER | wxHORIZONTAL | wxBOTTOM, 10);
    sizer->Add(submitButton, 0, wxALIGN_CENTER | wxBOTTOM, 25);
    sizer->Add(debugButton, 0, wxALIGN_CENTER | wxBOTTOM, 25);
    
    if(PasswordManager::masterPasswordExists())
    {
        signInPrompt->SetLabel(wxString("Please enter your master pin to sign in..."));
        
        //signInPrompt->Show(false);
        //masterPassEntryBox->Show(false);
        submitButton->SetLabel(wxString("Sign In"));
        
    }
    //sizer->Add(panel, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 50);
    this->SetSizerAndFit(sizer);

    
    
    
}


void MyFrame::onSubmitMasterPass(wxCommandEvent &commandEvent)
{
    
    auto encryptedPassword = EncryptionManager::encryptPassword(masterPassEntryBox->GetValue());
    
    using namespace std;
    //remove("master.dat");
    //return;
    //if master password exists, compare the hash
    if(validatePinInput()){
        if(PasswordManager::masterPasswordExists()){
            //if the master password matches, continue flow
            if(PasswordManager::compareMasterPassword(encryptedPassword))
            {
                cout << "Password Match!";
                signIn();
            }
            else
            {
                cout << "password does not match!";
            }
        }
        //if no master password exists
        else{
            
            //store the master password that was input;
            bool success = PasswordManager::storeMasterPassword(encryptedPassword);
            if(success){
                //cout << "new password stored!!!" << endl;
                cout << "new password: " << encryptedPassword << endl;
                submitButton->SetLabel(wxString("Sign In"));
                signInPrompt->SetLabel("Re-enter your 4-digit master pin to sign in.");
                sizer->Layout();
            }
            else{
                cout << "error storing the new password!!!";
            }
        }
    }
    else{
        masterPassEntryBox->SetHint("Please enter only digits 0-9, no spaces or special characters.");
        submitButton->SetLabel(wxString("Try Again"));
    }

    
    masterPassEntryBox->Clear();
    
}

bool MyFrame::validatePinInput(){
    using namespace std;
    string input = (string)masterPassEntryBox->GetValue();
    
    regex integer_expr("[[:digit:]][[:digit:]][[:digit:]][[:digit:]]");
    
    if(regex_match(input, integer_expr)){
        cout << "INPUT OK";
        return 1;
    }
    if(input.find(" ")){
        cout << "SPACE FOUND !!";
        return 0;
    }
    else return 0;
}

void MyFrame::signIn(){
    signInPrompt->SetLabel(wxString("SIGNED IN"));
    submitButton->Show(false);
    masterPassEntryBox->Show(false);
    sizer->Layout();
    
};

void MyFrame::onDebugButtonClicked(wxCommandEvent &commandEvent){
    remove("master.dat");
    signInPrompt->SetLabel(wxString("It looks like you don't have a master pin, please enter one below."));
    signInPrompt->Fit();
    masterPassEntryBox->Show(true);
    submitButton->SetLabel(wxString("Create Pin"));
    submitButton->Show(true);
    sizer->Layout();
    std::cout << "DEBUG -- DELETED 'master.dat' FILE" << std::endl;
    
}


/*
wxListView *list = new wxListView(this, wxID_ANY, wxDefaultPosition, wxSize(300, 200));
list->InsertColumn(0, "Name");
list->InsertItem(0, "Item");

wxButton *ok_button = new wxButton(this, wxID_ANY, "Ok");
wxButton *cancel_button = new wxButton(this, wxID_ANY, "Cancel");

wxBoxSizer *s1 = new wxBoxSizer(wxVERTICAL);
s1->Add(list, 1, wxEXPAND | wxALL, 5);

wxBoxSizer *s2 = new wxBoxSizer(wxHORIZONTAL);
s2->Add(ok_button, 0, wxRIGHT, 5);
s2->Add(cancel_button, 0);

s1->Add(s2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 5);

this->SetSizerAndFit(s1);
 */

/*
wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

wxSplitterWindow *right_splitter = new wxSplitterWindow(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

wxPanel *left = new wxPanel(splitter);
wxPanel *right = new wxPanel(right_splitter);
wxPanel *bottom = new wxPanel(right_splitter);

left->SetBackgroundColour(wxColor(200, 100, 100));
right->SetBackgroundColour(wxColor(100, 200, 100));
bottom->SetBackgroundColour(wxColor(200, 200, 100));

right_splitter->SetMinimumPaneSize(100);
right_splitter->SplitHorizontally(right, bottom);

//0, 0.5, 1);
//1 = top right resizes
//0 = bottom right resizes
//0.5 = equal resize rate
right_splitter->SetSashGravity(1);

splitter->SetMinimumPaneSize(200);

splitter->SplitVertically(left, right_splitter);
 */
