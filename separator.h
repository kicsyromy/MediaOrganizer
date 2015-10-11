#ifndef SEPARATOR_H
#define SEPARATOR_H

#include <wx/control.h>

class Separator: public wxControl
{
public:
    Separator(wxWindow *parent, wxWindowID id);

private:
    void onMouseDidShit(wxMouseEvent &event);

private:
    wxDECLARE_EVENT_TABLE();
};

#endif // SEPARATOR_H
