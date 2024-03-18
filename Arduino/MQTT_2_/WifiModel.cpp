#include "WifiModel.h"

// Constructor implementation
WifiModel::WifiModel(String netName, String ssidVal, String pass) {
  network_name = netName;
  ssid = ssidVal;
  password = pass;
}

// Getter for Network Name
String WifiModel::getNetworkName() {
  return network_name;
}

// Getter for SSID
String WifiModel::getSSID() {
  return ssid;
}

// Getter for Password
String WifiModel::getPassword() {
  return password;
}
