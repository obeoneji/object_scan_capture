//=============================================================================
// Copyright © 2008 Point Grey Research, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of Point
// Grey Research, Inc. ("Confidential Information").  You shall not
// disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with PGR.
//
// PGR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. PGR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
//=============================================================================
// $Id: AsyncTriggerEx.cpp,v 1.21 2010-07-22 22:51:51 soowei Exp $
//=============================================================================
#define WIN32_LEAN_AND_MEAN


#include "stdafx.h"

#include "FlyCapture2.h"
#include "Set_CamPara.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <string>
//#include <Windows.h>
#include <direct.h>
#include <conio.h>
#include <ctime>

//server include file
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")



#define DEFAULT_BUFLEN 1
#define DEFAULT_PORT "27015"


using namespace FlyCapture2;
using namespace std;

void PrintBuildInfo()
{
	FC2Version fc2Version;
	Utilities::GetLibraryVersion( &fc2Version );

	ostringstream version;
	version << "FlyCapture2 library version: " << fc2Version.major << "." << fc2Version.minor << "." << fc2Version.type << "." << fc2Version.build;
	cout << version.str() <<endl;

	ostringstream timeStamp;
	timeStamp << "Application build date: " << __DATE__ << " " << __TIME__;
	cout << timeStamp.str() << endl << endl;
}

void PrintCameraInfo( CameraInfo* pCamInfo )
{
	cout << endl;
	cout << "*** CAMERA INFORMATION ***" << endl;
	cout << "Serial number -" << pCamInfo->serialNumber << endl;
	cout << "Camera model - " << pCamInfo->modelName << endl;
	cout << "Camera vendor - " << pCamInfo->vendorName << endl;
	cout << "Sensor - " << pCamInfo->sensorInfo << endl;
	cout << "Resolution - " << pCamInfo->sensorResolution << endl;
	cout << "Firmware version - " << pCamInfo->firmwareVersion << endl;
	cout << "Firmware build time - " << pCamInfo->firmwareBuildTime << endl << endl;

}

void PrintFormat7Capabilities( Format7Info fmt7Info )
{
	cout << "Max image pixels: (" << fmt7Info.maxWidth << ", " << fmt7Info.maxHeight << ")" << endl;
	cout << "Image Unit size: (" << fmt7Info.imageHStepSize << ", " << fmt7Info.imageVStepSize << ")" << endl;
	cout << "Offset Unit size: (" << fmt7Info.offsetHStepSize << ", " << fmt7Info.offsetVStepSize << ")" << endl;
	cout << "Pixel format bitfield: 0x" << fmt7Info.pixelFormatBitField << endl;

}

void PrintError( Error error )
{
	error.PrintErrorTrace();
}

void GrabImages( Camera *ptCam, Image* Image_seq)
{
	FlyCapture2::Error error;

	error = ptCam->RetrieveBuffer( Image_seq);	

	
}

void GrabImages_unused( Camera *ptCam)
{
	FlyCapture2::Error error;
	Image imageTemp;

	error = ptCam->RetrieveBuffer( &imageTemp);	
	if (error != PGRERROR_OK)
	{
		printf("capture error\n");
		return;
	}
}



void GrabImages_rest( Camera *ptCam)
{
	FlyCapture2::Error error;
	Image imageTemp;
	while(1)
	{
		error = ptCam->RetrieveBuffer( &imageTemp);	
		if (error != PGRERROR_OK)
		{
			break;
		}
		else
		{
			cout << "still have image in buffer" << endl;
		}
	}
}

void release_buffered_images(Camera** ppCameras, int numCameras)
{
	std::clock_t seq_start;
	seq_start = std::clock();
	while (1)
	{
		for (unsigned int i = 0; i < numCameras; i++)
		{
			GrabImages_unused(ppCameras[i]);
		}

		std::clock_t seq_end;
		double duration;
		seq_end = std::clock();

		duration = (seq_end - seq_start) / (double)CLOCKS_PER_SEC;

		if (duration < 0.25)
		{
			printf("start sync cap\n");
			break;
		}

		seq_start = seq_end;
	}
}


string ZeroPadNumber(int num, int zero_num)
{
    std::ostringstream ss;
    ss << std::setw( zero_num ) << std::setfill( '0' ) << num;
    return ss.str();
}

void pad(char *s, int n, int c) 
{
    char *p = s + n - strlen(s);
    strcpy(p, s);
    p--;
    while (p >= s) 
	{ 
		p[0] = c; 
		p--; 
	}
}

