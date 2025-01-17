#pragma once


#include <iostream>
#include <fstream>
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>

#include "SFML/ASKII.hpp"
class Window : public wxFrame
{
    wxPanel * panel;
    wxSize win_size;
    wxPoint position;
    wxStaticBitmap * image;
    wxTextCtrl * result;
    wxFont *font;
    wxFileDialog *openFileDialog;
    askii::ASKII_ALGORITHM * askii;
    
public:
    Window(const wxString& title = "no",const wxPoint& pos = wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~Window();
private:
    void onButtonOpenClick(wxCommandEvent& ev);
    void onButtonConvertClick(wxCommandEvent& ev);
    void OnKeyDown(wxMouseEvent &event);
};
 
 