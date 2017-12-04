
#include "PracticalSocket.h" // For UDPSocket and SocketException
#include <iostream>          // For cout and cerr
#include <cstdlib>           // For atoi()
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <opencv/cv.h>
#include <queue>
#include <pthread.h>

#define BUF_LEN 65540 // Larger than maximum UDP packet size

#include "opencv2/opencv.hpp"
using namespace cv;
#include "config.h"

#define PORT_NUM 9000


// C++ std library dependencies
#include <chrono> // `std::chrono::` functions and classes, e.g. std::chrono::milliseconds
#include <thread> // std::this_thread
// Other 3rdparty dependencies
// GFlags: DEFINE_bool, _int32, _int64, _uint64, _double, _string
#include <gflags/gflags.h>
// Allow Google Flags in Ubuntu 14
#ifndef GFLAGS_GFLAGS_H_
    namespace gflags = google;
#endif
// OpenPose dependencies
#include <openpose/headers.hpp>
std::queue<cv::Mat> frameQueue;
int tcpsocket;

struct Pt{
    float x, y;
};

struct UserPoint{
struct Pt body;
struct Pt rightHand;
};
    
// Option b) Manually importing the desired modules. Recommended if you only intend to use a few modules.
// #include <openpose/core/headers.hpp>
// #include <openpose/filestream/headers.hpp>
// #include <openpose/gui/headers.hpp>
// #include <openpose/pose/headers.hpp>
// #include <openpose/producer/headers.hpp>
// #include <openpose/thread/headers.hpp>
// #include <openpose/utilities/headers.hpp>

// See all the available parameter options withe the `--help` flag. E.g. `build/examples/openpose/openpose.bin --help`
// Note: This command will show you flags for other unnecessary 3rdparty files. Check only the flags for the OpenPose
// executable. E.g. for `openpose.bin`, look for `Flags from examples/openpose/openpose.cpp:`.
// Debugging/Other
DEFINE_int32(logging_level,             3,              "The logging level. Integer in the range [0, 255]. 0 will output any log() message, while"
                                                        " 255 will not output any. Current OpenPose library messages are in the range 0-4: 1 for"
                                                        " low priority messages and 4 for important ones.");
// Producer
DEFINE_string(image_dir,                "examples/media/",      "Process a directory of images. Read all standard formats (jpg, png, bmp, etc.).");
// Consumer
DEFINE_bool(fullscreen,                 false,          "Run in full-screen mode (press f during runtime to toggle).");

// The W-classes can be implemented either as a template or as simple classes given
// that the user usually knows which kind of data he will move between the queues,
// in this case we assume a std::shared_ptr of a std::vector of op::Datum

// This worker will just read and return all the jpg files in a directory
class WUserInput : public op::WorkerProducer<std::shared_ptr<std::vector<op::Datum>>>
{
public:

    WUserInput(const std::string& directoryPath) :
        mImageFiles{op::getFilesOnDirectory(directoryPath, "jpg")},
        mCounter{0}
    {
        if (mImageFiles.empty())
            op::error("No images found on: " + directoryPath, __LINE__, __FUNCTION__, __FILE__);
    }

    void initializationOnThread() {}

    std::shared_ptr<std::vector<op::Datum>> workProducer()
    {
        try
        {
            // Close program when empty frame
            if (frameQueue.empty())
            {
                return nullptr;
            }
            else
            {
                // Create new datum
                auto datumsPtr = std::make_shared<std::vector<op::Datum>>();
                datumsPtr->emplace_back();
                auto& datum = datumsPtr->at(0);

                datum.cvInputData = frameQueue.front();
                frameQueue.pop();
                // If empty frame -> return nullptr
                if (datum.cvInputData.empty())
                {
                    op::log("Empty frame detected on path: " + mImageFiles.at(mCounter-1) + ". Closing program.",
                        op::Priority::High);
                    datumsPtr = nullptr;
                }

                return datumsPtr;
            }
        }
        catch (const std::exception& e)
        {
            op::log("Some kind of unexpected error happened.");
            this->stop();
            op::error(e.what(), __LINE__, __FUNCTION__, __FILE__);
            return nullptr;
        }
    }

private:
    const std::vector<std::string> mImageFiles;
    unsigned long long mCounter;
};

