
#ifndef CONTROLS
#define CONTROLS


#include "defaults.h"

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


#include "SettingsSingleton.h"
#include "canvas.h"

class ControlsFrame : public wxFrame {
public:
	ControlsFrame(CanvasFrame* canvas);

private:
	const float scaleFactor = 100.0f;

	CanvasFrame* associatedCanvas;

	SettingsSingleton& Settings = SettingsSingleton::getInstance();

	wxSlider* sliderRealPart;
	wxTextCtrl* textCtrlRealPart;
	void OnSliderRealPartChange(wxCommandEvent& event);
	void OnTextRealPartEnter(wxCommandEvent& event);

	wxSlider* sliderImPart;
	wxTextCtrl* textCtrlImPart;
	void OnSliderImPartChange(wxCommandEvent& event);
	void OnTextImPartEnter(wxCommandEvent& event);

	void OnExit(wxCloseEvent& event);

	wxStaticText* timing; 


	wxTextCtrl* textCtrlNumberOfIterations;
	void OnTextNumberOfIterationsEnter(wxCommandEvent& event);

	wxTextCtrl* textCtrlCutoff;
	void OnTextCutoffEnter(wxCommandEvent& event);

	wxChoice* comboTypeOfFractal;
	void OncomboTypeOfFractalEnter(wxCommandEvent& event);

	
	wxChoice* comboTypeOfCompute;
	void OncomboTypeOfComputeEnter(wxCommandEvent& event);

	std::unique_ptr<wxTimer> input_polling_timer = std::unique_ptr<wxTimer>(new wxTimer());
	void OnInputTimer(wxTimerEvent& event);


	void RedrawCanvas();
};








#endif
