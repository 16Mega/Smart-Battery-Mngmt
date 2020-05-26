//Smart Battery Manager
//Written by Carson Goodwin 5-18-2020

#include <iostream>
#include <windows.h>

using namespace std;

void PlugStatus(bool Onoff){
	PROCESS_INFORMATION ProcessInfo;
	STARTUPINFO StartupInfo;
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo;
	if(Onoff==true){
		CreateProcess( "Turn-On.bat",NULL,NULL,NULL,FALSE,0,NULL,NULL,&StartupInfo,&ProcessInfo);
		//cout<<"Charger Enabled";
	}
	else{
		CreateProcess( "Turn-Off.bat",NULL,NULL,NULL,FALSE,0,NULL,NULL,&StartupInfo,&ProcessInfo);
		//cout<<"Charger Disabled";
	}
}

int stopCharge(bool&monitorVar){
	SYSTEM_POWER_STATUS spsPwr;
	int batteryVar = 0;
	//cout<<"Under Construction"<<endl;
	PlugStatus(false);//turn off smart plug.
	monitorVar=true;
	while(monitorVar==true){
    	if( GetSystemPowerStatus(&spsPwr) ) {
			batteryVar=static_cast<int>(spsPwr.BatteryLifePercent);
    	}
    	Sleep(1000);
    	//cout<<batteryVar<<endl;
    	if(batteryVar<=55){//when battery falls below 55, start charging
    		PlugStatus(true);
    		return 0;
		}
	}
}

void monitor(bool&monitorVar){
	SYSTEM_POWER_STATUS spsPwr;
	int batteryVar = 0;//initialize our int to store current battery life.
	//cout<<"Enabled"<<endl;
	while(monitorVar==true){
    	if( GetSystemPowerStatus(&spsPwr) ) {
			batteryVar=static_cast<int>(spsPwr.BatteryLifePercent);//get battery life percentage as an int.
    	}
    	Sleep(1000);
    	//cout<<batteryVar<<endl;
    	if(batteryVar>=65){//if battery is more than 65 percent, stop monitoring and stop charging.
    		monitorVar=false;
    		stopCharge(monitorVar);
		}
	}
}

int main(int argc, char *argv[]) {
	bool monitorVar = true;//this variable controls wether or not we should monitor our charge status.
	PlugStatus(true);//Set the plug status to "on" every time we start the program to avoid issues"
	SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED); //Turn off sleep mode in order to be able to run this program with the display shut off
	monitor(monitorVar);// start monitoring.
}