// This worker will just invert the image
class WUserPostProcessing : public op::Worker<std::shared_ptr<std::vector<op::Datum>>>
{
public:
    WUserPostProcessing()
    {
        // User's constructor here
    }

    void initializationOnThread() {}

    void work(std::shared_ptr<std::vector<op::Datum>>& datumsPtr)
    {
        // User's post-processing (after OpenPose processing & before OpenPose outputs) here
            // datum.cvOutputData: rendered frame with pose or heatmaps
            // datum.poseKeypoints: Array<float> with the estimated pose
        try
        {
            if (datumsPtr != nullptr && !datumsPtr->empty())
                for (auto& datum : *datumsPtr)
                    cv::bitwise_not(datum.cvInputData, datum.cvOutputData);
        }
        catch (const std::exception& e)
        {
            op::log("Some kind of unexpected error happened.");
            this->stop();
            op::error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        }
    }
};

// This worker will just read and return all the jpg files in a directory
class WUserOutput : public op::WorkerConsumer<std::shared_ptr<std::vector<op::Datum>>>
{
public:
    void initializationOnThread() {}

    void workConsumer(const std::shared_ptr<std::vector<op::Datum>>& datumsPtr)
    {
        try
        {
            // User's displaying/saving/other processing here
                // datum.cvOutputData: rendered frame with pose or heatmaps
                // datum.poseKeypoints: Array<float> with the estimated pose
            if (datumsPtr != nullptr && !datumsPtr->empty())
            {
               // cv::imshow("User worker GUI", datumsPtr->at(0).cvOutputData);
                // It displays the image and sleeps at least 1 ms (it usually sleeps ~5-10 msec to display the image)
               // cv::waitKey(1);
            }
        }
        catch (const std::exception& e)
        {
            op::log("Some kind of unexpected error happened.");
            this->stop();
            op::error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        }
    }
};

int openPoseTutorialThread3()
{
    op::log("OpenPose Library Tutorial - Example 3.", op::Priority::High);
    // ------------------------- INITIALIZATION -------------------------
    // Step 1 - Set logging level
        // - 0 will output all the logging messages
        // - 255 will output nothing
    op::check(0 <= FLAGS_logging_level && FLAGS_logging_level <= 255, "Wrong logging_level value.",
              __LINE__, __FUNCTION__, __FILE__);
    op::ConfigureLog::setPriorityThreshold((op::Priority)FLAGS_logging_level);
    // Step 2 - Setting thread workers && manager
    typedef std::shared_ptr<std::vector<op::Datum>> TypedefDatums;
    typedef std::shared_ptr<op::Worker<TypedefDatums>> TypedefWorker;
    op::ThreadManager<TypedefDatums> threadManager;
    // Step 3 - Initializing the worker classes
    // Frames producer (e.g. video, webcam, ...)
    TypedefWorker wUserInput = std::make_shared<WUserInput>(FLAGS_image_dir);
    // Processing
    TypedefWorker wUserProcessing = std::make_shared<WUserPostProcessing>();
    // GUI (Display)
    TypedefWorker wUserOutput = std::make_shared<WUserOutput>();

    // ------------------------- CONFIGURING THREADING -------------------------
    // In this simple multi-thread example, we will do the following:
        // 3 (virtual) queues: 0, 1, 2
        // 1 real queue: 1. The first and last queue ids (in this case 0 and 2) are not actual queues, but the
        // beginning and end of the processing sequence
        // 2 threads: 0, 1
        // wUserInput will generate frames (there is no real queue 0) and push them on queue 1
        // wGui will pop frames from queue 1 and process them (there is no real queue 2)
    auto threadId = 0ull;
    auto queueIn = 0ull;
    auto queueOut = 1ull;
    threadManager.add(threadId++, wUserInput, queueIn++, queueOut++);       // Thread 0, queues 0 -> 1
    threadManager.add(threadId++, wUserProcessing, queueIn++, queueOut++);  // Thread 1, queues 1 -> 2
    threadManager.add(threadId++, wUserOutput, queueIn++, queueOut++);      // Thread 2, queues 2 -> 3

    // ------------------------- STARTING AND STOPPING THREADING -------------------------
    op::log("Starting thread(s)", op::Priority::High);
    // Two different ways of running the program on multithread environment
        // Option a) Using the main thread (this thread) for processing (it saves 1 thread, recommended)
    threadManager.exec();  // It blocks this thread until all threads have finished
        // Option b) Giving to the user the control of this thread
    // // VERY IMPORTANT NOTE: if OpenCV is compiled with Qt support, this option will not work. Qt needs the main
    // // thread to plot visual results, so the final GUI (which uses OpenCV) would return an exception similar to:
    // // `QMetaMethod::invoke: Unable to invoke methods with return values in queued connections`
    // // Start threads
    // threadManager.start();
    // // Keep program alive while running threads. Here the user could perform any other desired function
    // while (threadManager.isRunning())
    //     std::this_thread::sleep_for(std::chrono::milliseconds{33});
    // // Stop and join threads
    // op::log("Stopping thread(s)", op::Priority::High);
    // threadManager.stop();

    // ------------------------- CLOSING -------------------------
    // Logging information message
    op::log("Example 3 successfully finished.", op::Priority::High);
    // Return successful message
    return 0;
}
void* transfer(void*)
{
        openPoseTutorialThread3();
}


