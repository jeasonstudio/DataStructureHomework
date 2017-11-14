#include<map>  
#include<iostream>  
#include<algorithm>  
#include<string>  
#include<sstream>  
#include<fstream>  
using namespace std;  
  
void process (string filename, string theWord) {
  map<string,int> word_count;
  ifstream infile;
  // 1024 is a joke
  char line[1024];
   
  infile.open(filename.c_str(),ios::in);

  //read line from file and process
  while (infile.getline(line, 1024, '\n')) {
    string word;
    istringstream str(line);
    while (str >> word) {
      ++word_count[word];
    }
  }

  for (map<string, int>::iterator it = word_count.begin(); it != word_count.end(); ++it )
    if (it->first == theWord)
      cout << filename <<" "<<it->second<<endl;
}

int main (void) {

  string files[4] = {"Andy.txt", "Novak.txt", "Rafa.txt", "Roger.txt"};
  string action;

  cout << "4 students' text files are read." << endl;
  cout << "------\n" << "Options:\n" <<"1. Keyword Search\n2. Exit" << endl;
  
  cin >> action;
  while (action == "1") {
    cout << "Your choice:" << endl;
    string choiceWord;
    cin >> choiceWord;
    for (int i = 0; i < 4; i++) {
      process(files[i], choiceWord);
    }
    cout << "------\n" << "Options:\n" <<"1. Keyword Search\n2.Exit"<< endl;
    cin >> action;
  }
}
