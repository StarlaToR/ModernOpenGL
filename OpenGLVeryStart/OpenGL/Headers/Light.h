#pragma once
#include <Maths.h>

namespace LowRenderer
{
	class Light
	{
	private:
		
	public:
		int type;
		Vec3 ambientColor;
		Vec3 diffuseColor;
		Vec3 specularColor;
		Vec3 direction;
		Vec3 position;
	};

	class PointLight : public Light
	{
	public:
		PointLight(const Vec3& pos, const Vec3& color)
		{
			type = 1;
			position = pos;
			ambientColor = color;
			diffuseColor = color;
			specularColor = color;
		}

		PointLight(const Vec3& pos, const Vec3& amb, const Vec3& diff, const Vec3& spec)
		{
			type = 1;
			position = pos;
			ambientColor = amb;
			diffuseColor = diff;
			specularColor = spec;
		}
	};

	class DirectionnalLight : public Light
	{
	public:
		DirectionnalLight(const Vec3& dir, const Vec3& color)
		{
			type = 2;
			direction = dir;
			ambientColor = color;
			diffuseColor = color;
			specularColor = color;
		}

		DirectionnalLight(const Vec3& dir, const Vec3& amb, const Vec3& diff, const Vec3& spec)
		{
			type = 2;
			direction = dir;
			ambientColor = amb;
			diffuseColor = diff;
			specularColor = spec;
		}
	};

	class SpotLight : public Light
	{
	public:
		SpotLight(const Vec3& dir, const Vec3& pos, const Vec3& color)
		{
			type = 3;
			direction = dir;
			position = pos;
			ambientColor = color;
			diffuseColor = color;
			specularColor = color;
		}

		SpotLight(const Vec3& dir, const Vec3& pos, const Vec3& amb, const Vec3& diff, const Vec3& spec)
		{
			type = 3;
			direction = dir;
			position = pos;
			ambientColor = amb;
			diffuseColor = diff;
			specularColor = spec;
		}
	};
}