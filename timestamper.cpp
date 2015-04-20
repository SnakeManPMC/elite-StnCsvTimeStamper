#include "timestamper.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

TimeStamper::TimeStamper()
{

}

TimeStamper::~TimeStamper()
{

}

void TimeStamper::RunMe(int argc, char *argv[])
{
	//Check_Parameters(argc, argv);
	if (argc < 2)
	{
		printf("Incorrect parameters supplied.\nUsage:\n\nexe SOURCE.csv\n\n");
		exit(1);
	}

	// 1 copy the output file parameter into variable
	//strcpy(output_file, argv[1]);

	QFile file(argv[1]);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		printf("Unable to open source CSV file");
		exit(1);
	}
	QTextStream in(&file);

	QString timestampedcsv;
	timestampedcsv = argv[1];
	timestampedcsv.append("_TimeStamped.csv");
	QFile stampedfile(timestampedcsv);
	if (!stampedfile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		printf("Unable to create destination CSV file");
		exit(1);
	}
	QTextStream stamped(&stampedfile);

	QString line;
	QStringList list;
	// header
	line = in.readLine();
	stamped << line << "\n";

	QDateTime date = QDateTime::currentDateTimeUtc();
	QString utctime = date.toString("yyyy-MM-dd HH:mm:ss");

	while (!in.atEnd())
	{
		line = in.readLine();
		list = line.split(",");
		list[7] = "'" + utctime + "'";
		stamped << list[0] + "," + list[1] + "," + list[2] + "," + list[3] + "," + list[4] + "," + list[5] + ","
				+ list[6] + "," + list[7] + "," + list[8] + "," + list[9] + "," + list[10] + "," + list[11] << "\n";
	}
	file.close();
	stampedfile.close();
}
