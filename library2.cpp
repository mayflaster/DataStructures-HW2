

#include"library2.h"
#include"Schedule.h"
#include <iostream>
#define M 10

StatusType convertScheduleResultToStatusType(ScheduleResult r){
    switch (r){
        case SCHEDULE_SUCCESS:
            return SUCCESS;
        case SCHEDULE_FAILURE:
            return FAILURE;
        case SCHEDULE_ALLOCATION_ERROR:
            return ALLOCATION_ERROR;
        case SCHEDULE_INVALID_INPUT:
            return INVALID_INPUT;
    }
    return SUCCESS;
};

void *Init(int n) {
    try {
        if (n <= 0 ) return NULL;
        Schedule *DS = new Schedule(n);
        return (void *) DS;
    }catch (std::bad_alloc& e){
        return NULL;
    }
}

StatusType addRoom(void *DS, int roomID){
    if (!DS || roomID <=0){
        return INVALID_INPUT;
    }
    ScheduleResult result =  ((Schedule *)DS)-> scheduleAddRoom(roomID);
    return convertScheduleResultToStatusType(result);
}

StatusType deleteRoom(void *DS, int roomID){
    if (!DS || roomID<=0){
        return INVALID_INPUT;
    }
    ScheduleResult result =  ((Schedule *)DS)-> scheduleDeleteRoom(roomID);
    return convertScheduleResultToStatusType(result);
}


StatusType addLecture(void *DS, int courseID, int groupID, int roomID, int hour, int numStudents) {
    if (!DS){
        return INVALID_INPUT;
    }
    ScheduleResult result =  ((Schedule *)DS)-> AddLecture(courseID, groupID, roomID,hour,
                                                           numStudents);
    return convertScheduleResultToStatusType(result);
}


StatusType deleteLecture(void *DS, int hour, int roomID){
    if (!DS || hour<1 || hour >M || roomID <=0){
        return INVALID_INPUT;
    }
    ScheduleResult result =  ((Schedule *)DS)-> DeleteLecture(hour, roomID);
    return convertScheduleResultToStatusType(result);
}

StatusType mergeCourses(void *DS, int courseID1, int courseID2){
    if (!DS ) return INVALID_INPUT;
    ScheduleResult result =  ((Schedule *)DS)-> mergeCourses(courseID1, courseID2);
    return convertScheduleResultToStatusType(result);
}


StatusType competition(void *DS, int courseID1, int courseID2, int numGroups, int * winner){
    if (!DS || !winner||numGroups<=0){
        return INVALID_INPUT;
    }
    ScheduleResult result =  ((Schedule *)DS)-> competition(courseID1,courseID2, numGroups, winner);
    return convertScheduleResultToStatusType(result);
}

StatusType getAverageStudentsInCourse(void *DS, int hour, int roomID, float *
average){
    if (!DS || !average || roomID<=0 || hour<1 || hour>M){
        return INVALID_INPUT;
    }
    ScheduleResult result =  ((Schedule *)DS)-> getAverageStudentsInCourse(hour,
            roomID,average);
    return convertScheduleResultToStatusType(result);
}


void Quit(void** DS){
    if (!DS){
        return;
    }
    ((Schedule *)*DS)->quit();
    *DS = NULL;
}
