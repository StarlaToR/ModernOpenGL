#pragma once
#include <iostream>

namespace Resources
{
	class IResource
	{
    public:
        IResource();
        //virtual ~IResource() = 0;

        virtual void loadResource() {}
        virtual void unloadResource() {}

        void setResourceId(unsigned id);

        unsigned int getResourceId() const;

        void setResourcePath(const std::string& path);

        std::string getResourcePath() const;

    protected:
        unsigned int containerId;
        std::string resourcePath;
	};
}