#include "wall_post.h"
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

bool WallPost::operator == (const WallPost& w) const {
	if (w.author_username != author_username || w.text != text || w.time_created != time_created)
		return false;
	return true;
}


WallPost::WallPost(string author_username, string text)
{
  this->author_username = author_username;
  this->text = text;
  //next version will extract hour:min:sec from time
  time_t current_time;
  time(&current_time);
  time_created = ctime(&current_time);
}
WallPost::WallPost(string author_username, string text, string time_created)
{
  this->author_username = author_username;
  this->text = text;
  this->time_created = time_created;
}
WallPost::~WallPost()
{
  //intentinally left blank
}
string WallPost::GetText()
{
  return text;
}
string WallPost::GetTimeCreated()
{
  return time_created;
}
string WallPost::GetAuthorUsername()
{
  return author_username;
}
void WallPost::SetText(string text)
{
  this->text = text;
}
bool WallPost::SetTimeCreated(string time_created)
{
  //next version will check if time is valid
  //and will return if not valid
  this->time_created = time_created;
  return true;
}
void WallPost::SetAuthorUsername(string author_username)
{
  this->author_username = author_username;
}

void WallPost::SetDomainName(string domain_name) 
{
  this->domain_name = domain_name;
}

string WallPost::GetDomainName()
{
  return domain_name;
}


string WallPost::WallPostToString()
{
  string wall_post_as_string = "";
  wall_post_as_string += "DOMAIN_NAME:";
  wall_post_as_string += this->GetDomainName();
  wall_post_as_string += "POST_CONTENT:";
  wall_post_as_string += this->GetText();
  wall_post_as_string += '\n';
  wall_post_as_string += "POST_AUTHOR:";
  wall_post_as_string += this->GetAuthorUsername();
  wall_post_as_string += '\n';
  wall_post_as_string += "CREATION_TIME:";
  wall_post_as_string += this->GetTimeCreated();
  return wall_post_as_string;
}
void WallPost::ConstructFromString(string data) {
	istringstream ss(data);
	while (ss) {
		string s;
		if (!getline(ss, s)) break;
		size_t found = s.find(':');
		if (found == string::npos) continue;
		const string keyword = s.substr(0, found);
		string value = s.substr(found+1);
    if (keyword == "DOMAIN_NAME")
      text = value;
		else if (keyword == "POST_CONTENT")
			text = value;
    else if (keyword == "POST_AUTHOR")
      author_username = value;
		else if (keyword == "CREATION_TIME")
			time_created = value;
	} 
}

