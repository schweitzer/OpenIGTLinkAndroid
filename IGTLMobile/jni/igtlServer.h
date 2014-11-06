#ifndef __IGTLSERVER_H__
#define __IGTLSERVER_H__


#include <thread>

#include <android/log.h>

#include "igtlOSUtil.h"
#include "igtlTransformMessage.h"
#include "igtlClientSocket.h"
#include "igtlServerSocket.h"

#include "myUtils.h"


class Server
{
public:
    Server()
    {

        m_serverSocket = igtl::ServerSocket::New();
        m_clientSocket = igtl::ClientSocket::New();
        m_stop = false;
        m_isStarted = false;
    }

    ~Server()
    {

    }

    void create(int port)
    {
        LOGI("Server : Create server");
        m_serverSocket->CreateServer(port);
        m_isStarted = true;
    }

    void waitClient(int mseconds)
    {
        LOGI("Server : Wait for client ...");
        m_clientSocket = m_serverSocket->WaitForConnection(mseconds);

        if(m_clientSocket.IsNotNull())
        {
            LOGI("Server : Client connected !");
        }

    }


    //Do this in a thread
    void run()
    {
        LOGI("Server : Run...");
        bool stop = false;

        for(unsigned int i = 0; i< 100; i++)
        {
            // start receiving data
            igtl::MessageHeader::Pointer headerMsg;
            headerMsg = igtl::MessageHeader::New();
            headerMsg->InitPack();
            int r = m_clientSocket->Receive(headerMsg->GetPackPointer(), headerMsg->GetPackSize());

            LOGI("Server: Receive data...");

            // Message body handler for TRANSFORM
            igtl::TransformMessage::Pointer transMsg;
            transMsg = igtl::TransformMessage::New();

            transMsg->SetMessageHeader(headerMsg);
            transMsg->AllocatePack();

            m_clientSocket->Receive(transMsg->GetPackBodyPointer(), transMsg->GetPackBodySize());

            int c = transMsg->Unpack(1);
            if (c & igtl::MessageHeader::UNPACK_BODY)
            {
                // if CRC check is OK. Read transform data.
                igtl::Matrix4x4 matrix;
                transMsg->GetMatrix(matrix);

                if(myUtils::testMatrix(matrix))
                {
                    LOGI("Server : Matrix Test success...");

                }
                else
                {
                    LOGI("Server : Matrix Test failed ...");
                }
            }
            igtl::Sleep(1000);
        }

    }

    void closeConnection()
    {
        if(m_isStarted)
        {
            m_serverSocket->CloseSocket();
            if(m_clientSocket.IsNotNull())
            {
                m_clientSocket->CloseSocket();
            }
        }

    }

private:

    igtl::ServerSocket::Pointer m_serverSocket;
    igtl::ClientSocket::Pointer m_clientSocket;

    bool m_stop;
    bool m_isStarted;

};

#endif
