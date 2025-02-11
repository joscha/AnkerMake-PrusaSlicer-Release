#ifndef _ANKER_GCODE_IMPORT_DIALOG_H_
#define _ANKER_GCODE_IMPORT_DIALOG_H_

#include "wx/wx.h"
#include "slic3r/Utils/DataManger.hpp"

#include <boost/bind.hpp>
#include <boost/signals2/connection.hpp>
#include "Common/AnkerBaseCtls.h"



wxDECLARE_EVENT(wxCUSTOMEVT_FILEITEM_CLICKED, wxCommandEvent);
class AnkerBtn;
class AnkerLoadingMask;
class AnkerTitledPanel;
class AnkerGCodeFileItem : public wxControl
{
public:
	AnkerGCodeFileItem(wxWindow* parent);
	~AnkerGCodeFileItem();

	void setFileName(wxString filename);
	void setFilePath(wxString filepath);
	void setFileTimeStr(wxString time);

	wxString getFileName();
	wxString getFilePath();
	wxString getFileTimeStr();

private:
	void initUI();

	void OnPaint(wxPaintEvent& event);
	void OnMouseEnterWindow(wxMouseEvent& event);
	void OnMouseLeaveWindow(wxMouseEvent& event);


private:
	bool m_enterChildFlag;

	wxString m_fileName;
	wxString m_filePath;
	wxString m_filePathRenderStr;
	wxString m_fileTimeInfo;
	wxImage m_fileImage;

	wxStaticText* m_pFileNameText;
	wxStaticText* m_pFilePathText;
	wxStaticText* m_pFileTimeText;
};

class AnkerGCodeImportDialog : public wxDialog
{
public:
	enum FileSelectMode
	{
		FSM_NONE,
		FSM_COMPUTER,
		FSM_STORAGE,
		FSM_USB
	};
	struct GCodeImportResult
	{
		FileSelectMode m_srcType;
		std::string m_fileName;
		std::string m_filePath;

		std::string m_speedStr = "--";
		std::string m_filamentStr = "--";
		int m_timeSecond = 0;
		wxImage m_previewImage;
	};

	struct filamentInfo
	{
		wxString strfilamentColor;
		wxString strFilamentName;

		bool operator<(const filamentInfo& rhs) const
		{
			if (strFilamentName < rhs.strFilamentName)
				return true;
			else
				return false;
		}
	};

	struct  printFilamentInfo
	{
		int iIndex;
		filamentInfo infoDetail;
		bool bCanReplace;
	};

public:
	AnkerGCodeImportDialog(std::string currentDeviceSn, wxWindow* parent);
	~AnkerGCodeImportDialog();

	// set current device sn
	void setCurrentDeviceSn(std::string sn) { m_currentDeviceSn = sn; }

	// use these after init
	void setFileInfoSpeed(std::string str);
	void setFileInfoFilament(std::string str);
	void setFileInfoTime(int seconds);
	void setPreviewImage(int width, int height, unsigned char* data, unsigned char* alpha = nullptr, bool freeFlag = true);

	void switch2FileSelect(FileSelectMode mode);
	void switch2FileInfo(std::string filepath, std::string strTitleName="");
	void switch2PrintFinished(bool success, GCodeImportResult& result);

	void requestCallback(int type = -1);

	GCodeImportResult& getImportResult() { return m_importResult; }

private:
	void initUI();
	void SimulateData();
	bool initFSComputerSizer(wxWindow* parent);
	bool initFSEmptySizer(wxWindow* parent);
	bool initFSListSizer(wxWindow* parent);
	bool initFileInfoSizer(wxWindow* parent);
	bool initFinishedSizer(wxWindow* parent);

	void switch2FSMode(FileSelectMode mode);
	void setLoadingVisible(bool visible);

	void OnComputerBtn(wxCommandEvent& event);
	void OnStorageBtn(wxCommandEvent& event);
	void OnUSBBtn(wxCommandEvent& event);
	void OnComputerImportBtn(wxCommandEvent& event);
	void OnPrintBtn(wxCommandEvent& event);
	void OnFinishBtn(wxCommandEvent& event);
	void OnSearchBtn(wxCommandEvent& event);
	void OnSearchTextChanged(wxCommandEvent& event);
	void OnSearchTextEnter(wxCommandEvent& event);
	void OnFileItemClicked(wxMouseEvent& event);
	void OnShow(wxShowEvent& event);
	void OnLoadingTimeout(wxCommandEvent& event);
	void OnMove(wxMoveEvent& event);

private:
	bool m_gcodePreviewWaiting;
	std::string m_currentDeviceSn;
	std::string m_localImportDefaultDir;

	wxColour m_dialogColor;
	wxColour m_textLightColor;
	wxColour m_textDarkColor;
	wxColour m_btnFocusColor;
	wxColour m_btnFocusTextColor;
	wxColour m_splitLineColor;

	FileSelectMode m_currentMode;
    AnkerBtn* m_pComputerBtn;
    AnkerBtn* m_pStorageBtn;
    AnkerBtn* m_pUSBBtn;
	wxStaticBitmap* m_pPreviewImage;
	wxStaticText* m_pSpeedText;
	wxStaticText* m_pFilamentText;
	wxStaticText* m_pPrintTimeText;
	//wxPanel* m_pFSContentWindow;
	wxScrolledWindow* m_pFSComputerWidget;
	wxScrolledWindow* m_pFSEmptyWidget;
	wxScrolledWindow* m_pFSStorageListWidget;
	wxScrolledWindow* m_pFSUSBListWidget;

	AnkerTitledPanel* m_pTitledPanel;
	wxPanel* m_pFileSelectPanel;
	wxPanel* m_pFileInfoPanel;
	wxPanel* m_pFinishedPanel;

	// finish sizer
	AnkerBtn* m_pPrintBtn;
	AnkerBtn* m_pRePrintBtn;
	AnkerBtn* m_pFinishBtn;
	wxStaticBitmap* m_pFinishedStatusImage;
	wxStaticText* m_pFinishedStatusText;
	wxStaticText* m_pFinishedSpeedText;
	wxStaticText* m_pFinishedFilamentText;
	wxStaticText* m_pFinishedPrintTimeText;

	AnkerLoadingMask* m_pLoadingMask;

	GCodeImportResult m_importResult;
	bool m_fileListUpdateReq;
	bool m_gcodeInfoReq;
	std::string m_gcodeInfoFilePath;
	MqttType::FileList m_remoteFileList;
	boost::signals2::connection m_connect;

	wxTextCtrl* m_pSearchTextCtrl;
	std::vector<AnkerGCodeFileItem*> m_gfItemList;

	std::map<filamentInfo, printFilamentInfo> filamentMap;
	std::vector<printFilamentInfo> m_PrinterFilamentVec;
};

#endif // _ANKER_GCODE_IMPORT_DIALOG_H_

