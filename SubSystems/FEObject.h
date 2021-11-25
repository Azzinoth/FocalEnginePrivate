#pragma once

#ifndef FEOBJECT_H
#define FEOBJECT_H

#include "FELog.h"

namespace FocalEngine
{
	enum FEObjectType
	{
		FE_NULL = 0,
		FE_SHADER = 1,
		FE_TEXTURE = 2,
		FE_MESH = 3,
		FE_MATERIAL = 4,
		FE_GAMEMODEL = 5,
		FE_ENTITY = 6,
		FE_TERRAIN = 7,
		FE_ENTITY_INSTANCED = 8,
		FE_DIRECTIONAL_LIGHT = 9,
		FE_POINT_LIGHT = 10,
		FE_SPOT_LIGHT = 11,
		FE_CAMERA = 12,
		FE_FRAME_BUFFER = 13,
		FE_POST_PROCESS = 14,
		FE_TERRAIN_LAYER = 15
	};

	class FEObject;
	class FEngine;
	class FERenderer;
	class FEResourceManager;
	class FEScene;

	class FEObjectManager
	{
		friend FEObject;
		friend FEngine;
		friend FERenderer;
		friend FEResourceManager;
		friend FEScene;
	public:
		SINGLETON_PUBLIC_PART(FEObjectManager)
		FEObject* getFEObject(std::string ID);
	private:
		SINGLETON_PRIVATE_PART(FEObjectManager)
		std::unordered_map<std::string, FEObject*> allObjects;
		std::vector<std::unordered_map<std::string, FEObject*>> objectsByType;
	};

	static std::string FEObjectTypeToString(FEObjectType type)
	{
		switch (type)
		{
			case FocalEngine::FE_NULL:
			{
				return "FE_NULL";
				break;
			}
			case FocalEngine::FE_SHADER:
			{
				return "FE_SHADER";
				break;
			}
			case FocalEngine::FE_TEXTURE:
			{
				return "FE_TEXTURE";
				break;
			}
			case FocalEngine::FE_MESH:
			{
				return "FE_MESH";
				break;
			}
			case FocalEngine::FE_MATERIAL:
			{
				return "FE_MATERIAL";
				break;
			}
			case FocalEngine::FE_GAMEMODEL:
			{
				return "FE_GAMEMODEL";
				break;
			}
			case FocalEngine::FE_ENTITY:
			{
				return "FE_ENTITY";
				break;
			}
			
			case FocalEngine::FE_TERRAIN:
			{
				return "FE_TERRAIN";
				break;
			}
			case FocalEngine::FE_ENTITY_INSTANCED:
			{
				return "FE_ENTITY_INSTANCED";
				break;
			}
			case FocalEngine::FE_DIRECTIONAL_LIGHT:
			{
				return "FE_DIRECTIONAL_LIGHT";
				break;
			}
			case FocalEngine::FE_POINT_LIGHT:
			{
				return "FE_POINT_LIGHT";
				break;
			}
			case FocalEngine::FE_SPOT_LIGHT:
			{
				return "FE_SPOT_LIGHT";
				break;
			}
			case FocalEngine::FE_CAMERA:
			{
				return "FE_CAMERA";
				break;
			}
			case FocalEngine::FE_FRAME_BUFFER:
			{
				return "FE_FRAME_BUFFER";
				break;
			}
			case FocalEngine::FE_POST_PROCESS:
			{
				return "FE_POST_PROCESS";
				break;
			}
			default:
				break;
		}

		return "FE_NULL";
	}

	class FEShader;
	class FEMesh;
	class FETexture;
	class FEMaterial;
	class FEGameModel;
	class FEEntity;
	class FETerrain;
	class FEEntityInstanced;
	class FEScene;

	class FEObject
	{
		friend FEngine;
		friend FEShader;
		friend FEMesh;
		friend FETexture;
		friend FEMaterial;
		friend FEGameModel;
		friend FEEntity;
		friend FETerrain;
		friend FEEntityInstanced;
		friend FEResourceManager;
		friend FEScene;
	public:
		FEObject(FEObjectType objectType, std::string objectName);
		~FEObject();

		std::string getObjectID() const;
		FEObjectType getType() const;

		bool getDirtyFlag();
		void setDirtyFlag(bool newDirtyFlag);

		std::string getName();
		void setName(std::string newName);
		int getNameHash();

		void setIDOfUnTyped(std::string newID);
	private:
		std::string ID = "";
		FEObjectType type = FE_NULL;
		bool dirtyFlag = false;

		std::string name;
		int nameHash = 0;
		void setID(std::string newID);
		void setType(FEObjectType newType);
	protected:
		std::vector<std::string> callListOnDeleteFEObject;
		virtual void processOnDeleteCallbacks(std::string deletingFEObject);
	};
}

#endif FEOBJECT_H