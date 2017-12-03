#include <iostream>
#include <unistd.h>

using namespace::std;
int main()
{
	cout << "Start system"<<endl;
	pid_t pid;
	pid = fork();
	if( pid > 0)
	{
		execl("getSound1","getSound1",NULL);
		return 0;
	}
	pid = fork();
	if( pid > 0)
	{
		execl("getSound2","getSound2",NULL);
		return 0;
	}
//	pid = fork();
//	if( pid > 0)
//	{
//		execl("getImpulse1","getImpulse1",NULL);
//		return 0;
//	}
//	execl("getImpulse2","getImpulse2",NULL);
}
