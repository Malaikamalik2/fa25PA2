//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size]=idx;
        size++;
        upheap(size-1, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        //if statemnt
        if (size==0)
            return -1;
        int ret=data[0];
        data[0]=data[size -1];
        size--;

        // Replace root with last element, then call downheap()
        if (size>0) downheap(0, weightArr);
        return ret;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        //while loop
        while (pos>0) {
            int parent=(pos-1)/2;
            if (weightArr[data[pos]]< weightArr[data[parent]]) {
                int t = data[pos];
                data[pos]=data[parent];
                data[parent]=t;
                pos=parent;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (true) {
            int l=2*pos+1;
            int r=2*pos+2;
            int m =pos;
            if (l<size&&weightArr[l]>weightArr[m]) m=l;
            if (r<size&&weightArr[r]>weightArr[m]) m=r;
            if (m==pos);
            int t = data[pos];
            data[pos]=data[m];
            data[m]=t;
            pos=m;
        }
    }
};

#endif