/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <sys/socket.h>
#include <jni.h>
#include <errno.h>
#include <thread>
#include <chrono>

#include <android/log.h>
#include <android_native_app_glue.h>

#include "igtlOSUtil.h"
#include "igtlTransformMessage.h"
#include "igtlClientSocket.h"
#include "igtlServerSocket.h"

#include "igtlClient.h"
#include "igtlServer.h"


//-----------------------------------------------------------------------------

//main
void android_main(struct android_app* state)
{ 
    app_dummy();
    LOGI("Hello OpenIGTLink");

    Client* c = new Client();

    bool connection = c->connect("192.168.3.42",1234);

    if(connection)
    {
        c->sendData();

        c->closeConnection();
    }
    delete c;

}
