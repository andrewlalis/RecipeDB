#!/bin/sh
#Builds a static release of the RecipeDB program for linux.
echo "Building static release..."
qmake
make -C /home/andrew/Programming/Projects/RecipeDB/staticBuild_Linux/ clean
PATH=/home/andrew/Programming/Qt5_10static/bin:$PATH
export PATH
make -C /home/andrew/Programming/Projects/RecipeDB/staticBuild_Linux/
echo "Done!"