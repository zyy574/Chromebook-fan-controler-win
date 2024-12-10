
#include<stdlib.h>
#include<iostream>
#include<cstdio>
#include<thread>
#include<windows.h>
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // hide
using namespace std;
string cmdPopen(const string& cmdLine) {
	char buffer[1024] = { '\0' };
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
	temp_string=output.substr(129,2);
	//cout<<temp_string;
	temp=stoi(temp_string,0,10);
	return temp;
	
}
void fanctrl(){
	bool fan=1;
	system("\"C:\\Program Files\\crosec\\ectool.exe\" thermalset 2 0 363 373 323 353");
	system("\"C:\\Program Files\\crosec\\ectool.exe\" autofanctrl");
	while(1){
		Sleep(2000);
		int temp=get_temp();
		//cout<<temp;
		if(temp<=45){
			if(fan){
				system("\"C:\\Program Files\\crosec\\ectool.exe\" pwmsetfanrpm 0");
				fan=0;	
			}
			
		}
		else{
			if(!fan&&temp>55){
				system("\"C:\\Program Files\\crosec\\ectool.exe\" autofanctrl");
				fan=1;
				Sleep(30000);
			}
		}
	}
}
/*
void batteryctrl(){
	while(1){
		Sleep(600000);
	}
}*/
int main(){
	HWND hwnd;
	hwnd=FindWindow("ConsoleWindowClass",NULL);	//处理顶级窗口的类名和窗口名称匹配指定的字符串,不搜索子窗口。
	if(hwnd){
		ShowWindow(hwnd,SW_HIDE);				//设置指定窗口的显示状态
	}
	thread a(fanctrl);//,b(batteryctrl);
	a.join();
	//b.join();
	return 0;
}
