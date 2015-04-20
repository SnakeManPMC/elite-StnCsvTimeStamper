#include <QCoreApplication>
#include "timestamper.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	TimeStamper stn;
	stn.RunMe(argc, argv);

	return 0;
}
