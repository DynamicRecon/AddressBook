#include "AddressBookFrame.hpp"

//public methods

AddressBookFrame::AddressBookFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title)
{
  SetInitialSize(wxSize(600,300));
  m_main_sizer = new wxGridSizer(0,2,0,0);
  wxPanel *form_panel = new wxPanel(this, wxID_ANY);
  
  //name
  m_lbl_name = new wxStaticText(form_panel, wxID_ANY, _("Name:"), wxDefaultPosition, wxSize(10,20));
  m_txt_name = new wxTextCtrl(form_panel, wxID_ANY);
  m_main_sizer->Add(m_lbl_name, 0, wxALL|wxEXPAND);
  m_main_sizer->Add(m_txt_name, 0, wxALL|wxEXPAND);
  

  //address
  m_lbl_address = new wxStaticText(form_panel, wxID_ANY, _("Address:"), wxDefaultPosition, wxSize(10,20));
  m_txt_address = new wxTextCtrl(form_panel, wxID_ANY);
  m_main_sizer->Add(m_lbl_address, 0, wxALL|wxEXPAND);
  m_main_sizer->Add(m_txt_address, 0, wxALL|wxEXPAND);

  //city
  m_lbl_city = new wxStaticText(form_panel, wxID_ANY, _("City:"), wxDefaultPosition, wxSize(10,20));
  m_txt_city = new wxTextCtrl(form_panel, wxID_ANY);
  m_main_sizer->Add(m_lbl_city, 0, wxALL|wxEXPAND);
  m_main_sizer->Add(m_txt_city, 0, wxALL|wxEXPAND);

  //state
  m_lbl_state = new wxStaticText(form_panel, wxID_ANY, _("State:"), wxDefaultPosition, wxSize(10,20));
  m_txt_state = new wxTextCtrl(form_panel, wxID_ANY);
  m_main_sizer->Add(m_lbl_state,0, wxALL|wxEXPAND);
  m_main_sizer->Add(m_txt_state,0, wxALL|wxEXPAND);

  //zip
  m_lbl_zip = new wxStaticText(form_panel, wxID_ANY, wxT("Zip:"), wxDefaultPosition, wxSize(10,20));
  m_txt_zip = new wxTextCtrl(form_panel, wxID_ANY);
  m_main_sizer->Add(m_lbl_zip, 0, wxALL|wxEXPAND);
  m_main_sizer->Add(m_txt_zip, 0, wxALL|wxEXPAND);

  //phone
  m_lbl_phone = new wxStaticText(form_panel, wxID_ANY, _("Phone:"), wxDefaultPosition, wxSize(10,20));
  m_txt_phone = new wxTextCtrl(form_panel, wxID_ANY);
  m_main_sizer->Add(m_lbl_phone, 0, wxALL|wxEXPAND);
  m_main_sizer->Add(m_txt_phone, 0, wxALL|wxEXPAND);

  //email
  wxBoxSizer *email_sizer = new wxBoxSizer(wxHORIZONTAL);
  m_lbl_email = new wxStaticText(form_panel, wxID_ANY, _("Email:"), wxDefaultPosition, wxSize(10,20));
  m_txt_email = new wxTextCtrl(form_panel, wxID_ANY);
  m_main_sizer->Add(m_lbl_email, 0, wxALL|wxEXPAND);
  m_main_sizer->Add(m_txt_email, 0, wxALL|wxEXPAND);

  //Add and Search Buttons
  m_btn_add = new wxButton(form_panel, ADD, _("Add"));
  m_btn_search = new wxButton(form_panel, SEARCH, _("Search"));
  m_main_sizer->Add(m_btn_add, 0, wxALL|wxEXPAND);
  m_main_sizer->Add(m_btn_search, 0, wxALL|wxEXPAND);

  //Update and Delete Buttons
  m_btn_update = new wxButton(form_panel, UPDATE, _("Update"));
  m_btn_delete = new wxButton(form_panel, DELETE, _("Delete"));
  m_main_sizer->Add(m_btn_update, 0, wxALL|wxEXPAND);
  m_main_sizer->Add(m_btn_delete, 0, wxALL|wxEXPAND);

  DataLayer dl_settings;
  dl_settings.create_db_settings("Settings.db");
  if(dl_settings.is_opened() == false)
  {
    wxString error_msg(dl_settings.get_errors());
    wxMessageDialog msg(this, error_msg, _("Error!"));
    if(msg.ShowModal() == wxID_OK)
      return;
  }
  // if(dl_settings.get_errors() != "")
  //  std::cout << dl_settings.get_errors() << std::endl;
 
  form_panel->SetSizerAndFit(m_main_sizer);
  
  Layout();
}


//private methods

void AddressBookFrame::OnAdd(wxCommandEvent& event) 
{
  Settings app_settings;
  DataLayer dl_settings_db("Settings.db");
  app_settings.set_name("PATH");
  dl_settings_db.get_setting(&app_settings);
  
  if(app_settings.get_value() == "")
  {
    wxFileDialog saveDatabase(this, _("New Contacts Database"), "", "", 
    "DB Files (*.db)|*.db",  wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if(saveDatabase.ShowModal() == wxID_OK)
    {
      app_settings.set_value(saveDatabase.GetPath().ToStdString());
    }
    dl_settings_db.insert_setting(app_settings);
  }
  dl_settings_db.create_db_contacts(app_settings.get_value());

}

void AddressBookFrame::OnUpdate(wxCommandEvent& event) 
{}

void AddressBookFrame::OnDelete(wxCommandEvent& event) 
{}

void AddressBookFrame::OnSearch(wxCommandEvent& event) 
{}

wxBEGIN_EVENT_TABLE(AddressBookFrame, wxFrame)
  EVT_BUTTON(ADD, AddressBookFrame::OnAdd)
  EVT_BUTTON(SEARCH, AddressBookFrame::OnSearch)
  EVT_BUTTON(UPDATE, AddressBookFrame::OnUpdate)
  EVT_BUTTON(DELETE, AddressBookFrame::OnDelete)
wxEND_EVENT_TABLE()
