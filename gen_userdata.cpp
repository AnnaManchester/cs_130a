#include <iostream>
#include <string>
#include <ctime>
#include <unordered_map>
#include <vector>
#define NAME_LEN 7 //length of username
#define RNAME_LEN 12 //length of real name
#define POST_LEN 40 //length of posts/responses
#define PASSWORD "root" //same password for all users
#define POST_NUM 10 //post number

using namespace std;


// this function is modified based on 
//http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
string gen_random_string(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    char s[POST_LEN + 10];
    for (int i = 0; i < len && i < POST_LEN + 10; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
    return string(s);
}

string gen_random_date() {
	int v1 = rand() % 30 + 1;
	int v2 = rand() % 12 + 1;
	int v3 = rand() % 60 + 1950;
	return to_string(v2) + "/"+ to_string(v1) + "/" + to_string(v3);
}

string gen_time() {
	time_t current_time;
	time(&current_time);
	string myctime = ctime(&current_time);
	myctime[ myctime.length() - 1 ] = '\0';
	return myctime;
}


int main() {
	int number = 10000;
	vector<string> names, rnames, birthdays;
	unordered_map<string, int> name_dict;
	for (int i = 0; i < number; i++) {
		string random_name = gen_random_string(NAME_LEN);
		while (name_dict.find(random_name) != name_dict.end()) {
			random_name = gen_random_string(NAME_LEN);
		}
		name_dict[random_name] = 1;
		names.push_back(random_name);
		rnames.push_back(gen_random_string(RNAME_LEN));
		birthdays.push_back(gen_random_date());
	}
	unordered_map<int, vector<int>> m;
	for (int i = 0; i < number; i++) {
		for (int j = i + 1; j < number; j++) {
			if (rand() % 1000 < 10) {
				m[i].push_back(j);
				m[j].push_back(i);
			}
		}
	}

	for (int i = 0; i < number; i++) {
		cout << "USERNAME:" << names[i] << endl;
		cout << "PASSWORD:" << PASSWORD << endl;
		cout << "REALNAME:" << rnames[i] << endl;
		for (int j = 0; j < m[i].size(); j++) {
			cout << "FRIEND:" << names[m[i][j]] << endl;
		}
		cout << "BIRTHDAY:" << birthdays[i] << endl;
		int postnum = rand() % POST_NUM;
		for (int j = 0; j < postnum; j++) {
			if (rand() % 100 < 50 || j == 0) {
				cout << "DOMAIN_NAME:" << names[i] << endl;
				cout << "POST_CONTENT:" << gen_random_string(POST_LEN) << endl;
				if (m[i].size() == 0) {
					cout << "POST_AUTHOR:" << names[i] << endl;
				}
				else {
					int k = rand() % m[i].size();
					if (rand() % 100 < 50) {
						cout << "POST_AUTHOR:" << names[m[i][k]] << endl;
					}
					else {
						cout << "POST_AUTHOR:" << names[i] << endl;
					}
				}
				cout << "CREATION_TIME:" << gen_time() << endl;
			}
			else {
				cout << "DOMAIN_NAME:" << names[i] << endl;
				cout << "RESPONSE_CONTENT:" << gen_random_string(POST_LEN) << endl;
				if (m[i].size() == 0) {
					cout << "RESPONSE_AUTHOR:" << names[i] << endl;
				}
				else {
					int k = rand() % m[i].size();
					if (rand() % 100 < 50) {
						cout << "RESPONSE_AUTHOR:" << names[m[i][k]] << endl;
					}
					else {
						cout << "RESPONSE_AUTHOR:" << names[i] << endl;
					}					
				}
				cout << "CREATION_TIME:" << gen_time() << endl;
			}
		}
	}
	return 0;
}