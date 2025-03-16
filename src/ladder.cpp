#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error: " << word1 << " and " << word2 << " " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    // if same word --> never adjacent
    if (str1 == str2) return false;
    
    int len1 = str1.length();
    int len2 = str2.length();

    // if len diff > 1, can't be adjacent
    // adjacanecy only applies to one insertion/deletion/substitution
    if ( abs(len1 - len2) > 1 ) return false;

    int i = 0;
    int j = 0;
    int differences = 0;

    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            ++differences;
            
            // immediately break when differences > 1 
            // b/c more than one change is not allowed
            if (differences > 1) return false;

            // if lens are diff, move pointer of longer word
            if (len1 > len2) ++i; // deletion case
            else if (len1 < len2) ++j; // insertion case;
            else { // substition case
                ++i;
                ++j;
            }
        }
        else {
            ++i;
            ++j;
        }
    }

    // finished comparing but one word has an extra chr, count as diff
    if (i < len1 || j < len2) ++differences;

    return differences == 1;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladderQ;
    ladderQ.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while (!ladderQ.empty()) {
        vector<string> ladder = ladderQ.front();
        ladderQ.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {

            // visited.find(word) returns visited.end() if value does not exist
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);

                // create new ladder and add new word into
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                
                // if for-loop reaches end word, return new ladder
                if (word == end_word)
                    return new_ladder;
                
                // push new ladder into queue for future exploration
                ladderQ.push(new_ladder);
            }
        }
    }
    return {"no ladder found"};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in.is_open()) {
        cout << "file is not open" << endl;;
        return;
    }

    string word;
    while (in >> word) // error?
        word_list.insert(word);

    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for (const auto s : ladder)
        cout << s << " -> ";
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    if (generate_word_ladder("marty", "curls", word_list).size() != 6)
        error("marty", "curls", "is not generating shortest path.");

    if (generate_word_ladder("code", "data", word_list).size() != 6)
        error("code", "data", "is not generating shortest path.");

    if (generate_word_ladder("work", "play", word_list).size() != 6)
        error("work", "play", "is not generating shortest path.");

    if (generate_word_ladder("sleep", "awake", word_list).size() != 8)
        error("sleep", "awake", "is not generating shortest path.");

    if (generate_word_ladder("car", "cheat", word_list).size() != 4)
        error("car", "cheat", "is not generating shortest path.");
}
