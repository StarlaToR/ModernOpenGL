#include <IResource.h>

using namespace Resources;

IResource::IResource()
{
    containerId = 0;
    resourcePath = "";
}


void IResource::setResourceId(unsigned id)
{
    containerId = id;
}

unsigned int IResource::getResourceId() const
{
    return containerId;
}

void IResource::setResourcePath(const std::string& path)
{
    resourcePath = path;
}

std::string IResource::getResourcePath() const
{
    return resourcePath;
}