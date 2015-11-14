#include "doubly_linked_list.h"
#include "basic.h"
#include "wall.h"
#include "wall_post.h"
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
  wall_posts.insert(0, wall_post);
}

void Wall::AddPost(int pos, WallPost wall_post)
{
  wall_posts.insert(pos, wall_post);
}

void Wall::CreateWallFromString(string data) 
{
	size_t cur_pos = data.find("POST_CONTENT", 0);
	if (cur_pos == string::npos) {
		cout << "No post data found." << endl;
		return;
	}
	size_t next_pos = data.find("POST_CONTENT", cur_pos+1);
	string post_data;
	while (next_pos != string::npos) {
		post_data = data.substr(cur_pos, next_pos - cur_pos);
		WallPost post = WallPost();
		post.SetAuthorUsername(username);
		post.ConstructFromString(post_data);
		wall_posts.insert(0, post);
		cur_pos = next_pos;
		next_pos = data.find("POST_CONTENT", cur_pos + 1);
	}
	post_data = data.substr(cur_pos, data.length());
	WallPost post  = WallPost();
	post.SetAuthorUsername(username);
	post.ConstructFromString(post_data);
	wall_posts.insert(0,post);
}


string Wall::GetUsername()
{
  return username;
}

void Wall::RemovePost()
{
  int post_index = 1;
  cout << "Here are all your posts: " << endl;
  for (post_index = 0; post_index < wall_posts.size(); post_index++)
    {
      cout << "Post Index: " << post_index+1 << endl;
      cout << wall_posts.get(post_index).WallPostToString() << endl;
    }
  if (post_index == 0)
    {
      cout << "No wall post to delete." <<endl;
      return;
    }
  cout << "Input post index to delete: " << endl;
  int idx_del;
  while (!ReadInt(idx_del) || idx_del > post_index)
    {
      cout << "Invalid post index. Enter again: " << endl;
    }
  wall_posts.remove(idx_del-1);
 }

void Wall::RemovePost(int pos)
{
  wall_posts.remove(pos);
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
