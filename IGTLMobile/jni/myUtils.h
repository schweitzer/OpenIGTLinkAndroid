#ifndef __MYUTILS_H__
#define __MYUTILS_H__

#include <sys/socket.h>
#include <errno.h>

#include <android/log.h>

#include "igtlOSUtil.h"
#include "igtlTransformMessage.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "IGTLMobile", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "IGTLMobile", __VA_ARGS__))

namespace myUtils
{

//-----------------------------------------------------------------------------

void testSocket()
{
    LOGI("Test socket");
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int err = errno;

    if(sockfd == -1)
    {
        LOGI("Test failed ...");
    }
    else
    {
        LOGI("Test OK !");
    }
}


//-----------------------------------------------------------------------------

void getTestMatrix(igtl::Matrix4x4& matrix)
{

    //dummy values i+j
    matrix[0][0] = 0.0;
    matrix[0][1] = 1.0;
    matrix[0][2] = 2.0;
    matrix[0][3] = 3.0;
    matrix[1][0] = 1.0;
    matrix[1][1] = 2.0;
    matrix[1][2] = 3.0;
    matrix[1][3] = 4.0;
    matrix[2][0] = 2.0;
    matrix[2][1] = 3.0;
    matrix[2][2] = 4.0;
    matrix[2][3] = 5.0;
    matrix[3][0] = 0.0;
    matrix[3][1] = 0.0;
    matrix[3][2] = 0.0;
    matrix[3][3] = 1.0;


}

//-----------------------------------------------------------------------------

bool testMatrix(igtl::Matrix4x4& matrix)
{
    //Test if we have the same dummy values
    bool test = false;

    if(matrix[0][0] == 0.0 && matrix[0][1] == 1.0 && matrix[0][2] == 2.0 && matrix[0][3] == 3.0 &&
       matrix[1][0] == 1.0 && matrix[1][1] == 2.0 && matrix[1][2] == 3.0 && matrix[1][3] == 4.0 &&
       matrix[2][0] == 2.0 && matrix[2][1] == 3.0 && matrix[2][2] == 4.0 && matrix[2][3] == 5.0 &&
       matrix[3][0] == 0.0 && matrix[3][1] == 0.0 && matrix[3][2] == 0.0 && matrix[3][3] == 1.0)
    {
        test = true;
    }


    return test;
}

//-----------------------------------------------------------------------------
}

#endif
