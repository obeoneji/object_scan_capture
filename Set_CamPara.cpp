#include "Set_CamPara.hpp"
#include "stdafx.h"
#include <iostream>


void loadConfig_Color(string configName, float* shutterTime,
	float* brightVal, float* gammaVal, float* gainVal,
	unsigned int* sharpVal, unsigned int* redVal, unsigned int* blueVal,
	float* satuVal)
{
	ifstream in;
	string str;

	in.open(configName);

	string kk;

	while (!in.eof())
	{
		while (getline(in, str))
		{
			string::size_type begin = str.find_first_not_of(" \f\t\v");
			//Skips black lines
			if (begin == string::npos)
				continue;
			string firstWord;
			try {
				firstWord = str.substr(0, str.find(" "));
			}
			catch (std::exception &e) {
				firstWord = str.erase(str.find_first_of(" "), str.find_first_not_of(" "));
			}
			transform(firstWord.begin(), firstWord.end(), firstWord.begin(), ::toupper);

			if (firstWord == "SHUTTER_SPEED_C")
				*shutterTime = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "BRIGHT_VALUE_C")
				*brightVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "GAMMA_VALUE_C")
				*gammaVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "GAIN_VALUE_C")
				*gainVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "SHARP_VALUE_C")
				*sharpVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "RED_VALUE_C")
				*redVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "BLUE_VALUE_C")
				*blueVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "SATU_VALUE_C")
				*satuVal = stof(str.substr(str.find(" ") + 1, str.length()));
		}
	}


	std::cout << "color_camera_shutter_Speed is " << *shutterTime << std::endl;
	std::cout << "color_camera_bright_Value is " << *brightVal << std::endl;
	std::cout << "color_camera_gamma_Value is " << *gammaVal << std::endl;
	std::cout << "color_camera_gain_Value is " << *gainVal << std::endl;
	std::cout << "color_camera_sharp_Value is " << *sharpVal << std::endl;
	std::cout << "color_camera_red_Value is " << *redVal << std::endl;
	std::cout << "color_camera_blue_Value is " << *blueVal << std::endl;
	std::cout << "color_camera_satu_Value is " << *satuVal << std::endl;
}

void loadConfig_IR(string configName, float* shutterTime,
	float* brightVal, float* gammaVal, float* gainVal,
	unsigned int* sharpVal, float* satuVal)
{
	ifstream in;
	string str;

	in.open(configName);

	string kk;

	while (!in.eof())
	{
		while (getline(in, str))
		{
			string::size_type begin = str.find_first_not_of(" \f\t\v");
			//Skips black lines
			if (begin == string::npos)
				continue;
			string firstWord;
			try {
				firstWord = str.substr(0, str.find(" "));
			}
			catch (std::exception &e) {
				firstWord = str.erase(str.find_first_of(" "), str.find_first_not_of(" "));
			}
			transform(firstWord.begin(), firstWord.end(), firstWord.begin(), ::toupper);

			if (firstWord == "SHUTTER_SPEED_IR")
				*shutterTime = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "BRIGHT_VALUE_IR")
				*brightVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "GAMMA_VALUE_IR")
				*gammaVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "GAIN_VALUE_IR")
				*gainVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "SHARP_VALUE_IR")
				*sharpVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "SATU_VALUE_IR")
				*satuVal = stof(str.substr(str.find(" ") + 1, str.length()));
		}
	}

	cout << "IR_shutter_Speed is " << *shutterTime << endl;
	cout << "IR_bright_Value is " << *brightVal << endl;
	cout << "IR_gamma_Value is " << *gammaVal << endl;
	cout << "IR_gain_Value is " << *gainVal << endl;
	cout << "IR_sharp_Value is " << *sharpVal << endl;
	cout << "IR_satu_Value is " << *satuVal << endl;
}


