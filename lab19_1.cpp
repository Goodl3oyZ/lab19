#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

char score2grade(int score)
{
    if (score >= 80)
        return 'A';
    if (score >= 70)
        return 'B';
    if (score >= 60)
        return 'C';
    if (score >= 50)
        return 'D';
    else
        return 'F';
}

string toUpperStr(string x)
{
    string y = x;
    for (unsigned i = 0; i < x.size(); i++)
        y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &score, vector<char> &grades)
{
    ifstream source(filename);
    char format[] = "%[^:]: %d %d %d";
    char m[30];
    int x, y, z;
    string textline = "";
    while (getline(source, textline))
    {
        
        sscanf(textline.c_str(), format, m, &x, &y, &z);
        names.push_back(m);
        int sum = x + y + z;
        score.push_back(sum);
        grades.push_back(score2grade(sum));
    }
}

void getCommand(string &command, string &key)
{
    char cmd[6], k[100];
    string input;
    cout << "Please input your command: ";
    getline(cin, input);

    sscanf(input.c_str(), "%s %[^:]", cmd, k);
    command = cmd;
    key = k;
}

void searchName(vector<string> names, vector<int> score, vector<char> grades, string key)
{
    string name = "";
    int index ;
  
    for (unsigned int i = 0; i < names.size(); i++)
    {
        
        if (key.compare(toUpperStr(names[i])) == 0)
        { index = i ;
            name = names[i];
            break;
        }
    }

    if (name.size() == 0)
    {
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
    else
    {   
        cout << "---------------------------------\n";
        cout << name << "'s score = " << score[index] << "\n";
        cout << name << "'s grade = " << grades[index]<< "\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key)
{
    cout << "---------------------------------\n";
    for(unsigned int i=0;i< names.size();i++){
        if(key[0]==grades[i]){       
            cout << names[i] <<" (" << scores[i] << ")\n" ;
        }
    }
    cout << "---------------------------------\n";
}
int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}