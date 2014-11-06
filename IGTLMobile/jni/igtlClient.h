#ifndef __IGTLCLIENT_H__
#define __IGTLCLIENT_H__

#include "igtlOSUtil.h"
#include "igtlTransformMessage.h"
#include "igtlClientSocket.h"

#include "myUtils.h"


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "IGTLMobile", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "IGTLMobile", __VA_ARGS__))

class Client
{
public:

    Client()
    {
        m_socket = igtl::ClientSocket::New();
        m_isConnected = false;
    }

    ~Client()
    {

    }

    bool connect(const char* host, int port)
    {
        int r =m_socket->ConnectToServer(host, port);

        if (r != 0)
        {
            LOGI("Client : Failed to connect !");
            m_socket->CloseSocket();
            m_isConnected = false;
        }
        else
        {
            LOGI("Client : Connected !");
            m_isConnected = true;
        }
        return m_isConnected;
    }

    void closeConnection()
    {
        if(m_isConnected)
        {
             m_socket->CloseSocket();
        }

    }

     void sendData()
     {
        if(m_isConnected)
        {
            LOGI("Client : Sending matrix...");
            for(unsigned int i = 0; i< 100; i++)
            {
                igtl::TransformMessage::Pointer transMsg;
                transMsg = igtl::TransformMessage::New();
                transMsg->SetDeviceName("Test");

                igtl::Matrix4x4 matrix;
                myUtils::getTestMatrix(matrix);

                transMsg->SetMatrix(matrix);
                transMsg->Pack();
                m_socket->Send(transMsg->GetPackPointer(), transMsg->GetPackSize());
                igtl::Sleep(5000);
            }

            LOGI("Client : Matrix send !");
        }
        else
        {
             LOGI("Client : Can not send data if client is not connected");
        }
     }


private:

     igtl::Matrix4x4 m_matrix;
     igtl::ClientSocket::Pointer m_socket;
     bool m_isConnected;
};

#endif
