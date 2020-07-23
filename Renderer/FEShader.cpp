#include "FEShader.h"
using namespace FocalEngine;

FEShaderParam::FEShaderParam()
{
	data = nullptr;
}

FEShaderParam::FEShaderParam(int Data, std::string Name)
{
	data = new int(Data);
	type = FE_INT_SCALAR_UNIFORM;
	name = Name;
}

FEShaderParam::FEShaderParam(float Data, std::string Name)
{
	data = new float(Data);
	type = FE_FLOAT_SCALAR_UNIFORM;
	name = Name;
}

FEShaderParam::FEShaderParam(glm::vec2 Data, std::string Name)
{
	data = new glm::vec2(Data);
	type = FE_VECTOR2_UNIFORM;
	name = Name;
}

FEShaderParam::FEShaderParam(glm::vec3 Data, std::string Name)
{
	data = new glm::vec3(Data);
	type = FE_VECTOR3_UNIFORM;
	name = Name;
}

FEShaderParam::FEShaderParam(glm::vec4 Data, std::string Name)
{
	data = new glm::vec4(Data);
	type = FE_VECTOR4_UNIFORM;
	name = Name;
}

FEShaderParam::FEShaderParam(glm::mat4 Data, std::string Name)
{
	data = new glm::mat4(Data);
	type = FE_MAT4_UNIFORM;
	name = Name;
}

void FEShaderParam::updateData(int Data)
{
	if (type != FE_INT_SCALAR_UNIFORM)
		return; // to-do: error
	*(int*)data = Data;
}

void FEShaderParam::updateData(float Data)
{
	if (type != FE_FLOAT_SCALAR_UNIFORM)
		return; // to-do: error
	*(float*)data = Data;
}

void FEShaderParam::updateData(glm::vec2 Data)
{
	if (type != FE_VECTOR2_UNIFORM)
		return; // to-do: error
	*(glm::vec2*)data = Data;
}

void FEShaderParam::updateData(glm::vec3 Data)
{
	if (type != FE_VECTOR3_UNIFORM)
		return; // to-do: error
	*(glm::vec3*)data = Data;
}

void FEShaderParam::updateData(glm::vec4 Data)
{
	if (type != FE_VECTOR4_UNIFORM)
		return; // to-do: error
	*(glm::vec4*)data = Data;
}

void FEShaderParam::updateData(glm::mat4 Data)
{
	if (type != FE_MAT4_UNIFORM)
		return; // to-do: error
	*(glm::mat4*)data = Data;
}

void FEShaderParam::copyCode(const FEShaderParam& copy)
{
	switch (copy.type)
	{
		case FE_INT_SCALAR_UNIFORM:
		{
			data = new int;
			*(int*)data = *((int*)copy.data);
			break;
		}

		case FE_FLOAT_SCALAR_UNIFORM:
		{
			data = new float;
			*(float*)data = *((float*)copy.data);
			break;
		}

		case FE_VECTOR2_UNIFORM:
		{
			data = new glm::vec2;
			*(glm::vec2*)data = *((glm::vec2*)copy.data);
			break;
		}

		case FE_VECTOR3_UNIFORM:
		{
			data = new glm::vec3;
			*(glm::vec3*)data = *((glm::vec3*)copy.data);
			break;
		}

		case FE_VECTOR4_UNIFORM:
		{
			data = new glm::vec4;
			*(glm::vec4*)data = *((glm::vec4*)copy.data);
			break;
		}

		case FE_MAT4_UNIFORM:
		{
			data = new glm::mat4;
			*(glm::mat4*)data = *((glm::mat4*)copy.data);
			break;
		}

		default:
			break;
	}
}

FEShaderParam::FEShaderParam(const FEShaderParam& copy)
{
	this->type = copy.type;
	this->name = copy.name;
	this->loadedFromEngine = copy.loadedFromEngine;

	copyCode(copy);
}

void FEShaderParam::operator=(const FEShaderParam& assign)
{
	this->~FEShaderParam();
	this->type = assign.type;
	this->name = assign.name;
	this->loadedFromEngine = assign.loadedFromEngine;

	copyCode(assign);
}

