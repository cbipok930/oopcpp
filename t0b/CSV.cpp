#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
bool cmp(std::pair<std::string, int> a, std::pair<std::string, int> b) {
	return(a.second > b.second);
}
int main(int argc, char** argv) {
	using namespace std;
	if (argc == 1) {
		cout << "No args\n";
		return 1;
	}
	if (argc == 2){
	    cout << "No output arg\n";
	    return 1;
	}
	string file_name = argv[1];
	string out_name = argv[2];
	ifstream in_file;
	in_file.open(file_name);
	list<string> list_of_words;
	string word;
	int cnt_words = 0;
	string str_from_file;
	while (getline(in_file, str_from_file)) {
		for (int i = 0; i < str_from_file.length(); i++) {
			if (str_from_file[i] >= 'a' && str_from_file[i] <= 'z' ||
				str_from_file[i] >= 'A' && str_from_file[i] <= 'Z' ||
				str_from_file[i] >= '0' && str_from_file[i] <= '9')
			{
				char c = str_from_file[i];
				word.push_back(c);

			}
			else if (word.length() == 0) {
				continue;
			}
			else {
				list_of_words.push_back(word);
				word.clear();
				cnt_words += 1;
			}
		}
		if (word.length() > 0) {
			list_of_words.push_back(word);
			word.clear();
			cnt_words += 1;
		}
	}
	in_file.close();
	map<string, int> words_freqs;
	for (; list_of_words.size() !=0; ) {
		string word = list_of_words.front();
		list_of_words.pop_front();
		map<string, int>::iterator it;
		it = words_freqs.find(word);
		if (it != words_freqs.end()) {
			words_freqs[word] += 1;
		}
		else {
			words_freqs.insert(pair<string, int>(word, 1));
		}
	}
	list_of_words.clear();
	vector<pair<string, int>> vec_words_freqs;
	for (map<string, int>::iterator it = words_freqs.begin(); it != words_freqs.end(); it++) {
		vec_words_freqs.push_back(make_pair(it->first, it->second));
	}
	words_freqs.clear();
	std::sort(vec_words_freqs.begin(), vec_words_freqs.end(), cmp);
	ofstream out_file;
	out_file.open(out_name);
	for (vector<pair<string, int>>::iterator it = vec_words_freqs.begin(); it != vec_words_freqs.end(); it++) {
		double percent = ((double)it->second / (double)cnt_words * 100.0);
		cout.precision(3);
		out_file << it->first <<',' << it->second << ',' << percent <<'%'<<'\n' ;
	}
}
