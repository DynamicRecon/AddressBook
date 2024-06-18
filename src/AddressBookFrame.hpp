#ifndef ADDRESSBOOKFRAME_HPP
#define ADDRESSBOOKFRAME_HPP

#include<iostream>

#include <wx/wx.h>
#include <wx/fileconf.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/grid.h>
#include <wx/msgdlg.h>

#include "Models/ContactInfo.hpp"
#include "Models/ContactLoc.hpp"

enum
{
  ADD = 100,
  SEARCH,
  UPDATE,
  DELETE
};

class AddressBookFrame : public wxFrame
{
public:
  AddressBookFrame(const wxString& title);
private:
  wxGridSizer *m_main_sizer;
  //text form
  wxStaticText *m_lbl_name;
  wxTextCtrl *m_txt_name;
  wxStaticText *m_lbl_address;
  wxTextCtrl *m_txt_address;
  wxStaticText *m_lbl_city;
  wxTextCtrl *m_txt_city;
  wxStaticText *m_lbl_state;
  wxTextCtrl *m_txt_state;
  wxStaticText *m_lbl_zip;
  wxTextCtrl *m_txt_zip;
  wxStaticText *m_lbl_phone;
  wxTextCtrl *m_txt_phone;
  wxStaticText *m_lbl_email;
  wxTextCtrl *m_txt_email;
  
  wxFileConfig *m_ini_file;

  wxButton *m_btn_add;
  wxButton *m_btn_update;
  wxButton *m_btn_delete;
  wxButton *m_btn_search;

  wxString m_db_path;
  void Clear();
  void OnAdd(wxCommandEvent& event);
  void OnUpdate(wxCommandEvent& event);
  void OnDelete(wxCommandEvent& event);
  void OnSearch(wxCommandEvent& event);
  wxDECLARE_EVENT_TABLE();
};

#endif
