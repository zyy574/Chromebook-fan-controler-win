
#include<stdlib.h>
#include<iostream>
#include<cstdio>
#include<thread>
#include<windows.h>
using namespace std;
string cmdPopen(const string& cmdLine) {
	char buffer[1024] = { '\0' };
	FILE* pf = _popen(cmdLine.c_str(), "r");
	if (pf == NULL) {
		cout << ("open pipe failed\n");
		return "";
	}
	string ret;
	while (fgets(buffer, sizeof(buffer), pf)) {
		ret += buffer;
	}
	_pclose(pf);
	return ret;
}

int main() {
	string output = cmdPopen("\"C:\\Program Files\\crosec\\ectool.exe\" battery");
	//for (int i = 0; output[i] != 0; ++i) {
	//	cout << i << output[i];
	//}
	int a=((output[207]-'0')*1000+(output[208]-'0')*100+(output[209]-'0')*10+10);
	int b=((output[373]-'0')*1000+(output[374]-'0')*100+(output[375]-'0')*10);
	system(("\"C:\\Program Files\\crosec\\ectool.exe\" chargecurrentlimit "+to_string(a-b)).c_str());
	SYSTEM_POWER_STATUS powerStatus;
	GetSystemPowerStatus(&powerStatus);
	cout<<(int)powerStatus.ACLineStatus;
}
