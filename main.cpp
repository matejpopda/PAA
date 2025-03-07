
#include "controls.h"
#include "canvas.h"
#include "defaults.h"
#include "SettingsSingleton.h"




class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

bool MyApp::OnInit()
{
    CanvasFrame* canvas = new CanvasFrame();
    canvas->Show(true);

    canvas->SetMinSize(wxSize(CANVAS_SIZE_X, CANVAS_SIZE_Y));
    canvas->SetSize(wxSize(CANVAS_SIZE_X, CANVAS_SIZE_Y));
    canvas->SetMaxSize(wxSize(CANVAS_SIZE_X, CANVAS_SIZE_Y));


    ControlsFrame* controls = new ControlsFrame(canvas);
    controls->Show(true);

    controls->SetMinSize(wxSize(CONTROLS_SIZE_X, CONTROLS_SIZE_Y));
    controls->SetSize(wxSize(CONTROLS_SIZE_X, CONTROLS_SIZE_Y));
    controls->SetMaxSize(wxSize(CONTROLS_SIZE_X, CONTROLS_SIZE_Y));


    return true;
}


wxIMPLEMENT_APP(MyApp);
