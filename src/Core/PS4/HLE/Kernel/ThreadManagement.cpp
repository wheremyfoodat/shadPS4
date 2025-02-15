#include "ThreadManagement.h"
#include "../ErrorCodes.h"

namespace HLE::Libs::LibKernel::ThreadManagement
{

thread_local PthreadInternal* g_pthread_self = nullptr;
PThreadCxt* g_pthread_cxt = nullptr;



int scePthreadAttrInit(ScePthreadAttr* attr) {

    *attr = new PthreadAttrInternal{};

    int result = pthread_attr_init(&(*attr)->p);

    (*attr)->affinity = 0x7f;
    (*attr)->guard_size = 0x1000;

    SceKernelSchedParam param{};
    param.sched_priority = 700;

    result = (result == 0 ? scePthreadAttrSetinheritsched(attr, PTHREAD_INHERIT_SCHED) : result);
    result = (result == 0 ? scePthreadAttrSetschedparam(attr, &param) : result);
    result = (result == 0 ? scePthreadAttrSetschedpolicy(attr, SCHED_OTHER) : result);
    result = (result == 0 ? scePthreadAttrSetdetachstate(attr, PTHREAD_CREATE_JOINABLE) : result);

    switch (result) {
        case 0: return SCE_OK;
        case ENOMEM: return SCE_KERNEL_ERROR_ENOMEM;
        default: return SCE_KERNEL_ERROR_EINVAL;
    }
}

int scePthreadAttrSetdetachstate(ScePthreadAttr* attr, int detachstate) {

    if (attr == nullptr || *attr == nullptr) {
        return SCE_KERNEL_ERROR_EINVAL;
    }

    int pstate = PTHREAD_CREATE_JOINABLE;
    switch (detachstate) {
        case 0: pstate = PTHREAD_CREATE_JOINABLE; break;
        case 1: pstate = PTHREAD_CREATE_DETACHED; break;
        default: 
            __debugbreak(); //unknown state
    }

    int result = pthread_attr_setdetachstate(&(*attr)->p, pstate);

    (*attr)->detached = (pstate == PTHREAD_CREATE_DETACHED);

    if (result == 0) {
        return SCE_OK;
    }
    return SCE_KERNEL_ERROR_EINVAL;
}

int scePthreadAttrSetinheritsched(ScePthreadAttr* attr, int inheritSched) {

    if (attr == nullptr || *attr == nullptr) {
        return SCE_KERNEL_ERROR_EINVAL;
    }

    int pinherit_sched = PTHREAD_INHERIT_SCHED;
    switch (inheritSched) {
        case 0: pinherit_sched = PTHREAD_EXPLICIT_SCHED; break;
        case 4: pinherit_sched = PTHREAD_INHERIT_SCHED; break;
        default: __debugbreak();  // unknown inheritSched
    }

    int result = pthread_attr_setinheritsched(&(*attr)->p, pinherit_sched);

    if (result == 0) {
        return SCE_OK;
    }
    return SCE_KERNEL_ERROR_EINVAL;
}

int scePthreadAttrSetschedparam(ScePthreadAttr* attr, const SceKernelSchedParam* param) {

    if (param == nullptr || attr == nullptr || *attr == nullptr) {
        return SCE_KERNEL_ERROR_EINVAL;
    }

    SceKernelSchedParam pparam{};
    if (param->sched_priority <= 478) {
        pparam.sched_priority = +2;
    } else if (param->sched_priority >= 733) {
        pparam.sched_priority = -2;
    } else {
        pparam.sched_priority = 0;
    }

    int result = pthread_attr_setschedparam(&(*attr)->p, &pparam);

    if (result == 0) {
        return SCE_OK;
    }
    return SCE_KERNEL_ERROR_EINVAL;
}

int scePthreadAttrSetschedpolicy(ScePthreadAttr* attr, int policy) {

    if (attr == nullptr || *attr == nullptr) {
        return SCE_KERNEL_ERROR_EINVAL;
    }

    if (policy!= SCHED_OTHER)
    {
        __debugbreak();//invest if policy is other and if winpthreadlibrary support it
    }

    (*attr)->policy = policy;

    int result = pthread_attr_setschedpolicy(&(*attr)->p, policy);

    if (result == 0) {
        return SCE_OK;
    }
    return SCE_KERNEL_ERROR_EINVAL;
}

};