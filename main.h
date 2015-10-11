#ifndef MAINAPP_H
#define MAINAPP_H

#include <wx/wx.h>

class Main: public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(Main);

#endif // MAINAPP_H
