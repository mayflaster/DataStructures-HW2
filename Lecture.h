//
// Created by User on 11/05/2019.
//

#ifndef WET1_LECTURE_H
#define WET1_LECTURE_H
#define  AVAILABLE -1

#include <iostream>

struct Lecture{
    int groupID;
    int hour;
    int numStudents;
    int roomID;
    int courseID;
    Lecture(int groupID,int hour,int numStudents,int roomID,int courseID):groupID(groupID),hour(hour),numStudents(numStudents),roomID(roomID),courseID(courseID){};
    Lecture(): groupID(AVAILABLE),hour(AVAILABLE),numStudents(AVAILABLE),roomID(AVAILABLE),courseID(AVAILABLE){};
    bool operator==(const Lecture& l) const;
    bool operator>(const Lecture& l) const;
    int operator()() const;
    friend std::ostream& operator<<(std::ostream& os, const Lecture& l){
        return os << l.groupID << "." << l.hour ;
    }
};
int Lecture::operator()() const{
    return this->groupID;
}

bool Lecture::operator==(const Lecture& l) const{
    return l.hour==hour && l.groupID==groupID;
}

bool Lecture::operator>(const Lecture& l) const{
    if(groupID==l.groupID){
        return hour>l.hour;
    }
    else
        return groupID>l.groupID;
}

bool operator<(const Lecture& lec1,const Lecture& lec2) {
    return !((lec1>lec2)||lec1==lec2);
}

bool operator<=(const Lecture& lec1,const Lecture& lec2) {
    return ((lec1<lec2)||lec1==lec2);
}

bool operator>=(const Lecture& lec1,const Lecture& lec2) {
    return ((lec1>lec2)||lec1==lec2);
}

bool operator!=(const Lecture& lec1,const Lecture& lec2) {
    return !(lec1==(lec2));
}


/*
std::ostream& operator<<(std::ostream& os, const lecture& l){
    return os << l.hour << "." << l.room << "i";
}*/

struct LectureWithStudents : Lecture{
    LectureWithStudents(int groupID,int hour,int numStudents,int roomID,int courseID):  Lecture(groupID, hour,numStudents,roomID,courseID){};
    LectureWithStudents(): Lecture(){};
    LectureWithStudents(Lecture& l){
        groupID=l.groupID;
        hour=l.hour;
        numStudents=l.numStudents;
        roomID=l.roomID;
        courseID=l.courseID;
    }
    bool operator==(const LectureWithStudents& l) const;
    bool operator>(const LectureWithStudents& l) const;
    int operator()()const ;
    friend std::ostream& operator<<(std::ostream& os, const LectureWithStudents& l){
        return os << (Lecture) l << "." << l.numStudents ;
    }
};


int LectureWithStudents::operator()()const {
    return this->numStudents;
}

bool LectureWithStudents::operator==(const LectureWithStudents& l) const{
    return Lecture(*this)==Lecture(l) && l.numStudents==numStudents;
}

bool LectureWithStudents::operator>(const LectureWithStudents& l) const{
    if(numStudents==l.numStudents){
        return Lecture(*this)>Lecture(l);
    }
    else
        return numStudents>l.numStudents;
}

bool operator<(const LectureWithStudents& lec1,const LectureWithStudents& lec2) {
    return !((lec1>lec2)||lec1==lec2);
}

bool operator<=(const LectureWithStudents& lec1,const LectureWithStudents& lec2) {
    return ((lec1<lec2)||lec1==lec2);
}

bool operator>=(const LectureWithStudents& lec1,const LectureWithStudents& lec2) {
    return ((lec1>lec2)||lec1==lec2);
}

bool operator!=(const LectureWithStudents& lec1,const LectureWithStudents& lec2) {
    return !(lec1==(lec2));
}
#endif //WET1_LECTURE_H
