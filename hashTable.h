//
// Created by mayfl on 12/06/2019.
//

#ifndef WET_HASHTABLE_H
#define WET_HASHTABLE_H

#include "List.h"
#define  INIT_SIZE 10



class hashTable {
    List* roomsId;
    int size;
    int currSize;

public:
    hashTable(): size(INIT_SIZE),currSize(0) {
        roomsId = new List [size];
    }

    ~hashTable(){
        delete[] roomsId;
    }

    void copyToNewArr (List* new_array, int size){
        for (int i=0;i<size; i++){
            ListNode* current = roomsId[i].getFirst();
            //std::cout << current->room <<std :: endl;
            while (current){
                int currentRoom = current->room;
                ListNode* new_node = new_array[hashFunction(currentRoom)].insertTop(currentRoom);
                for (int i = 0; i<M ; i++){
                    new_node->lectures[i] = current->lectures[i];
                }
                current=current->next;
            }
        }
    }
    //operator =
    // copy c'tor

    hashTable &operator=(const hashTable & hash){
        if (this==&hash){
            return *this;
        }
        size=hash.size;
        delete[] this->roomsId;
        List* new_array = new List [size];
        copyToNewArr(new_array,size);
        return (*this);

    }


    hashTable (const hashTable& hash): roomsId(new List[hash.size]), size
    (hash.size), currSize(hash.currSize){
        copyToNewArr(roomsId,size);
    }





    int hashFunction (int roomId){
        return roomId%size;
    }


    void hashInsert (int roomId){
        //search if already exist
        //ListNode* node = roomsId[hashFunction(roomId)].searchByKey(roomId);
        //if (node == NULL){
            roomsId[hashFunction(roomId)].insertTop(roomId);
            currSize++;
            if (currSize == size){
                increase();
            }
        //}
    }

    void hashDelete (int roomId){
        ////search if not exist
        ListNode* node = roomsId[hashFunction(roomId)].searchByKey(roomId);
        //if (node != NULL) {
            roomsId[hashFunction(roomId)].deleteFromList(node);
            currSize--;
            if (currSize<=size/4){
                decrease();
            }
        //}
    }

    ListNode* hashSearch (int roomId){
        ListNode* node = roomsId[hashFunction(roomId)].searchByKey(roomId);
        return node;
    }

    bool isExist (int roomId){
        ListNode* node = hashSearch(roomId);
        if (!node) return false;
        return true;
    }


    Lecture* hashSearchHours (int roomId){
        ListNode* node = hashSearch(roomId);
        return  node->lectures;
    }

    Lecture getLecture (int roomId, int hour){
        Lecture* lectures = hashSearchHours(roomId);
        Lecture l = lectures[hour-1];
        return l;
    }

    void setToAvailable (int room, int hour){
        Lecture emptyLecture;
        ListNode *node = hashSearch(room);
        node->lectures[hour-1]=emptyLecture;
    }

    void updateLecture (Lecture lecture, int room, int hour){
        ListNode* node= hashSearch(room);
        node->lectures[hour-1]=lecture;
    }

    void increase (){
        size = 2*size;
        List* new_array = new List [size];
        copyToNewArr(new_array,currSize);
        delete[] roomsId;
        roomsId= new_array;
    }

    void decrease (){
        size = size/2;
        List* new_array = new List [size];
        copyToNewArr(new_array,2*size);
        delete[] roomsId;
        roomsId = new_array;
    }


    /*List* getArr (){
        return roomsId;
    }*/

};




#endif //WET_HASHTABLE_H
