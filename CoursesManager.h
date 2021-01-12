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
        std::shared_ptr<Tnode_v2> curr_cell = (*(remove_course->data))[i];
        if (curr_cell) {
            trio remove_key = curr_cell->key;
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
    std::shared_ptr<Tnode_v2> add_to_class = (*classes_data)[classID];
    if (!add_to_class) { //the class has never been viewed
        try {
            timeTree->insert(trio(time, courseID, classID));
        }
        catch (rankedAVL::AllocationError& e) {
            throw AllocationError();
        }
        (*classes_data)[classID] = timeTree->getKey(trio(time, courseID, classID));
    }
    else { //just need to update the time currently viewed
        int old_time = add_to_class->key.getData1();
        timeTree->remove(add_to_class->key);
        try {
            timeTree->insert(trio(old_time+time, courseID, classID));
        }
        catch (rankedAVL::AllocationError& e) {
            throw AllocationError();
        }
        (*classes_data)[classID] = timeTree->getKey(trio(time+old_time, courseID, classID));
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
    std::shared_ptr<Tnode_v2> viewed_class = (*classes_data)[classID];
    if (!viewed_class) {//its null
        *timeViewed = 0;
    }
    else {
        *timeViewed = (viewed_class->key).getData1();
    }
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