#include<map>
#include<iostream>
#include<algorithm>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;
  
int process (string filename, string theWord) {
  // map<string,int> word_count;
  ifstream infile;
  // 1024 is a joke
  char line[1024];

  infile.open(filename.c_str(),ios::in);
  int result = 0;
  string::size_type position;

  //read line from file and process
  while (infile.getline(line, 1024, '\n')) {
    string word;
    istringstream str(line);
    while (str >> word) {
      position = word.find(theWord);
      if (position != word.npos) {
        cout << position;
        result++;
      }
    }
  }
  return result;
}

int main (void) {

  // 128 means file `table_of_content.txt` should be less than 128 lines.
  string files[128];
  char line[1024];
  string action;
  ifstream infile;
  string tableOfContent = "table_of_content.txt";
  infile.open(tableOfContent.c_str(),ios::in);
  for (int j = 0; infile.getline(line, 1024, '\n'); j++) {
    string targetFile;
    istringstream str(line);
    str >> targetFile;
    files[j] = targetFile;
  }

  int fileNum = 0;
  for (int num = 0; num < 128; num++) {
    if (!files[num].empty()) fileNum++;
  }

  cout << fileNum << " students' text files are read." << endl;
  cout << "------\n" << "Options:\n" <<"1. Keyword Search\n2. Exit" << endl;
  
  cin >> action;
  while (action == "1") {
    cout << "Your choice:" << endl;
    string choiceWord;
    cin >> choiceWord;
    for (int i = 0; i < 128; i++) {
      if (!files[i].empty()) {
        // Print result here.
        cout << files[i] << " " << process(files[i], choiceWord) << endl;
      } else continue;
    }
    cout << "------\n" << "Options:\n" <<"1. Keyword Search\n2. Exit"<< endl;
    cin >> action;
  }
}
