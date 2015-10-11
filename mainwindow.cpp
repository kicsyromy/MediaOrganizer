#include "mainwindow.h"

#include <wx/listctrl.h>
#include "separator.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
//    EVT_MENU(MainWindow::ID_HELLO,  MainWindow::onHello)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxBoxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);
    Separator *sep = new Separator(this, wxALL);

    wxSizerFlags buttonFlags(1);
    buttonFlags.Expand().Center().Border(wxALL, 5);

    topSizer->Add(new wxButton(this, wxID_OK, "hello"), buttonFlags);
    topSizer->Add(sep, 0, wxALIGN_CENTER_VERTICAL, 0);
    topSizer->Add(new wxButton(this, wxID_OK, "there"), buttonFlags);

    SetSizer(topSizer);
}
