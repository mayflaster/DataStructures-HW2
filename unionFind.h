//
// Created by mayfl on 13/06/2019.
//

#ifndef WET_UNIONFIND_H
#define WET_UNIONFIND_H
#define ROOT -2

#include "avl.h"
#include "Lecture.h"


struct UnionFindNode{
    int parent;
    int sizeOfGroup;
    int numOfLectures;
    AvlTree<int,Lecture> LecturesOfCourseByGroups;
    AvlTree<int,LectureWithStudents> LecturesOfCourseByStudents;
    UnionFindNode():parent(ROOT),sizeOfGroup(1),numOfLectures(0){}

};


class UnionFind {
    UnionFindNode* courses;
    int n;
public:
    UnionFind(int n): courses(new UnionFindNode [n]), n(n){
        for (int i = 0; i < n; ++i) {
            courses[i]=UnionFindNode();
        }
    }

    UnionFind &operator=(const UnionFind & UF) {
        if (this==&UF){
            return *this;
        }
        delete[] this->courses;
        UnionFindNode* new_array = new UnionFindNode [UF.n];
        for (int i = 0; i < UF.n ; ++i) {
            new_array[i]= UF.courses[i];
        }
        courses=new_array;
        return (*this);
    }

    UnionFind (const UnionFind& UF): courses(new UnionFindNode[UF.n]), n(UF.n){
        courses=UF.courses;
    }

    ~UnionFind(){
        delete[] courses;
    }

    int find (int groupId){
        int tempGroupNum = groupId,rootOfGroup=groupId;
        while (courses[rootOfGroup-1].parent != ROOT){
            rootOfGroup=courses[rootOfGroup-1].parent;
        }
        //now rootOfGroup = ROOT
        int oldParent = courses[tempGroupNum-1].parent;
        while (oldParent != ROOT){
            courses[tempGroupNum-1].parent=rootOfGroup;
            tempGroupNum=oldParent;
            oldParent=courses[oldParent-1].parent;
        }
        return rootOfGroup;
    }


    int unionGroups (int group1, int group2){
        int root1 = find(group1);
        int root2 = find(group2);
        if (root1==root2)
            return root1;
        //int root1 = find(group1);
        int biggerGroup = courses[root1-1].sizeOfGroup >
                          courses[root2 -1].sizeOfGroup ? root1 : root2;
        int smallerGroup = (biggerGroup==root1)? root2:root1;
        courses[smallerGroup-1].parent=biggerGroup;
        courses[biggerGroup-1].sizeOfGroup+=courses[smallerGroup-1].sizeOfGroup;
        courses[biggerGroup-1].numOfLectures+=courses[smallerGroup-1].numOfLectures;
        courses[smallerGroup-1].numOfLectures=0;
        courses[smallerGroup-1].sizeOfGroup=0;

        if(courses[biggerGroup-1].LecturesOfCourseByGroups.root!=NULL&&
                courses[smallerGroup-1].LecturesOfCourseByGroups.root!=NULL) {
            AvlTree<int, Lecture> newTree1;
            newTree1.mergeTrees(courses[biggerGroup - 1].LecturesOfCourseByGroups.root,
                                courses[smallerGroup - 1].LecturesOfCourseByGroups.root);
            courses[biggerGroup - 1].LecturesOfCourseByGroups = newTree1;

            AvlTree<int, LectureWithStudents> newTree2;
            newTree2.mergeTrees(courses[biggerGroup - 1].LecturesOfCourseByStudents.root,
                                courses[smallerGroup - 1].LecturesOfCourseByStudents.root);
            courses[biggerGroup - 1].LecturesOfCourseByStudents = newTree2;
        }
         else if (courses[biggerGroup-1].LecturesOfCourseByGroups.root==NULL){
            courses[biggerGroup-1].LecturesOfCourseByGroups.root=courses[smallerGroup-1].LecturesOfCourseByGroups.root;
            courses[smallerGroup-1].LecturesOfCourseByGroups.root=NULL;
            courses[biggerGroup-1].LecturesOfCourseByStudents.root=courses[smallerGroup-1].LecturesOfCourseByStudents.root;
            courses[smallerGroup-1].LecturesOfCourseByStudents.root=NULL;
        }
        return biggerGroup;
    }

    UnionFindNode* getUFNode (int groupID){
        int root = find(groupID);
        return &courses[root-1];
    }


    int findParent (int x){
        return courses[x-1].parent;
    }




};

#endif //WET_UNIONFIND_H
