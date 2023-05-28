#ifndef PACKAGENODE_H
#define PACKAGENODE_H
#include "Package.h"

//Our cargo delivery system will use doubly linked list to store all packages.This struct will be used to create the list.
struct PackageNode
{
    Package package;      // This node can take both trucks and packages.(Polymorphism)
    PackageNode *next;
    PackageNode *previous;
};

#endif // PACKAGENODE_H