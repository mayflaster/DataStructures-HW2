//
// Created by mayfl on 08/05/2019.
//

#ifndef WET1_LIST_H
#define WET1_LIST_H

#include <iostream>
#include "Lecture.h"

#define M 10
#define  AVAILABLE -1

struct ListNode{
    int room;
    Lecture lectures[M];
    ListNode* next;
    ListNode* prev;
    ListNode (): room(0), next(NULL), prev(NULL){}
};


class List{
    ListNode* head;
    ListNode* tail;
    ListNode* bottom;
    bool listIsFull;
public:
    List(){
        head=NULL;
        tail=NULL;
        listIsFull= false;
    }

    ListNode* insertTop (int roomId){
        ListNode* node = new ListNode();
        node->room = roomId;
        node->prev = NULL;
        node->next = head;
        if(head !=  NULL)
            head->prev = node;
        if(!tail && !head){ //first node in the list case
            head=node;
            tail=node;
        }
        head = node;
        return node;
    }

    ListNode* insertBottom(int x){
        ListNode* node = new ListNode();
        node->room = x;
        node->prev = tail;
        node->next = NULL;
        if(tail !=  NULL)
            tail->next= node;
        if(!tail && !head){ //first node in the list case
            head=node;
            tail=node;
        }
        tail = node;
        return node;
    }

    void deleteFromList (ListNode* address){
        if (address==head && address == tail) { //one node in the list case
            head = NULL;
            tail = NULL;
            delete address;
            return;
        }
        if (address!=head){
            address->prev->next=address->next;
            if (address==tail) {
                tail=address->prev;
                delete address;
                return;
            }
        }
        if (address!=tail){
            address->next->prev=address->prev;
            if (address==head) head=address->next;
        }
        delete address;
    }

    ListNode* searchByKey (int roomId){
        ListNode* current;
        current = head;
        while (current){
            if (current->room == roomId ){
                return  current;
            }
            current=current->next;
        }
        return NULL;
    }




    int getRoom (ListNode* address ){
        if (!address)return -1;
        return address->room;
    }

    void pushNodeToTheEnd (ListNode* address){
        if (!address)return;
        if(address == bottom && bottom==head && !listIsFull){
            listIsFull=true;
        }
        if (address==bottom && bottom!=NULL){
            bottom=bottom->prev;
        }
        if (address==tail){
            return;
        }
        address->next->prev=address->prev;
        if(address!=head){
            address->prev->next=address->next;
        } else head=address->next;
        tail->next=address;
        address->prev=tail;
        address->next=NULL;
        tail=address;
    }

    void pointBottomToTail(){
        bottom=tail;
    }

    void pushNodeToTheStart (ListNode* address){
        if (!address)return;
        if (address==bottom && bottom!=NULL){
            bottom=bottom->prev;
        }
        if(listIsFull){
            listIsFull= false;
            bottom=address;
        }
        if (address==head){
            return;
        }
        address->prev->next=address->next;
        if(address!=tail){
            address->next->prev=address->prev;
        }else tail=address->prev;
        head->prev=address;
        address->next=head;
        address->prev=NULL;
        head=address;
    }

    bool isBottom (ListNode* node){
        return (node==bottom);
    }

    ListNode* getFirst(){
        return head;
    }

    ListNode* getNext (ListNode* node){
        if (!node) return NULL;
        return node->next;
    }


    ~List(){
        ListNode* temp=head;
        ListNode* current=NULL;
        while (temp!= NULL){
            current=temp;
            temp=temp->next;
            delete current;
        }
    }

    void display()
    {
        ListNode *temp= head;
        while(temp!=NULL)
        {
            std::cout<<temp->room<< std::endl;
            temp=temp->next;
        }
    }

    void displayAddress()
    {
        ListNode *temp= head;
        while(temp!=NULL)
        {
            std::cout<<temp<< std::endl;
            temp=temp->next;
        }
    }
/*
    void changeToCourseNumber (ListNode* node, int hourId , int course){
        node->hours [hourId-1]= course;
    }

    void changeToAvailble (ListNode* node, int hourId){
        node->hours[hourId-1]= AVAILABLE;
    }*/

};

#endif //WET1_LIST_H
