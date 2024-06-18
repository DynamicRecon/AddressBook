#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include<string>

class Settings {
  public:
    Settings();
    std::string get_name();
    void set_name(std::string val);
    std::string get_value();
    void set_value(std::string val);
  private:
      std::string m_name;
      std::string m_value;

};


#endif