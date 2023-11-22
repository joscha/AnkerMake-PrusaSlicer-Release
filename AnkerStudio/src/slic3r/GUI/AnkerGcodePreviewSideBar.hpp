#ifndef GCODE_INFOMATION_PANEL_H
#define GCODE_INFOMATION_PANEL_H

#include <wx/gauge.h>
#include <wx/dialog.h>
#include <wx/frame.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/timer.h>
#include <wx/stattext.h>

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>

#include <wx/dialog.h>
#include <wx/frame.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/timer.h>
#include <wx/stattext.h>

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/Overlay.h>
#include "wx/dcbuffer.h"
#include "wx/popupwin.h"
#include <wx/renderer.h>
#include <wx/renderer.h>


#include "GCodeViewer.hpp"


#include "AnkerBtn.hpp"

#include "AnkerCheckBox.hpp"
#include "Common/AnkerComboBox.hpp"
#include "Common/AnkerSimpleCombox.hpp"

using namespace Slic3r::GUI;
//using Slic3r::SLAPrint;
using namespace Slic3r;

class AnkerGcodeViewPanel : public wxPanel
{
public:
    AnkerGcodeViewPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY)
    {
        InitGUI();
    };
    ~AnkerGcodeViewPanel() {};

    void InitGUI();
    void UpdateViewGcodeLegendBtn();
    void UpdateCurrentChoice(Slic3r::GUI::GCodeViewer::EViewType viewType);
    void UpdateCurrentChoice();

private:
    GCodeViewer::EViewType GetViewTypeFromName(wxString viewTypeName);
    void onViewGcodeLegendBtnClick(wxCommandEvent& event);
    void OnChoiceSelected(wxCommandEvent& event);

private:
    wxButton* m_viewGcodeLegendBtn = nullptr;
    //ScalableButton* m_viewGcodeLegendBtn = nullptr;
    //wxChoice* m_viewTypeChoice = nullptr;
    AnkerSimpleCombox* m_viewTypeChoice = nullptr;
};



// show option Panel
class AnkerGCodeExtrusionRoleSelectPanel : public wxPanel
{
public:
    AnkerGCodeExtrusionRoleSelectPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY)
    {
        InitGUI();
    };
    ~AnkerGCodeExtrusionRoleSelectPanel() {};

    void InitGUI();
    void UpdateAllGCodeExtrusionRoleUI();

private:
    void SelectAllGCodeExtrusionRole(bool val);

    bool SetGCodeExtrusionRoleVisible(wxString roleName, bool visible);
    bool IsGCodeExtrusionRoleVisible(wxString roleName);


    wxString GcodeExtrusionRoleToroleName(GCodeExtrusionRole role);
    GCodeExtrusionRole roleNameToGcodeExtrusionRole(std::string roleStr);

    void OnAllClicked(wxCommandEvent& event);
    void OnGCodeExtrusionRoleClicked(wxCommandEvent& event);


private:
    AnkerCheckBox* m_allcheckBox = nullptr;
    std::map <wxWindowID, AnkerCheckBox*> m_ExtrusionRoleStringForCheckBoxID;
};



class GcodeExportProgressDialog : public wxDialog
{
public:
    GcodeExportProgressDialog(wxWindow* parent); 
    ~GcodeExportProgressDialog() {};
    void InitUI();

private:
    void onProgressChange(float percentage);

private:
    wxStaticText* m_exportingLabel = nullptr;
    wxBitmapButton* m_stopExportBtn = nullptr;
    wxGauge* m_exportProgressBar = nullptr;;
    wxStaticText* m_exportProgressText = nullptr;
};




class AnkerGcodeInfo : public wxPanel
{
public:
    AnkerGcodeInfo(wxWindow* parent) : wxPanel(parent, wxID_ANY) { 
        InitGUI();
    };
    ~AnkerGcodeInfo() {};

    void InitGUI();
    void UpdateSlicedInfo(bool GcodeValid);
private:

    std::string getReadableTime(int seconds);
    void OnGoPrintBtnClick(wxCommandEvent& event);
    void OnExportBtnClick(wxCommandEvent& event);


private:
    wxStaticText* m_sizeValueLabel = nullptr;
    wxStaticText* m_filametValueLabel = nullptr;
    wxStaticText* m_printTimeValLabel = nullptr;
    AnkerCheckBox* m_createAIFilecheckbox = nullptr;
    wxStaticText* m_AIFileNotSuportLabel = nullptr;

    wxBoxSizer* AISizer = nullptr;

    AnkerBtn* m_goPrintBtn = nullptr;
    AnkerBtn* m_sliceBtn = nullptr;
    AnkerBtn* m_exportBtn = nullptr;

    GcodeExportProgressDialog *m_exportProgressDlg = nullptr;
    bool m_exportingGcode = false;
};


class AnkerGcodePreviewSideBar : public wxPanel
{
public:
    AnkerGcodePreviewSideBar(wxWindow* parent) : wxPanel(parent, wxID_ANY)
    {
        InitGUI();
    };
    ~AnkerGcodePreviewSideBar() {};

    void InitGUI();
    void UpdateGcodePreviewSideBar(bool GcodeValid);
    void UpdateCurrentViewType(GCodeViewer::EViewType type);

private:

    AnkerGcodeViewPanel* m_GcodeViewPanel = nullptr;
    AnkerGCodeExtrusionRoleSelectPanel* m_gCodeExtrusionRoleSelectPanel = nullptr;
    AnkerGcodeInfo* m_GcodeInfoPanel = nullptr;

};

#endif // !GCODE_INFOMATION_PANEL_H
