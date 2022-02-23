//
// Created by pkozusnik on 18.02.22.
//

#ifndef FDBS_SEQ_RAND_ACCESS_H
#define FDBS_SEQ_RAND_ACCESS_H

#include <cstdlib>
#include <cassert>

class seq_rand_access {
private:
    int *memory;
    int *rand_indices;

    int capacity = 10000000;

public:
    seq_rand_access() {
        memory = new int[capacity];
        rand_indices = new int[capacity];

        for (int i = 0; i < capacity; i++) {
            rand_indices[i] = rand() % capacity;
        }
    }

    ~seq_rand_access() {
        delete memory;
        memory = nullptr;
        delete rand_indices;
        rand_indices = nullptr;
    }

    void Insert(bool rand) {
        if (rand) {
            for (int i = 0; i < capacity; i++) {
                memory[rand_indices[i]] = 12345;
            }
        } else {
            for (int i = 0; i < capacity; i++) {
                memory[i] = 12345;
            }
        }
    }

    int Read(bool rand) {
        int tmp = 0;
        if (rand) {
            for (int i = 0; i < capacity; i++) {
                tmp = memory[rand_indices[i]];
            }
        } else {
            for (int i = 1; i < capacity; i++) {
                tmp = memory[i];
            }
        }
        return tmp;
    };
};

#endif //FDBS_SEQ_RAND_ACCESS_H
