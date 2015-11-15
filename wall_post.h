#ifndef WALL_POST_H
#define WALL_POST_H
#include <string>
#include <ctime>
#include <vector>

using namespace std;

class WallPost
{
 private:
  string domain_name;
  string author_username;
  string text;
  string time_created;
  bool is_response;
  vector<WallPost*> resps;
  WallPost* parent;

 public:	
  WallPost() {is_response = false;}
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
  void SetResponseFlag() {is_response = true;}
  bool IsResponse() {return is_response;}


  string WallPostToString();
  void ConstructFromString(string data);

  void SetParent(WallPost* post) {parent = post;}
  WallPost* GetParent() {return parent;}
  void AddResponse(WallPost* post) {resps.push_back(post);}
  void DeleteResponse(WallPost post);
  vector<WallPost*> & GetAllResponses() {return resps;}
};
#endif
