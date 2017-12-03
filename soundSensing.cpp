#include <stdlib.h>
#include <iostream>
#include <string>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <math.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

using namespace::std;

//----------grobal variables---------
int fd;
int fd_myfifo;
char myfifo[] = "/tmp/myfifo";
char device[] = "/dev/ttyACM0";
unsigned int _baud = 9600;
unsigned int _time = 0;
string result;
//-----------------------------------
//--------function--------
int setup();
void loop();
string charstoString(char word);
string* StringSplit(string strTarget, string strTok);
void sendCircle(string data);
//-----------------------------
//----------data type----------
//------------------------------
int main()
{
	int setup_data;
	setup_data = setup();
	if(setup_data <0 )
		return 0;
	while(1) loop();
	unlink(myfifo);
}
int setup()
{
	cin.clear();
	fd = serialOpen(device, _baud);
	if (fd < 0)//ERROR001
	{
		cout << "Error001 : Unable to open serial device." << endl;
		return -1;
	}
	if (wiringPiSetup() == -1)//ERROR002
	{
		cout << "Error002 : Unable to start wiringPi" << endl;
		return -2;
	}
}
void loop()
{
	cin.clear();	
	if (serialDataAvail(fd)) {
		char newChar = serialGetchar(fd);
		string temp = charstoString(newChar); // data from sensors
		if (temp != "")
		{
			sendCircle(temp);
			cin.clear();
		}
	}
}
void sendCircle(string data)
{
	mkfifo(myfifo,0666);
	fd_myfifo = open(myfifo, O_WRONLY);
	write(fd_myfifo,data.c_str(),sizeof(char)*1024);
	close(fd_myfifo);
}
string charstoString(char word)
{
	if (word != '\n')
		result = result + word;
	else
	{
		string temp = result;
		result = "";
		return temp;
	}
	return "";
}

string* StringSplit(string strTarget, string strTok)
{
	int     nCutPos;
	int     nIndex = 0;
	string* strResult = new string[5];

	while ((nCutPos = strTarget.find_first_of(strTok)) != strTarget.npos)
	{
		if (nCutPos > 0)
		{
			strResult[nIndex++] = strTarget.substr(0, nCutPos);
		}
		strTarget = strTarget.substr(nCutPos + 1);
	}

	if (strTarget.length() > 0)
	{
		strResult[nIndex++] = strTarget.substr(0, nCutPos);
	}

	return strResult;
}
