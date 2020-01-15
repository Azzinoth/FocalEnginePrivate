#include "FEResourceManager.h"
using namespace FocalEngine;

FEResourceManager* FEResourceManager::_instance = nullptr;

FETexture* FEResourceManager::createTexture(const char* file_name, std::string Name)
{
	FETexture* newTexture = new FETexture();
	std::vector<unsigned char> rawData;
	unsigned uWidth, uHeight;

	if (Name.size() == 0)
		Name = getFileNameFromFilePath(file_name);

	lodepng::decode(rawData, uWidth, uHeight, file_name);
	newTexture->width = uWidth;
	newTexture->height = uHeight;

	FE_GL_ERROR(glGenTextures(1, &newTexture->textureID));
	FE_GL_ERROR(glBindTexture(GL_TEXTURE_2D, newTexture->textureID));
	FE_GL_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newTexture->width, newTexture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawData.data()));

	if (newTexture->mipEnabled)
	{
		FE_GL_ERROR(glGenerateMipmap(GL_TEXTURE_2D));
		FE_GL_ERROR(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f));// to-do: fix this
		FE_GL_ERROR(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0.0f));
	}

	FE_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	if (newTexture->magFilter == FE_LINEAR)
	{
		FE_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	}
	else
	{
		FE_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	}

	newTexture->setName(Name);
	newTexture->fileName = file_name;

	return newTexture;
}

FEMesh* FEResourceManager::rawDataToMesh(std::vector<float>& positions)
{
	GLuint vaoID;
	FE_GL_ERROR(glGenVertexArrays(1, &vaoID));
	FE_GL_ERROR(glBindVertexArray(vaoID));

	GLuint vboID;
	FE_GL_ERROR(glGenBuffers(1, &vboID));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	FE_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), positions.data(), GL_STATIC_DRAW));
	FE_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));

	FE_GL_ERROR(glBindVertexArray(0));

	return new FEMesh(vaoID, positions.size() / 3, FE_POSITION, FEAABB(positions));
}

FEMesh* FEResourceManager::rawDataToMesh(std::vector<float>& positions, std::vector<float>& normals)
{
	GLuint vaoID;
	FE_GL_ERROR(glGenVertexArrays(1, &vaoID));
	FE_GL_ERROR(glBindVertexArray(vaoID));

	GLuint vboID;
	FE_GL_ERROR(glGenBuffers(1, &vboID));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	FE_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), positions.data(), GL_STATIC_DRAW));
	FE_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));

	// normals
	FE_GL_ERROR(glGenBuffers(1, &vboID));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	FE_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), normals.data(), GL_STATIC_DRAW));
	FE_GL_ERROR(glVertexAttribPointer(2/*FE_NORMAL*/, 3, GL_FLOAT, false, 0, 0));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));

	FE_GL_ERROR(glBindVertexArray(0));

	return new FEMesh(vaoID, positions.size() / 3, FE_POSITION | FE_NORMAL, FEAABB(positions));
}

FEMesh* FEResourceManager::rawDataToMesh(std::vector<float>& positions, std::vector<float>& normals, std::vector<float>& tangents, std::vector<float>& UV, std::vector<int>& index)
{
	GLuint vaoID;
	FE_GL_ERROR(glGenVertexArrays(1, &vaoID));
	FE_GL_ERROR(glBindVertexArray(vaoID));

	GLuint vboID;
	// index
	FE_GL_ERROR(glGenBuffers(1, &vboID));
	FE_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID));
	FE_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * index.size(), index.data(), GL_STATIC_DRAW));

	// verCoords
	FE_GL_ERROR(glGenBuffers(1, &vboID));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	FE_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), positions.data(), GL_STATIC_DRAW));
	FE_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));

	// normals
	FE_GL_ERROR(glGenBuffers(1, &vboID));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	FE_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), normals.data(), GL_STATIC_DRAW));
	FE_GL_ERROR(glVertexAttribPointer(2/*FE_NORMAL*/, 3, GL_FLOAT, false, 0, 0));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));

	// tangents
	FE_GL_ERROR(glGenBuffers(1, &vboID));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	FE_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * tangents.size(), tangents.data(), GL_STATIC_DRAW));
	FE_GL_ERROR(glVertexAttribPointer(3/*FE_TANGENTS*/, 3, GL_FLOAT, false, 0, 0));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));

	// UV
	FE_GL_ERROR(glGenBuffers(1, &vboID));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	FE_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * UV.size(), UV.data(), GL_STATIC_DRAW));
	FE_GL_ERROR(glVertexAttribPointer(4/*FE_UV*/, 2, GL_FLOAT, false, 0, 0));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));

	FE_GL_ERROR(glBindVertexArray(0));

	return new FEMesh(vaoID, index.size(), FE_POSITION | FE_UV | FE_NORMAL | FE_TANGENTS | FE_INDEX, FEAABB(positions));
}

