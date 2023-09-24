#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

TrieNode* createNode() {
    TrieNode* pNode = (TrieNode*)malloc(sizeof(TrieNode));
    if (pNode) {
        pNode->isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            pNode->children[i] = NULL;
        }
    }
    return pNode;
}

void insert(TrieNode *root, const char *key) {
    TrieNode *pCrawl = root;
    for (int i = 0; i < strlen(key); i++) {
        int index = key[i] - 'a';
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = createNode();
        }
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
}

void searchTrie(TrieNode *root, const char *prefix, char *currentWord) {
    if (!root) return;

    if (root->isEndOfWord) {
        printf("%s\n", currentWord);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            char c = 'a' + i;
            strncat(currentWord, &c, 1);
            searchTrie(root->children[i], prefix, currentWord);
            currentWord[strlen(currentWord) - 1] = '\0'; // Remove the last character
        }
    }
}

void autocomplete(TrieNode *root, const char *prefix) {
    TrieNode *pCrawl = root;
    for (int i = 0; i < strlen(prefix); i++) {
        int index = prefix[i] - 'a';
        if (!pCrawl->children[index]) {
            return; // No words with given prefix
        }
        pCrawl = pCrawl->children[index];
    }
    char currentWord[1024] = {0};
    strncpy(currentWord, prefix, strlen(prefix));
    searchTrie(pCrawl, prefix, currentWord);
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <prefix>\n", argv[0]);
        return 1;
    }

    TrieNode *root = createNode();
    char word[1024];

    while (scanf("%s", word) != EOF) {
        insert(root, word);
    }
    autocomplete(root, argv[1]);
    return 0;
}