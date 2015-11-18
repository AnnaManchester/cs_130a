#ifndef USER_NETWORK_H
#define USER_NETWORK_H
#include "doubly_linked_list.h"
#include "user.h"
#include <set>
#include <unordered_map>
#include <climits>

using namespace std;

typedef unordered_map<string,set<string>> NET;

class User;

class UserNetwork {
private:
	DoublyLinkedList<User> users;
	NET network;

	class NetworkNode {
	public:
		enum State {
			WHITE,
			GREY,
			BLACK
		};
	private:
		string uname;
		State state;
		int dist;
		NetworkNode* prev;
	public:
		NetworkNode(string name) {
			uname = name;
			state = WHITE;
			dist = INT_MAX;
			prev = NULL;
		}
		NetworkNode() {
			state = WHITE;
			dist = INT_MAX;
			prev = NULL; 
		}
		~NetworkNode() {}

		void SetNodeName(string nname) {uname = nname;}
		string GetNodeName() {return uname;}
		void SetState(State color) {state = color;}
		State GetState() {return state;}
		void SetDistance(int n) {dist = n;}
		int GetDistance() {return dist;}
		void SetPrevious(NetworkNode* previous) {prev = previous;}
		NetworkNode* GetPrevious() {return prev;}
	};
public:
	UserNetwork() {}
	~UserNetwork() {}

	User* QueryUser(string uname);
	bool UserExists(string uname);	
	void AddUser(string uname, string pass, string rname, string bday);
	void DeleteUser(string uname);
	void WriteUsersToFile(string fname);
	void CreateUsersFromFile(string fname);
	User* AuthorizeUser(string uname, string pass);
	void SearchUser(string keyword);

	int Distance(string user1, string user2);
	void FindFriendWithDistance(string username, int distance);
	void UpdateNetwork(string user1, string user2, bool is_adding);
};
#endif
