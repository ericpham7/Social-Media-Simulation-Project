#include <iostream>
#include <vector>
using namespace std;

void startMenu();

// User class - represents a user in the social network
class User {
private:
    int id;
    string name;
    vector<User*>* friends; // list of friends (connections)
    
public:
    User() : id(0), name(""), friends(new vector<User*>()) {} // Default constructor  
    User(int userId, string userName) {  id = userId; name = userName; } // Constructor
    int getIdOfUser() const{ return id; }
    string getNameOfUser() const { return name; }
    void addFriend(User* newFriend) { friends->push_back(newFriend);} // Add a friend to the user's friend list
    vector<User*>* getFriendsOfUser() const { return friends;};  // Get the list of friends
};

// SocialNetwork class - manages all users and friendships
class SocialNetwork {
private:
    vector<User*>* users; // list of all users in the network
    
public:
    SocialNetwork(){  users = new vector<User*>(); }
    ~SocialNetwork() { delete users; }  // deletes the vector of user pointers but not pointers themselves }
    void addUser(User newUser) { users->push_back(newUser); } // create a pointer to a new user object on heap   
    void addFriendship(int userId1, int userId2) { // Create a friendship between two users
        
        }
    User* findUser(int id) {  // Find a user by ID
        for (int i = 0; i < users->size(); i++) {
            if (users->at(i)->getIdOfUser() == id) {
                    return users->at(i);
            }
        }
    }; 
    vector<User*>* getFriendsOfUser(int userId) { // Get all friends of a user
        return users;
    }; 
    void displayNetwork(); // Print all users and their friends
};

int main() {
    SocialNetwork* ericGram = new SocialNetwork();
    
    startMenu();
    
    for (int i = 0; i < 5; i++) {
        int ID;
        string name;
        cin >> ID;
        cin >> name;
    }

    return 0;
}

void startMenu() {
    cout << "ERICGRAM - A SIMPLE SOCIAL NETWORK" << endl;
    cout << "-----------------------------------" << endl;
    cout << "1. Add Users" << endl << "2. Add Friendships" << endl << "3. Search For Users" << endl;
    cout << "4. Display all users on Network (including friends)" << endl  << "5. Exit" << endl;
    cout << "-----------------------------------" << endl;
};