FEShaderParam::~FEShaderParam()
{
	if (data == nullptr)
		return;

	switch (type)
	{
		case FE_INT_SCALAR_UNIFORM:
		{
			delete (int*)data;
			break;
		}
	
		case FE_FLOAT_SCALAR_UNIFORM:
		{
			delete (float*)data;
			break;
		}
	
		case FE_VECTOR2_UNIFORM:
		{
			delete (glm::vec2*)data;
			break;
		}
	
		case FE_VECTOR3_UNIFORM:
		{
			delete (glm::vec3*)data;
			break;
		}
	
		case FE_VECTOR4_UNIFORM:
		{
			delete (glm::vec4*)data;
			break;
		}
	
		case FE_MAT4_UNIFORM:
		{
			delete (glm::mat4*)data;
			break;
		}
	
		default:
			break;
	}
}

std::string FEShaderParam::getName()
{
	return name;
}

void FEShaderParam::setName(std::string newName)
{
	name = newName;
}

FEShader::FEShader(std::string name, const char* vertexText, const char* fragmentText,
				   const char* tessControlText, const char* tessEvalText,
				   const char* geometryText, const char* computeText, bool testCompilation)
{
	testCompilationMode = testCompilation;
	setName(name);
	vertexShaderID = loadShader(vertexText, GL_VERTEX_SHADER);
	size_t textLenght = strlen(vertexText);
	vertexShaderText = new char[textLenght + 1];
	strcpy_s(vertexShaderText, textLenght + 1, vertexText);

	if (tessControlText != nullptr)
	{
		tessControlShaderID = loadShader(tessControlText, GL_TESS_CONTROL_SHADER);
		size_t textLenght = strlen(tessControlText);
		tessControlShaderText = new char[textLenght + 1];
		strcpy_s(tessControlShaderText, textLenght + 1, tessControlText);
	}

	if (tessEvalText != nullptr)
	{
		tessEvalShaderID = loadShader(tessEvalText, GL_TESS_EVALUATION_SHADER);
		size_t textLenght = strlen(tessEvalText);
		tessEvalShaderText = new char[textLenght + 1];
		strcpy_s(tessEvalShaderText, textLenght + 1, tessEvalText);
	}

	if (geometryText != nullptr)
	{
		geometryShaderID = loadShader(geometryText, GL_GEOMETRY_SHADER);
		size_t textLenght = strlen(geometryText);
		geometryShaderText = new char[textLenght + 1];
		strcpy_s(geometryShaderText, textLenght + 1, geometryText);
	}

	fragmentShaderID = loadShader(fragmentText, GL_FRAGMENT_SHADER);
	textLenght = strlen(fragmentText);
	fragmentShaderText = new char[textLenght + 1];
	strcpy_s(fragmentShaderText, textLenght + 1, fragmentText);

	if (computeText != nullptr)
	{
		testCompilationMode = testCompilation;
		computeShaderID = loadShader(computeText, GL_COMPUTE_SHADER);
		size_t textLenght = strlen(computeText);
		computeShaderText = new char[textLenght + 1];
		strcpy_s(computeShaderText, textLenght + 1, computeText);
	}

	if (testCompilationMode && compilationErrors.size() != 0)
		return;

	FE_GL_ERROR(programID = glCreateProgram());
	FE_GL_ERROR(glAttachShader(programID, vertexShaderID));
	if (tessControlText != nullptr)
		FE_GL_ERROR(glAttachShader(programID, tessControlShaderID));
	if (tessEvalText != nullptr)
		FE_GL_ERROR(glAttachShader(programID, tessEvalShaderID));
	if (geometryText != nullptr)
		FE_GL_ERROR(glAttachShader(programID, geometryShaderID));

	FE_GL_ERROR(glAttachShader(programID, fragmentShaderID));

	if (computeText != nullptr)
		FE_GL_ERROR(glAttachShader(programID, computeShaderID));

	bindAttributes();

	FE_GL_ERROR(glLinkProgram(programID));
	FE_GL_ERROR(glValidateProgram(programID)); // too slow ?

	FE_GL_ERROR(glDeleteShader(vertexShaderID));
	if (tessControlText != nullptr)
		FE_GL_ERROR(glDeleteShader(tessControlShaderID));
	if (tessEvalText != nullptr)
		FE_GL_ERROR(glDeleteShader(tessEvalShaderID));
	if (geometryText != nullptr)
		FE_GL_ERROR(glDeleteShader(geometryShaderID));

	FE_GL_ERROR(glDeleteShader(fragmentShaderID));

	if (computeText != nullptr)
		FE_GL_ERROR(glDeleteShader(computeShaderID));

	registerUniforms();
}

