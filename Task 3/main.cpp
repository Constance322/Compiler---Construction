#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

// Define the CFG
map<char, vector<string>> grammar = {
    {'S', {"aB", "bA"}},
    {'A', {"aS", ""}},
    {'B', {"bS", ""}},
};

// Define the terminals and non-terminals
set<char> terminals = {'a', 'b'};
set<char> non_terminals = {'S', 'A', 'B'};

// Global variables for First and Follow tables
map<char, set<char>> first_sets;
map<char, set<char>> follow_sets;

// Construct the LL(1) parsing table
map<char, map<char, vector<string>>> ll1_table;

// Helper function to compute First sets
// Helper function to compute First sets
void compute_first(char symbol) {
    if (terminals.count(symbol)) {
        first_sets[symbol].insert(symbol);
        return;
    }

    for (string production : grammar[symbol]) {
        char first_char = production[0];
        if (first_char == symbol) {
            continue; 
        }
        compute_first(first_char);
        first_sets[symbol].insert(first_sets[first_char].begin(), first_sets[first_char].end());

        // Include epsilon in First if the production can derive epsilon
        if (production == "") {
            first_sets[symbol].insert('e');
        }
    }
}

// function to compute Follow sets
void compute_follow(char symbol) {
    follow_sets[symbol].clear();
    if (symbol == 'S') {
        follow_sets[symbol].insert('$');
    }
    for (char non_terminal : non_terminals) {
        for (string production : grammar[non_terminal]) {
            for (size_t i = 0; i < production.size(); i++) {
                if (production[i] == symbol) {
                    // Add First of the substring after the symbol
                    string substring = production.substr(i + 1);
                    bool can_derive_epsilon = true;
                    for (char character : substring) {
                        follow_sets[symbol].insert(character);
                        if (!first_sets[character].count('e')) {
                            can_derive_epsilon = false;
                            break;
                        }
                    }

                    // If the substring can derive epsilon, add Follow of the non-terminal
                    if (can_derive_epsilon || i == production.size() - 1) {
                        for (char follow_symbol : follow_sets[non_terminal]) {
                            follow_sets[symbol].insert(follow_symbol);
                        }
                    }
                }
            }
        }
    }
}

// Construct the LL(1) parsing table
void construct_ll1_parsing_table() {
    for (char symbol : non_terminals) {
        compute_first(symbol);
    }

    for (char symbol : non_terminals) {
        for (char terminal : terminals) {
            for (string production : grammar[symbol]) {
                char first_char = production[0];
                if (terminals.count(first_char) && first_char != terminal) {
                    continue;
                }
                if (first_sets[first_char].count(terminal) || (first_sets[first_char].count('e') && follow_sets[symbol].count(terminal))) {
                    ll1_table[symbol][terminal].push_back(production);
                }
            }
        }
    }
}

// Print the First and Follow 
void print_first_and_follow() {
    cout << "First:" << endl;
    for (char symbol : non_terminals) {
        cout << "First(" << symbol << ") = {";
        bool first = true;
        for (char first_char : first_sets[symbol]) {
            if (!first) {
                cout << ", ";
            }
            first = false;
            cout << first_char;
        }
        cout << "}" << endl;
    }

    cout << "Follow Sets:" << endl;
    for (char symbol : non_terminals) {
        cout << "Follow(" << symbol << ") = {";
        bool first = true;
        for (char follow_char : follow_sets[symbol]) {
            if (!first) {
                cout << ", ";
            }
            first = false;
            cout << follow_char;
        }
        cout << "}" << endl;
    }
}

// Print the LL(1) parsing table
void print_ll1_parsing_table() {
    cout << "LL(1) Parsing Table:" << endl;
    for (char symbol : non_terminals) {
        for (char terminal : terminals) {
            cout << "[" << symbol << ", " << terminal << "] = {";
            if (ll1_table[symbol].count(terminal)) { 
                for (string production : ll1_table[symbol][terminal]) {
                    cout << symbol << " -> " << production;
                }
            }
            cout << "}" << endl;
        }
    }
}

int main() {
    construct_ll1_parsing_table();
    print_first_and_follow();
    print_ll1_parsing_table();
    return 0;
}
