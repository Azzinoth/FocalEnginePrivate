#include "FEStandardMaterial.h"
using namespace FocalEngine;

FEStandardMaterial::FEStandardMaterial()
{
	baseColor = glm::vec3(1.0f, 0.4f, 0.6f);
	shaders.push_back(new FEStandardShader());

	setParam("baseColor", baseColor);
}

FEStandardMaterial::~FEStandardMaterial()
{
}