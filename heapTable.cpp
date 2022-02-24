#include <stdio.h>
#include <chrono>
#include <iostream>

#include "cHeapTable.h"
#include "seq_rand_access.h"

#define TKey int
#define TData int

using namespace std;
using namespace std::chrono;

void seqRandAccessComparison() {

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

    printf("\nTASK 0.\nSeq. vs rand. access to the memory comparison.\n");

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

int main()
{
    //Task 0
    seqRandAccessComparison();

    // Task 1

    printf("\nTASK 1.\n");

    int const RowCount = 10000000;

    auto *table = new cHeapTable<TKey, TData>(RowCount);

    TKey key;
    TData data;

    // start insert
    auto t1 = high_resolution_clock::now();

    for (int i = 0; i < RowCount; i++)
    {
        key = data = i;
        if (!table->Add(key, data))
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
    printf("Add - Records insertion done. Time: %.2fs, Throughput: %.2f op/s.\n", time_span.count(), (float)RowCount / time_span.count());

    // start scan
    t1 = high_resolution_clock::now();

    for (int i = 0; i < RowCount; i++)
    {
        bool ret = table->Get(i, key, data);
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
    printf("Get - Table scan done. Time: %.2fs, Throughput: %.2f op/s.\n", time_span.count(), (float)RowCount / time_span.count());

    //FIND
    // start scan

    printf("Please wait for Find to finish...\n");

    // prepare random indices
    int num_of_keys = 100000;
    int *rand_keys = new int[num_of_keys];
    for (int i = 0; i < num_of_keys; i++) {
        rand_keys[i] = rand() % num_of_keys;
    }

    t1 = high_resolution_clock::now();

    for (int i = 0; i < num_of_keys; i++)
    {
        key = data = i;
        bool ret = table->Find(key, data);
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
    printf("Find - Table scan done. Time: %.2fs, Throughput: %.2f op/s.\n", time_span.count(), (float)num_of_keys / time_span.count());

    delete table;

    return 0;
}
