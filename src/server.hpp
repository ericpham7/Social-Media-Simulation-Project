#pragma once
#include "../include/httplib.h"
#include <iostream>
#include <string>

using namespace std;
  
// Forward declaration
class SocialNetwork;

// Helper function to extract value from simple JSON string
inline string getJSONValue(const string &json, const string &key) {
  string search = "\"" + key + "\":\"";
  size_t pos = json.find(search);
  if (pos == std::string::npos) {
    return "";
  }
  pos += search.length();
  size_t end = json.find("\"", pos);
  if (end == std::string::npos)
    return "";
  return json.substr(pos, end - pos);
}

// These functions will be implemented in main.cpp or after the classes are
// defined
void setupServer(httplib::Server &server, SocialNetwork *network);

inline void startServer(httplib::Server &server, const std::string &host,
                        int port) {
  cout << "Server starting on " << host << ":" << port << std::endl;
  server.listen(host, port); // computer actively listening for requests from
                             // the browser/react app/frontend
}

void addTestUsers(SocialNetwork *&ericGram);