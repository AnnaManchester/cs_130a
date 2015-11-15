#include <iostream>
#include <string>
#include <stdlib.h>
#include "user_network.h"
#include "wall_post.h"
#include "user.h"
#include "basic.h"
#include <fstream>
#include <sstream>

using namespace std;

void menu(User* user) {
	string oper;
	user->ShowRequests();
	while(true) {
		cout << endl << endl << endl;
		cout << "Enter your command (type Help for help): " << endl;
		getline(cin, oper);
		if (oper == "Quit") {
			return;
		} else if (oper == "Dis") {
			user->DisplayWallPosts();
		} else if (oper == "Help") {
			cout << "Available Commands:" << endl;
			cout << "  Help : show this message." << endl;
			cout << "  Dis : show all posts of this user." << endl;
			cout << "  Add: add post" << endl;
			cout << "  Del: delete post" << endl;
			cout << "  Save: dump user data to a file" << endl;
			cout << "  Read: read user data from a file" << endl;
			cout << "  Search: search users by name" << endl;
			cout << "  AddFriend: add a friend by his/her username" << endl;
			cout << "  ShowFriends: show current friends list" << endl;
			cout << "  DeFriend: delete a friend by his/her username" << endl;
			cout << "  ShowRequests: show all pending friend requests" << endl;
			cout << "  Approve: approve a friend request"  << endl;
			cout << "  PostTo: create a new post on a friend’s wall"  << endl;
			cout << "  Ignore: ignore a friend request (request deleted after this)"  << endl;
			cout << "  Quit : exit." << endl;
		} else if (oper == "Add") {
			cout << "Enter your post: " << endl;
			string post;
			getline(cin, post);
			user->AddWallPost(post);
		} else if (oper == "Del") {
			cout << "Choose from the following options: " << endl;
			cout << "1. delete posts on your own wall " << endl;
			cout << "2. delete your posts on friend’s walls " << endl;
			int option;
			ReadInt(option);
			if (option == 1) {
				user->DeleteWallPost();
			}
			else if (option == 2) {
				user->DeleteFromFriendWall();
			}
			
		} else if (oper == "Save") {
			cout << "Enter file name: " << endl;
			string fname;
			getline(cin, fname);
			ofstream output_file(fname);
			output_file << user->RetrieveInfo();
			output_file.close();
			cout << "User data saved." << endl;
		} else if (oper == "Read") {
			cout << "Enter file name: " << endl;
			string fname;
			getline(cin, fname);
			ifstream input_file(fname);
			if (!input_file) {
				cout << "Invalid file." << endl;
				continue;
			}
			string user_data ((std::istreambuf_iterator<char>(input_file)),
		     			  (std::istreambuf_iterator<char>()));
			user->ConstructUserFromString(user_data);
			cout << "User data restored." << endl;
		} else if (oper == "Search") {
 			cout << "Enter keyword: " << endl;
			string keyword;
			getline(cin, keyword);
			user->SearchFriend(keyword);
		} else if (oper == "AddFriend") {
			cout << "Enter friend's username: " << endl;
			string uname;
			getline(cin, uname);
			user->AddFriend(uname);
		} else if (oper == "ShowFriends") {
			user->ShowFriends();
		} else if (oper == "DeFriend") {
			cout << "Enter friend's username: " << endl;
			string uname;
			getline(cin, uname);
			user->DeFriend(uname);
		} else if (oper == "ShowRequests") {
			user->ShowRequests();	
		} else if (oper == "Approve") {
 			cout << "Enter index to approve: " << endl;
			int num;
			ReadInt(num);
			user->Approve(num);
		} else if (oper == "Ignore") {
 			cout << "Enter index to ignore: " << endl;
			int num;
			ReadInt(num);
			user->Ignore(num);
		} else if (oper == "PostTo") {
			cout << "Here are your friends:" << endl;
			user->ShowFriends();
			User* frd = NULL;
			string uname;
			while (true) {
				cout << "Post on which friend's wall? Enter his/her username: " << endl;
				getline(cin, uname);
				frd = user->QueryFriend(uname);
				if (!frd) cout << "This is not your friend. Re-enter: " << endl;
				else break;
			}
			cout << "Enter your post to add to this friend's wall: " << endl;
			string post;
			getline(cin, post);
			WallPost pp = frd->AddWallPost(user->GetUserName(), post);
			user->Remember(uname, pp);
		}
		else {
			cout << "Invalid command." << endl;
		}

	}
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Usage:./run datafile." << endl;
		return -1;
	} 
	UserNetwork * network = new UserNetwork;
	network->CreateUsersFromFile(string(argv[1]));
 	int option;
	string uname, pass, pass1, pass2, rname, bday;
	string input = "";
	User *user = NULL;
	while (true) {
		cout << endl << endl << endl << "What do you want to do?" << endl;
		cout << "Option 1: Create a new user." << endl;
 		cout << "Option 2: Log in."  << endl;
		cout << "Option 3: Quit."  << endl; 
		cout << "Please input your selection: " << endl;
		if (!ReadInt(option) || option > 3 || option < 1) {
			cout << "Invalid option, please input again: " << endl;
			continue;
		} 
		switch (option) {
		case 1:
			cout << "Create a new user: " << endl;
			cout << "Please input your username: " << endl;
			getline(cin, uname);
			while (network->UserExists(uname)) {
				cout << "Username already exists. Re-enter: " << endl;
				getline(cin, uname);
			}
		
			while (true){
				cout << "Set your password: " << endl;
				getline(cin, pass1);
				cout << "Confirm your password: " << endl;
				getline(cin, pass2);
				if (pass1 != pass2) {
					cout << "Passwords don't match. Re-enter. " << endl;
					continue;
				}
				break;
			}
			cout << "Enter your realname: " << endl;
			getline(cin, rname);
			cout << "Enter your birthday [MM/DD/YYYY] :  " << endl;
			getline(cin, bday);
			network->AddUser(uname, pass1, rname, bday);
			cout << "User " << uname << " added" << endl << endl;
			break;
		case 2:
			cout << "Enter username: " << endl;
			getline(cin, uname);
			while (!network->UserExists(uname)) {
				cout << "Username doesn't exist. Re-enter: " << endl;
				getline(cin, uname);
			}
			
			while (true){
				cout << "Enter your password: " << endl;
				getline(cin, pass);
				user = network->AuthorizeUser(uname, pass);
			        if (!user) {
					cout << "Wrong password. Re-enter. " << endl;
					continue;
				}
				break;
			}
			menu(user);
			break;
		case 3:
			network->WriteUsersToFile(string(argv[1]));
			return 0;
		} 
	}
} 
