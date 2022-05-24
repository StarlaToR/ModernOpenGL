#pragma once
#include <Maths.h>

namespace LowRenderer
{
	class Light
	{
	public:
		Vec3 ambientColor;
		Vec3 diffuseColor;
		Vec3 specularColor;
	};

	class PointLight : public Light
	{
	public:
		Vec3 position;

		float constant;
		float linear;
		float quadratic;

		PointLight(const Vec3& pos, const Vec3& color, float cons, float lin, float quad)
		{
			position = pos;
			ambientColor = color * 0.1f;
			diffuseColor = color * 0.5f;
			specularColor = color * 1.f;
			constant = cons;
			linear = lin;
			quadratic = quad;
		}

		PointLight(const Vec3& pos, const Vec3& amb, const Vec3& diff, const Vec3& spec, float cons, float lin, float quad)
		{
			position = pos;
			ambientColor = amb;
			diffuseColor = diff;
			specularColor = spec;
			constant = cons;
			linear = lin;
			quadratic = quad;
		}
	};

	class DirectionnalLight : public Light
	{
	public:
		Vec3 direction;

		DirectionnalLight(const Vec3& dir, const Vec3& color)
		{
			direction = dir;
			ambientColor = color * 0.1f;
			diffuseColor = color * 0.5f;
			specularColor = color * 1.f;
		}

		DirectionnalLight(const Vec3& dir, const Vec3& amb, const Vec3& diff, const Vec3& spec)
		{
			direction = dir;
			ambientColor = amb;
			diffuseColor = diff;
			specularColor = spec;
		}
	};

	class SpotLight : public Light
	{
	public:
		Vec3 position;
		Vec3 direction;

		float constant;
		float linear;
		float quadratic;

		float angle;  //only between M_PI / 3.1 and 0

		SpotLight(const Vec3& dir, const Vec3& pos, const Vec3& color, float cons, float lin, float quad, float ang)
		{
			direction = dir;
			position = pos;
			ambientColor = color * 0.1f;
			diffuseColor = color * 0.5f;
			specularColor = color * 1.f;
			constant = cons;
			linear = lin;
			quadratic = quad;
			angle = ang;
		}

		SpotLight(const Vec3& dir, const Vec3& pos, const Vec3& amb, const Vec3& diff, const Vec3& spec, float cons, float lin, float quad, float ang)
		{
			direction = dir;
			position = pos;
			ambientColor = amb;
			diffuseColor = diff;
			specularColor = spec;
			constant = cons;
			linear = lin;
			quadratic = quad;
			angle = ang;
		}
	};
}