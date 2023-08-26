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

class PasswordListWindow : public wxFrame
{
public:
    PasswordListWindow(const wxString &title, const wxPoint &pos, const wxSize &size);
    void init();
private:
    
    wxBoxSizer *sizer;
    wxListView *list;
};

