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
    MyFrame *frame;
};

wxIMPLEMENT_APP(MyApp);

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(2, MyFrame::onSubmitMasterPin)
EVT_BUTTON(3, MyFrame::onDebugButtonClicked)
EVT_BUTTON(56, PasswordListWindow::onSubmitNewAccount)
wxEND_EVENT_TABLE()




bool MyApp::OnInit()
{
    frame = new MyFrame("Password Manager", wxDefaultPosition, wxDefaultSize);
    frame->initLoginScreen();
    frame->Refresh();
    frame->Show(true);

    return true;
}


MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) :
    wxFrame(nullptr, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{}

void MyFrame::initLoginScreen(){
    wxStaticText *text = new wxStaticText(this, -1, "Welcome to Password Manager!", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
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
        submitButton->SetLabel(wxString("Sign In"));
        
    }
    this->SetSizerAndFit(sizer);
}


void MyFrame::onSubmitMasterPin(wxCommandEvent &commandEvent)
{
    using namespace std;
    
    //get the password input from the text control box
    string passwordInput = (string)masterPassEntryBox->GetValue();
    
    //first check input validity
    if(validatePinInput(passwordInput)){
        
        //if the input is valid, and the master pin already exists, try to sign in
        if(PasswordManager::masterPasswordExists()){
            //cout << "attempted sign in!";
            attemptSignIn(passwordInput);
        }
        
        //if the input is valid but the master pin does NOT exist, try to create a new master pin;
        else{
            createMasterPin(passwordInput);
        }
    }
    //if the input is invalid, update the GUI to inform the user...
    else{
        displayInvalidInput();
    }
    
    //always clear the input box, so the user knows that the button click did *something*
    if(masterPassEntryBox){
        //cout<< "box detected";
        masterPassEntryBox->Clear();
    }
}

void MyFrame::attemptSignIn(std::string input){
    
    std::string encryptedPassword = EncryptionManager::encryptPassword(input);
    if(PasswordManager::compareMasterPassword(encryptedPassword)){
        //std::cout << "password match";
        signIn();
    }
    else{
        displayIncorrectPassword();
    }
}


void MyFrame::createMasterPin(std::string input){
    
    std::string encryptedPassword = EncryptionManager::encryptPassword(input);
    bool success = PasswordManager::storeMasterPassword(encryptedPassword);
    if(success){
        //std::cout << "Created new master pin!";
        displayNewPinCreated();
    }
    else
        std::cout << "Error creating new master pin!";
}

void MyFrame::displayIncorrectPassword(){
    masterPassEntryBox->SetHint("Incorrect pin, try again");
    submitButton->SetLabel(wxString("Sign In"));
    signInPrompt->SetLabel(wxString("Please enter your master pin to sign in..."));
    sizer->Layout();
        
}

void MyFrame::displayInvalidInput(){
    masterPassEntryBox->SetHint("Please enter only digits 0-9, no spaces or special characters.");
    submitButton->SetLabel(wxString("Try Again"));
    if(PasswordManager::masterPasswordExists())
    {
        signInPrompt->SetLabel(wxString("Please enter your master pin to sign in..."));
        sizer->Layout();
    }
}
void MyFrame::displayNewPinCreated(){
    signInPrompt->SetLabel(wxString("Master pin successfully created! Re-enter it to sign in."));
    submitButton->SetLabel(wxString("Sign In"));
    sizer->Layout();
}

bool MyFrame::validatePinInput(std::string input){
    using namespace std;
    
    regex integer_expr("[[:digit:]][[:digit:]][[:digit:]][[:digit:]]");
    
    if(regex_match(input, integer_expr)){
        //cout << "INPUT OK";
        return 1;
    }
    if(input.find(" ")){
        //cout << "SPACE FOUND!!";
        return 0;
    }
    else return 0;
}

void MyFrame::signIn(){
    signInPrompt->SetLabel(wxString("SIGNED IN"));
    submitButton->Show(false);
    masterPassEntryBox->Show(false);
    sizer->Layout();
    
    signedIn = true;
    
    passwordList = new PasswordListWindow("Password List window", wxDefaultPosition, wxDefaultSize);
    passwordList->init();
    passwordList->Reparent(this->GetParent());
    passwordList->Show(true);
    this->Show(false);
    
    
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
