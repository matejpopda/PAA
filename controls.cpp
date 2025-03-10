#include "controls.h"
#include "canvas.h"
#include "kernel.cuh"
#include <iostream>  
#include <string>  

#include <chrono>

const long controls_style = wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX);

const int MS_PER_INPUT_POLL = 30;


const wxString mandelbrot = "Mandelbrot";
const wxString julia = "Julia";
const wxString singlethread = "SingleThread";
const wxString multithread = "MultiThread";
const wxString ompthread = "OMP MultiThread";
const wxString cuda = "CUDA";

static const wxString typesCompute[] = { singlethread , multithread, ompthread,  cuda };
static const wxString typesFractal[] = { mandelbrot,  julia };


ControlsFrame::ControlsFrame(CanvasFrame* canvas)
    : wxFrame(NULL, ID_Controls, "Controls", wxDefaultPosition, wxDefaultSize, controls_style)
{
    associatedCanvas = canvas;

    wxPanel* panel = new wxPanel(this);

    wxBoxSizer* vbox;
    wxStaticText* label;
    wxBoxSizer* hbox;
    

    vbox = new wxBoxSizer(wxVERTICAL);
    
    





    // Selection of fractal
    hbox = new wxBoxSizer(wxHORIZONTAL);
    label = new wxStaticText(panel, wxID_ANY, "Type of fractal:", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    hbox->Add(label, 1, wxALL | wxALIGN_CENTER, 10);

    comboTypeOfFractal = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(120, -1), WXSIZEOF(typesFractal), typesFractal);
    comboTypeOfFractal->Select(0);
    hbox->Add(comboTypeOfFractal, 1, wxALL | wxALIGN_CENTER, 10);
    vbox->Add(hbox);

    comboTypeOfFractal->Bind(wxEVT_CHOICE, &ControlsFrame::OncomboTypeOfFractalEnter, this);


    // Selection of how to calculate the fractal
    hbox = new wxBoxSizer(wxHORIZONTAL);
    label = new wxStaticText(panel, wxID_ANY, "Type of computation:", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    hbox->Add(label, 1, wxALL | wxALIGN_CENTER, 10);

    comboTypeOfCompute = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(120, -1), WXSIZEOF(typesCompute), typesCompute);
    comboTypeOfCompute->Select(0);
    hbox->Add(comboTypeOfCompute, 1, wxALL | wxALIGN_CENTER, 10);
    vbox->Add(hbox);

    comboTypeOfCompute->Bind(wxEVT_CHOICE, &ControlsFrame::OncomboTypeOfComputeEnter, this);


    // Selection of how many iterations to do 
    hbox = new wxBoxSizer(wxHORIZONTAL);
    label = new wxStaticText(panel, wxID_ANY, "Number of iterations:", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    hbox->Add(label, 1, wxALL | wxALIGN_CENTER, 10);

    textCtrlNumberOfIterations = new wxTextCtrl(panel, wxID_ANY, "255", wxDefaultPosition, wxSize(60, -1), wxTE_PROCESS_ENTER);
    hbox->Add(textCtrlNumberOfIterations, 1, wxALL | wxALIGN_CENTER, 10);
    vbox->Add(hbox);

    textCtrlNumberOfIterations->Bind(wxEVT_TEXT_ENTER, &ControlsFrame::OnTextNumberOfIterationsEnter, this);


    // Selection of how many iterations to do 
    hbox = new wxBoxSizer(wxHORIZONTAL);
    label = new wxStaticText(panel, wxID_ANY, "Cut-off value:", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    hbox->Add(label, 1, wxALL | wxALIGN_CENTER, 10);

    textCtrlCutoff = new wxTextCtrl(panel, wxID_ANY, "4", wxDefaultPosition, wxSize(60, -1), wxTE_PROCESS_ENTER);
    hbox->Add(textCtrlCutoff, 1, wxALL | wxALIGN_CENTER, 10);
    vbox->Add(hbox);

    textCtrlCutoff->Bind(wxEVT_TEXT_ENTER, &ControlsFrame::OnTextCutoffEnter, this);





    // Selecting the parameter
    label = new wxStaticText(panel, wxID_ANY, "Adjust the real part of the parameter:", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    vbox->Add(label, 0, wxALL | wxEXPAND, 10);

    hbox = new wxBoxSizer(wxHORIZONTAL);
    sliderRealPart = new wxSlider(panel, wxID_ANY, 0, -2 * scaleFactor, 2 * scaleFactor, wxDefaultPosition, wxSize(150, -1));
    textCtrlRealPart = new wxTextCtrl(panel, wxID_ANY, "0", wxDefaultPosition, wxSize(50, -1), wxTE_PROCESS_ENTER);

    hbox->Add(sliderRealPart, 1, wxRIGHT, 10);
    hbox->Add(textCtrlRealPart, 0);

    vbox->Add(hbox, 1, wxALL | wxEXPAND, 10);
    panel->SetSizer(vbox);

    sliderRealPart->Bind(wxEVT_SLIDER, &ControlsFrame::OnSliderRealPartChange, this);
    textCtrlRealPart->Bind(wxEVT_TEXT_ENTER, &ControlsFrame::OnTextRealPartEnter, this);


    label = new wxStaticText(panel, wxID_ANY, "Adjust the imaginary part of the parameter:", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    vbox->Add(label, 0, wxALL | wxEXPAND, 10);

    hbox = new wxBoxSizer(wxHORIZONTAL);
    sliderImPart = new wxSlider(panel, wxID_ANY, 0, -2 * scaleFactor, 2 * scaleFactor, wxDefaultPosition, wxSize(150, -1));
    textCtrlImPart = new wxTextCtrl(panel, wxID_ANY, "0", wxDefaultPosition, wxSize(50, -1), wxTE_PROCESS_ENTER);

    hbox->Add(sliderImPart, 1, wxRIGHT, 10);
    hbox->Add(textCtrlImPart, 0);

    vbox->Add(hbox, 1, wxALL | wxEXPAND, 10);
    panel->SetSizer(vbox);

    sliderImPart->Bind(wxEVT_SLIDER, &ControlsFrame::OnSliderImPartChange, this);
    textCtrlImPart->Bind(wxEVT_TEXT_ENTER, &ControlsFrame::OnTextImPartEnter, this);

    // Calculating execution time
    timing = new wxStaticText(panel, wxID_ANY, "Execution time for last drawing:", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    vbox->Add(timing, 0, wxALL | wxALIGN_LEFT, 10);
    





    Settings.redraw_on_next_input_poll = true;

    CreateStatusBar();
    SetStatusText("Settings can be edited in this window.");


    input_polling_timer.get()->Start(MS_PER_INPUT_POLL);
    input_polling_timer.get()->Bind(wxEVT_TIMER, &ControlsFrame::OnInputTimer, this);
    
    Bind(wxEVT_CLOSE_WINDOW, &ControlsFrame::OnExit, this);


}


void ControlsFrame::OnExit(wxCloseEvent& event)
{
    wxApp::GetInstance()->ExitMainLoop();
}


void ControlsFrame::OncomboTypeOfFractalEnter(wxCommandEvent& event){
    int selected;
    selected = comboTypeOfFractal->GetSelection();

    if (selected == MANDELBROT) {
        Settings.fractal_type = MANDELBROT;
    }
    
    if (selected == JULIA) {
        Settings.fractal_type = JULIA;
    }

    Settings.redraw_on_next_input_poll = true;

}
void ControlsFrame::OncomboTypeOfComputeEnter(wxCommandEvent& event) {
    int selected;
    selected = comboTypeOfCompute->GetSelection();

    if (selected == SINGLE_THREAD) {
        Settings.computation_type = SINGLE_THREAD;
    }

    else if (selected == MULTIPLE_THREADS) {
        Settings.computation_type = MULTIPLE_THREADS;
    }

    else if (selected == OPM_THREADS) {
        Settings.computation_type = OPM_THREADS;
    }

    else if (selected == CUDA) {
        Settings.computation_type = CUDA;
    }

 


    Settings.redraw_on_next_input_poll = true;


}


void ControlsFrame::OnSliderRealPartChange(wxCommandEvent& event) {

    auto value = sliderRealPart->GetValue() / scaleFactor;

    textCtrlRealPart->SetValue(wxString::Format("%.2f", value));

    Settings.real_part_parameter = value;


    Settings.redraw_on_next_input_poll = true;
}

void ControlsFrame::OnTextRealPartEnter(wxCommandEvent& event) {
    double value;
    if (textCtrlRealPart->GetValue().ToDouble(&value) && value >= sliderRealPart->GetMin() / scaleFactor && value <= sliderRealPart->GetMax() / scaleFactor) {
        sliderRealPart->SetValue(static_cast<int>(value * scaleFactor));

        Settings.real_part_parameter = value;


    }
    else {
        textCtrlRealPart->SetValue(wxString::Format("%.2f", sliderRealPart->GetValue() / scaleFactor));
    }




    Settings.redraw_on_next_input_poll = true;
}



void ControlsFrame::OnTextNumberOfIterationsEnter(wxCommandEvent& event) {

    int val; 
    if (textCtrlNumberOfIterations->GetValue().Trim().ToInt(&val) and val > 0) {


        Settings.number_of_iterations = val;
    }
    else {
        textCtrlNumberOfIterations->SetValue(std::to_string(Settings.number_of_iterations));
    }
    


    Settings.redraw_on_next_input_poll = true;
}


void ControlsFrame::OnTextCutoffEnter(wxCommandEvent& event) {

    double val;
    if (textCtrlCutoff->GetValue().Trim().ToDouble(&val) and val > 0) {

        Settings.cut_off_value = val;
    }
    else {
        textCtrlCutoff->SetValue(std::to_string(Settings.cut_off_value));
    }

    Settings.redraw_on_next_input_poll = true;
}


void ControlsFrame::OnSliderImPartChange(wxCommandEvent& event) {
    float value = sliderImPart->GetValue() / scaleFactor;
    textCtrlImPart->SetValue(wxString::Format("%.2f", value));

    Settings.im_part_parameter = value;

    Settings.redraw_on_next_input_poll = true;
}


void ControlsFrame::OnTextImPartEnter(wxCommandEvent& event) {
    double value;
    if (textCtrlImPart->GetValue().ToDouble(&value) && value >= sliderImPart->GetMin()/scaleFactor && value <= sliderImPart->GetMax() / scaleFactor) {
        sliderImPart->SetValue(static_cast<int>(value * scaleFactor));

        Settings.im_part_parameter = value;
    }
    else {
        textCtrlImPart->SetValue(wxString::Format("%.2f", sliderImPart->GetValue() / scaleFactor));
    }



    Settings.redraw_on_next_input_poll = true;
}



void ControlsFrame::RedrawCanvas() {

    auto start = std::chrono::high_resolution_clock::now();


    associatedCanvas->Redraw();


    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    timing->SetLabelText("Execution time for last drawing: " + std::to_string( duration.count()) + " ms");


}


void ControlsFrame::OnInputTimer(wxTimerEvent& event)
{
    input_polling_timer->Stop();

    bool redraw = false;

    if (Settings.redraw_on_next_input_poll) {
        redraw = true;
        Settings.redraw_on_next_input_poll = false;
    }


    double slide_modifier = 4;
    double scale_modifier = 0.5;



    if (wxGetKeyState(WXK_SHIFT)) {
        slide_modifier *= 4;
        scale_modifier = 0.8;
    }


    if (wxGetKeyState(wxKeyCode('A'))) {
        TypePrecision diff = Settings.bound_right - Settings.bound_left;
        diff = diff / slide_modifier;
        Settings.bound_left -= diff;
        Settings.bound_right -= diff;

        redraw = true;
    }

    if (wxGetKeyState(wxKeyCode('D'))) {
        TypePrecision diff = Settings.bound_right - Settings.bound_left;
        diff = diff / slide_modifier;
        Settings.bound_left += diff;
        Settings.bound_right += diff;

        redraw = true;
    }

    if (wxGetKeyState(wxKeyCode('S'))) {
        TypePrecision diff = Settings.bound_up - Settings.bound_down;
        diff = diff / slide_modifier;
        Settings.bound_up += diff;
        Settings.bound_down += diff;

        redraw = true;
    }

    if (wxGetKeyState(wxKeyCode('W'))) {
        TypePrecision diff = Settings.bound_up - Settings.bound_down;
        diff = diff / slide_modifier;
        Settings.bound_up -= diff;
        Settings.bound_down -= diff;

        redraw = true;
    }

    if (wxGetKeyState(wxKeyCode('Q'))) {
        TypePrecision center_x = (Settings.bound_left + Settings.bound_right)/2;
        TypePrecision center_y = (Settings.bound_up + Settings.bound_down)/2;


        TypePrecision diff_x = (Settings.bound_right - Settings.bound_left)/2;
        TypePrecision diff_y = (Settings.bound_up - Settings.bound_down)/2;


        
        Settings.bound_up = center_y + (diff_y * scale_modifier);
        std::cout << center_y << diff_y << Settings.bound_up << std::endl;
        Settings.bound_down = center_y - (diff_y * scale_modifier);
        Settings.bound_left = center_x - (diff_x * scale_modifier);
        Settings.bound_right = center_x + (diff_x * scale_modifier);


        redraw = true;
    }


    if (wxGetKeyState(wxKeyCode('Z'))) {
        TypePrecision center_x = (Settings.bound_left + Settings.bound_right) / 2;
        TypePrecision center_y = (Settings.bound_up + Settings.bound_down) / 2;


        TypePrecision diff_x = (Settings.bound_right - Settings.bound_left) / 2;
        TypePrecision diff_y = (Settings.bound_up - Settings.bound_down) / 2;



        Settings.bound_up = center_y + (diff_y / scale_modifier);
        Settings.bound_down = center_y - (diff_y / scale_modifier);
        Settings.bound_left = center_x - (diff_x / scale_modifier);
        Settings.bound_right = center_x + (diff_x / scale_modifier);


        redraw = true;
    }


    if (wxGetKeyState(WXK_SPACE)) {
        redraw = true;
    }

    if (redraw){
        RedrawCanvas();
    }
    input_polling_timer->Start();
}