FEMesh* FEResourceManager::rawObjDataToMesh()
{
	FEObjLoader& objLoader = FEObjLoader::getInstance();

	GLuint vaoID;
	FE_GL_ERROR(glGenVertexArrays(1, &vaoID));
	FE_GL_ERROR(glBindVertexArray(vaoID));

	GLuint vboID;
	// index
	FE_GL_ERROR(glGenBuffers(1, &vboID));
	FE_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID));
	FE_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * objLoader.fInd.size(), objLoader.fInd.data(), GL_STATIC_DRAW));

	// verCoords
	FE_GL_ERROR(glGenBuffers(1, &vboID));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	FE_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * objLoader.fVerC.size(), objLoader.fVerC.data(), GL_STATIC_DRAW));
	FE_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));

	// normals
	FE_GL_ERROR(glGenBuffers(1, &vboID));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	FE_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * objLoader.fNorC.size(), objLoader.fNorC.data(), GL_STATIC_DRAW));
	FE_GL_ERROR(glVertexAttribPointer(2/*FE_NORMAL*/, 3, GL_FLOAT, false, 0, 0));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));

	// tangents
	FE_GL_ERROR(glGenBuffers(1, &vboID));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	FE_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * objLoader.fTanC.size(), objLoader.fTanC.data(), GL_STATIC_DRAW));
	FE_GL_ERROR(glVertexAttribPointer(3/*FE_TANGENTS*/, 3, GL_FLOAT, false, 0, 0));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));

	// UV
	FE_GL_ERROR(glGenBuffers(1, &vboID));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vboID));
	FE_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * objLoader.fTexC.size(), objLoader.fTexC.data(), GL_STATIC_DRAW));
	FE_GL_ERROR(glVertexAttribPointer(4/*FE_UV*/, 2, GL_FLOAT, false, 0, 0));
	FE_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));

	FE_GL_ERROR(glBindVertexArray(0));

	return new FEMesh(vaoID, objLoader.fInd.size(), FE_POSITION | FE_UV | FE_NORMAL | FE_TANGENTS | FE_INDEX, FEAABB(objLoader.fVerC));
}