FEShader::~FEShader()
{
	cleanUp();
}

void FEShader::registerUniforms()
{
	GLint count;
	GLint size;
	GLenum type;

	const GLsizei bufSize = 64;
	GLchar name[bufSize];
	GLsizei length;

	FE_GL_ERROR(glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &count));
	for (size_t i = 0; i < size_t(count); i++)
	{
		FE_GL_ERROR(glGetActiveUniform(programID, (GLuint)i, bufSize, &length, &size, &type, name));
		
		switch (type)
		{
			case GL_INT:
			{
				addParameter(FEShaderParam(0, name));
				break;
			}

			case GL_FLOAT:
			{
				addParameter(FEShaderParam(0.0f, name));
				break;
			}

			case GL_FLOAT_VEC2:
			{
				addParameter(FEShaderParam(glm::vec2(0.0f), name));
				break;
			}

			case GL_FLOAT_VEC3:
			{
				addParameter(FEShaderParam(glm::vec3(0.0f), name));
				break;
			}

			case GL_FLOAT_VEC4:
			{
				addParameter(FEShaderParam(glm::vec4(0.0f), name));
				break;
			}

			case GL_FLOAT_MAT4:
			{
				addParameter(FEShaderParam(glm::mat4(1.0f), name));
				break;
			}

			default:
				break;
		}
	}

	// uniformBlocks
	GLuint uniformBlockIndex = -1;
	FE_GL_ERROR(uniformBlockIndex = glGetUniformBlockIndex(programID, "lightInfo"));
	if (uniformBlockIndex != size_t(-1))
	{
		FE_GL_ERROR(glUniformBlockBinding(programID, uniformBlockIndex, 0));
		blockUniforms["lightInfo"] = size_t(-1);
	}

	uniformBlockIndex = -1;
	FE_GL_ERROR(uniformBlockIndex = glGetUniformBlockIndex(programID, "directionalLightInfo"));
	if (uniformBlockIndex != size_t(-1))
	{
		FE_GL_ERROR(glUniformBlockBinding(programID, uniformBlockIndex, 1));
		blockUniforms["directionalLightInfo"] = size_t(-1);
	}

	start();
	for (size_t i = 0; i < textureUniforms.size(); i++)
	{
		int temp = i;
		loadScalar(textureUniforms[i].c_str(), temp);
	}

	if (CSM)
	{
		int temp = 16;
		loadScalar("CSM0", temp);
		temp = 17;
		loadScalar("CSM1", temp);
		temp = 18;
		loadScalar("CSM2", temp);
		temp = 19;
		loadScalar("CSM3", temp);
	}
	stop();
}

GLuint FEShader::loadShader(const char* shaderText, GLuint shaderType)
{
	GLuint shaderID;
	FE_GL_ERROR(shaderID = glCreateShader(shaderType));

	std::string tempString = parseShaderForMacro(shaderText);
	const char *parsedShaderText = tempString.c_str();
	FE_GL_ERROR(glShaderSource(shaderID, 1, &parsedShaderText, nullptr));
	FE_GL_ERROR(glCompileShader(shaderID));
	GLint status = 0;
	FE_GL_ERROR(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status));

	if (status == GL_FALSE) {
		GLint logSize = 0;
		FE_GL_ERROR(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logSize));
		std::vector<GLchar> errorLog(logSize);

		FE_GL_ERROR(glGetShaderInfoLog(shaderID, logSize, &logSize, &errorLog[0]));
		for (size_t i = 0; i < errorLog.size(); i++)
		{
			compilationErrors.push_back(errorLog[i]);
		}
		if (!testCompilationMode)
			assert(status);
	}

	return shaderID;
}

void FEShader::cleanUp()
{
	stop();
	delete[] vertexShaderText;
	delete[] fragmentShaderText;
	FE_GL_ERROR(glDeleteProgram(programID));
}

