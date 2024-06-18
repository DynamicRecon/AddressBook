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

  
  // if(dl_settings.get_errors() != "")
  //  std::cout << dl_settings.get_errors() << std::endl;
 
  form_panel->SetSizerAndFit(m_main_sizer);
  
  Layout();
}


//private methods

void AddressBookFrame::OnAdd(wxCommandEvent& event) 
{
  
  if(m_db_path == wxEmptyString)
  {
    wxFileDialog saveDatabase(this, _("New Contacts Database"), "", "", 
    "DB Files (*.db)|*.db",  wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if(saveDatabase.ShowModal() == wxID_OK)
    {
      m_db_path = saveDatabase.GetPath();
    }
  }
  
  ContactInfo info(m_db_path.ToStdString());
  info.set_name(m_txt_name->GetValue().ToStdString());
  info.set_email(m_txt_email->GetValue().ToStdString());
  info.set_phone_number(m_txt_phone->GetValue().ToStdString());  
  info.Add();

  ContactLoc loc(m_db_path.ToStdString());
  loc.set_contact_id(info.get_contact_id());
  loc.set_address(m_txt_address->GetValue().ToStdString());
  loc.set_city(m_txt_city->GetValue().ToStdString());
  loc.set_state(m_txt_state->GetValue().ToStdString());
  loc.set_zip(m_txt_zip->GetValue().ToStdString());
  loc.Add();

}

void AddressBookFrame::OnUpdate(wxCommandEvent& event) 
{
  ContactInfo info(m_db_path.ToStdString());
  info.set_name(m_txt_name->GetValue().ToStdString());
  info.set_email(m_txt_email->GetValue().ToStdString());
  info.set_phone_number(m_txt_phone->GetValue().ToStdString());  
  info.Update();

  ContactLoc loc(m_db_path.ToStdString());
  loc.set_contact_id(info.get_contact_id());
  loc.set_address(m_txt_address->GetValue().ToStdString());
  loc.set_city(m_txt_city->GetValue().ToStdString());
  loc.set_state(m_txt_state->GetValue().ToStdString());
  loc.set_zip(m_txt_zip->GetValue().ToStdString());
  loc.Update();
}

void AddressBookFrame::OnDelete(wxCommandEvent& event) 
{
  ContactInfo info(m_db_path.ToStdString());
  info.set_name(m_txt_name->GetValue().ToStdString());  
  info.Delete();

  ContactLoc loc(m_db_path.ToStdString());
  loc.set_contact_id(info.get_contact_id());
  loc.Delete();
}

void AddressBookFrame::OnSearch(wxCommandEvent& event) 
{
  ContactInfo info(m_db_path.ToStdString());
  info.set_name(m_txt_name->GetValue().ToStdString());  
  info.Search();

  ContactLoc loc(m_db_path.ToStdString());
  loc.set_contact_id(info.get_contact_id());
  loc.Search();
}

wxBEGIN_EVENT_TABLE(AddressBookFrame, wxFrame)
  EVT_BUTTON(ADD, AddressBookFrame::OnAdd)
  EVT_BUTTON(SEARCH, AddressBookFrame::OnSearch)
  EVT_BUTTON(UPDATE, AddressBookFrame::OnUpdate)
  EVT_BUTTON(DELETE, AddressBookFrame::OnDelete)
wxEND_EVENT_TABLE()
