// Check if WifiModel.h has already been included, and if not, define it.
#ifndef WifiModel_h
#define WifiModel_h


#include "Arduino.h"


class WifiModel {
  private:
    String network_name;
    String ssid;
    String password;

  public:
    WifiModel(String netName, String ssidVal, String pass); // Constructor declaration
    String getNetworkName(); // Method to get the network name
    String getSSID(); // Method to get the SSID
    String getPassword(); // Method to get the password
    
};

#endif
