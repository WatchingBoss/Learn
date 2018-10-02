#include "main.h"

bool MyApp::OnInit() {
	MyFrame *frame =
	    new MyFrame("This is title", wxPoint(50, 50), wxSize(640, 480));
	frame->Show(true);
	return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size) {
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
	                 "Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	CreateStatusBar();
	SetStatusText("This is status text");
}

void MyFrame::OnExit(wxCommandEvent &event) { Close(true); }

void MyFrame::OnAbout(wxCommandEvent &event) {
	wxMessageBox("This my first attempt of wxWidgets", "About this program",
	             wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &event){
	wxLogMessage("This is reaction on 'OnHello' event");
}
