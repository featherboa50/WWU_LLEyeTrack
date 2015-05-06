// -----------------------------------------------------------------------
//
// (c) Copyright 1997-2014, SensoMotoric Instruments GmbH
// 
// Permission  is  hereby granted,  free  of  charge,  to any  person  or
// organization  obtaining  a  copy  of  the  software  and  accompanying
// documentation  covered  by  this  license  (the  "Software")  to  use,
// reproduce,  display, distribute, execute,  and transmit  the Software,
// and  to  prepare derivative  works  of  the  Software, and  to  permit
// third-parties to whom the Software  is furnished to do so, all subject
// to the following:
// 
// The  copyright notices  in  the Software  and  this entire  statement,
// including the above license  grant, this restriction and the following
// disclaimer, must be  included in all copies of  the Software, in whole
// or  in part, and  all derivative  works of  the Software,  unless such
// copies   or   derivative   works   are   solely   in   the   form   of
// machine-executable  object   code  generated  by   a  source  language
// processor.
// 
// THE  SOFTWARE IS  PROVIDED  "AS  IS", WITHOUT  WARRANTY  OF ANY  KIND,
// EXPRESS OR  IMPLIED, INCLUDING  BUT NOT LIMITED  TO THE  WARRANTIES OF
// MERCHANTABILITY,   FITNESS  FOR  A   PARTICULAR  PURPOSE,   TITLE  AND
// NON-INFRINGEMENT. IN  NO EVENT SHALL  THE COPYRIGHT HOLDERS  OR ANYONE
// DISTRIBUTING  THE  SOFTWARE  BE   LIABLE  FOR  ANY  DAMAGES  OR  OTHER
// LIABILITY, WHETHER  IN CONTRACT, TORT OR OTHERWISE,  ARISING FROM, OUT
// OF OR IN CONNECTION WITH THE  SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// -----------------------------------------------------------------------

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "iViewXAPI.h"
#include "EyeTrackerFunctions.h"
#include <sstream>
#include <stdlib.h>

QPoint * EyePoint;
QPoint * mousePos;
MainWindow * w;
POINT * CursorPos;

// this function will only be executed when a sample is available
int __stdcall SampleCallbackFunctionV2(SampleStruct sampleData)
{
	int x = sampleData.leftEye.gazeX;
	int y = sampleData.leftEye.gazeY;
	std::cout << "From Sample Callback X: " << x << " Y: " << y << std::endl;
	EyePoint->setX(x);
	EyePoint->setY(y);

	GetCursorPos(CursorPos);

	mousePos->setX(CursorPos->x);
	mousePos->setY(CursorPos->y);


	return 1;
}

// this function will only be executed when a tracking monitor image is available
int __stdcall TrackingMonitorCallbackFunction(ImageStruct imageData)
{
	//std::cout << "From TrackingMonitor Callback ImageSize: " << imageData.imageSize << " Width: " << imageData.imageWidth << " Height: " << imageData.imageHeight << std::endl;
	return 1;
}


void onExitV2(){
	iV_SetSampleCallback(NULL);
	iV_SetTrackingMonitorCallback(NULL);

	// disconnect
	iV_Disconnect();

	delete(CursorPos);
}

int Eye_Tracker_Start(QPoint * p, QPoint * mp)
{
	EyePoint = p;
	mousePos = mp;
	CursorPos = new POINT();

	atexit(onExitV2);

	SystemInfoStruct systemInfoData;
	int ret_connect = 0; 


	// define logger 
	iV_SetLogger(1, "iViewXSDK_cpp_Demo.txt");

	// connect to iViewX 
	ret_connect = iV_Connect("127.0.0.1", 4444, "127.0.0.1", 5555);

	switch(ret_connect)
	{
		case RET_SUCCESS:
			//std::cout <<  "Connection was established successfully" << std::endl;
			/*
			// read out meta data from iViewX 
			std::cout << "GetSystemInfo: " << iV_GetSystemInfo(&systemInfoData) << std::endl;
			std::cout << "SystemInfo ETSystem: " << systemInfoData.iV_ETDevice << std::endl;
			std::cout << "SystemInfo iV_Version: " << systemInfoData.iV_MajorVersion << "." << systemInfoData.iV_MinorVersion << "." << systemInfoData.iV_Buildnumber << std::endl;
			std::cout << "SystemInfo API_Version: " << systemInfoData.API_MajorVersion << "." << systemInfoData.API_MinorVersion << "." << systemInfoData.API_Buildnumber << std::endl;
			std::cout << "SystemInfo samplerate: " << systemInfoData.samplerate << std::endl;
			*/

			break;
		case ERR_COULD_NOT_CONNECT:
			std::cout <<  "Connection could not be established" << std::endl;
			return 0;
		case ERR_WRONG_PARAMETER:
			std::cout <<  "Wrong Parameter used" << std::endl;
			return 0;
		default:
			std::cout <<  "Any other error appeared" << std::endl;
			return 0;
	}

	if(ret_connect == RET_SUCCESS)
	{

		// show some windows
		iV_ShowEyeImageMonitor();
		iV_ShowTrackingMonitor();
		//iV_ShowSceneVideoMonitor();



		// start data output via callback function
		// define a callback function for receiving samples 
		
		iV_SetSampleCallback(SampleCallbackFunctionV2);
		iV_SetTrackingMonitorCallback(TrackingMonitorCallbackFunction);

	}

	return 0;
}

