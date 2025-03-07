#ifndef CANVAS
#define CANVAS

#include "defaults.h"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "SettingsSingleton.h"


class CanvasFrame : public wxFrame {
public:
	void Redraw();

	CanvasFrame();
private:
		void OnExit(wxCloseEvent& event);
		wxBitmap bitmap;
		wxStaticBitmap* staticBitmap = new wxStaticBitmap(this, ID_Bitmap, bitmap);
		SettingsSingleton& Settings = SettingsSingleton::getInstance();

;

};



#endif