void loadConfig_gh(string configName, float* shutterTime, 
	float* brightVal, float* gammaVal, float* gainVal, 
	unsigned int* sharpVal, unsigned int* redVal, unsigned int* blueVal, 
	float* satuVal )
{
	ifstream in;
	string str;

	in.open(configName);

	string kk;

	while (!in.eof())
	{
		while (getline(in,str))
		{
			string::size_type begin = str.find_first_not_of(" \f\t\v");
			//Skips black lines
			if( begin == string::npos)
				continue;
			string firstWord;
			try {
				firstWord = str.substr(0, str.find(" "));
			}
			catch (std::exception &e) {
				firstWord = str.erase(str.find_first_of(" "), str.find_first_not_of(" "));
			}
			transform(firstWord.begin(), firstWord.end(), firstWord.begin(), ::toupper);

			if (firstWord == "SHUTTER_SPEED")
				*shutterTime = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "BRIGHT_VALUE_G")
				*brightVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "GAMMA_VALUE_G")
				*gammaVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "GAIN_VALUE_G")
				*gainVal = stof(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "SHARP_VALUE_G")
				*sharpVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "RED_VALUE_G")
				*redVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "BLUE_VALUE_G")
				*blueVal = stoi(str.substr(str.find(" ") + 1, str.length()));
			if (firstWord == "SATU_VALUE_G")
				*satuVal = stof(str.substr(str.find(" ") + 1, str.length()));
		}
	}
}

void loadConfig_sn(string configName, unsigned int *total_ang, unsigned int *pattern_num, unsigned int *seq_num,  char* server_addr, char* folder_path)
{

	ifstream in;
	string str;

	in.open(configName);

	string kk;
	string server_tmp;
	string file_folder_tmp;

	

	while (!in.eof())
	{
		while (getline(in,str))
		{
			string::size_type begin = str.find_first_not_of(" \f\t\v");
			//Skips black lines
			if( begin == string::npos)
				continue;
			string firstWord;
			try {
				firstWord = str.substr(0, str.find(" "));
			}
			catch (std::exception &e) {
				firstWord = str.erase(str.find_first_of(" "), str.find_first_not_of(" "));
			}
			transform(firstWord.begin(), firstWord.end(), firstWord.begin(), ::toupper);

			if (firstWord == "ROT_ANG")
			{
				int rot_ang = stoi(str.substr(str.find(" ") + 1, str.length()));
				*total_ang = 360 / rot_ang;
			}
			if (firstWord == "SEQ_NUM")
			{
				*seq_num = stoi(str.substr(str.find(" ") + 1, str.length()));
			}
			if (firstWord == "PATTERN_NUM")
			{
				*pattern_num = stoi(str.substr(str.find(" ") + 1, str.length()));
			}
			if (firstWord == "SERVER_IP")
			{
				server_tmp = (str.substr(str.find(" ") + 1, str.length()));
				strcpy(server_addr, server_tmp.c_str());
			}
			if (firstWord == "FOLDER_PATH")
			{
				file_folder_tmp = (str.substr(str.find(" ") + 1, str.length()));
				strcpy(folder_path, file_folder_tmp.c_str());
			}

		}
	}
}


void PrintError_setPara( Error error )
{
	error.PrintErrorTrace();
}

int setIRCameraPara(Camera *ptCam, float shutter_time, float brightVal, float gammaVal, float gainVal, float satuVal, unsigned int sharpVal)
{
	FlyCapture2::Error error;

	int setError;

	setError = setCameraBrightness(ptCam, brightVal);
	if (setError != 0)
	{
		return -1;
	}

	setError = setCameraSaturation(ptCam, satuVal);
	if (setError != 0)
	{
		return -1;
	}

	setError = setCameraShutterSpd(ptCam, shutter_time);
	if (setError != 0)
	{
		return -1;
	}

	setError = setCameraAutoExpo(ptCam);
	if (setError != 0)
	{
		return -1;
	}

	setError = setCameraGamma(ptCam, gammaVal);
	if (setError != 0)
	{
		return -1;
	}

	setError = setCameraGain(ptCam, gainVal);
	if (setError != 0)
	{
		return -1;
	}

	setError = setCameraSharpness(ptCam, sharpVal);
	if (setError != 0)
	{
		return -1;
	}

	if (error != PGRERROR_OK)
	{
		PrintError_setPara(error);
		return -1;
	}

	return 0;

}


