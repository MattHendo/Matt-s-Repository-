#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//used ta's template for this lab
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType *next; 
};


struct HashType
{
    struct RecordType *record; 
};


int hash(int x, int tableSize)
{
    return x % 11; // kept getting errors so i just used 11 and it worked for me
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    int index = hash(record->id, tableSize); //call the hash function to getindex
    if (hashTable[index].record == NULL) // if RecordType at that index is NULL
    {
        hashTable[index].record = record; // set record equal to the HashType pointer in the table at index
    }
    else // else
    {
        struct RecordType *current = hashTable[index].record; // traverse to the end of the linkedlist
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = record; // add 'record' to the end of it
    }
}
// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    // for each entry in the table
    for (int i = 0; i < tableSize; i++) {
        // skip if the entry is empty
        if (hashTable[i].record == NULL) {
            continue;
        }
        // print the index
        printf("Index %d -> ", i);
        // traverse the linked list and print the contents
        struct RecordType *cur = hashTable[i].record;
        while (cur != NULL) {
            printf("%d, %c, %d -> ", cur->id, cur->name, cur->order);
            cur = cur->next;
        }
        printf("NULL\n");
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    int hashTableSize = 11; //  size for the hash table
    struct HashType *hashTable = calloc(hashTableSize, sizeof(struct HashType)); // allocate and initialize the hash table
    if (hashTable == NULL) {
        printf("Cannot allocate memory\n");
        exit(-1);
    }
    for (int i = 0; i < recordSz; i++) {
        insertRecord(hashTable, &pRecords[i], hashTableSize); // insert record into the hash table
    }
    displayRecordsInHash(hashTable, hashTableSize); // display the records in the hash table
    free(pRecords);
    free(hashTable); // free the allocated memory for the hash table
    return 0;
}