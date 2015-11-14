#ifndef USER_H
#define USER_H
#include <string>
#include <ctime>
#include "doubly_linked_list.h"
#include "wall.h"
#include "user_network.h"

class UserNetwork;

class User
{
	class FriendRequest {
	public:
		string fname;
		string rtime;
		User* friendptr;
		FriendRequest() {}
		FriendRequest(string name, User* ptr) {
			fname = name;
			time_t t;
			time(&t);
			rtime = ctime(&t);
			friendptr = ptr;
		}
	};


private:
	Wall* wall;
	string username;
	string password;
	string realname;
	string birthday;
	DoublyLinkedList<string> friends;
	DoublyLinkedList<FriendRequest> requests;
	UserNetwork* network; 
public:
	User() {}
	User(UserNetwork* mynetwork) {network = mynetwork;}
	User(string uname, string pass, string rname, string bday, Wall* w, UserNetwork* mynetwork);
	~User();
	bool operator == (const User &u) const;
	string GetUserName() {
		return username;
	}
	void SetUserName(string name) {
		username = name;
	}
	string GetPassword() {
		return password;
	}
	void SetPassword(string pass) {
		password = pass;
	}
	string GetRealName() {
		return realname;
	}
	void SetRealName(string r_name) {
		realname = r_name;
	}
	string GetBirthday() {
		return birthday;
	}
	void SetBirthday(string bday) {
		birthday = bday;
	}
	void AddWallPost(string text);
	void DeleteWallPost();
	string RetrieveInfo();
	void ConstructUserFromString(string user_info);
	void DisplayWallPosts();
	void SearchFriend(string keyword);
	User* QueryFriend(string friendname);	
	void ReceiveRequest(FriendRequest req);
	void AddFriend(string uname);
	void ShowFriends();
	void DeFriend(string uname);
	void RemoveFriend(string uname);
	void ShowRequests();
	bool RequestExists(string uname); 
	void InsertFriend(string uname);
	void Approve(int pos);
	void Ignore(int pos);	
};
#endif

