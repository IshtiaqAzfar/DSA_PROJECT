#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <windows.h>

using namespace std;

vector<string> splitSentence(const std::string& sentence) {
    vector<string> words;
    string word;
    istringstream stream(sentence);
    
    while (stream >> word) {
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        words.push_back(word);
    }
    
    return words;
}

vector<string> filterStopWords(const vector<string>& words) {
    unordered_set<string> stopWords = {"what","the", "is", "are", "and", "a", "an", "in", "of", "to", "with","which","how","elements","examples","does","do","did","who","country","city","name","give","some"};
    vector<string> filteredWords;
    
    for (const auto& word : words) {
        if (stopWords.find(word) == stopWords.end()) {
            filteredWords.push_back(word);
        }
    }
    
    return filteredWords;
}

class node {
public:
    string Question;
    string Answer;
    vector<string> Key_words;
    node* left;
    node* right;
    
    node() : left(nullptr), right(nullptr) {}
    
    node(string q, string a) : Question(q), Answer(a), left(nullptr), right(nullptr) {
        vector<string> words = splitSentence(q);
        Key_words = filterStopWords(words);
    }
};

class binarytree {
private:
    node* root;

    node* insert(node* root, string q, string a) {
        if (root == nullptr) {
            return new node(q, a);
        }
        
        vector<string> keywords = filterStopWords(splitSentence(q));
        bool AllKeywordsExist = all_of(keywords.begin(), keywords.end(),
                                        [&root](const string& keyword) {
                                            return find(root->Key_words.begin(), root->Key_words.end(), keyword) != root->Key_words.end();
                                        });

        if (AllKeywordsExist) {
            return root; // Keywords already exist in the tree node, update the answer if needed
        }

        if (keywords[0] < root->Question) {
            root->left = insert(root->left, q, a);
        } else {
            root->right = insert(root->right, q, a);
        }
        return root;
    }

    void searchByKeyword(node* root, const string& q, const vector<string>& key_words) {
        if (root == nullptr) {
            cout << "\033[1;31mI DID NOT GET YOUR POINT: " << q << endl;
            cout << "PLEASE TRY AGAIN : " << endl;
            return;
        }

        vector<string> keywords = filterStopWords(splitSentence(q));
        int count = count_if(key_words.begin(), key_words.end(),
                             [&root](const string& keyword) {
                                 return find(root->Key_words.begin(), root->Key_words.end(), keyword) != root->Key_words.end();
                             });

        bool AllKeywordsExist = (count >= (root->Key_words.size() / 2) + 1 && count != 0);

        if (AllKeywordsExist) {
            cout << "\033[1;32mquestion: " << root->Question << endl;
            cout << "answer: " << root->Answer << endl;
            cout << "Keywords: \033[0m\n";
            for (const auto& keyword : root->Key_words) {
                cout << keyword << " ";
            }
            cout << endl;
            return;
        }

        if (keywords[0] < root->Question) {
            searchByKeyword(root->left, q, key_words);
        } else {
            searchByKeyword(root->right, q, key_words);
        }
    }

    void inorder(node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->Question << " - " << root->Answer << endl;
            cout << "Keywords: \n";
            for (const auto& keyword : root->Key_words) {
                cout << keyword << " ";
            }
            cout << endl;
            inorder(root->right);
        }
    }
    
    

public:
    binarytree() : root(nullptr) {}

    void insert(const string& q, const string& a) {
        root = insert(root, q, a);
    }
    
    void search(const string& q) {
        vector<string> keywords = filterStopWords(splitSentence(q));
        searchByKeyword(root, q, keywords);
    }

    void inorder() {
        inorder(root);
    }
};

void printWelcomeMessage() {
    cout << "\033[1;34mWELCOME TO CHATBOT.\033[0m" << endl;
    cout << "\033[1;35mMY NAME IS BOOO BOOO.\033[0m" << endl;
    cout << "\033[1;36mHOW CAN I ASSIST YOU?\033[0m" << endl;
    cout << "\n";
}

