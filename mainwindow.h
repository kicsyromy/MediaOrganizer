#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>

class MainWindow: public wxFrame
{
public:
    enum
    {
        ID_HELLO = 1
    };

public:
    MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    wxDECLARE_EVENT_TABLE();
};

#endif // MAINWINDOW_H
