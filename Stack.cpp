#include "Stack.h"
#include <iostream>
#include <stdexcept>
#include "Package.h"

template <typename T>
Stack<T>::Stack()
{
    _head = nullptr;   // At the beginning,there is no node in our stack.Therefore,head is equal to nullptr
    _size = 0;
}
template <typename T>
bool Stack<T>::isEmpty() const{
    if(_size == 0){
        return true;
    }
    return false;
}
template <typename T>
int Stack<T>::size () const{
    return _size;
}
template <typename T>
void Stack<T>::push(const T& newItem){
    if(_size==0)
    {
        ListNode *newNode = new ListNode();
        newNode->item = newItem;
        newNode->next = nullptr;
        _head = newNode;   //newNode is our head node
        _size++;     
    }
    else  
    {   //I am going to add new elements to the beginning of our list.(Top)
        ListNode *newNode = new ListNode();
        newNode->item = newItem;
        newNode->next = _head; 
        _head = newNode;  // newNode becomed head node here.
        _size++;
    }
}
template <typename T>
void Stack<T>::getTop(T& stackTop) const{
    if(_size == 0){
        // If our stack is empty,these function can not work.Therefore,I am throwing a basic exception by using std::string
        try{
            throw std::string("EmptyStackException");  
        }
        catch(std::string e){
            std::cout << "Stack is empty!" << std::endl;
            return;  // Terminates this function.
        }
    }
    else{
        stackTop = _head->item;  // Top of our stack is the first item which is taken by our head node.Now,our argument is changed.
    }
    
}
template <typename T>
void Stack<T>::pop(){
    if(_size == 0){
        try{
            //Same problem again.If our stack is empty,this function can not work.
            throw std::string("EmptyStackException!");
        }
        catch(std::string e){
            std::cout << "Stack is empty!" << std::endl;
            return;
        }
    }
    else if(_size == 1){
        _head = nullptr;  // No elements after this line.
        _size = 0;
    }
    else {
        _head = _head->next; // Our head node is changed here.topNode is gone.
        _size -- ;    
    }
}
template <typename T>
Stack<T>::~Stack()
{
    delete _head;
}
// We are going to use our stack with Package objects.As I implement our stack in .cpp file,I am using line 85 to prevent compiler errors.
template class Stack<Package>;  

