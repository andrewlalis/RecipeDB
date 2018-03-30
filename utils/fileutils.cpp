#include "fileutils.h"

namespace FileUtils{

void ensureAppDataFolderExists(){
	QDir folder(appDataPath);
	if (!folder.exists()){
		folder.mkpath(".");
	}
}

bool saveInstruction(int nr, Instruction instruction){
	ensureAppDataFolderExists();
	QString filename = appDataPath + QString::fromStdString(std::to_string(nr)) +".html";
	QFile file(filename);
	if (file.open(QIODevice::WriteOnly)){
		QTextStream stream(&file);
		stream<<instruction.getHTML().c_str()<<endl;
		file.close();
		return true;
	} else {
		fprintf(stderr, "Error opening file: %s to write instruction.\n", filename.toStdString().c_str());
		return false;
	}
}

Instruction loadInstruction(int nr){
	QString filename = appDataPath + QString::fromStdString(std::to_string(nr)) + ".html";
	QFile file(filename);
	if (!file.exists()){
		fprintf(stderr, "Instruction Nr: %d does not exist.\n", nr);
		return Instruction();
	}
	if (file.open(QIODevice::ReadOnly)){
		QTextStream stream(&file);
		QString s = stream.readAll();
		file.close();
		return Instruction(s.toStdString());
	} else {
		fprintf(stderr, "Error opening file: %s to read instruction.\n", filename.toStdString().c_str());
		return Instruction();
	}
}

bool saveImage(int nr, QImage image){
	QString filename = appDataPath + QString::fromStdString(std::to_string(nr)) + ".png";
	QFile file(filename);
	if (file.open(QIODevice::WriteOnly)){
		image.save(&file, "PNG");
		file.close();
		return true;
	} else {
		fprintf(stderr, "Error saving image to file: %s\n", filename.toStdString().c_str());
		return false;
	}
}

QImage loadImage(int nr){
	QString filename = appDataPath + QString::fromStdString(std::to_string(nr)) + ".png";
	QImage img(filename);
	return img;
}

bool deleteInstruction(int nr){
	ensureAppDataFolderExists();
	QString filename = appDataPath + QString::fromStdString(std::to_string(nr)) +".html";
	QFile file(filename);
	return file.remove();
}

bool deleteImage(int nr){
	ensureAppDataFolderExists();
	QString filename = appDataPath + QString::fromStdString(std::to_string(nr)) +".png";
	QFile file(filename);
	return file.remove();
}

}
