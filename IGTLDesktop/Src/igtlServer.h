#ifndef __IGTLSERVER_H__
#define __IGTLSERVER_H__

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
        std::cout<<"Server : Create server"<<std::endl;
        m_serverSocket->CreateServer(port);
        m_isStarted = true;
    }

    void waitClient(int mseconds)
    {
        std::cout<<"Server : Wait for client ..."<<std::endl;
        m_clientSocket = m_serverSocket->WaitForConnection(mseconds);

        if(m_clientSocket.IsNotNull())
        {
            std::cout<<"Server : Client connected !"<<std::endl;
        }

    }


    //Do this in a thread
    void run()
    {

        std::cout<<"Server : Run..."<<std::endl;
        bool stop = false;

        for(unsigned int i = 0; i< 100; i++)
        {
            if(m_clientSocket.IsNotNull())
            {
                // start receiving data
                igtl::MessageHeader::Pointer headerMsg;
                headerMsg = igtl::MessageHeader::New();
                headerMsg->InitPack();
                int r = m_clientSocket->Receive(headerMsg->GetPackPointer(), headerMsg->GetPackSize());

                if(r == 0 || r == -1)
                {
                    std::cout<<"Error on receive"<<std::endl;
                }

                std::cout<<"Server: Receive data of type : "<<headerMsg->GetDeviceType()<<std::endl;

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

                    igtl::PrintMatrix(matrix);

                    if(myUtils::testMatrix(matrix))
                    {
                        std::cout<<"Server : Matrix Test success..."<<std::endl;

                    }
                    else
                    {
                        std::cout<<"Server : Matrix Test failed ..."<<std::endl;
                    }
                }
                igtl::Sleep(1000);
            }
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
