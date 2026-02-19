#include "../include/httplib.h"
#include "server.hpp"
#include <string>
#include <vector>

using namespace std;

// ============================================
// USER CLASS
// ============================================
class User {
private:
  long long phoneNumber;

public:
  string email;
  string password;
  vector<User *> *friends;
  string userName;
  string name;

  User() : friends(new vector<User *>()) {}

  User(string userName, string name, long long num, string email,
       string password) {
    this->userName = userName;
    this->name = name;
    this->phoneNumber = num;
    this->email = email;
    this->password = password;
    this->friends = new vector<User *>();
  }

  string getIdOfUser() const { return userName; }
  string getNameOfUser() const { return name; }
  string getEmail() const { return email; }

  void addFriend(User *newFriend) { friends->push_back(newFriend); }
  vector<User *> *getFriendsOfUser() const { return friends; }

  bool checkPassword(const string &inputPassword) const {
    return password == inputPassword;
  }

  // Convert to JSON for sending to frontend (c++ objects -> json string)
  // JSON is a string representation of an object
  // Example: {"userName":"ericpham","name":"Eric
  // Pham","email":"[EMAIL_ADDRESS]","friendsCount":1} JSON is used for
  // communication between frontend and backend bc c++ objects cannot be sent to
  // frontend / directly over the internet
  string toJSON() const {
    string json = "{";
    json += "\"userName\":\"" + userName + "\",";
    json += "\"name\":\"" + name + "\",";
    json += "\"email\":\"" + email + "\",";
    json += "\"friendsCount\":" + to_string(friends->size());
    json += "}";
    return json;
  }
};

// ============================================
// SOCIAL NETWORK CLASS - Your "database"
// ============================================
class SocialNetwork {
private:
  vector<User *> *users; // This acts like your database table

public:
  SocialNetwork() : users(new vector<User *>()) {}
  ~SocialNetwork() {
    for (auto user : *users) {
      delete user;
    }
    delete users;
  }

  // CREATE - Add new user
  void addUser(User *newUser) { users->push_back(newUser); }

  // READ - Find user by username
  User *findUser(string userName) {
    for (int i = 0; i < users->size(); i++) {
      if (users->at(i)->getIdOfUser() == userName) {
        return users->at(i);
      }
    }
    return nullptr;
  }

  // READ - Find user by email
  User *findUserByEmail(const string &email) {
    for (int i = 0; i < users->size(); i++) {
      if (users->at(i)->getEmail() == email) {
        return users->at(i);
      }
    }
    return nullptr;
  }

  // READ - Get all users as JSON array
  string getAllUsersJSON() {
    string json = "[";
    for (int i = 0; i < users->size(); i++) {
      json += users->at(i)->toJSON();
      if (i < users->size() - 1)
        json += ",";
    }
    json += "]";
    return json;
  }

  int getUserCount() { return users->size(); }
};

// Implementation of addTestUsers (declared in server.hpp)
void addTestUsers(SocialNetwork *&ericGram) {
  ericGram->addUser(new User("ericphXm", "Eric Pham", 4089089824LL,
                             "ERICPHAM0902@GMAIL.COM", "password123"));
  ericGram->addUser(new User("alice123", "Alice Smith", 1234567890LL,
                             "alice@email.com", "password123"));
  ericGram->addUser(new User("bob456", "Bob Johnson", 9876543210LL,
                             "bob@email.com", "mypassword"));
  ericGram->addUser(new User("charlie789", "Charlie Brown", 5555555555LL,
                             "charlie@email.com", "secret123"));
}

// Implementation of setupServer (declared in server.hpp)
void setupServer(httplib::Server &server, SocialNetwork *network) {
  // CORS preflight for all endpoints (allows frontend to talk to backend) -
  // Cross-Origin Resource Sharing
  server.Options(R"(/api/.*)", [](const httplib::Request &, httplib::Response &res) {
    res.set_header("Access-Control-Allow-Origin", "*"); // server allows any origin to access it
    res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS"); // server allows GET, POST, and OPTIONS methods
    res.set_header("Access-Control-Allow-Headers", "Content-Type"); // Since frontend is sending JSON data to backend, we need to allow Content-Type header
    res.status = 200; // successful response
  });

  // Login endpoint - handles login requests from frontend
  server.Post("/api/login", [network](const httplib::Request &req, httplib::Response &res) {
        string email = getJSONValue(req.body, "email");
        string password = getJSONValue(req.body, "password");
        User *user = network->findUserByEmail(email);
        res.set_header("Access-Control-Allow-Origin", "*");

        // If user is not found or password is incorrect, return 401
        // error
        if (!user || !user->checkPassword(password)) {
          res.status = 401;
          res.set_content("{\"error\":\"Invalid email or password\"}", "application/json");
          return;
        }

        // If user is found and password is correct, return 200 success
        res.set_content(user->toJSON(), "application/json");
      });

  // Get all users endpoint
  server.Get("/api/users", [network](const httplib::Request &, httplib::Response &res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(network->getAllUsersJSON(), "application/json");
        });
}

// ============================================
// MAIN
// ============================================
int main() {
  // Create server so that the computer can listen for requests from the
  // browser/react app/frontend httplib is a C++ library for creating servers
  // and clients Server is a class that represents a server
  httplib::Server server;

  // Create social network database
  SocialNetwork *ericGram = new SocialNetwork();
  // dummy users
  addTestUsers(ericGram);

  // Setup server
  setupServer(server, ericGram);
  // Start server (blocking) - computer actively listening for requests from the
  // browser/react app/frontend
  startServer(server, "localhost", 8080);

  delete ericGram; // Free up memory

  return 0;
}
