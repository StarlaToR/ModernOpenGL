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

		float* ambientCol;
		float* diffuseCol;
		float* specularCol;
	};

	class PointLight : public Light
	{
	public:
		Vec3 position;
		float* posit;

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

			posit = new float[3]{ pos.x, pos.y, pos.z };
			ambientCol = new float[3]{ ambientColor.x, ambientColor.y, ambientColor.z };
			diffuseCol = new float[3]{ diffuseColor.x, diffuseColor.y, diffuseColor.z };
			specularCol = new float[3]{ specularColor.x, specularColor.y, specularColor.z };
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

			posit = new float[3]{ pos.x, pos.y, pos.z };
			ambientCol = new float[3]{ ambientColor.x, ambientColor.y, ambientColor.z };
			diffuseCol = new float[3]{ diffuseColor.x, diffuseColor.y, diffuseColor.z };
			specularCol = new float[3]{ specularColor.x, specularColor.y, specularColor.z };
		}
	};

	class DirectionnalLight : public Light
	{
	public:
		Vec3 direction;
		float* direct;

		DirectionnalLight(const Vec3& dir, const Vec3& color)
		{
			direction = dir;
			ambientColor = color * 0.1f;
			diffuseColor = color * 0.5f;
			specularColor = color * 1.f;

			direct = new float[3]{ direction.x, direction.y, direction.z };
		}

		DirectionnalLight(const Vec3& dir, const Vec3& amb, const Vec3& diff, const Vec3& spec)
		{
			direction = dir;
			ambientColor = amb;
			diffuseColor = diff;
			specularColor = spec;

			direct = new float[3]{ direction.x, direction.y, direction.z };
		}
	};

	class SpotLight : public Light
	{
	public:
		Vec3 position;
		Vec3 direction;

		float* posit;
		float* direct;

		float constant;
		float linear;
		float quadratic;

		float angle;  //only between M_PI / 3.1 and 0
		float angl;

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

			posit = new float[3]{ pos.x, pos.y, pos.z };
			direct = new float[3]{ dir.x, dir.y, dir.z };
			ambientCol = new float[3]{ ambientColor.x, ambientColor.y, ambientColor.z };
			diffuseCol = new float[3]{ diffuseColor.x, diffuseColor.y, diffuseColor.z };
			specularCol = new float[3]{ specularColor.x, specularColor.y, specularColor.z };
			angl = angle;
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

			posit = new float[3]{ pos.x, pos.y, pos.z };
			direct = new float[3]{ dir.x, dir.y, dir.z };
			ambientCol = new float[3]{ ambientColor.x, ambientColor.y, ambientColor.z };
			diffuseCol = new float[3]{ diffuseColor.x, diffuseColor.y, diffuseColor.z };
			specularCol = new float[3]{ specularColor.x, specularColor.y, specularColor.z };
			angl = angle;
		}
	};
}