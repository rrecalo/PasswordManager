//
//  PasswordListWindow.cpp
//  PasswordManager
//
//  Created by Robert Recalo on 8/26/23.
//

#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/splitter.h>
#include "PasswordListWindow.hpp"


PasswordListWindow::PasswordListWindow(const wxString &title, const wxPoint &pos, const wxSize &size) :
    wxFrame(nullptr, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
};

void PasswordListWindow::init(){
    list = new wxListView(this, wxID_ANY, wxDefaultPosition, wxSize(500, 300));
    list->InsertColumn(0, "Name");
    list->InsertItem(0, "Item");
    //wxBoxSizer *passSizer = new wxBoxSizer(wxVERTICAL);
    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->SetMinSize(500, 300);
    this->SetSizerAndFit(sizer);
}


