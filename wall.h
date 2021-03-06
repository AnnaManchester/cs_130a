#ifndef WALL_H
#define WALL_H
#include <string>
#include "wall_post.h"
#include "doubly_linked_list.h"
#include "user.h"

using namespace std;
class User;
class Wall
{
 private:
  string username;
 public:
  DoublyLinkedList<WallPost> wall_posts;

  //public:
  Wall(string username);
  void AddPost(WallPost wall_post);
  void AddPost(int pos, WallPost wall_post);
  void CreateWallFromString(string); //Wall will only have WallPosts given by the string parameter
  void ConstructPostResponseRelationship(User* user);
  string GetUsername();
  int ChoosePost();
  WallPost DeletePost(int idx_del);
  WallPost RemovePost(int pos);
  int FindPostIndex(WallPost* post);
  void SetUsername(string username);
  string WriteWallToString();
  int GetWallSize();
  void DisplayPosts();
  void AddResponseToPost(int post_index, WallPost& post); 
};
#endif