void write_out_image(Camera *ptCam, Image Image_data, int cam_num, int seq_num, char* bayerType, char* sn_num, char * folder)
{
	FlyCapture2::Error error;

	char fn[30];
	strcpy(fn,folder);
	strcat(fn,"//");
	char preidx[10] = "img_";
	strcat(fn,preidx);
	char id_num[20];

	strcat(fn,bayerType);
	strcat(fn,"_");

	strcat(fn,sn_num);
	strcat(fn,"_");

	string img_num = ZeroPadNumber(seq_num,4);

	strcat(fn,img_num.c_str());
	strcat(fn,".bmp");


	error = Image_data.Save( fn );	
}


int main(int /*argc*/, char** /*argv*/)
{
	//////////////////////////////////////////////////////////////////////////////////////
	//load config file
	unsigned int total_ang, pat_num, seq_num ;
	

	string configSeqNum = "seqnum.ini";
	char server_ip[60];
	char folder_path[60];


	loadConfig_sn(configSeqNum, &total_ang, &pat_num, &seq_num, server_ip, folder_path);
	char output_path[80];
	char output_fd[15] = "output_raw";
	strcpy(output_path, folder_path);
	strcat(output_path, output_fd);
	_mkdir(output_path);


	// Load parameters for color camera
	float *shutter_time_c = new float[pat_num];
	float *brightVal_c = new float[pat_num];
	float *gammaVal_c = new float[pat_num];
	float *gainVal_c = new float[pat_num];
	float *satuVal_c = new float[pat_num];
	unsigned int *sharpVal_c = new unsigned int[pat_num];
	unsigned int *redVal_c = new unsigned int[pat_num];
	unsigned int *blueVal_c = new unsigned int[pat_num];

	for (int i = 0; i < pat_num; i++)
	{
		std::string configFile;
		configFile = std::string("config_color_pat_") + std::to_string(i) + ".ini";

		loadConfig_Color(configFile, &shutter_time_c[i], &brightVal_c[i], &gammaVal_c[i], &gainVal_c[i], &sharpVal_c[i], &redVal_c[i], &blueVal_c[i], &satuVal_c[i]);
	}
	
		

	// Load parameters for IR camera
	float *shutter_time_ir = new float[pat_num];
	float *brightVal_ir = new float[pat_num];
	float *gammaVal_ir = new float[pat_num];
	float *gainVal_ir = new float[pat_num];
	float *satuVal_ir = new float[pat_num];
	unsigned int *sharpVal_ir = new unsigned int[pat_num];
	for (int i = 0; i < pat_num; i++)
	{
		std::string configFile;
		configFile = std::string("config_ir_pat_") + std::to_string(i) + ".ini";

		loadConfig_IR(configFile, &shutter_time_ir[i], &brightVal_ir[i], &gammaVal_ir[i], &gainVal_ir[i], &sharpVal_ir[i], &satuVal_ir[i]);
	}
	//load config file
	//////////////////////////////////////////////////////////////////////////////////////





	////////// *STEP 1* initialize Winsock //////////
	WSADATA wsaData;

	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	

	////////// *STEP 2* creating a socket for the client //////////
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port (using the 1st parameter from the Command Arguments)
	iResult = getaddrinfo(server_ip, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// create Socket object
	SOCKET ConnectSocket = INVALID_SOCKET;

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		////////// *STEP 3* Connect to server
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}






	//////////////////////////////////////////////////////////////////////////////////////
	// Connect to all the cameras
	PrintBuildInfo();

	const int pre_Image_cap = 6;

	Error error;

	BusManager busMgr;
	unsigned int numCameras;
	error = busMgr.GetNumOfCameras(&numCameras);
	if (error != PGRERROR_OK)
	{
		PrintError(error);
		return -1;
	}

	cout << "Number of cameras detected: " << numCameras << endl;

	if (numCameras < 1)
	{
		cout << "Insufficient number of cameras... exiting" << endl;
		return -1;
	}

	// new space for image
	FlyCapture2::Image* Image_temp = new FlyCapture2::Image[numCameras];

	//Connect to camera and get camera info;
	Camera** ppCameras = new Camera*[numCameras];
	char** bayerType = new char *[numCameras];
	char** sn_num = new char *[numCameras];

	for (unsigned int i = 0; i < numCameras; i++)
	{
		ppCameras[i] = new Camera();
		PGRGuid guid;
		error = busMgr.GetCameraFromIndex(i, &guid);
		if (error != PGRERROR_OK)
		{
			PrintError(error);
			return -1;
		}

		// Connect to a camera
		error = ppCameras[i]->Connect(&guid);
		if (error != PGRERROR_OK)
		{
			PrintError(error);
			return -1;
		}

		CameraInfo camInfo;
		error = ppCameras[i]->GetCameraInfo(&camInfo);
		bayerType[i] = new char[10];
		if (camInfo.bayerTileFormat == NONE)
		{
			strcpy(bayerType[i], "IR");
			//strcat(bayerType[i],"_");
		}
		else
		{
			strcpy(bayerType[i], "COLOR");
			//strcat(bayerType[i],"_");
		}
		sn_num[i] = new char[15];
		_itoa(camInfo.serialNumber, sn_num[i], 10);
	}


	// Restore all the camera to Factory Setting
	const unsigned int k_cameraMemory = 0x618;
	unsigned int regMemVal = 0xDEAFBEEF;
	for (unsigned int i = 0; i < numCameras; i++)
	{
		error = ppCameras[i]->WriteRegister(k_cameraMemory, regMemVal);
		printf("Restore to Factory setting!\n");
	}


	// Power on the camera
	const unsigned int k_cameraPower = 0x610;
	const unsigned int k_powerVal = 0x80000000;
	const unsigned int millisecondsToSleep = 100;
	unsigned int regVal = 0;
	unsigned int retries = 10;

	for (unsigned int i = 0; i < numCameras; i++)
	{

		error = ppCameras[i]->WriteRegister(k_cameraPower, k_powerVal);
		if (error != PGRERROR_OK)
		{
			PrintError(error);
			return -1;
		}

		// Wait for camera to complete power-up
		do
		{

			Sleep(millisecondsToSleep);

			error = ppCameras[i]->ReadRegister(k_cameraPower, &regVal);
			if (error == PGRERROR_TIMEOUT)
			{
				// ignore timeout errors, camera may not be responding to
				// register reads during power-up
			}
			else if (error != PGRERROR_OK)
			{
				PrintError(error);
				return -1;
			}

			retries--;
		} while ((regVal & k_powerVal) == 0 && retries > 0);

		// Check for timeout errors after retrying
		if (error == PGRERROR_TIMEOUT)
		{
			PrintError(error);
			return -1;
		}
	}

	// Connect to all the cameras
	//////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////////
	// custom image mode
	const Mode k_fmt7Mode = MODE_0;
	const PixelFormat k_fmt7PixFmt = PIXEL_FORMAT_RAW8;
	Format7Info fmt7Info;
	bool supported;
	fmt7Info.mode = k_fmt7Mode;
	for (unsigned int i = 0; i < numCameras; i++)
	{
		error = ppCameras[i]->GetFormat7Info(&fmt7Info, &supported);
		if (error != PGRERROR_OK)
		{
			PrintError(error);
			return -1;
		}

		PrintFormat7Capabilities(fmt7Info);

		if ((k_fmt7PixFmt & fmt7Info.pixelFormatBitField) == 0)
		{
			// Pixel format not supported!
			cout << "Pixel format is not supported" << endl;
			return -1;
		}
	}

	Format7ImageSettings fmt7ImageSettings;


	bool valid;
	Format7PacketInfo fmt7PacketInfo;
	for (unsigned int i = 0; i < numCameras; i++)
	{

		error = ppCameras[i]->GetFormat7Info(&fmt7Info, &supported);
		fmt7ImageSettings.mode = k_fmt7Mode;
		fmt7ImageSettings.offsetX = 0;
		fmt7ImageSettings.offsetY = 0;
		fmt7ImageSettings.width = fmt7Info.maxWidth;
		fmt7ImageSettings.height = fmt7Info.maxHeight;
		fmt7ImageSettings.pixelFormat = k_fmt7PixFmt;

		// Validate the settings to make sure that they are valid
		error = ppCameras[i]->ValidateFormat7Settings(
			&fmt7ImageSettings,
			&valid,
			&fmt7PacketInfo);
		if (error != PGRERROR_OK)
		{
			PrintError(error);
			return -1;
		}

		if (!valid)
		{
			// Settings are not valid
			cout << "Format7 settings are not valid" << endl;
			return -1;
		}

		// Set the settings to the camera
		error = ppCameras[i]->SetFormat7Configuration(
			&fmt7ImageSettings,
			fmt7PacketInfo.recommendedBytesPerPacket);
		if (error != PGRERROR_OK)
		{
			PrintError(error);
			return -1;
		}
	}





	// Set Buffer for image sequence
	// need to be modified for RAID 
	for (unsigned int i = 0; i < numCameras; i++)
	{
		FC2Config BufferFrame;
		error = ppCameras[i]->GetConfiguration(&BufferFrame);
		if (error != PGRERROR_OK)
		{
			PrintError(error);
			return -1;
		}

		BufferFrame.numBuffers = 10;
		//BufferFrame.numBuffers = seq_num+1;
		BufferFrame.grabMode = BUFFER_FRAMES;
		BufferFrame.highPerformanceRetrieveBuffer = true;
		error = ppCameras[i]->SetConfiguration(&BufferFrame);
		if (error != PGRERROR_OK)
		{
			PrintError(error);
			return -1;
		}
	}

	// Check for external trigger support
	// Trigger
	TriggerMode triggerMode;

	for (unsigned int i = 0; i < numCameras; i++)
	{
		triggerMode = setTriggerMode(ppCameras[i]);
		cout << "Camera " << i << "External trigger is set! ..." << endl;
	}
	cout << "Trigger the camera by sending a trigger pulse to GPIO" << endl;



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int cur_pat_id = 0;
	bool capture_continue = true;

	while (capture_continue) // for every rotate angle (terminated decide by controller)
	{
		
		
		//////////////////////////////////////////////////////////////////////////////////////
		// Set the camera capture parameters
		for (unsigned int i = 0; i < numCameras; i++)
		{
			// Get the camera information
			CameraInfo camInfo;
			error = ppCameras[i]->GetCameraInfo(&camInfo);
			if (error != PGRERROR_OK)
			{
				PrintError(error);
				return -1;
			}

			PrintCameraInfo(&camInfo);

			int setError;

			if (camInfo.modelName[0] == 'G')
			{
				setError = setColorCameraPara(ppCameras[i], 
											  shutter_time_c[cur_pat_id], 
											  brightVal_c[cur_pat_id], 
											  gammaVal_c[cur_pat_id], 
											  gainVal_c[cur_pat_id], 
											  satuVal_c[cur_pat_id], 
											  sharpVal_c[cur_pat_id], 
											  redVal_c[cur_pat_id], 
											  blueVal_c[cur_pat_id]);
				if (setError != 0)
				{
					return -1;
				}
			}
			else if (camInfo.modelName[0] == 'F' && camInfo.modelName[13] == '2')
			{
				setError = setIRCameraPara(ppCameras[i], 
										   shutter_time_ir[cur_pat_id], 
										   brightVal_ir[cur_pat_id], 
										   gammaVal_ir[cur_pat_id], 
										   gainVal_ir[cur_pat_id], 
										   satuVal_ir[cur_pat_id], 
										   sharpVal_ir[cur_pat_id]);
				if (setError != 0)
				{
					return -1;
				}
			}
			else
			{
				cout << "some model is not assigned!!! Camera model is " << camInfo.modelName << endl;
			}

		}
		// Set the camera capture parameters
		//////////////////////////////////////////////////////////////////////////////////////


		////////// *STEP 4* Sending & Receiving Data on the Client
		int recvbuflen = DEFAULT_BUFLEN;

		char *sendbuf_p = "=";
		char* recvbuf = new char[1];

		// send an initial buffer
		iResult = send(ConnectSocket, sendbuf_p, (int)strlen(sendbuf_p), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		printf("Bytes Sent: %ld\n", iResult);
		// Receive until the server closes the connection
		do
		{

			iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

			if (recvbuf[0] == 'p')
			{
				printf("receive p signal.\n");
				break;
			}

		} while (iResult > 0);


		//////////////////////////////////////////////////////////////////////////////////////
		// Start Capture for all cameras
		for (unsigned int i = 0; i < numCameras; i++)
		{
			// Camera is ready, start capturing images
			error = ppCameras[i]->StartCapture();
			if (error != PGRERROR_OK)
			{
				PrintError(error);
				return -1;
			}
		}



		// Retrieve frame rate property
		for (unsigned int i = 0; i < numCameras; i++)
		{
			Property frmRate;
			frmRate.type = FRAME_RATE;
			error = ppCameras[i]->GetProperty(&frmRate);
			if (error != PGRERROR_OK)
			{
				PrintError(error);
				return -1;
			}

			cout << "Camera " << i << "'s frame rate is " << frmRate.absValue << " fps" << endl;


			Property shutterSpeed;
			shutterSpeed.type = SHUTTER;
			error = ppCameras[i]->GetProperty(&shutterSpeed);
			if (error != PGRERROR_OK)
			{
				PrintError(error);
				return -1;
			}

			cout << "Camera " << i << "'s shutter Speed is " << shutterSpeed.absValue << " ms" << endl;
		}
		// Set the camera capture parameters
		//////////////////////////////////////////////////////////////////////////////////////




		////////// **send "s" to controller to say all the camera is start
		// send an new buffer
		char *sendbuf_n = "s";
		iResult = send(ConnectSocket, sendbuf_n, (int)strlen(sendbuf_n), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
		printf("Bytes Sent: %ld\n", iResult);




		//////////////////////////////////////////////////////////////////////////////////////
		// idle capture unused
		release_buffered_images(ppCameras, numCameras);




		//////////////////////////////////////////////////////////////////////////////////////
		// grab frame from camera to disk
		std::clock_t start;
		double duration;

		start = std::clock();

		for (int imageCount = 0; imageCount < seq_num; imageCount++)
		{
#pragma omp parallel for
			for (int i = 0; i < numCameras; i++)
			{

				GrabImages(ppCameras[i], &Image_temp[i]);
				write_out_image(ppCameras[i], Image_temp[i], i, imageCount, bayerType[i], sn_num[i], output_path);
			}
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC * 1000.0;

			cout << " ." << imageCount << ". frame rate is " << duration << "ms per frame! " << endl;
			start = std::clock();
		}

		// save image from memory to disk


		// grab frame from camera to disk
		//////////////////////////////////////////////////////////////////////////////////////


		////////// **send "d" to controller to say all the camera capture for one pattern is finished, and image is saved 
		char *sendbuf_d = "d";
		iResult = send(ConnectSocket, sendbuf_d, (int)strlen(sendbuf_d), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
		printf("Bytes Sent: %ld\n", iResult);

		


		// Receive until the server closes the connection
		do
		{

			iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

			if (recvbuf[0] == 'e')
			{
				printf("receive e signal.\n");
				stopAllCamera(ppCameras, numCameras);
				cur_pat_id = 0; // reset pattern to the first
				break;
			}
			if (recvbuf[0] == 'w')
			{
				printf("receive w signal.\n");
				cur_pat_id++;
				stopAllCamera(ppCameras, numCameras);
				break;
			}
			if (recvbuf[0] == 'f')
			{
				printf("receive final end signal.\n");
				stopAllCamera(ppCameras, numCameras);
				capture_continue = false;
				break;
			}

		} while (iResult > 0);
	}
	

		
	// shutdown the send half of the connection since no more data will be sent
	// the client can still use the ConnectSocket for receiving data
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) 
	{
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}


	

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	cout << "Capture Finished!" << endl;
	cout << "write all the image to disk. " << endl;



	// write all the images to disk after finished capture
	// need to be modified for RAID 
	//for( int imageCount= seq_num-1; imageCount >= 0 ; imageCount--)
	//{

	//	for ( int cam_num = numCameras-1; cam_num >= 0 ; cam_num-- )
	//	{
	//		write_out_image(ppCameras[cam_num], Image_Seq[cam_num][imageCount], cam_num, imageCount, output_fd);
	//		
	//		//delete Image_Seq[cam_num][imageCount];
	//	}
	//	cout << imageCount << " for all image is saved" << endl;

	//	
	//}

	/*for ( int cam_num = numCameras-1; cam_num >= 0 ; cam_num-- )
	{
		delete [] Image_Seq[cam_num];
	}*/


	delete [] Image_temp;


	////////// *STEP 5* Disconnecting the Client
	closesocket(ConnectSocket);
	WSACleanup();




	// Turn trigger mode off.
	triggerMode.onOff = false;
	for ( unsigned int i = 0; i < numCameras; i++)
	{
	
		error = ppCameras[i]->SetTriggerMode( &triggerMode );
		if (error != PGRERROR_OK)
		{
			PrintError( error );
			return -1;
		}
		cout << "Camera " << i << " trigger has been turn off" << endl;
	}

	
	for ( unsigned int i = 0; i < numCameras; i++)
	{
		error  = ppCameras[i]->WriteRegister( k_cameraMemory, regMemVal );
		printf("Restore to Factory setting!\n");
	}
	

	for ( int i = numCameras-1; i >= 0 ; i-- )
	{
		CameraInfo camInfo;
		error = ppCameras[i]->GetCameraInfo( &camInfo );

		cout << "delete Camera " << camInfo.serialNumber  << endl;

		//ppCameras[i]->StopCapture();
		//ppCameras[i]->Disconnect();
		delete ppCameras[i];

		cout << "Camera " << camInfo.serialNumber << " is deleted!" << endl;
	}

	delete [] ppCameras;

	cout << "Done! Press Enter to exit..." << endl;
	cin.ignore();

	return 0;
}
