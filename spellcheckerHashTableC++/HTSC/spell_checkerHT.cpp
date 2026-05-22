#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

vector<string> load_dictionary(const string &filename)
{
    vector<string> dictionary;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return dictionary;
    }

    string word;
    while (file >> word)
    {
        dictionary.push_back(word);
    }

    file.close();
    return dictionary;
}

unordered_set<string> create_dictionary_hash(const vector<string> &dictionary)
{
    unordered_set<string> dict_hash(dictionary.begin(), dictionary.end());
    return dict_hash;
}

bool is_word_in_dictionary(const string &word, const unordered_set<string> &dict_hash)
{
    return dict_hash.find(word) != dict_hash.end();
}

vector<string> generate_edits1(const string &word)
{
    vector<string> edits;
    int n = word.length();

    // Deletions
    for (int i = 0; i < n; ++i)
    {
        edits.push_back(word.substr(0, i) + word.substr(i + 1));
    }

    // Insertions
    for (int i = 0; i <= n; ++i)
    {
        for (char c = 'a'; c <= 'z'; ++c)
        {
            edits.push_back(word.substr(0, i) + c + word.substr(i));
        }
    }

    // Substitutions
    for (int i = 0; i < n; ++i)
    {
        for (char c = 'a'; c <= 'z'; ++c)
        {
            if (c != word[i])
            {
                edits.push_back(word.substr(0, i) + c + word.substr(i + 1));
            }
        }
    }

    return edits;
}

vector<string> spell_check(const string &word, const unordered_set<string> &dict_hash)
{
    vector<string> suggestions;
    vector<string> edits = generate_edits1(word);

    for (const string &edit : edits)
    {
        if (is_word_in_dictionary(edit, dict_hash))
        {
            suggestions.push_back(edit);
        }
    }

    return suggestions;
}

int main()
{
    string filename = "words.txt";
    vector<string> dictionary = load_dictionary(filename);
    unordered_set<string> dict_hash = create_dictionary_hash(dictionary);

    string word;
    while (true)
    {
        cout << "Enter a word to spell check (or 'q' to quit): ";
        cin >> word;

        if (word == "q")
        {
            break;
        }

        if (is_word_in_dictionary(word, dict_hash))
        {
            cout << word << " is spelled correctly." << endl;
        }
        else
        {
            vector<string> suggestions = spell_check(word, dict_hash);

            cout << "Suggestions for '" << word << "':" << endl;
            for (const string &suggestion : suggestions)
            {
                cout << "  " << suggestion << endl;
            }
        }
    }

    return 0;
}