void printGoodbyeMessage() {
    cout << R"(
   ____                 _ _               
  / ___| ___   ___   __| | | ___ _ __ ___ 
 | |  _ / _ \ / _ \ / _` | |/ _ \ '__/ __|
 | |_| | (_) | (_) | (_| | |  __/ |  \__ \
  \____|\___/ \___/ \__,_|_|\___|_|  |___/
                                          
    )" << endl;
    cout << "\033[1;31mGOOD BYE BOOO BOOO\033[0m" << endl;
}

void loadingAnimation() {
    const char* animation[] = { "-", "\\", "|", "/" };
    cout << "\033[1;33mLoading \033[0m";
    for (int i = 0; i < 10; ++i) {
        cout << "\b" << animation[i % 4];
        cout.flush();
        Sleep(200); // Wait for 0.2 seconds
    }
    cout << "\b " << "\n";
}

void processingAnimation() {
    const char* animation = "|/-\\";
    cout << "\033[1;33m Generating Response \033[0m";
    for (int i = 0; i < 10; ++i) {
        cout << "\r" << animation[i % 4];
        cout.flush();
        Sleep(200); // Wait for 0.2 seconds
    }
    cout << "\rProcessing done!    \n";
}

int main() {
    binarytree tree;
    string q, a;
    int check;
    string search;
    string x;
    bool run=true;
    
    const string str = "hello";
    const string STR = "HELLO";
    
    cout << endl;
    system("Color 0A");
    cout << "ENTER \033[1;32mhello\033[0m TO START THE CONVERSATION: " << endl;
    cout << "\n";
    cout << "->";
    cin >> x;
    if (x == str || x == STR) {
        printWelcomeMessage();
    } else {
        cout << "\033[1;31mInvalid input. Exiting program.\033[0m" << endl;
        return 0;
    }
    cout << "\nI CAN PERFORM THESE TWO FUNCTIONS: " << endl;
    cout << "\n";
    while(run!=false)
    {
	    
        cout<<"******************************************************************************************************************"<<endl;
        cout << "\033[1;33mPRESS 2 FOR SEARCHING IN FILE: \033[0m" << endl;
        cout << "\033[1;33mPRESS 3 FOR ENTERING NEW DATA IN FILE: \033[0m" << endl;
        cout << "\033[1;31mPRESS 0 TO SAY BYE TO BOOO BOOO: \033[0m" << endl;
        cout << "\n";
        cout << "\033[1;36mIF YOU WANT TO PURSUE THEN -> PLEASE ENTER: 2 ( for searching ): 3 (for entering data) : else press 0 \033[0m" << endl;
        cout<<"******************************************************************************************************************"<<endl;
        cout << "\n";
        cout << "->";
        cin >> check;
        cin.ignore();    

        if (check == 2) {
            loadingAnimation();
            ifstream infile("final new project file.txt");
            if (!infile) {
                cout << "\033[1;31mFailed to open file.\033[0m" << endl;
                continue;
            }
            while (getline(infile, q)) {
                if (getline(infile, a)) {
                    tree.insert(q, a);
                }
            }

            cout << "ENTER QUESTION TO SEARCH: ";
            getline(cin, search);
            processingAnimation();
            tree.search(search);
        } else if (check == 3) {
            cout << "ENTER YOUR QUESTION: ";
            getline(cin, q);
            cout << "ENTER YOUR ANSWER: ";
            cout << endl;
            getline(cin, a);
            ofstream onfile("final new project file.txt", ios::app);
            if (!onfile) {
                cout << "\033[1;31mFailed to open file.\033[0m" << endl;
                continue;
            }
            loadingAnimation();
            onfile << q << endl;
            onfile << a << endl;
            cout << "\033[1;32mDATA INSERTED SUCCESSFULLY.\033[0m" << endl;
        } else if (check == 0) {
            printGoodbyeMessage();
            run=false;
            break;
        }
    }
}