int main(int argc, char *argv[])
{
    // Parsing command line flags
    gflags::ParseCommandLineFlags(&argc, &argv, true);

       try {

        pthread_t serverThread;
        int sockfd=socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in serverAddress;
        struct sockaddr_in clientAddress;
        memset(&serverAddress,0,sizeof(serverAddress));
        serverAddress.sin_family=AF_INET;
        serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
        serverAddress.sin_port=htons(PORT_NUM);
        bind(sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress));

        listen(sockfd,5);

        string th_str;

        socklen_t sosize  = sizeof(clientAddress);
        tcpsocket = accept(sockfd,(struct sockaddr*)&clientAddress,&sosize);
        th_str = inet_ntoa(clientAddress.sin_addr);
        cout<<"3"<<endl;
        pthread_create(&serverThread,NULL,&transfer,NULL);



        UDPSocket sock(PORT_NUM);

        char buffer[BUF_LEN]; // Buffer for echo string
        int recvMsgSize; // Size of received message
        string sourceAddress; // Address of datagram source
        unsigned short sourcePort; // Port of datagram source

        clock_t last_cycle = clock();

        while (1) 
        {
            // Block until receive message from a client
            do 
            {
                recvMsgSize = sock.recvFrom(buffer, BUF_LEN, sourceAddress, sourcePort);
            } while (recvMsgSize > sizeof(int));
            int total_pack = ((int * ) buffer)[0];

    //        cout << "expecting length of packs:" << total_pack << endl;
            char * longbuf = new char[PACK_SIZE * total_pack];
            for (int i = 0; i < total_pack; i++) 
            {
                recvMsgSize = sock.recvFrom(buffer, BUF_LEN, sourceAddress, sourcePort);
                if (recvMsgSize != PACK_SIZE) 
                {
                    cerr << "Received unexpected size pack:" << recvMsgSize << endl;
                    continue;
                }
                memcpy( & longbuf[i * PACK_SIZE], buffer, PACK_SIZE);
            }

    //        cout << "Received packet from " << sourceAddress << ":" << sourcePort << endl;

            Mat rawData = Mat(1, PACK_SIZE * total_pack, CV_8UC1, longbuf);
            Mat frame = imdecode(rawData, CV_LOAD_IMAGE_COLOR);
            if (frame.size().width == 0) 
            {
                cerr << "decode failure!" << endl;
                continue;
            }

            if(frameQueue.size()<50)
            {
                frameQueue.push(frame);
            }

            //imshow("recv", frame);

            free(longbuf);

            //waitKey(1);
            clock_t next_cycle = clock();
            double duration = (next_cycle - last_cycle) / (double) CLOCKS_PER_SEC;
    //        cout << "\teffective FPS:" << (1 / duration) << " \tkbps:" << (PACK_SIZE * total_pack / duration / 1024 * 8) << endl;

     //       cout << next_cycle - last_cycle;
            last_cycle = next_cycle;
        }
    } catch (SocketException & e) {
        cerr << e.what() << endl;
        exit(1);
    }

    // Running openPoseTutorialThread3
    return openPoseTutorialThread3();
}