void FEShader::bindAttributes()
{
	if ((vertexAttributes & FE_POSITION) == FE_POSITION) FE_GL_ERROR(glBindAttribLocation(programID, 0, "FEPosition"));
	if ((vertexAttributes & FE_COLOR) == FE_COLOR) FE_GL_ERROR(glBindAttribLocation(programID, 1, "FEColor"));
	if ((vertexAttributes & FE_NORMAL) == FE_NORMAL) FE_GL_ERROR(glBindAttribLocation(programID, 2, "FENormal"));
	if ((vertexAttributes & FE_TANGENTS) == FE_TANGENTS) FE_GL_ERROR(glBindAttribLocation(programID, 3, "FETangent"));
	if ((vertexAttributes & FE_UV) == FE_UV) FE_GL_ERROR(glBindAttribLocation(programID, 4, "FETexCoord"));
}

void FEShader::start()
{
	FE_GL_ERROR(glUseProgram(programID));
}

void FEShader::stop()
{
	FE_GL_ERROR(glUseProgram(0));
}

std::string FEShader::parseShaderForMacro(const char* shaderText)
{
	size_t index = -1;
	std::string parsedShaderText = shaderText;

	index = parsedShaderText.find(FE_VERTEX_ATTRIBUTE_POSITION);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_VERTEX_ATTRIBUTE_POSITION), "layout (location = 0) in vec3 FEPosition;");
		vertexAttributes |= FE_POSITION;
	}
	index = parsedShaderText.find(FE_VERTEX_ATTRIBUTE_COLOR);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_VERTEX_ATTRIBUTE_COLOR), "layout (location = 1) in vec3 FEColor;");
		vertexAttributes |= FE_COLOR;
	}
	index = parsedShaderText.find(FE_VERTEX_ATTRIBUTE_NORMAL);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_VERTEX_ATTRIBUTE_NORMAL), "layout (location = 2) in vec3 FENormal;");
		vertexAttributes |= FE_NORMAL;
	}
	index = parsedShaderText.find(FE_VERTEX_ATTRIBUTE_TANGENT);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_VERTEX_ATTRIBUTE_TANGENT), "layout (location = 3) in vec3 FETangent;");
		vertexAttributes |= FE_TANGENTS;
	}
	index = parsedShaderText.find(FE_VERTEX_ATTRIBUTE_UV);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_VERTEX_ATTRIBUTE_UV), "layout (location = 4) in vec2 FETexCoord;");
		vertexAttributes |= FE_UV;
	}

	index = parsedShaderText.find(FE_WORLD_MATRIX_MACRO);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_WORLD_MATRIX_MACRO), "uniform mat4 FEWorldMatrix;");
	}

	index = parsedShaderText.find(FE_VIEW_MATRIX_MACRO);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_VIEW_MATRIX_MACRO), "uniform mat4 FEViewMatrix;");
	}

	index = parsedShaderText.find(FE_PROJECTION_MATRIX_MACRO);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_PROJECTION_MATRIX_MACRO), "uniform mat4 FEProjectionMatrix;");
	}

	index = parsedShaderText.find(FE_PVM_MATRIX_MACRO);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_PVM_MATRIX_MACRO), "uniform mat4 FEPVMMatrix;");
	}

	index = parsedShaderText.find(FE_CAMERA_POSITION_MACRO);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_CAMERA_POSITION_MACRO), "uniform vec3 FECameraPosition;");
	}

	index = parsedShaderText.find(FE_LIGHT_POSITION_MACRO);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_LIGHT_POSITION_MACRO), "uniform vec3 FELightPosition;");
	}

	index = parsedShaderText.find(FE_LIGHT_COLOR_MACRO);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_LIGHT_COLOR_MACRO), "uniform vec3 FELightColor;");
	}

	index = parsedShaderText.find(FE_TEXTURE_MACRO);
	while (index != size_t(-1))
	{
		size_t semicolonPos = parsedShaderText.find(";", index);
		std::string textureName = parsedShaderText.substr(index + strlen(FE_TEXTURE_MACRO) + 1, semicolonPos - (index + strlen(FE_TEXTURE_MACRO)) - 1);

		parsedShaderText.replace(index, strlen(FE_TEXTURE_MACRO), "uniform sampler2D");

		// several shaders could use same texture
		bool wasAlreadyDefined = false;
		for (size_t i = 0; i < textureUniforms.size(); i++)
		{
			if (textureName == textureUniforms[i])
			{
				wasAlreadyDefined = true;
				break;
			}
		}

		if (wasAlreadyDefined)
		{
			index = parsedShaderText.find(FE_TEXTURE_MACRO);
			continue;
		}

		// only 16 user textures can be used.
		if (textureUniforms.size() < 16)
			textureUniforms.push_back(textureName);
		index = parsedShaderText.find(FE_TEXTURE_MACRO);
	}

	index = parsedShaderText.find(FE_CSM_MACRO);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_CSM_MACRO), "uniform sampler2D CSM0; uniform sampler2D CSM1; uniform sampler2D CSM2; uniform sampler2D CSM3;");
		CSM = true;
	}

	index = parsedShaderText.find(FE_RECEVESHADOWS_MACRO);
	if (index != size_t(-1))
	{
		parsedShaderText.replace(index, strlen(FE_RECEVESHADOWS_MACRO), "uniform int FEReceiveShadows;");
	}
	
	return parsedShaderText;
}

