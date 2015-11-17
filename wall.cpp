#include "doubly_linked_list.h"
#include "basic.h"
#include "wall.h"
#include "wall_post.h"
#include "user.h"
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

Wall::Wall(string username)
{
  this->username = username;
}

void Wall::AddPost(WallPost wall_post)
{
  wall_post.SetDomainName(username);
  wall_posts.insert(wall_posts.size(), wall_post);
}

void Wall::AddPost(int pos, WallPost wall_post)
{
  wall_post.SetDomainName(username);
  wall_posts.insert(pos, wall_post);
}

void Wall::AddResponseToPost(int post_index, WallPost& post) {
  WallPost* parent = &(wall_posts.get(post_index - 1));
  if (parent->IsResponse()){
      parent = parent->GetParent();
  }
  post.SetParent(parent);
  post.SetDomainName(username);
  parent->AddResponse(&post);
  wall_posts.insert(post_index, post);
}

void Wall::CreateWallFromString(string data) 
{
	size_t cur_pos = data.find("DOMAIN_NAME", 0);
	if (cur_pos == string::npos) {
		cout << "No post data found." << endl;
		return;
	}
	size_t next_pos = data.find("DOMAIN_NAME", cur_pos+1);
	string post_data;
	while (next_pos != string::npos) {
		post_data = data.substr(cur_pos, next_pos - cur_pos);
		WallPost post = WallPost();
		post.SetAuthorUsername(username);
		post.ConstructFromString(post_data);
		wall_posts.insert(wall_posts.size(), post);
		cur_pos = next_pos;
		next_pos = data.find("DOMAIN_NAME", cur_pos + 1);
	}
	post_data = data.substr(cur_pos, data.length());
	WallPost post  = WallPost();
	post.SetAuthorUsername(username);
	post.ConstructFromString(post_data);
	wall_posts.insert(wall_posts.size(),post);
}

void Wall::ConstructPostResponseRelationship(User* user) {
  DoublyLinkedList<WallPost>::iterator it;
  WallPost* parent = NULL;
  for (it = wall_posts.begin(); it != wall_posts.end(); it++) {
    if ((*it).IsResponse()) {
      (*it).SetParent(parent);
      parent->AddResponse(&(*it));
    }
    else {
      parent = &(*it);
    }
    if ((*it).GetAuthorUsername() != user->GetUserName()) {
      User* ptr = user->QueryFriend((*it).GetAuthorUsername());
      ptr->Remember(user->GetUserName(), *it);
    }
  }
}

string Wall::GetUsername()
{
  return username;
}

int Wall::ChoosePost() {
  int post_index = 0;
  int idx_del;
  cout << "Here are all your posts: " << endl;
  for (post_index = 0; post_index < wall_posts.size(); post_index++)
    {
      cout << "Post Index: " << post_index+1 << endl;
      cout << wall_posts.get(post_index).WallPostToString() << endl;
    }
  cout << "Input post index to delete: " << endl;
  if (!ReadInt(idx_del) || idx_del > post_index) {
    cout << "Invalid post index. " << endl;
    return -1;
  }
  return idx_del - 1;
}

WallPost Wall::DeletePost(int idx_del)
{ 
  WallPost copy = wall_posts.get(idx_del);
  if (copy.IsResponse()) {
    WallPost* parent = copy.GetParent();
    parent->DeleteResponse(copy);
  }
  wall_posts.remove(idx_del);
  return copy;
 }

WallPost Wall::RemovePost(int pos)
{
  WallPost copy = wall_posts.get(pos);
  wall_posts.remove(pos);
  return copy;
}

int Wall::FindPostIndex(WallPost* post) {
  DoublyLinkedList<WallPost>::iterator it;
  int i = 0;
  for (it = wall_posts.begin(); it != wall_posts.end(); it++, i++) {
    if ((*it == *post)) {
      return i;
    }
  }
  return -1;
}

void Wall::SetUsername(string username)
{
  this->username = username;
}

string Wall::WriteWallToString()
{
  string wall_as_string = "";
  DoublyLinkedList<WallPost>::iterator it;
  for (it = wall_posts.begin(); it != wall_posts.end(); it++) {
    wall_as_string += (*it).WallPostToString();
    wall_as_string += '\n';
  }
  return wall_as_string;
}

int Wall::GetWallSize() {
  return wall_posts.size();
}

void Wall::DisplayPosts() {
  for (int post_index = 0; post_index < wall_posts.size(); post_index++)
    {
      cout << "Post Index: " << post_index + 1 << endl;
      cout << wall_posts.get(post_index).WallPostToString() << endl;
    }
}
