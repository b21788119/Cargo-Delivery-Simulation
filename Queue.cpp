#include "Queue.h"
#include "Truck.h"
#include <iostream>   // To print exception warnings to the console.

template <typename T>
Queue<T>::Queue()
{   
    _front = nullptr;
    _lastNode = nullptr;
    _size = 0;
}
template <typename T>
bool Queue<T>::isEmpty() const {
    if(_size == 0){
        return true;
    }
    return false;
}
template <typename T>
int Queue<T>::size() const {
    return _size;
}
template <typename T>
void Queue<T>::enqueue(const T& newItem){
    if(_size == 0){
        QueueNode *newNode = new QueueNode();
        newNode->item = newItem;
        newNode->next = nullptr;
        _front = newNode;     // If there is just one item in our queue,_front and _rear are equal.
        _lastNode = newNode;
        _size++;
    }
    else {
        QueueNode *newNode = new QueueNode();
        newNode->item = newItem;
        newNode->next = nullptr;   // Unlike stack,I will add new nodes at the end of our list.
        _lastNode->next = newNode;
        _lastNode = newNode;   // At the end,our newNode becomes -lastNode of our list.
        _size++;
    }
}
template <typename T>
void Queue<T>::dequeue(){
    if(_size == 0){
        try{
            // If our queue is empty,this function can not work.Therefore,I am throwing a basic exception and catch it.
            throw std::string("QueueEception");
        }
        catch(std::string e){
            std::cout << "Queue is empty!" << std::endl;
        }
    }
    else if(_size == 1){
        // If our size is equal to 1,all pointers must be NULL or nullptr.
        _front = nullptr;
        _lastNode = nullptr;
        _size = 0;
    }
    else {
        _front = _front->next;   // As we are working with queues,dequeue will only change _front.
        _size--;
    }
}
template <typename T>
void Queue<T>::getFront(T& queueTop) const {
    if(_size == 0){
        try{
            throw std::string("QueueException");
        }
        catch(std::string e){
            std::cout << "Queue is empty!"<< std::endl;
            return;
        }
    }
    queueTop = _front->item;  // We are assigning the item that is in our _front node to the function argument.
}
template <typename T>
Queue<T>::~Queue()
{
   delete _front;
   delete _lastNode;
}

template class Queue<Truck>;  // To prevent errors..