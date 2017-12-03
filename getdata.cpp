#include "getdata.h"
#include <QThread>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <QStringList>


void getdata::setCircle(QString input_data)
{
	QStringList datalist = input_data.split("/");
	if(datalist.length() <= 2)
		return;
	int datas[datalist.length()]={0};
	for(int i = 0 ; i<datalist.length();i++)
        	datas[i] = datalist[i].toInt();
	do_make(datas[0],datas[1], datas[2]);
}
void getdata::do_make(int _x, int _y, int _r)
{
	emit make(_x,_y,_r);
}

