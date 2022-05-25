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

		void Create(const string& path, const string& name)
		{
			T* resource = new T();
			resource->setResourcePath(path);
			resource->setResourceId(mResources.size());
			resource->loadResource();

			mResources.insert(pair<string, IResource*>(name, (IResource*)resource));
		}

		void Add(IResource* resource, const string& name)
		{
			resource->setResourceId(mResources.size());
			resource->loadResource();
			mResources.insert(pair<string, IResource*>(name, resource));
		}
		
		template <typename T>
		T* Get(const string& name)
		{
			auto itr = mResources.find(name);
			if (itr != mResources.end())
				return dynamic_cast<T*>(itr->second);
			else
			{
				cout << "can't get the texture" << endl;
				return nullptr;
			}
		}

		void Delete(const string& path)
		{
			mResources.erase(path);
		}
		
	};
}