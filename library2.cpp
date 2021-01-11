#include "library2.h"
#include "CoursesManager.h"

void* Init() {
    CoursesManager *DS = new CoursesManager();
    return (void*)DS;
}

StatusType AddCourse (void *DS, int courseID) {
    if (!DS || courseID<=0) {
        return INVALID_INPUT;
    }
    try {
        ((CoursesManager*)DS)->AddCourse(courseID);
    }
    catch (CoursesManager::AllocationError& e) {
        return ALLOCATION_ERROR;
    }
    catch (CoursesManager::Failure& e) {
        return FAILURE;
    }
    catch (...) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemoveCourse (void *DS, int courseID) {
    if (!DS || courseID<=0) {
        return INVALID_INPUT;
    }
    try {
        ((CoursesManager*)DS)->RemoveCourse(courseID);
    }
    catch (CoursesManager::AllocationError& e) {
        return ALLOCATION_ERROR;
    }
    catch (CoursesManager::Failure& e) {
        return FAILURE;
    }
    catch (...) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType AddClass(void *DS, int courseID, int* classID) {
    if (!DS || courseID<=0) {
        return INVALID_INPUT;
    }
    try {
        ((CoursesManager*)DS)->AddClass(courseID, classID);
    }
    catch (CoursesManager::AllocationError& e) {
        return ALLOCATION_ERROR;
    }
    catch (CoursesManager::Failure& e) {
        return FAILURE;
    }
    catch (...) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType WatchClass(void *DS, int courseID, int classID, int time) {
    if (!DS || courseID<=0 || classID<0 || time<=0) {
        return INVALID_INPUT;
    }
    try {
        ((CoursesManager*)DS)->WatchClass(courseID, classID, time);
    }
    catch (CoursesManager::InvalidInput& e) {
        return INVALID_INPUT;
    }
    catch (CoursesManager::AllocationError& e) {
        return ALLOCATION_ERROR;
    }
    catch (CoursesManager::Failure& e) {
        return FAILURE;
    }
    catch (...) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed) {
    if (!DS || courseID<=0 || classID<0) {
        return INVALID_INPUT;
    }
    try {
        ((CoursesManager*)DS)->TimeViewed(courseID, classID, timeViewed);
    }
    catch (CoursesManager::InvalidInput& e) {
        return INVALID_INPUT;
    }
    catch (CoursesManager::AllocationError& e) {
        return ALLOCATION_ERROR;
    }
    catch (CoursesManager::Failure& e) {
        return FAILURE;
    }
    catch (...) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetIthWatchedClass(void* DS, int i, int* courseID, int* classID) {
    if (!DS || i<=0) {
        return INVALID_INPUT;
    }
    try {
        ((CoursesManager*)DS)->GetIthWatchedClass(i, courseID, classID);
    }
    catch (CoursesManager::AllocationError& e) {
        return ALLOCATION_ERROR;
    }
    catch (CoursesManager::Failure& e) {
        return FAILURE;
    }
    catch (...) {
        return FAILURE;
    }
    return SUCCESS;
}

void Quit(void** DS) {
    delete ((CoursesManager*)*DS);
    *DS = nullptr;
}