#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include "MinHeap.h"

// Node of the words with their g and h values for A* search
struct Node {
    std::string word;
    int g;
    int h;

    // Parent used to help trace back path
    Node* parent;
    
    // Constructer
    Node(std::string w, int g_val, int h_val, Node* p)
        : word(w), g(g_val), h(h_val), parent(p) {}
    
    // To calculate F value
    int f() const {
        return g + h;
    }
};

int heuristic(const std::string& current, const std::string& goal) {
    int mismatch = 0;
    for (int i = 0; i < current.size(); ++i) {
        if (tolower(current[i]) != tolower(goal[i])) {
            mismatch++;
        }
    }
    return mismatch;
}

// Function to convert string to lowercase
std::string to_lower(const std::string& str) {
    std::string result = str;
    for (char &c : result) {
        c = std::tolower(c);
    }
    return result;
}


// Creating map of adjacent words as each word goes to its neighbouring words
std::map<std::string, std::vector<std::string>> adjacencygraph(const std::set<std::string>& wordSet) {
    std::map<std::string, std::vector<std::string>> graph;
    std::map<std::string, std::vector<std::string>> lowercasewords;
    
    // First converting words to lowercase
    for (const auto& word : wordSet) {
        lowercasewords[to_lower(word)].push_back(word);
    }

    for (const auto& word : wordSet) {
        std::string variant = to_lower(word);
        for (int i = 0; i < word.length(); ++i) {
            char original = variant[i];
            for (char c = 'a'; c <= 'z'; ++c) {
                variant[i] = c;
                if (c != original && lowercasewords.find(variant) != lowercasewords.end()) {
                    for (const auto& actualWord : lowercasewords[variant]) {
                        if (actualWord != word) {
                            graph[to_lower(word)].push_back(actualWord);  
                        }
                    }
                }
            }
            variant[i] = original;
        }
    }

    return graph;
}

int main(int argc, char** argv) {

    // Checking if input format is wrong
    if (argc != 4) {
        std::cout << "./doublet startWord endWord wordFile" << std::endl;
        return 1;
    }

    std::string startWord = to_lower(argv[1]);
    std::string endWord = to_lower(argv[2]);
    std::ifstream wordFile(argv[3]);

    std::set<std::string> wordSet;
    // Maps words to their nodes
    std::map<std::string, Node*> nodeMap;
    
    int n;
    wordFile >> n;
    
    // Adding words to the set lol
    for (int i = 0; i < n; ++i) {
        std::string word;
        wordFile >> word;
        wordSet.insert(to_lower(word));
    }

    // MinHeap acts like priority queue for heuristics
    MinHeap<std::string> heuristics(2);
    
    // Initializing the node with the first word

    Node* startnode = new Node(startWord, 0, heuristic(startWord, endWord), nullptr);

    int priority = startnode->f() * (endWord.size() + 1) + startnode->h;

    heuristics.add(startnode->word, priority);

    nodeMap[startnode->word] = startnode;

    Node* goalNode = nullptr;

    int expansions = 0;
    // Stores expanded words
    std::set<std::string> closedSet;
    auto graph = adjacencygraph(wordSet);

    // Loop does A* search

    while (!heuristics.isEmpty()) {
        std::string currentWord = heuristics.peek();
        Node* current = nodeMap[currentWord];
        heuristics.remove();
        
        // Checks if word already got expanded 
        if (closedSet.find(current->word) != closedSet.end()) {
            continue;
        }
        
        // Checks if final word got found
        if (current->word == endWord) {
            goalNode = current;
            break;
        }

        std::vector<std::string> adjacentWords = graph[to_lower(current->word)];

        // Loop finds new expansions and computes priority and add to heap.
        for (const auto& word : adjacentWords) {
            std::string word_lower = to_lower(word);

            // Skips in case word is already in the list
            if (closedSet.find(word_lower) != closedSet.end()) {
                continue;
            }

            int updated_g = current->g + 1;

            // If node is not there in nodemap yet
            if (nodeMap.find(word_lower) == nodeMap.end()) {
                Node* adjNode = new Node(word, updated_g, heuristic(word, endWord), current);
                nodeMap[word_lower] = adjNode;
                int priority = adjNode->f() * (endWord.size() + 1) + adjNode->h;
                heuristics.add(adjNode->word, priority);
            // If node is already in nodemap but needs g value to be updated
            } else if (nodeMap[word_lower]->g > updated_g) {  
                Node* adjNode = nodeMap[word_lower];
                adjNode->g = updated_g;
                adjNode->parent = current;
                int priority = adjNode->f() * (endWord.size() + 1) + adjNode->h;
                heuristics.add(adjNode->word, priority);
            }
        }

        expansions++;
        
        if (heuristics.isEmpty() || heuristics.peek() != currentWord) {
            closedSet.insert(current->word);
        }

    }

    if (!goalNode) { // When final word is not found
        std::cout << "No transformation" << std::endl;
        std::cout << expansions << std::endl;
    } else { // Going back to find the final path
        std::vector<std::string> path;
        Node* iter = goalNode;
        while (iter) {
            path.push_back(iter->word);
            iter = iter->parent;
        }
        std::reverse(path.begin(), path.end());

        std::cout << path.size() - 1 << std::endl;
        std::cout << expansions << std::endl;
    }
    
    // Deallocating memory
    for (const auto& pair : nodeMap) {
        delete pair.second;
    }

    return 0;
}


