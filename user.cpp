#include "user.h"
#include "wall_post.h"
#include "basic.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

bool User::operator == (const User &u) const {
   if (u.username != username
	|| u.realname != realname 
	|| u.password != password 
	|| u.birthday != birthday)
	return false;
  return true;
}

User::User(string uname, string pass, string rname, string bday, Wall* w, UserNetwork* mynetwork) {
	wall = w;
	username = uname;
	password = pass;
	realname = rname;
	birthday = bday;
	network = mynetwork;
}

User::~User() {
	if (wall) delete wall; //This is done by destructor of Wall in part 4. 
}

void User::AddWallPost(string text) {
	if (wall) {
		WallPost *post = new WallPost(username,text);
		wall->AddPost(*post);
	} 
}

WallPost User::AddWallPost(string authorname, string text) {
	if (wall) {
		WallPost *post = new WallPost(authorname,text);
		wall->AddPost(*post);
		post->SetDomainName(username);
		return *post;
	} 
	cout << "Error: no wall." << endl;
	exit(1);
}		

WallPost User::AddResponse(int post_index, string authorname, string post) {
	if (wall && post_index > 0 && post_index <= wall->GetWallSize()) {
		WallPost *resp = new WallPost(authorname, post);
		resp->SetResponseFlag();
		resp->SetDomainName(username);
		wall->AddResponseToPost(post_index, *resp);
		return *resp;
	} 
	else {
		cout << "Error: failed to add response." << endl;
	}
}

void User::Remember(string friendname, WallPost& post) {
		memory.push_back(make_pair(friendname, post));
}

void User::DeleteWallPost() {
	if (wall->GetWallSize() == 0) {
		cout << "No post to delete." << endl;
		cout << endl;
		return;
	}
	WallPost pp = wall->RemovePost();
	if (pp.GetAuthorUsername() != username) {
		User* frd = QueryFriend(pp.GetAuthorUsername());
		frd->DeleteFromMemory(pp);
	}
	if (pp.IsResponse())
		return;
	vector<WallPost*> resps = pp.GetAllResponses();
	vector<WallPost*>::iterator it;
	for (it = resps.begin(); it != resps.end(); it++) {
		if ((*it)->GetAuthorUsername() != username) {
			User* frd = QueryFriend((*it)->GetAuthorUsername());
			frd->DeleteFromMemory(**it);
		}
		DeleteWallPost(**it);
	}

}

void User::DeleteWallPost(WallPost& post) {
	wall->RemovePost(post);
}

void User::DeleteFromFriendWall() {
	cout << "Your posts on friends' walls: " << endl;
	MEM::iterator it;
	int post_index = 0;
	for (it = memory.begin(); it != memory.end(); it++) {
			cout << "Post Index: " << ++post_index << endl;
			cout << (it->second).WallPostToString() << endl;
	}
	cout << "Input post index to delete: " << endl;
 	int idx_del;
	while (!ReadInt(idx_del) || idx_del > post_index)
	{
		cout << "Invalid post index. Enter again: " << endl;
    }
	User* frd = QueryFriend(memory[idx_del - 1].first);
	WallPost post = memory[idx_del - 1].second;
	memory.erase(memory.begin() + idx_del - 1);
	frd->DeleteWallPost(post);
}

void User::DeleteFromMemory(WallPost& post) {
	MEM::iterator it;
	for (it = memory.begin(); it != memory.end(); it++) {
		if (it->second == post) {
			memory.erase(it);
			break;
		}
	}
}


void User::DisplayWallPosts() {
	cout << username << "'s wall: " << endl;
	wall->DisplayPosts();
}

void User::DisplayMemory(){
	cout << username << "'s posts on his/her friends' walls: " << endl;
	MEM::iterator it;
	for (it = memory.begin(); it != memory.end(); it++) {
		cout << (it->second).WallPostToString() << endl;
	}
}

string User::RetrieveInfo() {
	string userinfo;
	userinfo = "USERNAME:" + username + "\n";
	userinfo += "PASSWORD:" + password + "\n";
	userinfo += "REALNAME:" + realname + "\n";
  	DoublyLinkedList<string>::iterator it;
  	for (it = friends.begin(); it != friends.end(); it++) {
		userinfo += "FRIEND:" + (*it) + "\n";
	}
	userinfo += "BIRTHDAY:" + birthday + "\n";
	userinfo += wall->WriteWallToString();
	return userinfo;
}

