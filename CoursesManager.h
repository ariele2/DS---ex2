#ifndef COURSES_MANAGER_H
#define COURSES_MANAGER_H
#include <stdlib.h>
#include "HashChain.h"
#include "rankedAVL.h"

class CoursesManager {
    HashChain* coursesData;
    rankedAVL* timeTree;
    public:
    CoursesManager (); //constructor
    ~CoursesManager(); //destructor
    void AddCourse(int courseID);
    void RemoveCourse(int courseID);
    void AddClass(int courseID, int* classID);
    void WatchClass(int courseID, int classID, int time);
    void TimeViewed(int courseID, int classID, int *timeViewed);
    void GetIthWatchedClass(int i, int *courseID, int *classID);
    class AllocationError{};
    class InvalidInput{};
    class Failure{};
};

CoursesManager::CoursesManager() {
    coursesData = new HashChain(4);
    if (!coursesData) {
        throw AllocationError();
    }
    timeTree = new rankedAVL;
    if (!timeTree) {
        throw AllocationError();
    }
}

CoursesManager::~CoursesManager() {
    delete timeTree;
    delete coursesData;
}

void CoursesManager::AddCourse(int courseID) {
    if (coursesData->findCourse(courseID)) {
        throw Failure();
    }
    try {
        coursesData->insertCourse(courseID);
    }
    catch (HashChain::AllocationError& e) {
        throw AllocationError();
    }
}

void CoursesManager::RemoveCourse(int courseID) {
    auto remove_course = coursesData->findCourse(courseID);
    if (!remove_course) {
        throw Failure();
    }
    for (int i=0; i<remove_course->data->getCapacity(); i++) { //iterate over the classes
        int curr_time = (*(remove_course->data))[i];
        if (curr_time) {
            trio remove_key(curr_time, courseID, i);
            timeTree->remove(remove_key);
        }
    }
    try {
        coursesData->deleteCourse(courseID);
    }
    catch (HashChain::AllocationError& e) {
        throw AllocationError();
    }
}

void CoursesManager::AddClass(int courseID, int* classID) {
    try {
        *classID = coursesData->insertClass(courseID);
    }
    catch (HashChain::Failure& e) {
        throw Failure();
    }
    catch (HashChain::AllocationError& e) {
        throw AllocationError();
    }
}

void CoursesManager::WatchClass(int courseID, int classID, int time) {
    auto course = coursesData->findCourse(courseID);
    if (!course) {
        throw Failure();
    }
    auto classes_data = course->data;
    if (classes_data->getCapacity() < classID+1) {
        throw InvalidInput();
    }
    int curr_class_time = (*classes_data)[classID];
    if (curr_class_time == 0) { //the class has never been viewed
        try {
            timeTree->insert(trio(time, courseID, classID));
        }
        catch (rankedAVL::AllocationError& e) {
            throw AllocationError();
        }
        (*classes_data)[classID] = time;
    }
    else { //just need to update the time currently viewed
        timeTree->remove(trio(curr_class_time, courseID, classID));
        try {
            timeTree->insert(trio(curr_class_time+time, courseID, classID));
        }
        catch (rankedAVL::AllocationError& e) {
            throw AllocationError();
        }
        (*classes_data)[classID] = curr_class_time+time;
    }
}

void CoursesManager::TimeViewed(int courseID, int classID, int* timeViewed) {
    auto course = coursesData->findCourse(courseID);
    if (!course) {
        throw Failure();
    }
    auto classes_data = course->data;
    if (classes_data->getCapacity() < classID+1) {
        throw InvalidInput();
    }
    *timeViewed = (*classes_data)[classID];
}

void CoursesManager::GetIthWatchedClass(int i, int *courseID, int *classID) {
    trio ith_watched_class = timeTree->findIBiggest(i);
    if (ith_watched_class == trio(-1,-1,-1)) {
        throw Failure();
    }
    else {
        *courseID = ith_watched_class.getData2();
        *classID = ith_watched_class.getData3();
    }
}

#endif //COURSES_MANAGER_H