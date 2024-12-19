#include<fstream>
#include<stdlib.h>
#include<iostream>
#include<cstdio>
#include<thread>
#include<windows.h>
static bool endpro=0;
static int temp_low=45;
static int temp_high=50;
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // hide
using namespace std;
string cmdPopen(const string& cmdLine) {
	char buffer[550] = { '\0' };
	FILE* pf = _popen(cmdLine.c_str(), "r");
	if (pf == NULL) {
		printf("open pipe failed\n");
		return "";
	}
	string ret;
	while (fgets(buffer, sizeof(buffer), pf)) {
		ret += buffer;
	}
	_pclose(pf);
	return ret;
}
int get_temp(){
	string output=cmdPopen("\"C:\\Program Files\\crosec\\ectool.exe\" temps 2");
	//cout<<output;
	int temp;
	string temp_string;
	/*
	for(int i=0;i<output.length();++i){
		if(output[i]=='C'&&output[i+1]=='P'){
			temp_string=output.substr(i+31,2);
			cout<<i;
			break;
		}
	}*/
	/*temp_string=output.substr(129,2);
	cout<<temp_string;
	temp=stoi(temp_string,0,10);//old*/
	temp=output[120]*100+output[121]*10+output[122]-5601;
	//cout<<temp;
	return temp;
	
}
void autoend(){
	Sleep(1800000);
	//endpro=1;	
}
void fanctrl(){
	bool fan=1;
	system("\"C:\\Program Files\\crosec\\ectool.exe\" thermalset 2 0 363 373 323 353");
	system("\"C:\\Program Files\\crosec\\ectool.exe\" autofanctrl");
	//cout<<temp_low<<endl<<temp_high;
	//int error=0;
	while(endpro==0){
		Sleep(5000);
		int temp=get_temp();
		//cout<<temp;
		if(temp<=temp_low&&fan){
			
				system("\"C:\\Program Files\\crosec\\ectool.exe\" pwmsetfanrpm 0");
				fan=0;	
			
			
		}
		else if(!fan&&temp>temp_high){
				system("\"C:\\Program Files\\crosec\\ectool.exe\" autofanctrl");
				fan=1;
				Sleep(30000);
			}
		
	}
	return;
}

void batteryctrl(){
	SYSTEM_POWER_STATUS powerStatus;
	while(endpro==0){
		if(!GetSystemPowerStatus(&powerStatus)){
			system("\"C:\\Program Files\\crosec\\ectool.exe\" chargecurrentlimit 3400");
			Sleep(1800000);
			continue;
		}
		string output = cmdPopen("\"C:\\Program Files\\crosec\\ectool.exe\" battery");
		int a=((output[207]-'0')*1000+(output[208]-'0')*100+(output[209]-'0')*10);
		int b=((output[373]-'0')*1000+(output[374]-'0')*100+(output[375]-'0')*10);
		system(("\"C:\\Program Files\\crosec\\ectool.exe\" chargecurrentlimit "+to_string(a-b)).c_str());
		Sleep(300000);
	}
}
int main(){
	ifstream ifstr;
	ifstr.open("config.txt");
	//string config;
	//ifstr>>config;
	//cout<<config;
	int cfg[10];
	for(int i=0;i<10;++i){
		ifstr>>cfg[i];
	}
	/*int index=0,buffer=0;
	bool read=0;
	for(int i=0;config[i]!=0;++i){
		if(read){
			if(config[i]==';'){
				read=0;
				cfg[index]=buffer;
				++index;
				buffer=0;
			}
			else{
				buffer=buffer*10+config[i]-'0';
			}
			
		}
		else if(config[i]=='='){
			read=1;
		}
	}*/
	bool batctrl=cfg[0];
	if(cfg[1]<cfg[2]){
		temp_low=cfg[1];
		temp_high=cfg[2];
	}
	//cout<<temp_low<<endl<<temp_high;
	HWND hwnd;
	hwnd=FindWindow("ConsoleWindowClass",NULL);	//处理顶级窗口的类名和窗口名称匹配指定的字符串,不搜索子窗口。
	if(hwnd){
		ShowWindow(hwnd,SW_HIDE);				//设置指定窗口的显示状态
	}
	thread a(fanctrl),b(autoend);
	if(batctrl){
		thread c(batteryctrl);
		c.join();
	}
	a.join();
	b.join();
	return 0;
}
