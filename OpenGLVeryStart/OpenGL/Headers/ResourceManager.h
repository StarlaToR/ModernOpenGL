#pragma once
#include <iostream>
#include <IResource.h>
#include <unordered_map>

using namespace std;

namespace Resources
{
	class ResourceManager
	{
	private:
		unordered_map<string, IResource*> mResources = {};

	public:
		ResourceManager()
		{
		}
		
		template <typename T>

		T* Create(const string& path, const string& name)
		{
			T* resource = new T();
			resource->setResourcePath(path);
			resource->setResourceId(mResources.size());
			resource->loadResource(path);

			mResources.insert(pair<string, IResource*>(path, (IResource*)resource));

			return resource;
		}

		void Add(IResource* resource, const string& name)
		{
			resource->setResourceId(mResources.size());
			mResources.insert(pair<string, IResource*>(name, resource));
		}
		
		template <typename T>
		T* Get(const string& path)
		{
			return dynamic_cast<T*>(mResources.find(path)->second);
		}

		void Delete(const string& path)
		{
			mResources.erase(path);
		}
		
	};
}