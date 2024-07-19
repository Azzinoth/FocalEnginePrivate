#include "FESceneManager.h"
using namespace FocalEngine;

FESceneManager* FESceneManager::Instance = nullptr;

FESceneManager::FESceneManager()
{
}

FEScene* FESceneManager::GetScene(std::string ID)
{
	if (SceneMap.find(ID) == SceneMap.end())
		return nullptr;

	return SceneMap[ID];
}

FEScene* FESceneManager::CreateScene(bool bActive, std::string Name, std::string ForceObjectID)
{
	FEScene* Scene = new FEScene();
	Scene->bActive = bActive;

	if (Name.empty())
		Scene->SetName(Name);

	if (!ForceObjectID.empty())
		Scene->ID = ForceObjectID;

	SceneMap[Scene->GetObjectID()] = Scene;
	if (bActive)
	{
		ActiveSceneMap[Scene->GetObjectID()] = Scene;
		RegisterAllComponentCallbacks(Scene);
	}

	return Scene;
}

void FESceneManager::RegisterAllComponentCallbacks(FEScene* NewScene)
{
	NewScene->Registry.on_construct<FETagComponent>().connect<&FESceneManager::OnComponentConstructWrapper<FETagComponent>>();
	NewScene->Registry.on_construct<FETransformComponent>().connect<&FESceneManager::OnComponentConstructWrapper<FETransformComponent>>();
	NewScene->Registry.on_construct<FELightComponent>().connect<&FESceneManager::OnComponentConstructWrapper<FELightComponent>>();
	NewScene->Registry.on_construct<FEGameModelComponent>().connect<&FESceneManager::OnComponentConstructWrapper<FEGameModelComponent>>();
	NewScene->Registry.on_construct<FEInstancedComponent>().connect<&FESceneManager::OnComponentConstructWrapper<FEInstancedComponent>>();
	NewScene->Registry.on_construct<FETerrainComponent>().connect<&FESceneManager::OnComponentConstructWrapper<FETerrainComponent>>();
	NewScene->Registry.on_construct<FESkyDomeComponent>().connect<&FESceneManager::OnComponentConstructWrapper<FESkyDomeComponent>>();

	NewScene->Registry.on_destroy<FETagComponent>().connect<&FESceneManager::OnComponentDestroyWrapper<FETagComponent>>();
	NewScene->Registry.on_destroy<FETransformComponent>().connect<&FESceneManager::OnComponentDestroyWrapper<FETransformComponent>>();
	NewScene->Registry.on_destroy<FELightComponent>().connect<&FESceneManager::OnComponentDestroyWrapper<FELightComponent>>();
	NewScene->Registry.on_destroy<FEGameModelComponent>().connect<&FESceneManager::OnComponentDestroyWrapper<FEGameModelComponent>>();
	NewScene->Registry.on_destroy<FEInstancedComponent>().connect<&FESceneManager::OnComponentDestroyWrapper<FEInstancedComponent>>();
	NewScene->Registry.on_destroy<FETerrainComponent>().connect<&FESceneManager::OnComponentDestroyWrapper<FETerrainComponent>>();
	NewScene->Registry.on_destroy<FESkyDomeComponent>().connect<&FESceneManager::OnComponentDestroyWrapper<FESkyDomeComponent>>();

	NewScene->Registry.on_update<FETagComponent>().connect<&FESceneManager::OnComponentUpdateWrapper<FETagComponent>>();
	NewScene->Registry.on_update<FETransformComponent>().connect<&FESceneManager::OnComponentUpdateWrapper<FETransformComponent>>();
	NewScene->Registry.on_update<FELightComponent>().connect<&FESceneManager::OnComponentUpdateWrapper<FELightComponent>>();
	NewScene->Registry.on_update<FEGameModelComponent>().connect<&FESceneManager::OnComponentUpdateWrapper<FEGameModelComponent>>();
	NewScene->Registry.on_update<FEInstancedComponent>().connect<&FESceneManager::OnComponentUpdateWrapper<FEInstancedComponent>>();
	NewScene->Registry.on_update<FETerrainComponent>().connect<&FESceneManager::OnComponentUpdateWrapper<FETerrainComponent>>();
	NewScene->Registry.on_update<FESkyDomeComponent>().connect<&FESceneManager::OnComponentUpdateWrapper<FESkyDomeComponent>>();
}

std::vector<std::string> FESceneManager::GetSceneIDList()
{
	FE_MAP_TO_STR_VECTOR(SceneMap)
}

std::vector<FEScene*> FESceneManager::GetSceneByName(const std::string Name)
{
	std::vector<FEScene*> Result;

	auto SceneIterator = SceneMap.begin();
	while (SceneIterator != SceneMap.end())
	{
		if (SceneIterator->second->GetName() == Name)
			Result.push_back(SceneIterator->second);

		SceneIterator++;
	}

	return Result;
}

void FESceneManager::DeleteScene(std::string ID)
{
	if (SceneMap.find(ID) == SceneMap.end())
		return;

	DeleteScene(SceneMap[ID]);
}

void FESceneManager::DeleteScene(FEScene* Scene)
{
	if (Scene == nullptr)
		return;

	std::string SceneID = Scene->GetObjectID();
	delete Scene;

	if (ActiveSceneMap.find(SceneID) != ActiveSceneMap.end())
		ActiveSceneMap.erase(SceneID);

	// Should scene be deactivated?
	SceneMap.erase(SceneID);
}

void FESceneManager::Update()
{
	auto SceneIterator = ActiveSceneMap.begin();
	while (SceneIterator != ActiveSceneMap.end())
	{
		SceneIterator->second->Update();
		SceneIterator++;
	}
}

std::vector<FEScene*> FESceneManager::GetAllScenes()
{
	std::vector<FEScene*> Result;

	auto SceneIterator = SceneMap.begin();
	while (SceneIterator != SceneMap.end())
	{
		Result.push_back(SceneIterator->second);
		SceneIterator++;
	}

	return Result;
}

std::vector<FEScene*> FESceneManager::GetActiveScenes()
{
	std::vector<FEScene*> Result;

	auto SceneIterator = ActiveSceneMap.begin();
	while (SceneIterator != ActiveSceneMap.end())
	{
		Result.push_back(SceneIterator->second);
		SceneIterator++;
	}

	return Result;
}