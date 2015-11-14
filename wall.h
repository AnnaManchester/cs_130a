#ifndef WALL_H
#define WALL_H
#include <string>
#include "wall_post.h"
#include "doubly_linked_list.h"

using namespace std;

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
  
  string GetUsername();
  void RemovePost();
  void RemovePost(WallPost* post);
  void RemovePost(int pos);
  void SetUsername(string username);
  string WriteWallToString();
};
#endif
