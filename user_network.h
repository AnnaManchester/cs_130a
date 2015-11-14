#ifndef USER_NETWORK_H
#define USER_NETWORK_H
#include "doubly_linked_list.h"
#include "user.h"

class User;

class UserNetwork {
private:
	DoublyLinkedList<User> users;
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
};
#endif