GLuint FEShader::getUniformLocation(const char* name)
{
	FE_GL_ERROR(return glGetUniformLocation(programID, name));
}

void FEShader::loadScalar(const char* uniformName, GLfloat& value)
{
	FE_GL_ERROR(glUniform1f(getUniformLocation(uniformName), value));
}

void FEShader::loadScalar(const char* uniformName, GLint& value)
{
	FE_GL_ERROR(glUniform1i(getUniformLocation(uniformName), value));
}

void FEShader::loadVector(const char* uniformName, glm::vec2& vector)
{
	FE_GL_ERROR(glUniform2f(getUniformLocation(uniformName), vector.x, vector.y));
}

void FEShader::loadVector(const char* uniformName, glm::vec3& vector)
{
	FE_GL_ERROR(glUniform3f(getUniformLocation(uniformName), vector.x, vector.y, vector.z));
}

void FEShader::loadVector(const char* uniformName, glm::vec4& vector)
{
	FE_GL_ERROR(glUniform4f(getUniformLocation(uniformName), vector.x, vector.y, vector.z, vector.w));
}

void FEShader::loadMatrix(const char* uniformName, glm::mat4& matrix)
{
	FE_GL_ERROR(glUniformMatrix4fv(getUniformLocation(uniformName), 1, false, glm::value_ptr(matrix)));
}

void FEShader::loadDataToGPU()
{
	auto iterator = parameters.begin();
	while (iterator != parameters.end())
	{
		if (iterator->second.data == nullptr)
			continue;

		switch (iterator->second.type)
		{
			case FE_INT_SCALAR_UNIFORM:
			{
				loadScalar(iterator->second.getName().c_str(), *(int*)iterator->second.data);
				break;
			}

			case FE_FLOAT_SCALAR_UNIFORM:
			{
				loadScalar(iterator->second.getName().c_str(), *(float*)iterator->second.data);
				break;
			}

			case FE_VECTOR2_UNIFORM:
			{
				loadVector(iterator->second.getName().c_str(), *(glm::vec2*)iterator->second.data);
				break;
			}

			case FE_VECTOR3_UNIFORM:
			{
				loadVector(iterator->second.getName().c_str(), *(glm::vec3*)iterator->second.data);
				break;
			}

			case FE_VECTOR4_UNIFORM:
			{
				loadVector(iterator->second.getName().c_str(), *(glm::vec4*)iterator->second.data);
				break;
			}

			case FE_MAT4_UNIFORM:
			{
				loadMatrix(iterator->second.getName().c_str(), *(glm::mat4*)iterator->second.data);
				break;
			}

			default:
				break;
		}
		iterator++;
	}
}

void FEShader::addParameter(FEShaderParam Parameter)
{
	bool find = false;
	for (size_t i = 0; i < FEStandardUniforms.size(); i++)
	{
		if (Parameter.getName().find(FEStandardUniforms[i]) != size_t(-1))
			find = true;
	}
	Parameter.loadedFromEngine = find;

	parameters[Parameter.getName()] = Parameter;
}

