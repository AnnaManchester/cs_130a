#include "user_network.h"
#include "wall.h"
#include "user.h"
#include "doubly_linked_list.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <queue>
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

int UserNetwork::Distance(string user1, string user2) {
	unordered_map<string, Node> nodes;
	DoublyLinkedList<User>::iterator it;
  	for (it = users.begin(); it != users.end(); it++) {
  		string uname = it->GetUserName();
  		Node node;
  		node.SetNodeName(uname);
  		nodes[uname] = node;
	}
	queue<Node> q;
	Node& node1 = nodes[user1];
	node1.SetState(Node::State::GREY);
	node1.SetDistance(0);
	q.push(node1);
	while (q.size() > 0) {
		Node& tmp = q.front();
		if (tmp.GetNodeName() == user2) {
			Node* prev = tmp.GetPrevious();
			cout << "Here is the path from " << user2 << " to " << user1 << ": "<< endl;
			cout << user2;
			while (prev) {
				cout << " -> " << prev->GetNodeName();
				prev = prev->GetPrevious();
			}
			cout << endl;
			return tmp.GetDistance();
		}
		set<string>::iterator it;
		set<string> &frds = network[tmp.GetNodeName()];
		for (it = frds.begin(); it != frds.end(); it++) {
			Node& frd = nodes[*it];
			if (frd.GetState() == Node::State::WHITE) {
				frd.SetDistance(tmp.GetDistance() + 1);
				frd.SetPrevious(&tmp);
				frd.SetState(Node::State::GREY);
				q.push(frd);
			}
		}
		q.pop();
		tmp.SetState(Node::State::BLACK);
	}
	return -1;
}


//void FindFriendWithDistance(string username, int distance

void UserNetwork::UpdateNetwork(string user1, string user2, bool is_adding) {
	set<string> &frd1 = network[user1];
	set<string> &frd2 = network[user2];
	if (is_adding) {
		frd1.insert(user2);
		frd2.insert(user1);
	}
	else {
		set<string>::iterator it1 = frd1.find(user2), it2 = frd2.find(user1);
		if (it1 != frd1.end()) {
			frd1.erase(it1);
		}
		if (it2 != frd2.end()) {
			frd2.erase(it2);
		}
	}
}
