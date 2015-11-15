#ifndef WALL_POST_H
#define WALL_POST_H
#include <string>
#include <ctime>

using namespace std;

class WallPost
{
 private:
  string domain_name;
  string author_username;
  string text;
  string time_created;

 public:	
  WallPost() {}
  WallPost(string author_username, string text);
  WallPost(string author_username, string text, string time_created);
  ~WallPost();

  bool operator == (const WallPost& w) const;
  string GetText();
  string GetTimeCreated();
  string GetAuthorUsername();

  void SetText(string text);
  bool SetTimeCreated(string time_created);
  void SetAuthorUsername(string author_username);
  void SetDomainName(string domain_name);
  string GetDomainName();

  string WallPostToString();
  void ConstructFromString(string data);
};
#endif
