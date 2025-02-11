#ifndef _ANKER_SIDEBAR_NEW_HPP_
#define _ANKER_SIDEBAR_NEW_HPP_

#include <memory>
#include <vector>

#include <wx/panel.h>
#include <wx/event.h>

#include "libslic3r/Preset.hpp"
#include "PresetComboBoxes.hpp"
#include "./PrinterConfigPlater/AnkerParameterPanel.hpp"
#include "Search.hpp"

class wxButton;
class ScalableButton;
class wxScrolledWindow;
class wxString;
class AnkerBitmapCombox;

enum CurrentPane
{
    PANEL_RIGHT_MENU_PARAMETER = 0,
    PANEL_PARAMETER_PANEL = 1,
    PANEL_OTHER_PARAMETER = 2,
};

namespace Slic3r {
    namespace GUI {
        class Plater;
        wxDECLARE_EVENT(wxCUSTOMEVT_CLICK_FILAMENT_BTN, wxCommandEvent);
        wxDECLARE_EVENT(wxCUSTOMEVT_REMOVE_FILAMENT_BTN, wxCommandEvent);
        wxDECLARE_EVENT(wxCUSTOMEVT_UPDATE_FILAMENT_INFO, wxCommandEvent);
        wxDECLARE_EVENT(wxCUSTOMEVT_CHECK_RIGHT_DIRTY_DATA, wxCommandEvent);
        wxDECLARE_EVENT(wxCUSTOMEVT_MAIN_SIZER_CHANGED, wxCommandEvent);

        enum FilamentViewType {
            singleColorView = 1,
            multiColorHorView = 2,
            multiColorVerView = 3
        };

        // means filament source type,maybe system or user created
        enum FilamentSourceType {
            systemFilamentType = 1,
            userFilamentType = 2
        };

        typedef struct SFilamentInfo {
            wxString wxStrColor     = "";
            wxString wxStrColorName = "";
            wxString wxStrLabelName = "";
            wxString wxStrLabelType = "";
            FilamentSourceType filamentSrcType = systemFilamentType;
            // add by allen for add anker_filament_id and anker_colour_id
            wxString wxStrFilamentId = "";
            wxString wxStrColorId = "";
            SFilamentInfo(wxString color = "", wxString colorName = "", wxString labelname = "", wxString type = "",
                FilamentSourceType srcType = systemFilamentType, wxString filamenId = "", 
                wxString colourId = "") :
                wxStrColor(color),
                wxStrColorName(colorName),
                wxStrLabelName(labelname),
                wxStrLabelType(type),
                filamentSrcType(systemFilamentType),
                wxStrFilamentId(filamenId),
                wxStrColorId(colourId){
            };
            SFilamentInfo(const SFilamentInfo& info) {
                wxStrColor = info.wxStrColor;
                wxStrColorName = info.wxStrColorName;
                wxStrLabelName = info.wxStrLabelName;
                wxStrLabelType = info.wxStrLabelType;
                filamentSrcType = info.filamentSrcType;
                wxStrFilamentId = info.wxStrFilamentId;
                wxStrColorId = info.wxStrColorId;
            }
        }SFilamentInfo;

        typedef struct SFilamentEditInfo {
            int editIndex = 0;
            SFilamentInfo filamentInfo;
            SFilamentEditInfo(int index, SFilamentInfo info):
            editIndex(index),
            filamentInfo(info) {

            }
            SFilamentEditInfo(const SFilamentEditInfo& info){
                editIndex = info.editIndex;
                filamentInfo = info.filamentInfo;
            }

            SFilamentEditInfo() {

            }

            bool operator == (const SFilamentEditInfo& editInfo) {
                return (editInfo.filamentInfo.wxStrColor == this->filamentInfo.wxStrColor 
                    && editInfo.filamentInfo.wxStrLabelName == this->filamentInfo.wxStrLabelName
                    && editInfo.filamentInfo.wxStrLabelType == this->filamentInfo.wxStrLabelType);
            }
        } SFilamentEditInfo;

        wxDECLARE_EVENT(wxCUSTOMEVT_ANKER_FILAMENT_CHANGED, wxCommandEvent);
        class AnkerFilamentEditDlg : public wxDialog
        {
        public:
            AnkerFilamentEditDlg(wxWindow* parent, std::string title, SFilamentEditInfo filamentEditInfo, wxButton* btn);
            ~AnkerFilamentEditDlg();
            void SetEditColorBtnPtr(wxButton* btn);

        private:
            void initUI();

            void initFilamentCombox();
            void initColorCombox();
            void resetColorCombox(bool bInitCreate = true);
            wxBitmap createBitmapFromColor(int width, int height, wxColour color);
            void OnFilamentComboSelected(wxCommandEvent& event);
            void OnColorComboSelected(wxCommandEvent& event);
            void PostFilamentUpdateEvent();

            void OnExitButtonClicked(wxCommandEvent& event);
			void onComboBoxClick(Slic3r::GUI::AnkerPlaterPresetComboBox* presetComboBox);
			void onPresetComboSelChanged(Slic3r::GUI::AnkerPlaterPresetComboBox* presetChoice, const int selection);
        private:
            std::string m_title;
            wxStaticText* m_pTitleText{nullptr};
            ScalableButton* m_pExitBtn{nullptr};
            wxButton* m_pEditColorBtn{ nullptr };
            SFilamentEditInfo m_oldFilamentEditInfo;
            SFilamentEditInfo m_newFilamentEditInfo;

            std::set<wxString> m_filamentList;
            std::map<wxString, std::vector<SFilamentInfo>> m_filamentInfoList;

            AnkerPlaterPresetComboBox* m_comboFilament{nullptr};
            AnkerBitmapCombox* m_comboColor{nullptr};
            int m_comboColorLastSelected;
            
        };

