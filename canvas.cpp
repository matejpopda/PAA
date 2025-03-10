#include "canvas.h"
#include <wx/rawbmp.h>

#include "fractal.h"
#include "kernel.cuh"

const long canvas_style = wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX);

CanvasFrame::CanvasFrame()
    : wxFrame(NULL, ID_Canvas, "Canvas", wxPoint(500, 100), wxSize(CANVAS_SIZE_X, CANVAS_SIZE_Y), canvas_style)
{




    Bind(wxEVT_CLOSE_WINDOW, &CanvasFrame::OnExit, this);
}



void CanvasFrame::OnExit(wxCloseEvent& event)
{
    wxApp::GetInstance()->ExitMainLoop();
}

void CanvasFrame::Redraw() {


    wxBitmap bitmap = wxBitmap(CANVAS_SIZE_X, CANVAS_SIZE_Y, 24);

    SettingsSingleton settings = SettingsSingleton::getInstance();

    Color* fractal = new Color[CANVAS_SIZE_X * CANVAS_SIZE_Y];


    if (settings.computation_type == SINGLE_THREAD) {
        calcurate_fractal_singlethread(fractal);
    }
    else if (settings.computation_type == MULTIPLE_THREADS) {
        calcurate_fractal_multithread(fractal);
    }
    else if (settings.computation_type == CUDA) {
        calcurate_fractal_cuda(fractal);
    }
    else if (settings.computation_type == OPM_THREADS) {
        calcurate_fractal_openMP(fractal);
    }
    
    wxNativePixelData data = wxNativePixelData(bitmap);
    wxNativePixelData::Iterator p(data);

    for (int i = 0; i < CANVAS_SIZE_Y; ++i)
    {
        wxNativePixelData::Iterator rowStart = p;

        for (int j = 0; j < CANVAS_SIZE_X; ++j, ++p)
        {
            Color color = fractal[i * CANVAS_SIZE_X + j];
            p.Red() = color.red;
            p.Green() = color.green;
            p.Blue() = color.blue;
        }

        p = rowStart;
        p.OffsetY(data, 1);
    }

    staticBitmap->SetBitmap(bitmap);

    delete[] fractal;
}