void FEResourceManager::loadStandardMeshes()
{
	if (meshes.find("cube") != meshes.end())
		return;

	std::vector<int> cubeIndices = {
		4, 2, 0, 9, 7, 3, 6, 5,	20,	21,	15,
		22,	10,	12,	18,	8, 1, 19, 4, 17, 2,
		9, 23, 7, 6, 13, 5, 24, 16, 15, 10,
		14, 12, 8, 11, 1
	};

	std::vector<float> cubePositions = {
		1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f
	};

	std::vector<float> cubeNormals = {
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, -1.0f, 0.0f
	};

	std::vector<float> cubeTangents = {
		1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f
	};

	std::vector<float> cubeUV = {
		0.375f, 1.0f, 0.625f, 0.25f, 0.375f, 0.75f,
		0.375f, 0.75f, 0.625f, 1.0f, 0.375f, 0.25f,
		0.625f, 0.5f, 0.375f, 0.5f, 0.875f, 0.5f,
		0.625f, 0.75f, 0.375f, 0.5f, 0.875f, 0.25f,
		0.125f, 0.25f, 0.625f, 0.25f, 0.375f, 0.25f,
		0.375f, 0.0f, 0.625f, 0.0f, 0.625f, 0.75f,
		0.125f, 0.5f, 0.625f, 0.5f, 0.375f, 0.5f,
		0.625f, 0.25f, 0.375f, 0.25f, 0.625f, 0.5f,
		0.625f, 0.25f
	};

	meshes["cube"] = rawDataToMesh(cubePositions, cubeNormals, cubeTangents, cubeUV, cubeIndices);
	meshes["cube"]->setName("cube");

	std::vector<int> planeIndices = {
		0, 1, 2, 3, 0, 2
	};

	std::vector<float> planePositions = {
		-1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f
	};

	std::vector<float> planeNormals = {
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };

	std::vector<float> planeTangents = {
		0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f
	};

	std::vector<float> planeUV = {
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	meshes["plane"] = rawDataToMesh(planePositions, planeNormals, planeTangents, planeUV, planeIndices);
	meshes["plane"]->setName("plane");
}

FEResourceManager::FEResourceManager()
{
	loadStandardMaterial();
	loadStandardMeshes();
}

FEResourceManager::~FEResourceManager()
{
	clear();
}

FEMesh* FEResourceManager::getSimpleMesh(std::string meshName)
{
	if (meshes.find(meshName) != meshes.end())
		return meshes[meshName];

	return nullptr;
}

FEMesh* FEResourceManager::createMesh(const char* fileName, std::string Name)
{
	FEObjLoader& objLoader = FEObjLoader::getInstance();
	objLoader.readFile(fileName);
	FEMesh* newMesh = rawObjDataToMesh();

	if (Name.size() == 0)
		Name = getFileNameFromFilePath(fileName);

	if (meshes.find(Name) != meshes.end())
		Name = "mesh_" + std::to_string(meshes.size());
	
	newMesh->setName(Name);
	newMesh->fileName = fileName;

	meshes[newMesh->getName()] = newMesh;

	return newMesh;
}

FEPostProcess* FEResourceManager::createPostProcess(int ScreenWidth, int ScreenHeight, std::string Name)
{
	return new FEPostProcess(getSimpleMesh("plane"), ScreenWidth, ScreenHeight, Name);
}

FEMaterial* FEResourceManager::createMaterial(std::string Name)
{
	int nextID = int(materials.size());
	if (Name.size())
	{
		// if there is material with that name already
		if (materials.find(Name) != materials.end())
			return nullptr;
	}
	else
	{
		Name = "material_" + std::to_string(nextID);
	}

	materials[Name] = new FEMaterial(nextID, Name);
	return materials[Name];
}

FEEntity* FEResourceManager::createEntity(FEMesh* Mesh, FEMaterial* Material, std::string Name)
{
	return new FEEntity(Mesh, Material, Name);
}

std::vector<std::string> FEResourceManager::getMaterialList()
{
	FE_MAP_TO_STR_VECTOR(materials)
}

FEMaterial* FEResourceManager::getMaterial(std::string name)
{
	if (materials.find(name) == materials.end())
		return nullptr;

	return materials[name];
}

std::string FEResourceManager::getFileNameFromFilePath(std::string filePath)
{
	for (size_t i = filePath.size() - 1; i > 0; i--)
	{
		if (filePath[i] == '\\' || filePath[i] == '/')
			return filePath.substr(i + 1, filePath.size() - 1 - i);
	}

	return std::string("");
}

std::vector<std::string> FEResourceManager::getMeshList()
{
	FE_MAP_TO_STR_VECTOR(meshes)
}

FEMesh* FEResourceManager::getMesh(std::string name)
{
	if (meshes.find(name) == meshes.end())
		return nullptr;

	return meshes[name];
}

void FEResourceManager::loadStandardMaterial()
{
	FEMaterial* newMat = createMaterial("SolidColorMaterial");
	newMat->shader = new FEShader(FESolidColorVS, FESolidColorFS);
	FocalEngine::FEShaderParam color(glm::vec3(1.0f, 0.4f, 0.6f), "baseColor");
	newMat->addParameter(color);
}

void FEResourceManager::clear()
{
	materials.clear();
	meshes.clear();

	loadStandardMaterial();
	loadStandardMeshes();
}

