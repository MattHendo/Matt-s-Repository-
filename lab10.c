#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 26

struct Trie {
    int count;
    struct Trie* children[SIZE];
};

struct Trie* createnode() {
    struct Trie* trie = malloc(sizeof(struct Trie));
    trie->count = 0;
    for (int i = 0; i < SIZE; i++) {
        trie->children[i] = NULL;
    }
    return trie;
}

void insert(struct Trie** dpTrie, char* word) {
    struct Trie* trie = *dpTrie;
    for (int i = 0; word[i]; i++) {
        char c = tolower(word[i]);
        if (trie->children[c-'a'] == NULL) {
            trie->children[c-'a'] = createnode();
        }
        trie = trie->children[c-'a'];
    }
    trie->count++;
}

int numberOfOccurances(struct Trie* pTrie, char* word) {
    struct Trie* trie = pTrie;
    for (int i = 0; word[i]; i++) {
        char c = tolower(word[i]);
        if (trie->children[c-'a'] == NULL) {
            return 0;
        }
        trie = trie->children[c-'a'];
    }
    return trie->count;
}

struct Trie* deallocateTrie(struct Trie* pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < SIZE; i++) {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    // read the number of the words in the dictionary
    // parse line by line, and insert each word to the trie data structure
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    struct Trie* trie = createnode();

    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
    }

    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}