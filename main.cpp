#include <iostream>
#include <vector>
using namespace std;


// User class - represents a user in the social network
class User {
private:
    string email;
    string password;
    int phoneNumber;
    
public:
vector<User*>* friends; // list of friends (connections)
    string userName;
    string name;

    User() : friends(new vector<User*>()) {} // default constructor
    User(string userName, string name, int num, string email, string password) { // Constructor
        this->userName = userName; 
        this->name = name; 
        this->phoneNumber = num;
        this->email = email;
        this->password = password;
    };
    string getIdOfUser() const{ return userName; } // Get the username of the user
    string getNameOfUser() const { return name; } // Get the name of the user
    void addFriend(User* newFriend) { friends->push_back(newFriend);} // Add a friend to the user's friend list
    vector<User*>* getFriendsOfUser() const { return friends;};  // Get the list of friends
};

// SocialNetwork class - manages all users and friendships
class SocialNetwork {
private:
    vector<User*>* users; // list of all users in the network
    
public:
    SocialNetwork() : users(new vector<User*>(100)) {};
    ~SocialNetwork() { delete users; }  // deletes the vector of user pointers but not pointers themselves
    void addUser(User* newUser) { users->push_back(newUser); } // add a pointer to a user object on heap   
    void followUser(string userName1, string userName2) {  // Create a friendship between two users
        
    }
    User* findUser(string userName) {  // Find a user by ID
        for (int i = 0; i < users->size(); i++) {
            if (users->at(i)->getIdOfUser() == userName) {
                    return users->at(i);
            }
        }
        return nullptr;
    }; 
    vector<User*>* getFriendsOfUser(string userName) { // Get all friends of a user
        return users;
    }; 
    void displayNetwork(); // Print all users and their friends
};

void startMenu();

void signUpScreen(SocialNetwork*& ericGram, User*& user);

int main() {
    SocialNetwork* ericGram = new SocialNetwork();
    
    startMenu();
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        User* user;
        signUpScreen(ericGram, user);
        
        startMenu();
        
    }
    return 0;
}

void startMenu() {
    cout << "\nERICGRAM - A SIMPLE SOCIAL NETWORK" << '\n';
    cout << "-----------------------------------" << '\n';
    cout << "1. Create New Account" << '\n' << "2. Add Friends" << '\n' << "3. Search For Users" << '\n';
    cout << "4. Display all users on Network (including friends)" << '\n'  << "5. Exit" << '\n';
    cout << "-----------------------------------" << '\n';
};

void signUpScreen(SocialNetwork*& ericGram, User*& user) {
    cout << "\nSIGN UP WITH ERICGRAM" << '\n';
    cout << "---------------------" << '\n';
    cout << "Enter your username: ";
    string userName;
    cin.ignore();
    getline(cin, userName);
    cout << "Enter your name: ";
    string name;
    int phoneNumber;
    cin >> phoneNumber;
    cout << "Enter your email: ";
    string email;
    getline(cin, email);
    cout << "Enter your password: ";
    string password;
    getline(cin, password);
    user = new User(userName, name, phoneNumber, email, password);
    ericGram->addUser(user);
    cout << "Account created successfully!" << '\n' << user->getIdOfUser();
};