        class AnkerSidebarNew : public wxPanel
        {
            ConfigOptionMode    m_mode{ ConfigOptionMode::comSimple };
        public:
            AnkerSidebarNew(Plater* parent);
            AnkerSidebarNew(AnkerSidebarNew&&) = delete;
            AnkerSidebarNew(const AnkerSidebarNew&) = delete;
            AnkerSidebarNew& operator=(AnkerSidebarNew&&) = delete;
            AnkerSidebarNew& operator=(const AnkerSidebarNew&) = delete;
            ~AnkerSidebarNew();

            void reloadParameterData();
            void updatePreset(DynamicPrintConfig&config);
            void hidePopupWidget();
            void enableSliceBtn(bool isSaveBtn, bool isEnable);
            // if you want to reset and restore sidebar,please see usage examples in OnTimer function
            // if sizer is nullptr, use default m_pParameterVSizer instead;
            //changed by alves.
            bool replaceUniverseSubSizer(wxSizer* sizer = nullptr,wxString sizerFlags = "");
            // use default main sizer when sizer is nullptr
            void setMainSizer(wxSizer* sizer = nullptr, bool bForceAllDefault = true);
            bool checkDirtyDataonParameterpanel();
            void showRightMenuParameterPanel(const wxString& objName, Slic3r::ModelConfig* config);
            void exitRightMenuParameterPanel();
           
            void updatePresets(Slic3r::Preset::Type preset_type);

            void onExtrudersChange(size_t changedExtruderNums = 0);
            //add by alves
            wxString getSizerFlags()const;
            const std::vector<SFilamentInfo>& getEditFilamentList();
            const std::map<wxString, std::vector<SFilamentInfo>>& getAllFilamentList();
              
            bool isMultiFilament();

            void onMove(wxMoveEvent& evt);
            void onSize(wxSizeEvent& evt);
            void onMinimize(wxIconizeEvent& evt);
            void onMaximize(wxMaximizeEvent& evt);

            void shutdown();
            void closeFilamentEditDlg();

            void syncFilamentInfo(const std::vector<SFilamentInfo> syncFilamentInfo);

            // add by allen for ankerCfgDlg search
            void check_and_update_searcher(bool respect_mode = false);
            Search::OptionsSearcher& get_searcher();
            std::string& get_search_line();
            void update_mode();
            void jump_to_option(size_t selected);
            void jump_to_option(const std::string& opt_key, Preset::Type type, const std::wstring& category);
            void search();
            void getItemList(wxStringList& list, ControlListType listType);
            void setItemValue(const wxString tabName, const wxString& widgetLabel, wxVariant data);
            void openSupportMaterialPage(wxString itemName, wxString text);

            // set load file flag
            void setLoadProjectFileFlag(bool bFlag = true);
            bool getLoadProjectFileFlag();
        private:
            void updateFilamentEditDlgPos();
            void modifyExtrudersInfo(const std::vector<SFilamentEditInfo> filamentInfoList, 
                bool bRemove = false, int removeIndex = 0);
            void updateAllPresetComboboxes();
            void getEditFilamentFromCfg(size_t changedExtruderNums = 0);
            void getAllFilamentFromCfg();
            void presetNameSplit(const std::string presetName, std::string& colorName);
           

            void refreshSideBarLayout();

            void createPrinterSiderbar();
            void createFilamentSidebar();
            void createPrintParameterSidebar();
            void createRightMenuPrintParameterSidebar();
            void setFixedDefaultSidebar();
            void setAllDefaultSidebar();

            void onFilamentListToggle(wxEvent& event);
            void updateFilamentInfo(bool bDestoryPanel = false);
            void updateFilamentBtnColor(SFilamentEditInfo* filamentEditInfo, wxButton* editColorBtn);
    
            void singleColorFilamentHorInit();
            void multiColorFilamentHorInit();
            void multiColorFilamentVerInit();

            // event
            void onHorSingleColorFilament();
            void onHorMultiColorFilament();
            void onVerMultiColorFilament();

            void onFilamentMenuOpen(wxMouseEvent& event);
            void onFilamentBtnLeftClicked(wxMouseEvent& event);
            void onFilamentTextLeftClicked(wxMouseEvent& event);
            void onFilamentPopupClick(wxCommandEvent& event);
            void onFilmentEditSelected(const uint32_t btnIndex, wxButton* btn);
            void onFilamentRemoveSelected(const uint32_t btnIndex, wxButton* btn);
            void onUpdateFilamentInfo(wxCommandEvent& event);
            // add by aden for sync filament info
            void onSyncFilamentInfo(wxCommandEvent& event);

            void OnTimer(wxTimerEvent& event);

            void updateCfgComboBoxPresets(Slic3r::Preset::Type presetType);
            void updateFilamentColourInCfg(const std::string strLabelName, const int selectedIndex, bool bUseSelectedIndex = true);

            void filamentInfoChanged();

            void updateFilamentColorBtnPtr(wxButton* colorBtn);
			void onComboBoxClick(Slic3r::GUI::AnkerPlaterPresetComboBox* presetComboBox);
			void onPresetComboSelChanged(Slic3r::GUI::AnkerPlaterPresetComboBox* presetChoice, const int selection);
        private:
            struct priv;
            std::unique_ptr<priv> p;
            std::string m_multiColorSelectedSn = "";
            wxDECLARE_EVENT_TABLE();

            wxString m_sizerFlags = "";
            CurrentPane m_showRightMenuPanel = PANEL_PARAMETER_PANEL;
            std::atomic_bool m_bLoadProjectFile{ false };
        };
    } // namespace GUI
} // namespace Slic3r

#endif