int setColorCameraPara(Camera *ptCam, float shutter_time, float brightVal, float gammaVal, float gainVal, float satuVal, unsigned int sharpVal, unsigned int redVal, unsigned int blueVal)
{
	FlyCapture2::Error error;

	int setError;
	setError = setCameraBrightness(ptCam, brightVal);
	if (setError != 0)
	{
		return -1;
	}

	setError = setCameraSaturation(ptCam, satuVal);
	if (setError != 0)
	{
		return -1;
	}

	setError = setCameraShutterSpd(ptCam, shutter_time);
	if (setError != 0)
	{
		return -1;
	}

	setError = setCameraAutoExpo(ptCam);
	if (setError != 0)
	{
		return -1;
	}

	setError = setCameraGamma(ptCam, gammaVal);
	if (setError != 0)
	{
		return -1;
	}

	setError = setCameraGain(ptCam, gainVal);
	if (setError != 0)
	{
		return -1;
	}

	setError = setCameraSharpness(ptCam, sharpVal);
	if (setError != 0)
	{
		return -1;
	}

	setError = setCameraWB(ptCam, redVal, blueVal);
	if (setError != 0)
	{
		return -1;
	}


	if (error != PGRERROR_OK)
	{
		PrintError_setPara(error);
		return -1;
	}

	return 0;
}

int setCameraShutterSpd( Camera *ptCam, float shutter_time )
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property shutterSpd;
	//Define the property to adjust.
	shutterSpd.type = SHUTTER;
	//Ensure the property is on.
	shutterSpd.onOff = true;
	//Ensure auto-adjust mode is off.
	shutterSpd.autoManualMode = false;
	//Ensure the property is set up to use absolute value control.
	shutterSpd.absControl = true;
	//Set the absolute value of shutter to 20 ms.
	shutterSpd.absValue = shutter_time;
	//Set the property.
	error = ptCam->SetProperty( &shutterSpd );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}



int setCameraBrightness( Camera *ptCam, float brightVal)
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property brightness;
	//Define the property to adjust.
	brightness.type = BRIGHTNESS;
	//Ensure the property is set up to use absolute value control.
	brightness.absControl = true;
	//Set the absolute value of brightness to 0.5.
	brightness.absValue = brightVal;
	//Set the property.
	error = ptCam->SetProperty( &brightness );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;

}

int setCameraAutoExpo( Camera *ptCam)
{
	FlyCapture2::Error error;

	Property autoExpo;
	//Define the property to adjust.
	autoExpo.type = AUTO_EXPOSURE;
	//Ensure the property is on.
	autoExpo.onOff = false;
	//Ensure auto-adjust mode is off.
	autoExpo.autoManualMode = false;
	//Ensure the property is set up to use absolute value control.
	autoExpo.absControl = true;
	//Set the property.
	error = ptCam->SetProperty( &autoExpo );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}

int setCameraGamma(Camera *ptCam, float gammaVal)
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property gammaProp;
	//Define the property to adjust.
	gammaProp.type = GAMMA;
	//Ensure the property is on.
	gammaProp.onOff = true;
	//Ensure the property is set up to use absolute value control.
	gammaProp.absControl = true;
	//Set the absolute value of gain to 1 dB.
	gammaProp.absValue = gammaVal;
	//Set the property.	

	error = ptCam->SetProperty( &gammaProp );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}

int setCameraGain( Camera *ptCam, float gainVal)
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property gainProp;
	//Define the property to adjust.
	gainProp.type = GAIN;
	//Ensure auto-adjust mode is off.
	gainProp.autoManualMode = false;
	//Ensure the property is set up to use absolute value control.
	gainProp.absControl = true;
	//Set the absolute value of gain to 1 dB.
	gainProp.absValue = gainVal;
	//Set the property.	

	error = ptCam->SetProperty( &gainProp );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}

int setCameraSharpness( Camera *ptCam, unsigned int sharpVal)
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property sharp;
	//Define the property to adjust.
	sharp.type = SHARPNESS;
	//Ensure the property is on.
	sharp.onOff = true;
	//Ensure auto-adjust mode is off.
	sharp.autoManualMode = false;
	//Set the value of sharpness to 1500.
	sharp.valueA = sharpVal;
	//Set the property.
	error = ptCam->SetProperty( &sharp );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}


