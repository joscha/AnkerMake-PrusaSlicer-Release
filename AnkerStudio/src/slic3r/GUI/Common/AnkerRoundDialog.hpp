#ifndef ANKER_ROUND_DIALOG_HPP
#define ANKER_ROUND_DIALOG_HPP
#include <wx/wx.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include "AnkerRoundBaseDialog.hpp"
#include "AnkerBaseCtls.h"

namespace Slic3r {
	namespace GUI {
			
		class AnkerRoundDialog : public AnkerRoundBaseDialog
		{
		public:
			AnkerRoundDialog(wxWindow* parent,wxString strTitle = "Title", wxString strContentText = "");
			~AnkerRoundDialog();

			void InitUi();
			void InitEvent();
			void OnPaint(wxPaintEvent& event); 
			void SetHeadHeight(int iNewHeight) { m_iHeadPanelHeight = iNewHeight; }
			void SetBottomHeight(int iNewHeight){ m_iBottomPanelHeight = iNewHeight; }

			void SetHeadPanel(AnkerBasePanel* pNewPanel) { m_pHeadPanel = pNewPanel; }
			void SetContentPanel(AnkerBasePanel* pNewPanel) { m_pContentPanel = pNewPanel; }
			AnkerBasePanel* GetContentPanel() { return m_pContentPanel; }
			void SetBottomPanel(AnkerBasePanel* pNewPanel) { m_pBottomPanel = pNewPanel; }
			void SetCloseFileName(std::string strFileName) { m_strCloseImgFileName = strFileName; }


		private:
			void resetWindow(wxWindow* parent);
			void OnExitButtonClicked(wxCommandEvent& event);
			void OnOKButtonClicked(wxCommandEvent& event);
			void OnCancelButtonClicked(wxCommandEvent& event);
			

		private:
			AnkerBasePanel* m_pHeadPanel;
			AnkerBasePanel* m_pContentPanel;
			AnkerBasePanel* m_pBottomPanel;
			int m_iHeadPanelHeight;
			int m_iBottomPanelHeight;
			wxSizer* m_pSizer;
			wxString m_TitleText;
			wxString m_ContentText;
			std::string m_strCloseImgFileName;
			std::string m_cancelText{"No"};
			std::string m_okText{"Yes"};
			wxSizerItem* m_pBtnSpaceItem{ nullptr };
		};
	}
}

#endif // !ANKER_ROUND_DIALOG_HPP
