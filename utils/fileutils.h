#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QImage>

#include "model/recipe/instruction.h"

namespace FileUtils{

	const QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.recipeDB/";

	void ensureAppDataFolderExists();

	bool saveInstruction(int nr, Instruction instruction);

	Instruction loadInstruction(int nr);

	bool saveImage(int nr, QImage image);

	QImage loadImage(int nr);
}

#endif // FILEUTILS_H
