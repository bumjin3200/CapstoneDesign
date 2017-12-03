#ifndef GETDATA_H
#define GETDATA_H

#include <QThread>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <QString>

using namespace::std;

class getdata : public QThread
{
    Q_OBJECT
public:
    getdata():QThread(){}
    void run()
    {
        myfifo = "/tmp/myfifo";
        while(1){
            fflush(stdin);
            fd = open(myfifo, O_RDONLY);
            read(fd,buf,1024);
	    if(buf!=""){
 	    QString input = QString(buf);
	    if(input.length() < 5 || input.length() >12)
		continue;
 //           QString input("2/500/1200/600/200");
	    setCircle(input);
//	    do_make(100,100,100);
           }

	}
        close(fd);
    }
    int fd;
    char *myfifo;
    char buf[1024];
    int x;
    int y;
    int r;
	
	
	void setCircle(QString input_data);
	void do_make(int _x,int _y,int _r);
signals:
    void make(int,int,int);
};
#endif // GETDATA_H
