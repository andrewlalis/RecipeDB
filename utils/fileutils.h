#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QTextStream>

#include "model/recipe/instruction.h"

namespace FileUtils {

	QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.recipeDB/";

	void ensureAppDataFolderExists(){
		QDir folder(appDataPath);
		if (!folder.exists()){
			folder.mkpath(".");
		}
	}

	void saveInstruction(int nr, Instruction instruction){
		ensureAppDataFolderExists();
		QString filename = appDataPath + QString::fromStdString(std::to_string(nr)) +".html";
		QFile file(filename);
		if (file.open(QIODevice::WriteOnly)){
			QTextStream stream(&file);
			stream<<instruction.getHTML().c_str()<<endl;
			file.close();
		} else {
			fprintf(stderr, "Error opening file: %s to write instruction.\n", filename.toStdString().c_str());
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

}

#endif // FILEUTILS_H
