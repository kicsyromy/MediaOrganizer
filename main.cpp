#include "main.h"

#include "mainwindow.h"

// equivalent for int main(int argc, char *argv)
bool Main::OnInit()
{
    MainWindow *window= new MainWindow("Hello World", wxPoint(50, 50), wxSize(450, 340));
    window->Show(true);

    return true;
}

