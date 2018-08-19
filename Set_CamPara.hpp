#include "FlyCapture2.h"
#include <fstream>
#include <algorithm>


#include "stdafx.h"

using namespace std;
using namespace FlyCapture2;

bool PollForTriggerReady(Camera* pCam);

int setCameraShutterSpd( Camera *ptCam, float shutter_time );
int setCameraBrightness( Camera *ptCam, float brightVal);
int setCameraAutoExpo( Camera *ptCam);
int setCameraGamma(Camera *ptCam, float gammaVal);
int setCameraGain( Camera *ptCam, float gainVal);
int setCameraSharpness( Camera *ptCam, unsigned int sharpVal);
int setCameraWB( Camera *ptCam, unsigned int redVal, unsigned int blueVal);
int setCameraSaturation( Camera *ptCam, float satuVal);
int setColorCameraPara(Camera *ptCam, float shutter_time, float brightVal, float gammaVal, float gainVal, float satuVal, unsigned int sharpVal, unsigned int redVal, unsigned int blueVal);
int setIRCameraPara(Camera *ptCam, float shutter_time, float brightVal, float gammaVal, float gainVal, float satuVal, unsigned int sharpVal);
TriggerMode setTriggerMode(Camera *ptCam);
void PrintError_setPara( Error error );
void loadConfig_Color(string configName, float* shutterTime,
	float* brightVal, float* gammaVal, float* gainVal,
	unsigned int* sharpVal, unsigned int* redVal, unsigned int* blueVal,
	float* satuVal);

void stopAllCamera(Camera** ppCameras, int numCameras);


void loadConfig_IR(string configName, float* shutterTime, 
	float* brightVal, float* gammaVal, float* gainVal, 
	unsigned int* sharpVal,	float* satuVal );
void loadConfig_sn(string configName, unsigned int *total_ang, unsigned int *pattern_num, unsigned int *seq_num,  char* server_addr, char* folder_path);

