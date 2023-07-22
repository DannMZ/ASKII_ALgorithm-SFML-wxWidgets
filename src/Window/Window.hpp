#pragma once


#include <iostream>
#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>

#include "Settings/Settings.hpp"
#include "ASKII/ASKII2.hpp"
class Window : public wxFrame
{
    wxPanel * panel;
    wxSize win_size;
    wxPoint position;
    wxStaticBitmap * image;
    wxTextCtrl * result;
    wxMenuBar * menu;
    wxFileDialog *openFileDialog;
    askii::ASKII_ALGORITHM * askii;
    Settings_Window * settings;
    
public:
    Window(const wxString& title = "no",const wxPoint& pos = wxDefaultPosition, const wxSize& size= wxDefaultSize);
    ~Window();
private:
    void onButtonOpenClick(wxCommandEvent& ev);
    void onButtonConvertClick(wxCommandEvent& ev);
    void onSettingsClicked(wxCommandEvent& ev);

};
 
 