void User::ConstructUserFromString(string user_info) {
	istringstream ss(user_info);
	while (ss) {
		string s;
		if (!getline(ss, s)) break;
		size_t found = s.find(':');
		if (found == string::npos) continue;
		const string keyword = s.substr(0, found);
		string value = s.substr(found+1);
		if (keyword == "USERNAME")
			username = value;
		else if (keyword == "PASSWORD")
			password = value;
		else if (keyword == "REALNAME")	
			realname = value;
		else if (keyword == "FRIEND")
			friends.Add(value);
		else if (keyword == "BIRTHDAY") {
			birthday = value;
			wall = new Wall(username);
			string wall_data = ss.str().substr(ss.tellg());
			cout << "Adding user: " << username << endl;
			wall->CreateWallFromString(wall_data);
		}
	} 
}

void User::SearchFriend(string keyword) {
	network->SearchUser(keyword);
}

User* User::QueryFriend(string friendname) {
  	DoublyLinkedList<string>::iterator it;
  	for (it = friends.begin(); it != friends.end(); it++) {
  	    if (*it == friendname)
  	      return network->QueryUser(*it);
  	  }
	return NULL;
}

void User::AddFriend(string uname) {
	User* user = network->QueryUser(uname);
	if (user == NULL) {
		cout << "User not found! " << endl;
		return;
	}	
	if (QueryFriend(uname)) {
		cout << "This user is already your friend. " << endl;
		return;
	}
	if (user->RequestExists(username)) {
		cout << "Request already sent. " << endl;
		return;
	}
	FriendRequest request(username, this);
	cout << "Request sent." << endl;
	user->ReceiveRequest(request);
}

void User::ReceiveRequest(FriendRequest req) {
	requests.Add(req);
}


void User::ShowFriends() {
	cout << "Here are your friends: " << endl;
  	DoublyLinkedList<string>::iterator it;
  	int index = 1;
  	for (it = friends.begin(); it != friends.end(); it++) {
  		User* user = network->QueryUser(*it);
		cout << index << ". Username: " << (*it)
			<< ",  Realname: " << user->GetRealName() << endl; 
		index++;  
	}
	return;
}

void User::DeFriend(string uname) {
	User* ptr = QueryFriend(uname);
	if(!ptr) {
		cout << "This is not your friend." << endl;
		return;
	}
	friends.Remove(uname);
	cout << "Friend deleted." << endl; 
	ptr->RemoveFriend(username);	
}

void User::RemoveFriend(string uname) {
	User* ptr = QueryFriend(uname);
	if(!ptr) {
		return;
	}
	friends.Remove(uname);
}

void User::ShowRequests() {
	if (requests.size() == 0) {
		cout << "No friend requests. " << endl;
		return;
	}
	cout << "Here are your friend requests: " << endl;
  	int num = 1;
	DoublyLinkedList<FriendRequest>::iterator it;
  	for (it = requests.begin(); it != requests.end(); it++) {
		cout << num++ 
			<<". Request from: " << it->fname
			<< " Time: " << it->rtime << endl;   
	}
	return;
}

void User::InsertFriend(string uname) {
	friends.Add(uname);
} 

bool User::RequestExists(string uname) {
	DoublyLinkedList<FriendRequest>::iterator it;
  	for (it = requests.begin(); it != requests.end(); it++) {
		if (it->fname == uname) {
			return true;
		}
	}
	return false;
}

void User::Approve(int pos) {
	if (pos <= 0 || pos > requests.size()) {
		cout << "Invalid Range!" << endl;
		return;
	}
	FriendRequest req = requests.get(pos - 1); 
	friends.Add(req.fname);
	req.friendptr->InsertFriend(username);
	cout << "Request approved, start chatting!" << endl;
	requests.remove(pos - 1);
	return;
}

void User::Ignore(int pos) {
	if (pos <= 0 || pos > requests.size()) {
		cout << "Invalid Range!" << endl;
		return;
	}
	requests.remove(pos - 1);
	cout << "Request ignored." << endl;
	return; 
}


