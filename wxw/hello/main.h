#ifndef MY_MAIN_H
#define MY_MAIN_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif

/* #include <iostream> */

/* Initialize program */
class MyApp : public wxApp {
  public:
	virtual bool OnInit();
};

/* Create window */
class MyFrame : public wxFrame {
  public:
	MyFrame(const wxString &, const wxPoint &, const wxSize &);

  private:
	void OnHello(wxCommandEvent &);
	void OnExit(wxCommandEvent &);
	void OnAbout(wxCommandEvent &);

	wxDECLARE_EVENT_TABLE();
};

enum { ID_Hello = 1 };

#endif
