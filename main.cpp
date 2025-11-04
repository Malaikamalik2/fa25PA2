//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}
//step 3
int buildEncodingTree(int nextFree) {
    MinHeap H;
    //pushing all leaf
    for (int i = 0; i < nextFree; ++i)
        H.push(i, weightArr);
        if (H.size==0)
            return -1;
        if (H.size ==1)
            return H.pop(weightArr);
        int cur = nextFree;
        while (H.size>1) {
            int a = H.pop(weightArr);
            int b = H.pop(weightArr);

            charArr[cur]='\0';
            weightArr[cur] = weightArr[a] + weightArr[b];
            leftArr[cur] = a;
            rightArr[cur] = b;
            H.push(cur, weightArr);
            cur++;

        }
        return H.pop(weightArr);
    }

    // Step 4: Use an STL stack to generate codes
    void generateCodes(int root, string codes[]) {
    if (root<0)
        return;
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    //defing item
    struct Item {int node;string path;};
    stack<Item> st;
    st.push({root,""});
    while(!st.empty()) {
        Item it = st.top();
        st.pop();
        int v =it.node;
        bool leaf=(leftArr[v]==-1 && rightArr[v]==-1);
        if (leaf) {
            char c =charArr[v];
            string code= it.path.empty() ?"0" : it.path;
            if (c>='a' && c<='z') codes[c-'a'] = code;
        }else {
            if (rightArr[v] != -1) st.push({rightArr[v], it.path+ "1"});
            if (leftArr[v] != -1) st.push({leftArr[v], it.path+"0"});
        }
    }
}

                // Step 5: Print table and encoded message
                void encodeMessage(const string& filename, string codes[]) {
                    cout << "\nCharacter : Code\n";
                    for (int i = 0; i < 26; ++i) {
                        if (!codes[i].empty())
                            cout << char('a' + i) << " : " << codes[i] << "\n";
                    }

                    cout << "\nEncoded message:\n";

                    ifstream file(filename);
                    char ch;
                    while (file.get(ch)) {
                        if (ch >= 'A' && ch <= 'Z')
                            ch = ch - 'A' + 'a';
                        if (ch >= 'a' && ch <= 'z')
                            cout << codes[ch - 'a'];
                    }
                    cout << "\n";
                    file.close();
                }
