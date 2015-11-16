#include "user_network.h"
#include "wall.h"
#include "user.h"
#include "doubly_linked_list.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

User* UserNetwork::QueryUser(string uname) {
  	DoublyLinkedList<User>::iterator it;
  	for (it = users.begin(); it != users.end(); it++) {
  	    if ((*it).GetUserName() == uname)
  	      return &(*it);
  	  }
	return NULL;
}

bool UserNetwork::UserExists(string uname) {
  	DoublyLinkedList<User>::iterator it;
  	for (it = users.begin(); it != users.end(); it++) {
  	    if ((*it).GetUserName() == uname)
  	      return true;
  	  }
  	return false;
}

void UserNetwork::AddUser(string uname, string pass, string rname, string bday) {
	if (UserExists(uname)) {
		return;
	}
	Wall* wall = new Wall(uname);
	User* user = new User(uname, pass, rname, bday, wall, this);
	users.insert(0, *user);
}


void UserNetwork::DeleteUser(string uname) {
  	DoublyLinkedList<User>::iterator it;
  	for (it = users.begin(); it != users.end(); it++) {
	    if ((*it).GetUserName() == uname)
	  	users.remove(it);
	}  
}
	


void UserNetwork::WriteUsersToFile(string fname) {
	ofstream output_file(fname);
  	DoublyLinkedList<User>::iterator it;
  	for (it = users.begin(); it != users.end(); it++) {
	    output_file << (*it).RetrieveInfo();
	}
	output_file.close();
}


void UserNetwork::CreateUsersFromFile(string fname) {
	ifstream input_file(fname);
	if (!input_file) {
		cout << "File doesn't exist." << endl;
		return;
	}
	cout << "Adding users from file: " << fname << endl;
	string data ((std::istreambuf_iterator<char>(input_file)),
		     (std::istreambuf_iterator<char>()));
	size_t cur_pos = data.find("USERNAME", 0);
	if (cur_pos == string::npos) {
		cout << "No user data found." << endl;
		return;
	}
	size_t next_pos = data.find("USERNAME", cur_pos+1);
	string user_data;
	while (next_pos != string::npos) {
		user_data = data.substr(cur_pos, next_pos - cur_pos);
		User *user = new User(this);
		user->ConstructUserFromString(user_data);
		users.insert(0, *user);
		cur_pos = next_pos;
		next_pos = data.find("USERNAME", cur_pos + 1);
	}
	user_data = data.substr(cur_pos, data.length());
	User *user = new User(this);
	user->ConstructUserFromString(user_data);
	users.insert(0, *user);
	input_file.close();
	DoublyLinkedList<User>::iterator it;
	for (it = users.begin(); it != users.end(); it++) {
		it->ConstructPostResponseRelationship();
	}
}

User* UserNetwork::AuthorizeUser(string uname, string pass) {
  	DoublyLinkedList<User>::iterator it;
  	for (it = users.begin(); it != users.end(); it++) {
  	    if ((*it).GetUserName() == uname && (*it).GetPassword() == pass)
  	      return &(*it);
  	  }
  	return NULL;
  
}

void UserNetwork::SearchUser(string keyword) {
  	transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
	DoublyLinkedList<User>::iterator it;
  	for (it = users.begin(); it != users.end(); it++) {
  		string uname = it->GetUserName();
		string rname = it->GetRealName();
		transform(uname.begin(), uname.end(), uname.begin(), ::tolower);
		transform(rname.begin(), rname.end(), rname.begin(), ::tolower);
		if(uname.find(keyword) != string::npos || rname.find(keyword) != string::npos) {
			cout << "Username: " << it->GetUserName() 
				<< " Realname: " << it->GetRealName() << endl;
		}
	}
}

