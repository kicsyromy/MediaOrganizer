#include "separator.h"

#include <iostream>

wxBEGIN_EVENT_TABLE(Separator, wxControl)
    EVT_MOUSE_EVENTS(Separator::onMouseDidShit)
wxEND_EVENT_TABLE()

Separator::Separator(wxWindow *parent, wxWindowID id) :
    wxControl(parent, id, wxDefaultPosition, wxSize(6, 10))
{
}

void Separator::onMouseDidShit(wxMouseEvent &event)
{
    std::cerr << "Mouse did shit!!! yeeeey\n";
}