std::vector<std::string> FEShader::getParameterList()
{
	FE_MAP_TO_STR_VECTOR(parameters)
}

FEShaderParam* FEShader::getParameter(std::string name)
{
	if (parameters.find(name) == parameters.end())
		return nullptr;

	return &parameters[name];
}

std::vector<std::string> FEShader::getTextureList()
{
	return textureUniforms;
}

std::string FEShader::getName()
{
	return name;
}

void FEShader::setName(std::string newName)
{
	name = newName;
	nameHash = std::hash<std::string>{}(name);
}

int FEShader::getNameHash()
{
	return nameHash;
}

char* FEShader::getVertexShaderText()
{
	return vertexShaderText;
}

char* FEShader::getFragmentShaderText()
{
	return fragmentShaderText;
}

std::string FEShader::getCompilationErrors()
{
	return compilationErrors;
}

char* FEShader::getTessControlShaderText()
{
	return tessControlShaderText;
}

char* FEShader::getTessEvalShaderText()
{
	return tessEvalShaderText;
}

char* FEShader::getGeometryShaderText()
{
	return geometryShaderText;
}

char* FEShader::getComputeShaderText()
{
	return computeShaderText;
}

//bool FEShader::addTessControlShader(char* tessControlShader, bool testCompilation)
//{
//	testCompilationMode = testCompilation;
//	tessControlShaderID = loadShader(tessControlShader, GL_TESS_CONTROL_SHADER);
//	size_t textLenght = strlen(tessControlShader);
//	if (tessControlShaderText != nullptr)
//		delete tessControlShaderText;
//	tessControlShaderText = new char[textLenght + 1];
//	strcpy_s(tessControlShaderText, textLenght + 1, tessControlShader);
//
//	if (compilationErrors.size() != 0)
//		return false;
//
//	FE_GL_ERROR(glAttachShader(programID, tessControlShaderID));
//	FE_GL_ERROR(glLinkProgram(programID));
//	FE_GL_ERROR(glValidateProgram(programID));
//
//	FE_GL_ERROR(glDeleteShader(tessControlShaderID));
//
//	return true;
//}
//
//bool FEShader::addTessEvalShader(char* tessEvalShader, bool testCompilation)
//{
//	testCompilationMode = testCompilation;
//	tessEvalShaderID = loadShader(tessEvalShader, GL_TESS_EVALUATION_SHADER);
//	size_t textLenght = strlen(tessEvalShader);
//	if (tessEvalShaderText != nullptr)
//		delete tessEvalShaderText;
//	tessEvalShaderText = new char[textLenght + 1];
//	strcpy_s(tessEvalShaderText, textLenght + 1, tessEvalShader);
//
//	if (compilationErrors.size() != 0)
//		return false;
//
//	FE_GL_ERROR(glAttachShader(programID, tessEvalShaderID));
//	FE_GL_ERROR(glLinkProgram(programID));
//	FE_GL_ERROR(glValidateProgram(programID));
//
//	FE_GL_ERROR(glDeleteShader(tessEvalShaderID));
//
//	return true;
//}
//
//bool FEShader::addGeometryShader(char* geometryShader, bool testCompilation)
//{
//	testCompilationMode = testCompilation;
//	geometryShaderID = loadShader(geometryShader, GL_GEOMETRY_SHADER);
//	size_t textLenght = strlen(geometryShader);
//	if (geometryShaderText != nullptr)
//		delete geometryShaderText;
//	geometryShaderText = new char[textLenght + 1];
//	strcpy_s(geometryShaderText, textLenght + 1, geometryShader);
//
//	if (compilationErrors.size() != 0)
//		return false;
//
//	return true;
//}
//
//bool FEShader::addComputeShader(char* computeShader, bool testCompilation)
//{
//	testCompilationMode = testCompilation;
//	computeShaderID = loadShader(computeShader, GL_COMPUTE_SHADER);
//	size_t textLenght = strlen(computeShader);
//	if (computeShaderText != nullptr)
//		delete computeShaderText;
//	computeShaderText = new char[textLenght + 1];
//	strcpy_s(computeShaderText, textLenght + 1, computeShader);
//
//	if (compilationErrors.size() != 0)
//		return false;
//
//	return true;
//}

