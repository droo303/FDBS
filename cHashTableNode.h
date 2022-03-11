#pragma once

#include "cHashTableNode.h"
#include "cMemory.h"

template<class TKey, class TData>
class cHashTableNode
{
private:
    bool mEmptyNode;
    TKey mKey;
    TData mData;
    cHashTableNode* mNextNode;

public:
    cHashTableNode();
    ~cHashTableNode();

    bool Add(const TKey &key, const TData &data, int &itemCount, int &nodeCount);
    bool Add(const TKey &key, const TData &data, cMemory*& memory, int &itemCount, int &nodeCount);
    bool Find(const TKey &key, TData &data) const;

    bool AddNonRecursive(const TKey &key, const TData &data, int &itemCount, int &nodeCount);
    bool AddNonRecursive(const TKey &key, const TData &data, cMemory *&memory, int &itemCount, int &nodeCount);

    bool FindNonRecursive(const TKey &key, TData &data) const;
};

template<class TKey, class TData>
cHashTableNode<TKey, TData>::cHashTableNode()
{
    mNextNode = NULL;
    mEmptyNode = true;
}

template<class TKey, class TData>
cHashTableNode<TKey, TData>::~cHashTableNode()
{
    if (mNextNode != NULL)
    {
        delete mNextNode;
        mNextNode = NULL;
    }
}

//recursive
template<class TKey, class TData>
bool cHashTableNode<TKey, TData>::Add(const TKey &key, const TData &data, int &itemCount, int &nodeCount)
{
    bool ret = true;

    if (!mEmptyNode) {
        if (mKey == key) {
            ret = false;
        }
        else {
            if (mNextNode == NULL) {
                mNextNode = new cHashTableNode<TKey, TData>();
                nodeCount++;
            }
            ret = mNextNode->Add(key, data, itemCount, nodeCount);
        }
    }
    else {
        mKey = key;
        mData = data;
        mEmptyNode = false;
        itemCount++;

        ret = true;
    }
    return ret;
}

//non-recursive
template<class TKey, class TData>
bool cHashTableNode<TKey, TData>::AddNonRecursive(const TKey &key, const TData &data, int &itemCount, int &nodeCount) {

    const cHashTableNode *node_ptr = this;

    while (true){

        if (node_ptr->mEmptyNode) {

            node_ptr->mKey = key;
            node_ptr->mData = data;
            itemCount++;

            return true;

        } else if (node_ptr->mKey == key) {
            return false;
        }

        if (node_ptr->mNextNode == NULL) {
            node_ptr->mNextNode = new cHashTableNode<TKey, TData>();

            nodeCount++;

            node_ptr->mNextNode->mKey = key;
            node_ptr->mNextNode->mData = data;

            itemCount++;

            return true;
        }

        node_ptr = node_ptr->mNextNode;
    }
}

// recursive
template<class TKey, class TData>
bool cHashTableNode<TKey, TData>::Find(const TKey &key, TData &data) const
{
    if (mEmptyNode) return false;
    if (mKey == key) {
        data = mData;
        return true;
    }
    if (mNextNode != NULL) return mNextNode->Find(key, data);
    return false;
}

// non-recursive implementation
template<class TKey, class TData>
bool cHashTableNode<TKey, TData>::FindNonRecursive(const TKey &key, TData &data) const {

    const cHashTableNode *node_ptr = this;

    while (true) {

        if (node_ptr->mEmptyNode) return false;

        if (node_ptr->mKey == key) {
            data = node_ptr->mData;
            return true;

        }

        if (node_ptr->mNextNode == NULL) return false;

        node_ptr = node_ptr->mNextNode;
    }
}

//recursive
template<class TKey, class TData>
bool cHashTableNode<TKey, TData>::Add(const TKey &key, const TData &data, cMemory *&memory, int &itemCount, int &nodeCount) {
    bool ret = true;
    if (!mEmptyNode ) {
        if(mKey == key) {
            ret = false;
        }
        else {
            if (mNextNode == NULL) {
                if (memory == NULL) {
                    mNextNode = new cHashTableNode<TKey , TData> () ;
                }
                else {
                    char* mem = memory->New(sizeof(cHashTableNode<TKey,TData>));
                    mNextNode = new (mem)cHashTableNode<TKey,TData>();
                }
                nodeCount++;
            }
            ret = mNextNode->Add(key,data,memory,itemCount,nodeCount);
        }
    }
    else {
        mKey = key ;
        mData = data ;
        mEmptyNode = false;
        itemCount++;
        ret = true;
    }
    return ret;
}

//non-recursive
template<class TKey, class TData>
bool cHashTableNode<TKey, TData>::AddNonRecursive(const TKey &key, const TData &data, cMemory *&memory, int &itemCount, int &nodeCount) {

    cHashTableNode *node_ptr = this;

    while (true){

        if (node_ptr->mEmptyNode) {

            node_ptr->mKey = key;
            node_ptr->mData = data;
            node_ptr->mEmptyNode = false;

            itemCount++;

            return true;

        } else if (node_ptr->mKey == key) {
            return false;
        }

        if (node_ptr->mNextNode == NULL) {
            if (memory == NULL) {
                node_ptr->mNextNode = new cHashTableNode<TKey , TData> () ;
            }
            else {
                char* mem = memory->New(sizeof(cHashTableNode<TKey,TData>));
                node_ptr->mNextNode = new (mem)cHashTableNode<TKey,TData>();
            }

            nodeCount++;

            node_ptr->mNextNode->mKey = key;
            node_ptr->mNextNode->mData = data;
            node_ptr->mNextNode->mEmptyNode = false;

            itemCount++;

            return true;
        }

        node_ptr = node_ptr->mNextNode;
    }
}