//
// Created by mayfl on 14/06/2019.
//

#ifndef WET_SCHEDULE_H
#define WET_SCHEDULE_H
#include <iostream>
#include "unionFind.h"
#include "hashTable.h"
#define AVAILABLE -1

typedef enum {
    SCHEDULE_SUCCESS = 0,
    SCHEDULE_FAILURE = -1,
    SCHEDULE_ALLOCATION_ERROR = -2,
    SCHEDULE_INVALID_INPUT = -3
} ScheduleResult;

class Schedule{
    UnionFind courses;
    hashTable rooms;
    int n;
public:
    explicit Schedule(int n): courses(n),n(n) {}
    ~Schedule() = default ;
    ScheduleResult scheduleAddRoom(int roomID){
        try{
            if (rooms.isExist(roomID)) return SCHEDULE_FAILURE;
            else rooms.hashInsert(roomID);
            return SCHEDULE_SUCCESS;
        }
        catch (std::bad_alloc& e){
            return SCHEDULE_ALLOCATION_ERROR;
        }
    }

    ScheduleResult scheduleDeleteRoom(int roomID){
        if (!rooms.isExist(roomID)) return SCHEDULE_FAILURE;
        Lecture * LecturesOfRoom= rooms.hashSearchHours(roomID);
        //ListNode* node = rooms.hashSearch(roomID);
        for (int i = 0; i <M ; ++i) { //O(1)
            if (LecturesOfRoom[i].courseID!=AVAILABLE) {
                return SCHEDULE_FAILURE;
            }
        }

        rooms.hashDelete(roomID);
        return SCHEDULE_SUCCESS;
    }

    ScheduleResult AddLecture( int courseID, int groupID, int roomID, int hour,
            int numStudents) {
        if (groupID<0||courseID>n||courseID<1||numStudents<0||hour<=0||hour >M||roomID<=0){
            return SCHEDULE_INVALID_INPUT;
        }
        if (!rooms.isExist(roomID)) return SCHEDULE_FAILURE;
        Lecture lecture = rooms.getLecture(roomID,hour);
        if (lecture.courseID != AVAILABLE)
            return SCHEDULE_FAILURE;
        Lecture newLecture(groupID,hour,numStudents,roomID,courseID);
        UnionFindNode* course = courses.getUFNode(newLecture.courseID);
        if (course->LecturesOfCourseByGroups.isExsist(newLecture)) {
            return SCHEDULE_FAILURE;
        }
        rooms.updateLecture(newLecture,roomID,hour);
        LectureWithStudents l(newLecture);
        course->numOfLectures++;
        course->LecturesOfCourseByGroups.insert(newLecture,NULL);
        course->LecturesOfCourseByStudents.insert(l,NULL);
        return SCHEDULE_SUCCESS;
    }


    ScheduleResult DeleteLecture(int hour, int roomID){
        //////////updating rooms//////////////
        if (!rooms.isExist(roomID))
            return SCHEDULE_FAILURE;
        Lecture lecture = rooms.getLecture(roomID,hour);
        if (lecture.courseID == AVAILABLE)
            return SCHEDULE_FAILURE;
        rooms.setToAvailable(roomID,hour);
        //////////updating courses/////////////
        LectureWithStudents l(lecture);
        UnionFindNode* course = courses.getUFNode(lecture.courseID);
        course->LecturesOfCourseByStudents.remove(l);
        course->LecturesOfCourseByGroups.remove(lecture);
        course->numOfLectures--;
        return SCHEDULE_SUCCESS;
    }

       ScheduleResult mergeCourses( int courseID1, int courseID2){
        try{
            if (courseID1>n || courseID2 >n || courseID1<=0 || courseID2<=0){
                return SCHEDULE_INVALID_INPUT;
            }
            if(this->courses.find(courseID1)==this->courses.find(courseID2)){
                return SCHEDULE_FAILURE;
            }
            ////// other checks !////
            UnionFindNode* course1 = courses.getUFNode(courseID1);
            UnionFindNode* course2 = courses.getUFNode(courseID2);
            int k1= course1->LecturesOfCourseByGroups.countNodesInTree();
            int k2 = course2->LecturesOfCourseByGroups.countNodesInTree();
            Lecture* arr1 = new Lecture [k1];
            Lecture* arr2 = new Lecture [k2];
            course1->LecturesOfCourseByGroups.printTreeInArray(arr1);
            course2->LecturesOfCourseByGroups.printTreeInArray(arr2);
            int i=0,j=0;
            while (j<k2 && i<k1) {
                if (arr1[i]==arr2[j]){
                    delete[] arr1;
                    delete[] arr2;
                    return SCHEDULE_FAILURE;

                }
                else if (arr1[i]>arr2[j])j++;
                else i++;
            }
            delete[] arr1;
            delete[] arr2;
            courses.unionGroups(courseID1,courseID2);
        }
        catch (std::bad_alloc& e){
            return SCHEDULE_ALLOCATION_ERROR;
        }
        return SCHEDULE_SUCCESS;
    }
    
     ScheduleResult competition(int courseID1,int courseID2,int  numGroups,int * winner){
        if (courseID1>n || courseID2 >n || courseID1<=0 || courseID2<=0) return SCHEDULE_INVALID_INPUT;
        if(this->courses.find(courseID1)==this->courses.find(courseID2)){
            return SCHEDULE_FAILURE;
        }
        int sum1=0;
        int sum2=0;
        UnionFindNode* nodeID1= this->courses.getUFNode(courseID1);
        UnionFindNode* nodeID2=this->courses.getUFNode(courseID2);
        nodeID1->LecturesOfCourseByStudents.calculateSumOfMaxXNodes(numGroups,&sum1);
        nodeID2->LecturesOfCourseByStudents.calculateSumOfMaxXNodes(numGroups,&sum2);
        if(sum1>sum2){
            *winner=courseID1;
        }else if(sum2>sum1){
            *winner=courseID2;
        }else *winner=courseID1>courseID2 ? courseID1: courseID2;
         return SCHEDULE_SUCCESS;
    }


    ScheduleResult getAverageStudentsInCourse(int hour, int roomID, float
    *average){
        if (!rooms.isExist(roomID))
            return SCHEDULE_FAILURE;
        Lecture lecture = rooms.getLecture(roomID,hour);
        if (lecture.courseID == AVAILABLE)
            return SCHEDULE_FAILURE;
        UnionFindNode* course = courses.getUFNode(lecture.courseID);
        int numOfLectures = course->numOfLectures;
        if (numOfLectures==0){
            *average=0;
            return SCHEDULE_SUCCESS;
        }
        int numOfStudentInCourse = course->LecturesOfCourseByStudents
                .getSumOfNodesInSubTree();
        *average=((float)(numOfStudentInCourse))/((float)(numOfLectures));

        return SCHEDULE_SUCCESS;

    }

    void quit(){
        delete this;
    }


};
#endif //WET_SCHEDULE_H
