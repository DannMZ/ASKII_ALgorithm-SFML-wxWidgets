#include "Window.hpp"
#include "DIRS.h"

Window::Window(const wxString& title,const wxPoint& position,const wxSize& win_size):wxFrame(nullptr,wxID_ANY,title,position,win_size)
{
    this->position = position;
    this->win_size = win_size;
    std::cout<<win_size.GetWidth() << " " << win_size.GetHeight()<<std::endl;
    
    
    
    
    wxBoxSizer * main_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer * left = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer * centre = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer * right = new wxBoxSizer(wxVERTICAL);

   // this = new wxPanel(this);
    wxButton * open = new wxButton(this,wxID_ANY,wxString("Open"),wxPoint((this->win_size.GetWidth()/2)-50,(this->win_size.GetHeight()/2)-25),wxSize(100,50));
    wxButton * convert = new wxButton(this,wxID_ANY,wxString("Convert"),wxPoint(open->GetPosition().x,open->GetPosition().y+50),wxSize(100,50));

    result = new wxTextCtrl(this,wxID_ANY,wxString("Nothing added yet.."),wxPoint(this->win_size.GetWidth()/2+100,50),wxSize(400,600),  wxTE_MULTILINE |wxTE_READONLY | wxHSCROLL);
    right->Add(result,0,wxEXPAND | wxTOP,20);
    
    font = new wxFont(wxSize(16, 16), wxFontFamily::wxFONTFAMILY_TELETYPE, wxFontStyle::wxFONTSTYLE_NORMAL, wxFontWeight::wxFONTWEIGHT_NORMAL);//Monospace font
    result->SetFont(*font);
    wxInitAllImageHandlers();
    image = new wxStaticBitmap(this,wxID_ANY,wxBitmap(REFS "no.png",wxBITMAP_TYPE_PNG),wxPoint(this->win_size.GetWidth()/4-200,this->win_size.GetHeight()/4),wxSize(200, 500));
    
    
    open->Bind(wxEVT_BUTTON,&Window::onButtonOpenClick,this);
    convert->Bind(wxEVT_BUTTON,&Window::onButtonConvertClick,this);
    result->Bind(wxEVT_MOUSEWHEEL,&Window::OnKeyDown,this);

    centre->Add(open,1,wxEXPAND | wxTOP,300);
    centre->Add(convert,1,wxEXPAND | wxBOTTOM,300);
    left->Add(image,1,wxEXPAND | wxALL,5);
    main_sizer->Add(left,1,wxEXPAND | wxALL,5);
    main_sizer->Add(centre,1,wxEXPAND | wxALL,5);
    main_sizer->Add(right,0,wxEXPAND | wxALL,5);
    this->SetSizer(main_sizer);
    //wxLog::SetActiveTarget(new wxLogTextCtrl(result));
    CreateStatusBar();
}


void Window::onButtonOpenClick(wxCommandEvent& ev){
    openFileDialog = new wxFileDialog(this, _("Open PNG file"), "", "",
                       "PNG files (*.png)|*.png", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog->ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...
    
    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxFileInputStream input_stream(openFileDialog->GetPath());
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog->GetPath());
        return;
    }
    wxBitmap tmp;
    tmp.LoadFile(openFileDialog->GetPath(),wxBITMAP_TYPE_PNG);
    image->SetBitmap(tmp);
    wxLogStatus(openFileDialog->GetPath());
    
}

void Window::onButtonConvertClick(wxCommandEvent& ev){
    result->Clear();
    std::ifstream myfile;
    myfile.open(file_T"/index.txt");
    if(myfile.is_open()){
        std::cout<<"file opened sucessfuly\n";
    }else{
        return;
    }
    std::string row;
    askii = new askii::ASKII_ALGORITHM(openFileDialog->GetPath().ToStdString());
    
    askii->convert_to_aski();
    while (getline (myfile, row))
    {
        
        
        *result<<row<<'\n';
    }
    myfile.close();
    delete askii;
}
void Window::OnKeyDown(wxMouseEvent &event){
    if(event.GetWheelRotation() >0){
        font->Scale(1.5);
        wxLogStatus("+");
    }else if(event.GetWheelRotation() <0){
        font->Scale(0.5);
        wxLogStatus("-");
    }
    
    result->SetFont(*font);
}

Window::~Window(){}