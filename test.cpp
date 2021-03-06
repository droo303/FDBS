#include <stdio.h>
#include <chrono>
#include <iostream>


#include "cHeapTable.h"
#include "cHashTable.h"
#include "seq_rand_access.h"

#define TKey int
#define TData int

using namespace std;
using namespace std::chrono;

float GetThroughput(int opsCount, float period, int unit = 10e6);
void seqRandAccessTest();
void heapTableTest(const int rowCount);
void hashTableTest(const int rowCount);
void hashTableTest(const int i, cMemory *pMemory);
void hashTableTestNonRecursive(int rowCount, cMemory *pMemory);

int main()
{
    seqRandAccessTest();

    const int RowCount = 10000000;
    heapTableTest(RowCount);
    printf("\n");

    hashTableTest(RowCount);
    printf("\n");

    cMemory *memory = new cMemory (300000000);
    hashTableTest(RowCount, memory);

    cMemory *memory2 = new cMemory (300000000);
    hashTableTestNonRecursive(RowCount, memory2);


    delete memory ;

    return 0;
}

float GetThroughput(int opsCount, float period, int unit)
{
    return ((float)opsCount / unit) / period;
}


void seqRandAccessTest() {

    // seq vs rand access to memory
    auto *seqRandAccess = new seq_rand_access();

    auto tp1 = high_resolution_clock::now();
    seqRandAccess->Insert(false);
    auto tp2 = high_resolution_clock::now();
    seqRandAccess->Read(false);
    auto tp3 = high_resolution_clock::now();
    seqRandAccess->Insert(true);
    auto tp4 = high_resolution_clock::now();
    seqRandAccess->Read(true);
    auto tp5 = high_resolution_clock::now();

    printf("\nSeq. vs rand. access to the memory comparison.\n");

    duration<double> ts = duration_cast<duration<double>>(tp2 - tp1);
    printf("Seq. insertion done. Time: %.2fs, Throughput: %.2f op/s.\n", ts.count(), (float)1000 / ts.count());

    ts = duration_cast<duration<double>>(tp3 - tp2);
    printf("Seq. read done. Time: %.2fs, Throughput: %.2f op/s.\n", ts.count(), (float)1000 / ts.count());

    ts = duration_cast<duration<double>>(tp4 - tp3);
    printf("Rand. insertion done. Time: %.2fs, Throughput: %.2f op/s.\n", ts.count(), (float)1000 / ts.count());

    ts = duration_cast<duration<double>>(tp5 -tp4);
    printf("Rand. read done. Time: %.2fs, Throughput: %.2f op/s.\n", ts.count(), (float)1000 / ts.count());

    printf("\n");
}

void heapTableTest(const int rowCount)
{
    cHeapTable<TKey, TData> *heapTable = new cHeapTable<TKey, TData>(rowCount);

    TKey key;
    TData data;

    // start insert heap table
    auto t1 = high_resolution_clock::now();

    for (int i = 0; i < rowCount; i++)
    {
        key = data = i;
        if (!heapTable->Add(key, data))
        {
            printf("Critical Error: Record %d insertion failed!\n", i);
        }
        if (i % 10000 == 0)
        {
            printf("#Record inserted: %d   \r", i);
        }
    }

    auto t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Records insertion done, HeapTable. Time: %.2fs, Throughput: %.2f mil. op/s.\n", time_span.count(), GetThroughput(rowCount, time_span.count()));

    // start scan heap table
    t1 = high_resolution_clock::now();

    for (int i = 0; i < rowCount; i++)
    {
        bool ret = heapTable->Get(i, key, data);
        if (!ret || key != i || data != i) {
            printf("Critical Error: Record %d not found!\n", i);
        }
        if (i % 10000 == 0)
        {
            printf("#Records retrieved: %d   \r", i);
        }
    }

    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Table scan (Get) done, HeapTable. Time: %.2fs, Throughput: %.2f mil. op/s.\n", time_span.count(), GetThroughput(rowCount, time_span.count()));

    // start scan heap table, Find is invoked 7x
    const int findRowCount = 7;
    int keys[] = { 0, 100000, 1000000, 2500000, 5000000, 8000000, 10000001 };
    t1 = high_resolution_clock::now();

    for (int i = 0; i < findRowCount; i++) {
        bool ret = heapTable->Find(keys[i], data);
        if (ret != true || keys[i] != data) {
            printf("cHeapTable::Find, Key: %d is not found.\n", keys[i]);
        }
    }

    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Table Find done, %dx, HeapTable. Time: %.6fs, Throughput: %.2f op/s.\n", findRowCount, time_span.count(), GetThroughput(findRowCount, time_span.count(), 1));

    delete heapTable;
}

