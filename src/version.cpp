#include <iostream>
#include "version.h"

int getProjectBuildNumber()
{
	return PROJECT_VERSION_PATCH;
}

std::string getProjectVersion()
{
    return PROJECT_VERSION;
}
