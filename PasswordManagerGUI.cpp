// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include <string>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/splitter.h>
#include "PasswordManagerGUI.h"
#include "EncryptionManager.cpp"
#include "StorageManager.cpp"
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
    
    wxStaticText *text2 = new wxStaticText(this, 1, "It looks like you don't have a master password, please enter one below.", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    
    masterPassEntryBox = new wxTextCtrl(this, 1, "");
    masterPassEntryBox->SetMinSize(wxSize(300, 25));
    masterPassEntryBox->SetHint("Enter your master password here...");
    
    wxButton *submitButton = new wxButton(this, 2, "Submit Password", wxDefaultPosition, wxDefaultSize);
    submitButton->Fit();

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->SetMinSize(500, 300);

    sizer->Add(text, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    sizer->Add(text2, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    sizer->Add(masterPassEntryBox, 0.5, wxALIGN_CENTER | wxHORIZONTAL | wxBOTTOM, 10);
    sizer->Add(submitButton, 0, wxALIGN_CENTER | wxBOTTOM, 25);
    //sizer->Add(panel, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 50);
    this->SetSizerAndFit(sizer);

    
    
    
}


void MyFrame::onSubmitMasterPass(wxCommandEvent &commandEvent)
{
    //validate
    
    //encrypt
    auto encryptedPassword = EncryptionManager::encryptPassword(masterPassEntryBox->GetValue());
    
    //store
    //StorageManager::storePassword(encryptedPassword);
    using namespace std;
//
//    ofstream outstream("master.dat", ios::out);
//    if(!outstream)
//    {
//        cout << "Can't open file!" << endl;
//    }
//    outstream << encryptedPassword;
//    outstream.close();
//    if(!outstream.good())
//    {
//        cout << "Error writing!" << endl;
//    }
//
    //remove("master.dat");
    
    if(!ifstream("master.dat")){
        cout << "file does not exist!";
        ofstream outstream("master.dat", ios::out);
            if(!outstream)
            {
                cout << "Can't make file!" << endl;
            }
            else
            {
                cout << "File created!";
                outstream << encryptedPassword;
                outstream.close();
                if(!outstream.good())
                {
                    cout << "Error writing!" << endl;
                }
            }
    }
    else{
        cout << "File already exists, move to read!" << endl;
    }
    
    ifstream instream("master.dat", ios::in);
    if(!instream)
    {
        cout << "Can't open file!" << endl;
    }
    string a;
    getline(instream, a);
    cout << a;
    
    
    
    
    //instream.getline(string& s, char delim );
    
    
    
    

    //cleanup
    
    //std::cout << encryptedPassword;
    masterPassEntryBox->Clear();
    
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