void hashTableTest (const int rowCount , cMemory *memory) {
    printf("HashTable test with cMemory\n");

    cHashTable<TKey, TData>* hashTable = new cHashTable<TKey, TData>(rowCount/2, memory);

    TKey key;
    TData data;

    // start insert hash table
    auto t1 = high_resolution_clock::now();

    for (int i = 0; i < rowCount; i++) {
        key = data = i;
        if (!hashTable->Add(key, data)) {
            printf("Critical Error: Record %d insertion failed!\n", i);
        }

        // for testing only
        /*for (int j = 0; j <= i; j++) {
        bool ret = hashTable->Find(j, data);
        if (!ret || data != j) {
        printf("Critical Error: Record %d not found!\n", i);
        return 0;
        }
        }*/

        if (i % 10000 == 0) {
            printf("#Record inserted: %d   \r", i);
        }
    }

    auto t2 = high_resolution_clock::now();
    auto time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Records insertion done, HashTable. Time: %.2fs, Throughput: %.2f mil. op/s.\n", time_span.count(), GetThroughput(rowCount, time_span.count()));

    // start scan hash table
    t1 = high_resolution_clock::now();

    for (int i = 0; i < rowCount; i++)
    {
        bool ret = hashTable->Find(i, data);
        if (!ret || data != i) {
            printf("Critical Error: Record %d not found!\n", i);
        }
        if (i % 10000 == 0)
        {
            printf("#Records retrieved: %d   \r", i);
        }
    }

    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Table scan done, HashTable. Time: %.2fs, Throughput: %.2f mil. op/s.\n", time_span.count(), GetThroughput(rowCount, time_span.count()));

    hashTable->PrintStat();

    delete hashTable;
}

void hashTableTest(const int rowCount)
{
    cHashTable<TKey, TData> *hashTable = new cHashTable<TKey, TData>(rowCount / 2);

    TKey key;
    TData data;

    // start insert hash table
    auto t1 = high_resolution_clock::now();

    for (int i = 0; i < rowCount; i++) {
        key = data = i;
        if (!hashTable->Add(key, data)) {
            printf("Critical Error: Record %d insertion failed!\n", i);
        }

        // for testing only
        /*for (int j = 0; j <= i; j++) {
        bool ret = hashTable->Find(j, data);
        if (!ret || data != j) {
        printf("Critical Error: Record %d not found!\n", i);
        return 0;
        }
        }*/

        if (i % 10000 == 0) {
            printf("#Record inserted: %d   \r", i);
        }
    }

    auto t2 = high_resolution_clock::now();
    auto time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Records insertion done, HashTable. Time: %.2fs, Throughput: %.2f mil. op/s.\n", time_span.count(), GetThroughput(rowCount, time_span.count()));

    // start scan hash table
    t1 = high_resolution_clock::now();

    for (int i = 0; i < rowCount; i++)
    {
        bool ret = hashTable->Find(i, data);
        if (!ret || data != i) {
            printf("Critical Error: Record %d not found!\n", i);
        }
        if (i % 10000 == 0)
        {
            printf("#Records retrieved: %d   \r", i);
        }
    }

    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Table scan done, HashTable. Time: %.2fs, Throughput: %.2f mil. op/s.\n", time_span.count(), GetThroughput(rowCount, time_span.count()));

    hashTable->PrintStat();

    delete hashTable;
}

void hashTableTestNonRecursive(const int rowCount, cMemory *memory)
{
    printf("\nHashTable test with cMemory, v2\n");

    cHashTable<TKey, TData> *hashTable = new cHashTable<TKey, TData>(rowCount / 2, memory);

    TKey key;
    TData data;

    // start insert hash table
    auto t1 = high_resolution_clock::now();

    for (int i = 0; i < rowCount; i++) {
        key = data = i;
        if (!hashTable->AddNonRecursive(key, data)) {
            printf("Critical Error: Record %d insertion failed!\n", i);
        }

        // for testing only
        /*for (int j = 0; j <= i; j++) {
        bool ret = hashTable->Find(j, data);
        if (!ret || data != j) {
        printf("Critical Error: Record %d not found!\n", i);
        return 0;
        }
        }*/

        if (i % 10000 == 0) {
            printf("#Record inserted: %d   \r", i);
        }
    }

    auto t2 = high_resolution_clock::now();
    auto time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Records insertion done, HashTable. Time: %.2fs, Throughput: %.2f mil. op/s.\n", time_span.count(), GetThroughput(rowCount, time_span.count()));

    // start scan hash table
    t1 = high_resolution_clock::now();

    for (int i = 0; i < rowCount; i++)
    {
        bool ret = hashTable->FindNonRecursive(i, data);
        if (!ret || data != i) {
            printf("Critical Error: Record %d not found!\n", i);
        }
        if (i % 10000 == 0)
        {
            printf("#Records retrieved: %d   \r", i);
        }
    }

    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Table scan done, HashTable. Time: %.2fs, Throughput: %.2f mil. op/s.\n", time_span.count(), GetThroughput(rowCount, time_span.count()));

    hashTable->PrintStat();

    delete hashTable;
}