int setCameraWB( Camera *ptCam, unsigned int redVal, unsigned int blueVal)
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property WBprop;
	//Define the property to adjust.
	WBprop.type = WHITE_BALANCE;
	//Ensure the property is on.
	WBprop.onOff = true;
	//Ensure auto-adjust mode is off.
	WBprop.autoManualMode = false;
	//Set the white balance red channel to 500.
	WBprop.valueA = redVal;
	//Set the white balance blue channel to 750.
	WBprop.valueB = blueVal;
	//Set the property.
	error = ptCam->SetProperty( &WBprop );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}

int setCameraSaturation( Camera *ptCam, float satuVal)
{
	FlyCapture2::Error error;

	//Declare a Property struct.
	Property saturation;
	//Define the property to adjust.
	saturation.type = SATURATION;
	//Ensure the property is on.
	saturation.onOff = true;
	//Ensure auto-adjust mode is off.
	saturation.autoManualMode = false;
	//Ensure the property is set up to use absolute value control.
	saturation.absControl = true;
	//Set the value of saturation to 75.0.
	saturation.absValue = satuVal;
	//Set the property.
	error = ptCam->SetProperty( &saturation );
	if (error != PGRERROR_OK)
	{
		PrintError_setPara( error );
		return -1;
	}

	return 0;
}

bool PollForTriggerReady(Camera* pCam)
{
	const unsigned int k_softwareTrigger = 0x62C;
	Error error;
	unsigned int regVal = 0;

	do
	{
		error = pCam->ReadRegister(k_softwareTrigger, &regVal);
		if (error != PGRERROR_OK)
		{
			error.PrintErrorTrace();
			return false;
		}

	} while ((regVal >> 31) != 0);

	return true;
}


TriggerMode setTriggerMode(Camera *ptCam)
{

	TriggerMode triggerMode;
	FlyCapture2::Error error;
	TriggerModeInfo triggerModeInfo;

	error = ptCam->GetTriggerModeInfo(&triggerModeInfo);
	if (error != PGRERROR_OK)
	{
		error.PrintErrorTrace();
	}

	if (triggerModeInfo.present != true)
	{
		cout << "Camera does not support external trigger! Exiting..." << endl;
	}


	// Get current trigger settings

	error = ptCam->GetTriggerMode(&triggerMode);
	if (error != PGRERROR_OK)
	{
		error.PrintErrorTrace();
	}

	// Set camera to trigger mode 0
	triggerMode.onOff = true;
	triggerMode.mode = 0;
	triggerMode.parameter = 0;
	triggerMode.source = 2;

	error = ptCam->SetTriggerMode(&triggerMode);
	if (error != PGRERROR_OK)
	{
		error.PrintErrorTrace();
	}

	// Poll to ensure camera is ready
	bool retVal = PollForTriggerReady(ptCam);
	if (!retVal)
	{
		cout << endl;
		cout << "Error polling for trigger ready!" << endl;
	}


	// Get the camera configuration
	FC2Config config;
	error = ptCam->GetConfiguration(&config);
	if (error != PGRERROR_OK)
	{
		error.PrintErrorTrace();
	}



	// Set the grab timeout to 100 seconds
	config.grabTimeout = 100000;

	// Set the camera configuration
	error = ptCam->SetConfiguration(&config);
	if (error != PGRERROR_OK)
	{
		error.PrintErrorTrace();
	}

	return triggerMode;
}



void stopAllCamera(Camera** ppCameras, int numCameras)
{
	FlyCapture2::Error error;

	for (int i = numCameras - 1; i >= 0; i--)
	{
		CameraInfo camInfo;
		error = ppCameras[i]->GetCameraInfo(&camInfo);

		cout << "set Camera " << camInfo.serialNumber << " to stop " << endl;

		ppCameras[i]->StopCapture();
		//ppCameras[i]->Disconnect();
		delete ppCameras[i];

		cout << "Camera " << camInfo.serialNumber << " is stopped!" << endl;
	}
}
