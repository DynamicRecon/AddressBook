#include "AddressBookFrame.hpp"


// Declare the application class
class AddressBookApp : public wxApp
{
public:
    // Called on application startup
    virtual bool OnInit();
};


// Implements &AddressBookApp GetApp()
DECLARE_APP(AddressBookApp)

// Give wxWidgets the means to create a AddressBookApp object
IMPLEMENT_APP(AddressBookApp)


// Initialize the application
bool AddressBookApp::OnInit()
{
    // Create the main application window
    AddressBookFrame *frame = new AddressBookFrame(wxT("Simple Address Book"));

    // Show it
    frame->Show(true);

    // Start the event loop
    return true;
}
