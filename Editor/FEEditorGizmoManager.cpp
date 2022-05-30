#include "FEEditorGizmoManager.h"
using namespace FocalEngine;
using namespace FEGizmoManager;

GizmoManager* GizmoManager::_instance = nullptr;
GizmoManager::GizmoManager() {}
GizmoManager::~GizmoManager() {}

void GizmoManager::initializeResources()
{
	SELECTED.setOnUpdateFunc(onSelectedObjectUpdate);
	FEMesh* TransformationGizmoMesh = RESOURCE_MANAGER.loadFEMesh((RESOURCE_MANAGER.getDefaultResourcesFolder() + "45191B6F172E3B531978692E.model").c_str(), "transformationGizmoMesh");
	RESOURCE_MANAGER.makeMeshStandard(TransformationGizmoMesh);

	// transformationXGizmo
	FEMaterial* currentMaterial = RESOURCE_MANAGER.createMaterial("transformationXGizmoMaterial");
	currentMaterial->setAlbedoMap(RESOURCE_MANAGER.noTexture);
	currentMaterial->shader = RESOURCE_MANAGER.getShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	currentMaterial->addParameter(FEShaderParam(glm::vec3(0.9f, 0.1f, 0.1f), "baseColor"));
	RESOURCE_MANAGER.makeMaterialStandard(currentMaterial);
	transformationXGizmoEntity = SCENE.addEntity(new FEGameModel(TransformationGizmoMesh, currentMaterial, "TransformationXGizmoGM"), "transformationXGizmoEntity");
	RESOURCE_MANAGER.makePrefabStandard(transformationXGizmoEntity->prefab);
	RESOURCE_MANAGER.makeGameModelStandard(transformationXGizmoEntity->prefab->getComponent(0)->gameModel);
	transformationXGizmoEntity->setCastShadows(false);
	transformationXGizmoEntity->transform.setScale(glm::vec3(gizmosScale));
	transformationXGizmoEntity->transform.setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
	transformationXGizmoEntity->setIsPostprocessApplied(false);

	// transformationYGizmo
	currentMaterial = RESOURCE_MANAGER.createMaterial("transformationYGizmoMaterial");
	currentMaterial->setAlbedoMap(RESOURCE_MANAGER.noTexture);
	currentMaterial->shader = RESOURCE_MANAGER.getShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	currentMaterial->addParameter(FEShaderParam(glm::vec3(0.1f, 0.9f, 0.1f), "baseColor"));
	RESOURCE_MANAGER.makeMaterialStandard(currentMaterial);
	transformationYGizmoEntity = SCENE.addEntity(new FEGameModel(TransformationGizmoMesh, currentMaterial, "TransformationYGizmoGM"), "transformationYGizmoEntity");
	RESOURCE_MANAGER.makePrefabStandard(transformationYGizmoEntity->prefab);
	RESOURCE_MANAGER.makeGameModelStandard(transformationYGizmoEntity->prefab->getComponent(0)->gameModel);
	transformationYGizmoEntity->setCastShadows(false);
	transformationYGizmoEntity->transform.setScale(glm::vec3(gizmosScale));
	transformationYGizmoEntity->transform.setRotation(glm::vec3(0.0f));
	transformationYGizmoEntity->setIsPostprocessApplied(false);

	// transformationZGizmo
	currentMaterial = RESOURCE_MANAGER.createMaterial("transformationZGizmoMaterial");
	currentMaterial->setAlbedoMap(RESOURCE_MANAGER.noTexture);
	currentMaterial->shader = RESOURCE_MANAGER.getShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	currentMaterial->addParameter(FEShaderParam(glm::vec3(0.1f, 0.1f, 0.9f), "baseColor"));
	RESOURCE_MANAGER.makeMaterialStandard(currentMaterial);
	transformationZGizmoEntity = SCENE.addEntity(new FEGameModel(TransformationGizmoMesh, currentMaterial, "TransformationZGizmoGM"), "transformationZGizmoEntity");
	RESOURCE_MANAGER.makePrefabStandard(transformationZGizmoEntity->prefab);
	RESOURCE_MANAGER.makeGameModelStandard(transformationZGizmoEntity->prefab->getComponent(0)->gameModel);
	transformationZGizmoEntity->setCastShadows(false);
	transformationZGizmoEntity->transform.setScale(glm::vec3(gizmosScale));
	transformationZGizmoEntity->transform.setRotation(glm::vec3(90.0f, 0.0f, 90.0f));
	transformationZGizmoEntity->setIsPostprocessApplied(false);

	// plane gizmos
	currentMaterial = RESOURCE_MANAGER.createMaterial("transformationXYGizmoMaterial");
	currentMaterial->setAlbedoMap(RESOURCE_MANAGER.noTexture);
	currentMaterial->shader = RESOURCE_MANAGER.getShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	currentMaterial->addParameter(FEShaderParam(glm::vec3(1.0f, 1.0f, 1.0f), "baseColor"));
	RESOURCE_MANAGER.makeMaterialStandard(currentMaterial);
	transformationXYGizmoEntity = SCENE.addEntity(new FEGameModel(RESOURCE_MANAGER.getMesh("84251E6E0D0801363579317R"/*"cube"*/), currentMaterial, "TransformationXYGizmoGM"), "transformationXYGizmoEntity");
	RESOURCE_MANAGER.makePrefabStandard(transformationXYGizmoEntity->prefab);
	RESOURCE_MANAGER.makeGameModelStandard(transformationXYGizmoEntity->prefab->getComponent(0)->gameModel);
	transformationXYGizmoEntity->setCastShadows(false);
	transformationXYGizmoEntity->transform.setScale(glm::vec3(gizmosScale, gizmosScale, gizmosScale * 0.02f));
	transformationXYGizmoEntity->transform.setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
	transformationXYGizmoEntity->setIsPostprocessApplied(false);

	currentMaterial = RESOURCE_MANAGER.createMaterial("transformationYZGizmoMaterial");
	currentMaterial->setAlbedoMap(RESOURCE_MANAGER.noTexture);
	currentMaterial->shader = RESOURCE_MANAGER.getShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	currentMaterial->addParameter(FEShaderParam(glm::vec3(1.0f, 1.0f, 1.0f), "baseColor"));
	RESOURCE_MANAGER.makeMaterialStandard(currentMaterial);
	transformationYZGizmoEntity = SCENE.addEntity(new FEGameModel(RESOURCE_MANAGER.getMesh("84251E6E0D0801363579317R"/*"cube"*/), currentMaterial, "TransformationYZGizmoGM"), "transformationYZGizmoEntity");
	RESOURCE_MANAGER.makePrefabStandard(transformationYZGizmoEntity->prefab);
	RESOURCE_MANAGER.makeGameModelStandard(transformationYZGizmoEntity->prefab->getComponent(0)->gameModel);
	transformationYZGizmoEntity->setCastShadows(false);
	transformationYZGizmoEntity->transform.setScale(glm::vec3(gizmosScale * 0.02f, gizmosScale, gizmosScale));
	transformationYZGizmoEntity->transform.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	transformationYZGizmoEntity->setIsPostprocessApplied(false);

	currentMaterial = RESOURCE_MANAGER.createMaterial("transformationXZGizmoMaterial");
	currentMaterial->setAlbedoMap(RESOURCE_MANAGER.noTexture);
	currentMaterial->shader = RESOURCE_MANAGER.getShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	currentMaterial->addParameter(FEShaderParam(glm::vec3(1.0f, 1.0f, 1.0f), "baseColor"));
	RESOURCE_MANAGER.makeMaterialStandard(currentMaterial);
	transformationXZGizmoEntity = SCENE.addEntity(new FEGameModel(RESOURCE_MANAGER.getMesh("84251E6E0D0801363579317R"/*"cube"*/), currentMaterial, "TransformationXZGizmoGM"), "transformationXZGizmoEntity");
	RESOURCE_MANAGER.makePrefabStandard(transformationXZGizmoEntity->prefab);
	RESOURCE_MANAGER.makeGameModelStandard(transformationXZGizmoEntity->prefab->getComponent(0)->gameModel);
	transformationXZGizmoEntity->setCastShadows(false);
	transformationXZGizmoEntity->transform.setScale(glm::vec3(gizmosScale, gizmosScale * 0.02f, gizmosScale));
	transformationXZGizmoEntity->transform.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	transformationXZGizmoEntity->setIsPostprocessApplied(false);

	// scale gizmos
	FEMesh* scaleGizmoMesh = RESOURCE_MANAGER.loadFEMesh((RESOURCE_MANAGER.getDefaultResourcesFolder() + "637C784B2E5E5C6548190E1B.model").c_str(), "scaleGizmoMesh");
	RESOURCE_MANAGER.makeMeshStandard(scaleGizmoMesh);

	// scaleXGizmo
	currentMaterial = RESOURCE_MANAGER.createMaterial("scaleXGizmoMaterial");
	currentMaterial->setAlbedoMap(RESOURCE_MANAGER.noTexture);
	currentMaterial->shader = RESOURCE_MANAGER.getShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	currentMaterial->addParameter(FEShaderParam(glm::vec3(0.9f, 0.1f, 0.1f), "baseColor"));
	RESOURCE_MANAGER.makeMaterialStandard(currentMaterial);
	scaleXGizmoEntity = SCENE.addEntity(new FEGameModel(scaleGizmoMesh, currentMaterial, "scaleXGizmoGM"), "scaleXGizmoEntity");
	RESOURCE_MANAGER.makePrefabStandard(scaleXGizmoEntity->prefab);
	RESOURCE_MANAGER.makeGameModelStandard(scaleXGizmoEntity->prefab->getComponent(0)->gameModel);
	scaleXGizmoEntity->setCastShadows(false);
	scaleXGizmoEntity->transform.setScale(glm::vec3(gizmosScale));
	scaleXGizmoEntity->transform.setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
	scaleXGizmoEntity->setIsPostprocessApplied(false);

	// scaleYGizmo
	currentMaterial = RESOURCE_MANAGER.createMaterial("scaleYGizmoMaterial");
	currentMaterial->setAlbedoMap(RESOURCE_MANAGER.noTexture);
	currentMaterial->shader = RESOURCE_MANAGER.getShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	currentMaterial->addParameter(FEShaderParam(glm::vec3(0.1f, 0.9f, 0.1f), "baseColor"));
	RESOURCE_MANAGER.makeMaterialStandard(currentMaterial);
	scaleYGizmoEntity = SCENE.addEntity(new FEGameModel(scaleGizmoMesh, currentMaterial, "scaleYGizmoGM"), "scaleYGizmoEntity");
	RESOURCE_MANAGER.makePrefabStandard(scaleYGizmoEntity->prefab);
	RESOURCE_MANAGER.makeGameModelStandard(scaleYGizmoEntity->prefab->getComponent(0)->gameModel);
	scaleYGizmoEntity->setCastShadows(false);
	scaleYGizmoEntity->transform.setScale(glm::vec3(gizmosScale));
	scaleYGizmoEntity->transform.setRotation(glm::vec3(0.0f));
	scaleYGizmoEntity->setIsPostprocessApplied(false);

	// scaleZGizmo
	currentMaterial = RESOURCE_MANAGER.createMaterial("scaleZGizmoMaterial");
	currentMaterial->setAlbedoMap(RESOURCE_MANAGER.noTexture);
	currentMaterial->shader = RESOURCE_MANAGER.getShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	currentMaterial->addParameter(FEShaderParam(glm::vec3(0.1f, 0.1f, 0.9f), "baseColor"));
	RESOURCE_MANAGER.makeMaterialStandard(currentMaterial);
	scaleZGizmoEntity = SCENE.addEntity(new FEGameModel(scaleGizmoMesh, currentMaterial, "scaleZGizmoGM"), "scaleZGizmoEntity");
	RESOURCE_MANAGER.makePrefabStandard(scaleZGizmoEntity->prefab);
	RESOURCE_MANAGER.makeGameModelStandard(scaleZGizmoEntity->prefab->getComponent(0)->gameModel);
	scaleZGizmoEntity->setCastShadows(false);
	scaleZGizmoEntity->transform.setScale(glm::vec3(gizmosScale));
	scaleZGizmoEntity->transform.setRotation(glm::vec3(90.0f, 0.0f, 90.0f));
	scaleZGizmoEntity->setIsPostprocessApplied(false);

	// rotate gizmos
	FEMesh* rotateGizmoMesh = RESOURCE_MANAGER.loadFEMesh((RESOURCE_MANAGER.getDefaultResourcesFolder() + "19622421516E5B317E1B5360.model").c_str(), "rotateGizmoMesh");
	RESOURCE_MANAGER.makeMeshStandard(rotateGizmoMesh);

	// rotateXGizmo
	currentMaterial = RESOURCE_MANAGER.createMaterial("rotateXGizmoMaterial");
	currentMaterial->setAlbedoMap(RESOURCE_MANAGER.noTexture);
	currentMaterial->shader = RESOURCE_MANAGER.getShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	currentMaterial->addParameter(FEShaderParam(glm::vec3(0.9f, 0.1f, 0.1f), "baseColor"));
	RESOURCE_MANAGER.makeMaterialStandard(currentMaterial);
	rotateXGizmoEntity = SCENE.addEntity(new FEGameModel(rotateGizmoMesh, currentMaterial, "rotateXGizmoGM"), "rotateXGizmoEntity");
	RESOURCE_MANAGER.makePrefabStandard(rotateXGizmoEntity->prefab);
	RESOURCE_MANAGER.makeGameModelStandard(rotateXGizmoEntity->prefab->getComponent(0)->gameModel);
	rotateXGizmoEntity->setCastShadows(false);
	rotateXGizmoEntity->transform.setScale(glm::vec3(gizmosScale * 2.0f));
	rotateXGizmoEntity->transform.setRotation(rotateXStandardRotation);
	rotateXGizmoEntity->setIsPostprocessApplied(false);

	// rotateYGizmo
	currentMaterial = RESOURCE_MANAGER.createMaterial("rotateYGizmoMaterial");
	currentMaterial->setAlbedoMap(RESOURCE_MANAGER.noTexture);
	currentMaterial->shader = RESOURCE_MANAGER.getShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	currentMaterial->addParameter(FEShaderParam(glm::vec3(0.1f, 0.9f, 0.1f), "baseColor"));
	RESOURCE_MANAGER.makeMaterialStandard(currentMaterial);
	rotateYGizmoEntity = SCENE.addEntity(new FEGameModel(rotateGizmoMesh, currentMaterial, "rotateYGizmoGM"), "rotateYGizmoEntity");
	RESOURCE_MANAGER.makePrefabStandard(rotateYGizmoEntity->prefab);
	RESOURCE_MANAGER.makeGameModelStandard(rotateYGizmoEntity->prefab->getComponent(0)->gameModel);
	rotateYGizmoEntity->setCastShadows(false);
	rotateYGizmoEntity->transform.setScale(glm::vec3(gizmosScale * 2.0f));
	rotateYGizmoEntity->transform.setRotation(rotateYStandardRotation);
	rotateYGizmoEntity->setIsPostprocessApplied(false);

	// rotateZGizmo
	currentMaterial = RESOURCE_MANAGER.createMaterial("rotateZGizmoMaterial");
	currentMaterial->setAlbedoMap(RESOURCE_MANAGER.noTexture);
	currentMaterial->shader = RESOURCE_MANAGER.getShader("6917497A5E0C05454876186F"/*"FESolidColorShader"*/);
	currentMaterial->addParameter(FEShaderParam(glm::vec3(0.1f, 0.1f, 0.9f), "baseColor"));
	RESOURCE_MANAGER.makeMaterialStandard(currentMaterial);
	rotateZGizmoEntity = SCENE.addEntity(new FEGameModel(rotateGizmoMesh, currentMaterial, "rotateZGizmoGM"), "rotateZGizmoEntity");
	RESOURCE_MANAGER.makePrefabStandard(rotateZGizmoEntity->prefab);
	RESOURCE_MANAGER.makeGameModelStandard(rotateZGizmoEntity->prefab->getComponent(0)->gameModel);
	rotateZGizmoEntity->setCastShadows(false);
	rotateZGizmoEntity->transform.setScale(glm::vec3(gizmosScale * 2.0f));
	rotateZGizmoEntity->transform.setRotation(rotateZStandardRotation);
	rotateZGizmoEntity->setIsPostprocessApplied(false);

	transformationGizmoIcon = RESOURCE_MANAGER.LoadFETexture((RESOURCE_MANAGER.getDefaultResourcesFolder() + "456A31026A1C3152181A6064.texture").c_str(), "transformationGizmoIcon");
	RESOURCE_MANAGER.makeTextureStandard(transformationGizmoIcon);
	scaleGizmoIcon = RESOURCE_MANAGER.LoadFETexture((RESOURCE_MANAGER.getDefaultResourcesFolder() + "3F2118296C1E4533506A472E.texture").c_str(), "scaleGizmoIcon");
	RESOURCE_MANAGER.makeTextureStandard(scaleGizmoIcon);
	rotateGizmoIcon = RESOURCE_MANAGER.LoadFETexture((RESOURCE_MANAGER.getDefaultResourcesFolder() + "7F6057403249580D73311B54.texture").c_str(), "rotateGizmoIcon");
	RESOURCE_MANAGER.makeTextureStandard(rotateGizmoIcon);
}

void GizmoManager::hideAllGizmo()
{
	transformationXGizmoEntity->setVisibility(false);
	transformationYGizmoEntity->setVisibility(false);
	transformationZGizmoEntity->setVisibility(false);

	transformationXYGizmoEntity->setVisibility(false);
	transformationYZGizmoEntity->setVisibility(false);
	transformationXZGizmoEntity->setVisibility(false);

	transformationXGizmoActive = false;
	transformationYGizmoActive = false;
	transformationZGizmoActive = false;

	transformationXYGizmoActive = false;
	transformationYZGizmoActive = false;
	transformationXZGizmoActive = false;

	scaleXGizmoEntity->setVisibility(false);
	scaleYGizmoEntity->setVisibility(false);
	scaleZGizmoEntity->setVisibility(false);

	scaleXGizmoActive = false;
	scaleYGizmoActive = false;
	scaleZGizmoActive = false;

	rotateXGizmoEntity->setVisibility(false);
	rotateYGizmoEntity->setVisibility(false);
	rotateZGizmoEntity->setVisibility(false);

	rotateXGizmoActive = false;
	rotateYGizmoActive = false;
	rotateZGizmoActive = false;
}

void GizmoManager::updateGizmoState(int newState)
{
	if (SELECTED.getTerrain() != nullptr)
	{
		if (SELECTED.getTerrain()->getBrushMode() != FE_TERRAIN_BRUSH_NONE)
			return;
	}

	if (newState < 0 || newState > 2)
		newState = 0;

	gizmosState = newState;
	hideAllGizmo();

	if (SELECTED.getSelected() == nullptr || SELECTED.getSelected()->getType() == FE_CAMERA)
		return;

	switch (newState)
	{
		case TRANSFORM_GIZMOS:
		{
			transformationXGizmoEntity->setVisibility(true);
			transformationYGizmoEntity->setVisibility(true);
			transformationZGizmoEntity->setVisibility(true);

			transformationXYGizmoEntity->setVisibility(true);
			transformationYZGizmoEntity->setVisibility(true);
			transformationXZGizmoEntity->setVisibility(true);

			break;
		}
		case SCALE_GIZMOS:
		{
			scaleXGizmoEntity->setVisibility(true);
			scaleYGizmoEntity->setVisibility(true);
			scaleZGizmoEntity->setVisibility(true);
			
			break;
		}
		case ROTATE_GIZMOS:
		{
			rotateXGizmoEntity->setVisibility(true);
			rotateYGizmoEntity->setVisibility(true);
			rotateZGizmoEntity->setVisibility(true);
		
			break;
		}
		default:
			break;
	}
}

void GizmoManager::deactivateAllGizmo()
{
	transformationXGizmoActive = false;
	transformationYGizmoActive = false;
	transformationZGizmoActive = false;

	transformationXYGizmoActive = false;
	transformationYZGizmoActive = false;
	transformationXZGizmoActive = false;

	scaleXGizmoActive = false;
	scaleYGizmoActive = false;
	scaleZGizmoActive = false;

	rotateXGizmoActive = false;
	rotateYGizmoActive = false;
	rotateZGizmoActive = false;
}

void GizmoManager::render()
{
	if (SELECTED.getSelected() == nullptr || SELECTED.getSelected()->getType() == FE_CAMERA)
	{
		hideAllGizmo();
		return;
	}	

	FETransformComponent objTransform = getTransformComponentOfSelectedObject();
	glm::vec3 objectSpaceOriginInWorldSpace = glm::vec3(objTransform.getTransformMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	glm::vec3 toObject = objectSpaceOriginInWorldSpace - ENGINE.getCamera()->getPosition();
	toObject = glm::normalize(toObject);

	// This will center gizmos in AABB center, but it will produce bug while moving object under some circumstances.
	/*if (SELECTED.getEntity() != nullptr && SELECTED.getEntity()->getType() == FE_ENTITY_INSTANCED && SELECTED.instancedSubObjectIndexSelected == -1)
	{
		FEAABB AABB = SELECTED.getEntity()->getAABB();
		glm::vec3 center = AABB.getMin() + ((AABB.getMax() - AABB.getMin()) / 2.0f);
		toObject = glm::normalize(center - ENGINE.getCamera()->getPosition());
	}*/

	if (GIZMO_MANAGER.gizmosState == TRANSFORM_GIZMOS)
	{
		GIZMO_MANAGER.transformationXGizmoEntity->transform.setPosition((ENGINE.getCamera()->getPosition() + toObject * 0.15f));
		GIZMO_MANAGER.transformationYGizmoEntity->transform.setPosition((ENGINE.getCamera()->getPosition() + toObject * 0.15f));
		GIZMO_MANAGER.transformationZGizmoEntity->transform.setPosition((ENGINE.getCamera()->getPosition() + toObject * 0.15f));

		glm::vec3 newP = ENGINE.getCamera()->getPosition() + toObject * 0.15f;
		newP.x += 0.005f;
		newP.y += 0.005f;
		GIZMO_MANAGER.transformationXYGizmoEntity->transform.setPosition(newP);
		newP = ENGINE.getCamera()->getPosition() + toObject * 0.15f;
		newP.z += 0.005f;
		newP.y += 0.005f;
		GIZMO_MANAGER.transformationYZGizmoEntity->transform.setPosition(newP);
		newP = ENGINE.getCamera()->getPosition() + toObject * 0.15f;
		newP.x += 0.005f;
		newP.z += 0.005f;
		GIZMO_MANAGER.transformationXZGizmoEntity->transform.setPosition(newP);

		// X Gizmos
		GIZMO_MANAGER.transformationXGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(0.9f, 0.1f, 0.1f));
		if (GIZMO_MANAGER.transformationXZGizmoActive || GIZMO_MANAGER.transformationXYGizmoActive || GIZMO_MANAGER.transformationXGizmoActive)
			GIZMO_MANAGER.transformationXGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.5f, 1.5f, 0.2f));

		// Y Gizmos
		GIZMO_MANAGER.transformationYGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(0.1f, 0.9f, 0.1f));
		if (GIZMO_MANAGER.transformationYZGizmoActive || GIZMO_MANAGER.transformationXYGizmoActive || GIZMO_MANAGER.transformationYGizmoActive)
			GIZMO_MANAGER.transformationYGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.5f, 1.5f, 0.2f));

		// Z Gizmos
		GIZMO_MANAGER.transformationZGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(0.1f, 0.1f, 0.9f));
		if (GIZMO_MANAGER.transformationYZGizmoActive || GIZMO_MANAGER.transformationXZGizmoActive || GIZMO_MANAGER.transformationZGizmoActive)
			GIZMO_MANAGER.transformationZGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.5f, 1.5f, 0.2f));

		// XY Gizmos
		GIZMO_MANAGER.transformationXYGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.0f, 1.0f, 1.0f));
		if (GIZMO_MANAGER.transformationXYGizmoActive)
			GIZMO_MANAGER.transformationXYGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.5f, 1.5f, 0.2f));

		// YZ Gizmos
		GIZMO_MANAGER.transformationYZGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.0f, 1.0f, 1.0f));
		if (GIZMO_MANAGER.transformationYZGizmoActive)
			GIZMO_MANAGER.transformationYZGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.5f, 1.5f, 0.2f));

		// XZ Gizmos
		GIZMO_MANAGER.transformationXZGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.0f, 1.0f, 1.0f));
		if (GIZMO_MANAGER.transformationXZGizmoActive)
			GIZMO_MANAGER.transformationXZGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.5f, 1.5f, 0.2f));
	}
	else if (GIZMO_MANAGER.gizmosState == SCALE_GIZMOS)
	{
		GIZMO_MANAGER.scaleXGizmoEntity->transform.setPosition((ENGINE.getCamera()->getPosition() + toObject * 0.15f));
		GIZMO_MANAGER.scaleYGizmoEntity->transform.setPosition((ENGINE.getCamera()->getPosition() + toObject * 0.15f));
		GIZMO_MANAGER.scaleZGizmoEntity->transform.setPosition((ENGINE.getCamera()->getPosition() + toObject * 0.15f));

		// X Gizmos
		GIZMO_MANAGER.scaleXGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(0.9f, 0.1f, 0.1f));
		if (GIZMO_MANAGER.scaleXGizmoActive)
			GIZMO_MANAGER.scaleXGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.5f, 1.5f, 0.2f));

		// Y Gizmos
		GIZMO_MANAGER.scaleYGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(0.1f, 0.9f, 0.1f));
		if (GIZMO_MANAGER.scaleYGizmoActive)
			GIZMO_MANAGER.scaleYGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.5f, 1.5f, 0.2f));

		// Z Gizmos
		GIZMO_MANAGER.scaleZGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(0.1f, 0.1f, 0.9f));
		if (GIZMO_MANAGER.scaleZGizmoActive)
			GIZMO_MANAGER.scaleZGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.5f, 1.5f, 0.2f));
	}
	else if (GIZMO_MANAGER.gizmosState == ROTATE_GIZMOS)
	{
		GIZMO_MANAGER.rotateXGizmoEntity->transform.setPosition((ENGINE.getCamera()->getPosition() + toObject * 0.15f));
		GIZMO_MANAGER.rotateYGizmoEntity->transform.setPosition((ENGINE.getCamera()->getPosition() + toObject * 0.15f));
		GIZMO_MANAGER.rotateZGizmoEntity->transform.setPosition((ENGINE.getCamera()->getPosition() + toObject * 0.15f));

		if (SELECTED.SELECTED.getSelected() != nullptr)
		{
			GIZMO_MANAGER.rotateXGizmoEntity->setVisibility(true);
			GIZMO_MANAGER.rotateYGizmoEntity->setVisibility(true);
			GIZMO_MANAGER.rotateZGizmoEntity->setVisibility(true);
		}

		// X Gizmos
		GIZMO_MANAGER.rotateXGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(0.9f, 0.1f, 0.1f));
		if (GIZMO_MANAGER.rotateXGizmoActive)
		{
			GIZMO_MANAGER.rotateXGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.5f, 1.5f, 0.2f));
			GIZMO_MANAGER.rotateYGizmoEntity->setVisibility(false);
			GIZMO_MANAGER.rotateZGizmoEntity->setVisibility(false);
		}

		// Y Gizmos
		GIZMO_MANAGER.rotateYGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(0.1f, 0.9f, 0.1f));
		if (GIZMO_MANAGER.rotateYGizmoActive)
		{
			GIZMO_MANAGER.rotateYGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.5f, 1.5f, 0.2f));
			GIZMO_MANAGER.rotateXGizmoEntity->setVisibility(false);
			GIZMO_MANAGER.rotateZGizmoEntity->setVisibility(false);
		}

		// Z Gizmos
		GIZMO_MANAGER.rotateZGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(0.1f, 0.1f, 0.9f));
		if (GIZMO_MANAGER.rotateZGizmoActive)
		{
			GIZMO_MANAGER.rotateZGizmoEntity->prefab->getComponent(0)->gameModel->material->setBaseColor(glm::vec3(1.5f, 1.5f, 0.2f));
			GIZMO_MANAGER.rotateXGizmoEntity->setVisibility(false);
			GIZMO_MANAGER.rotateYGizmoEntity->setVisibility(false);
		}
	}
}

bool GizmoManager::wasSelected(int index)
{
	deactivateAllGizmo();

	if (SELECTED.objectsUnderMouse[index]->getType() == FE_CAMERA)
		return true;

	FEEntity* selectedEntity = nullptr;
	if (SELECTED.objectsUnderMouse[index]->getType() == FE_ENTITY)
		selectedEntity = SCENE.getEntity(SELECTED.objectsUnderMouse[index]->getObjectID());

	int entityNameHash = selectedEntity == nullptr ? -1 : selectedEntity->getNameHash();
	if (gizmosState == TRANSFORM_GIZMOS && entityNameHash == transformationXGizmoEntity->getNameHash())
	{
		transformationXGizmoActive = true;
	}
	else if (gizmosState == TRANSFORM_GIZMOS && entityNameHash == transformationYGizmoEntity->getNameHash())
	{
		transformationYGizmoActive = true;
	}
	else if (gizmosState == TRANSFORM_GIZMOS && entityNameHash == transformationZGizmoEntity->getNameHash())
	{
		transformationZGizmoActive = true;
	}
	else if (gizmosState == TRANSFORM_GIZMOS && entityNameHash == transformationXYGizmoEntity->getNameHash())
	{
		transformationXYGizmoActive = true;
	}
	else if (gizmosState == TRANSFORM_GIZMOS && entityNameHash == transformationYZGizmoEntity->getNameHash())
	{
		transformationYZGizmoActive = true;
	}
	else if (gizmosState == TRANSFORM_GIZMOS && entityNameHash == transformationXZGizmoEntity->getNameHash())
	{
		transformationXZGizmoActive = true;
	}
	else if (gizmosState == SCALE_GIZMOS && entityNameHash == scaleXGizmoEntity->getNameHash())
	{
		if (selectedEntity != nullptr && selectedEntity->transform.uniformScaling)
		{
			scaleXGizmoActive = true;
			scaleYGizmoActive = true;
			scaleZGizmoActive = true;
		}

		scaleXGizmoActive = true;
	}
	else if (gizmosState == SCALE_GIZMOS && entityNameHash == scaleYGizmoEntity->getNameHash())
	{
		if (selectedEntity != nullptr && selectedEntity->transform.uniformScaling)
		{
			scaleXGizmoActive = true;
			scaleYGizmoActive = true;
			scaleZGizmoActive = true;
		}

		scaleYGizmoActive = true;
	}
	else if (gizmosState == SCALE_GIZMOS && entityNameHash == scaleZGizmoEntity->getNameHash())
	{
		if (selectedEntity != nullptr && selectedEntity->transform.uniformScaling)
		{
			scaleXGizmoActive = true;
			scaleYGizmoActive = true;
			scaleZGizmoActive = true;
		}

		scaleZGizmoActive = true;
	}
	else if (gizmosState == ROTATE_GIZMOS && entityNameHash == rotateXGizmoEntity->getNameHash())
	{
		rotateXGizmoActive = true;
	}
	else if (gizmosState == ROTATE_GIZMOS && entityNameHash == rotateYGizmoEntity->getNameHash())
	{
		rotateYGizmoActive = true;
	}
	else if (gizmosState == ROTATE_GIZMOS && entityNameHash == rotateZGizmoEntity->getNameHash())
	{
		rotateZGizmoActive = true;
	}
	else
	{
		return false;
	}

	return true;
}

glm::vec3 GizmoManager::getMousePositionDifferenceOnPlane(glm::vec3 planeNormal)
{
	FETransformComponent objTransform = getTransformComponentOfSelectedObject();
	glm::vec3 entitySpaceOriginInWorldSpace = glm::vec3(objTransform.getTransformMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::vec3 lastMouseRayVector = SELECTED.mouseRay(lastMouseX, lastMouseY);

	glm::vec3 mouseRayVector = SELECTED.mouseRay(mouseX, mouseY);
	glm::vec3 cameraPosition = ENGINE.getCamera()->getPosition();

	float signedDistanceToOrigin = glm::dot(planeNormal, entitySpaceOriginInWorldSpace);

	float nominator = signedDistanceToOrigin - glm::dot(cameraPosition, planeNormal);
	float lastDenominator = glm::dot(lastMouseRayVector, planeNormal);
	float denominator = glm::dot(mouseRayVector, planeNormal);

	if (denominator == 0 || lastDenominator == 0)
		return glm::vec3(0.0f);

	float lastIntersectionT = nominator / lastDenominator;
	float intersectionT = nominator / denominator;

	glm::vec3 lastPointOnPlane = cameraPosition + lastIntersectionT * lastMouseRayVector;
	glm::vec3 pointOnPlane = cameraPosition + intersectionT * mouseRayVector;

	return pointOnPlane - lastPointOnPlane;
}

glm::vec3 GizmoManager::getMousePositionDifferenceOnPlane(glm::vec3 planeNormal, glm::vec3& lastMousePointOnPlane)
{
	FETransformComponent objTransform = getTransformComponentOfSelectedObject();
	glm::vec3 entitySpaceOriginInWorldSpace = glm::vec3(objTransform.getTransformMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glm::vec3 lastMouseRayVector = SELECTED.mouseRay(lastMouseX, lastMouseY);

	glm::vec3 mouseRayVector = SELECTED.mouseRay(mouseX, mouseY);
	glm::vec3 cameraPosition = ENGINE.getCamera()->getPosition();

	float signedDistanceToOrigin = glm::dot(planeNormal, entitySpaceOriginInWorldSpace);

	float nominator = signedDistanceToOrigin - glm::dot(cameraPosition, planeNormal);
	float lastDenominator = glm::dot(lastMouseRayVector, planeNormal);
	float denominator = glm::dot(mouseRayVector, planeNormal);

	if (denominator == 0 || lastDenominator == 0)
		return glm::vec3(0.0f);

	float lastIntersectionT = nominator / lastDenominator;
	float intersectionT = nominator / denominator;

	glm::vec3 lastPointOnPlane = cameraPosition + lastIntersectionT * lastMouseRayVector;
	glm::vec3 pointOnPlane = cameraPosition + intersectionT * mouseRayVector;

	lastMousePointOnPlane = lastPointOnPlane;
	return pointOnPlane;
}

bool GizmoManager::raysIntersection(glm::vec3& fRayOrigin, glm::vec3& fRayDirection,
									glm::vec3& sRayOrigin, glm::vec3& sRayDirection,
									float& fT, float& sT)
{
	glm::vec3 directionsCross = glm::cross(fRayDirection, sRayDirection);
	// two rays are parallel
	if (directionsCross == glm::vec3(0.0f))
		return false;

	fT = glm::dot(glm::cross((sRayOrigin - fRayOrigin), sRayDirection), directionsCross);
	fT /= glm::length(directionsCross) * glm::length(directionsCross);

	sT = glm::dot(glm::cross((sRayOrigin - fRayOrigin), fRayDirection), directionsCross);
	sT /= glm::length(directionsCross) * glm::length(directionsCross);

	return true;
}

void GizmoManager::mouseMoveTransformationGizmos()
{
	FETransformComponent objTransform = getTransformComponentOfSelectedObject();
	glm::vec3 viewDirection = ENGINE.getCamera()->getForward();

	float fT = 0.0f;
	float sT = 0.0f;

	float lastFT = 0.0f;
	float lastST = 0.0f;

	if (GIZMO_MANAGER.transformationXGizmoActive)
	{
		glm::vec3 lastMouseRayVector = SELECTED.mouseRay(lastMouseX, lastMouseY);
		raysIntersection(ENGINE.getCamera()->getPosition(), lastMouseRayVector,
						 glm::vec3(objTransform.getTransformMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)), glm::vec3(1.0f, 0.0f, 0.0f),
						 lastFT, lastST);

		glm::vec3 mouseRayVector = SELECTED.mouseRay(mouseX, mouseY);
		raysIntersection(ENGINE.getCamera()->getPosition(), mouseRayVector,
						 glm::vec3(objTransform.getTransformMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)), glm::vec3(1.0f, 0.0f, 0.0f),
						 fT, sT);

		float tDifference = sT - lastST;
		glm::vec3 newPosition = objTransform.getPosition();
		newPosition.x += tDifference;
		objTransform.setPosition(newPosition);
	}

	if (GIZMO_MANAGER.transformationYGizmoActive)
	{
		glm::vec3 lastMouseRayVector = SELECTED.mouseRay(lastMouseX, lastMouseY);
		raysIntersection(ENGINE.getCamera()->getPosition(), lastMouseRayVector,
						 glm::vec3(objTransform.getTransformMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)), glm::vec3(0.0f, 1.0f, 0.0f),
						 lastFT, lastST);

		glm::vec3 mouseRayVector = SELECTED.mouseRay(mouseX, mouseY);
		raysIntersection(ENGINE.getCamera()->getPosition(), mouseRayVector,
						 glm::vec3(objTransform.getTransformMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)), glm::vec3(0.0f, 1.0f, 0.0f),
						 fT, sT);

		float tDifference = sT - lastST;
		glm::vec3 newPosition = objTransform.getPosition();
		newPosition.y += tDifference;
		objTransform.setPosition(newPosition);
	}

	if (GIZMO_MANAGER.transformationZGizmoActive)
	{
		glm::vec3 lastMouseRayVector = SELECTED.mouseRay(lastMouseX, lastMouseY);
		raysIntersection(ENGINE.getCamera()->getPosition(), lastMouseRayVector,
						 glm::vec3(objTransform.getTransformMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)), glm::vec3(0.0f, 0.0f, 1.0f),
						 lastFT, lastST);

		glm::vec3 mouseRayVector = SELECTED.mouseRay(mouseX, mouseY);
		raysIntersection(ENGINE.getCamera()->getPosition(), mouseRayVector,
						 glm::vec3(objTransform.getTransformMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)), glm::vec3(0.0f, 0.0f, 1.0f),
						 fT, sT);

		float tDifference = sT - lastST;
		glm::vec3 newPosition = objTransform.getPosition();
		newPosition.z += tDifference;
		objTransform.setPosition(newPosition);
	}

	if (GIZMO_MANAGER.transformationXYGizmoActive)
	{
		glm::vec3 difference = getMousePositionDifferenceOnPlane(glm::vec3(0.0f, 0.0f, 1.0f));
		glm::vec3 newPosition = objTransform.getPosition();
		newPosition.x += difference.x;
		newPosition.y += difference.y;
		objTransform.setPosition(newPosition);
	}

	if (GIZMO_MANAGER.transformationYZGizmoActive)
	{
		glm::vec3 difference = getMousePositionDifferenceOnPlane(glm::vec3(1.0f, 0.0f, 0.0f));
		glm::vec3 newPosition = objTransform.getPosition();
		newPosition.y += difference.y;
		newPosition.z += difference.z;
		objTransform.setPosition(newPosition);
	}

	if (GIZMO_MANAGER.transformationXZGizmoActive)
	{
		glm::vec3 difference = getMousePositionDifferenceOnPlane(glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec3 newPosition = objTransform.getPosition();
		newPosition.x += difference.x;
		newPosition.z += difference.z;
		objTransform.setPosition(newPosition);
	}

	applyChangesToSelectedObject(objTransform);
}

void GizmoManager::mouseMoveScaleGizmos()
{
	FETransformComponent objTransform = getTransformComponentOfSelectedObject();

	if (GIZMO_MANAGER.scaleXGizmoActive && GIZMO_MANAGER.scaleYGizmoActive && GIZMO_MANAGER.scaleZGizmoActive)
	{
		glm::vec3 difference = getMousePositionDifferenceOnPlane(-ENGINE.getCamera()->getForward());
		float magnitude = difference.x + difference.y + difference.z;

		glm::vec3 entityScale = objTransform.getScale();
		entityScale += magnitude;
		objTransform.setScale(entityScale);
	}
	else if (GIZMO_MANAGER.scaleXGizmoActive || GIZMO_MANAGER.scaleYGizmoActive || GIZMO_MANAGER.scaleZGizmoActive)
	{
		if (GIZMO_MANAGER.scaleXGizmoActive)
		{
			glm::vec3 difference = getMousePositionDifferenceOnPlane(glm::vec3(0.0f, 0.0f, 1.0f));
			glm::vec3 entityScale = objTransform.getScale();
			entityScale.x += difference.x;
			objTransform.setScale(entityScale);
		}

		if (GIZMO_MANAGER.scaleYGizmoActive)
		{
			glm::vec3 difference = getMousePositionDifferenceOnPlane(glm::vec3(0.0f, 0.0f, 1.0f));
			glm::vec3 entityScale = objTransform.getScale();
			entityScale.y += difference.y;
			objTransform.setScale(entityScale);
		}

		if (GIZMO_MANAGER.scaleZGizmoActive)
		{
			glm::vec3 difference = getMousePositionDifferenceOnPlane(glm::vec3(0.0f, 1.0f, 0.0f));
			glm::vec3 entityScale = objTransform.getScale();
			entityScale.z += difference.z;
			objTransform.setScale(entityScale);
		}
	}

	applyChangesToSelectedObject(objTransform);
}

void GizmoManager::mouseMoveRotateGizmos()
{
	FETransformComponent objTransform = getTransformComponentOfSelectedObject();

	float differenceX = float(mouseX - lastMouseX);
	float differenceY = float(mouseY - lastMouseY);

	float difference = (differenceX + differenceY) / 2.0f;

	if (GIZMO_MANAGER.rotateXGizmoActive)
	{
		glm::vec3 xVector = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 xVectorInEntitySpace = glm::normalize(glm::inverse(glm::toMat4(objTransform.getQuaternion())) * glm::vec4(xVector, 0.0f));

		glm::quat rotationQuaternion1 = glm::quat(cos(difference * ANGLE_TORADIANS_COF / 2),
												  xVector.x * sin(difference * ANGLE_TORADIANS_COF / 2),
												  xVector.y * sin(difference * ANGLE_TORADIANS_COF / 2),
												  xVector.z * sin(difference * ANGLE_TORADIANS_COF / 2));

		objTransform.rotateByQuaternion(rotationQuaternion1);
	}

	if (GIZMO_MANAGER.rotateYGizmoActive)
	{
		glm::vec3 yVector = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 yVectorInEntitySpace = glm::normalize(glm::inverse(glm::toMat4(objTransform.getQuaternion())) * glm::vec4(yVector, 0.0f));

		glm::quat rotationQuaternion1 = glm::quat(cos(difference * ANGLE_TORADIANS_COF / 2),
												  yVector.x * sin(difference * ANGLE_TORADIANS_COF / 2),
												  yVector.y * sin(difference * ANGLE_TORADIANS_COF / 2),
												  yVector.z * sin(difference * ANGLE_TORADIANS_COF / 2));

		objTransform.rotateByQuaternion(rotationQuaternion1);
	}

	if (GIZMO_MANAGER.rotateZGizmoActive)
	{
		glm::vec3 zVector = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 zVectorInEntitySpace = glm::normalize(glm::inverse(glm::toMat4(objTransform.getQuaternion())) * glm::vec4(zVector, 0.0f));

		glm::quat rotationQuaternion1 = glm::quat(cos(difference * ANGLE_TORADIANS_COF / 2),
												  zVector.x * sin(difference * ANGLE_TORADIANS_COF / 2),
												  zVector.y * sin(difference * ANGLE_TORADIANS_COF / 2),
												  zVector.z * sin(difference * ANGLE_TORADIANS_COF / 2));

		objTransform.rotateByQuaternion(rotationQuaternion1);
	}

	applyChangesToSelectedObject(objTransform);
}

void GizmoManager::mouseMove(double lastMouseX, double lastMouseY, double mouseX, double mouseY)
{
	this->lastMouseX = lastMouseX;
	this->lastMouseY = lastMouseY;
	this->mouseX = mouseX;
	this->mouseY = mouseY;

	if (gizmosState == TRANSFORM_GIZMOS)
	{
		mouseMoveTransformationGizmos();
	}
	else if (gizmosState == SCALE_GIZMOS)
	{
		mouseMoveScaleGizmos();
	}
	else if (gizmosState == ROTATE_GIZMOS)
	{
		mouseMoveRotateGizmos();
	}
}

void GizmoManager::onSelectedObjectUpdate()
{
	if (SELECTED.getSelected() == nullptr)
	{
		GIZMO_MANAGER.hideAllGizmo();
	}
	else
	{
		if (SELECTED.getTerrain() != nullptr)
		{
			if (SELECTED.getTerrain()->getBrushMode() != FE_TERRAIN_BRUSH_NONE)
			{
				GIZMO_MANAGER.hideAllGizmo();
				return;
			}
		}

		if (GIZMO_MANAGER.gizmosState == TRANSFORM_GIZMOS)
		{
			GIZMO_MANAGER.transformationXGizmoEntity->setVisibility(true);
			GIZMO_MANAGER.transformationYGizmoEntity->setVisibility(true);
			GIZMO_MANAGER.transformationZGizmoEntity->setVisibility(true);
			GIZMO_MANAGER.transformationXYGizmoEntity->setVisibility(true);
			GIZMO_MANAGER.transformationYZGizmoEntity->setVisibility(true);
			GIZMO_MANAGER.transformationXZGizmoEntity->setVisibility(true);
		}
		else if (GIZMO_MANAGER.gizmosState == SCALE_GIZMOS)
		{
			GIZMO_MANAGER.scaleXGizmoEntity->setVisibility(true);
			GIZMO_MANAGER.scaleYGizmoEntity->setVisibility(true);
			GIZMO_MANAGER.scaleZGizmoEntity->setVisibility(true);
		}
		else if (GIZMO_MANAGER.gizmosState == ROTATE_GIZMOS)
		{
			GIZMO_MANAGER.rotateXGizmoEntity->setVisibility(true);
			GIZMO_MANAGER.rotateYGizmoEntity->setVisibility(true);
			GIZMO_MANAGER.rotateZGizmoEntity->setVisibility(true);
		}
	}
}

FETransformComponent GizmoManager::getTransformComponentOfSelectedObject()
{
	if (SELECTED.getSelected() == nullptr)
		FETransformComponent();

	if (SELECTED.getSelected()->getType() == FE_ENTITY)
	{
		return SELECTED.getEntity()->transform;
	}
	else if (SELECTED.getSelected()->getType() == FE_ENTITY_INSTANCED)
	{
		if (SELECTED.instancedSubObjectIndexSelected != -1)
		{
			return reinterpret_cast<FEEntityInstanced*>(SELECTED.getEntity())->getTransformedInstancedMatrix(SELECTED.instancedSubObjectIndexSelected);
		}
		else
		{
			return SELECTED.getEntity()->transform;
		}
	}
	else if (SELECTED.getSelected()->getType() == FE_TERRAIN)
	{
		return SELECTED.getTerrain()->transform;
	}
	else if (SELECTED.getSelected()->getType() == FE_DIRECTIONAL_LIGHT || SELECTED.getSelected()->getType() == FE_SPOT_LIGHT || SELECTED.getSelected()->getType() == FE_POINT_LIGHT)
	{
		return SELECTED.getLight()->transform;
	}

	return FETransformComponent();
}

void GizmoManager::applyChangesToSelectedObject(FETransformComponent changes)
{
	if (SELECTED.getSelected() == nullptr)
		FETransformComponent();

	if (SELECTED.getSelected()->getType() == FE_ENTITY)
	{
		SELECTED.getEntity()->transform = changes;
	}
	else if (SELECTED.getSelected()->getType() == FE_ENTITY_INSTANCED)
	{
		if (SELECTED.instancedSubObjectIndexSelected != -1)
		{
			reinterpret_cast<FEEntityInstanced*>(SELECTED.getEntity())->modifyInstance(SELECTED.instancedSubObjectIndexSelected, changes.getTransformMatrix());
		}
		else
		{
			SELECTED.getEntity()->transform = changes;
		}
	}
	else if (SELECTED.getSelected()->getType() == FE_TERRAIN)
	{
		SELECTED.getTerrain()->transform = changes;
	}
	else if (SELECTED.getSelected()->getType() == FE_DIRECTIONAL_LIGHT || SELECTED.getSelected()->getType() == FE_SPOT_LIGHT || SELECTED.getSelected()->getType() == FE_POINT_LIGHT)
	{
		SELECTED.getLight()->transform = changes;
	}
}

void GizmoManager::reInitializeEntities()
{
	// transformationXGizmo
	transformationXGizmoEntity = SCENE.addEntity(RESOURCE_MANAGER.getPrefabByName("TransformationXGizmoGM")[0], "transformationXGizmoEntity");
	transformationXGizmoEntity->setCastShadows(false);
	transformationXGizmoEntity->transform.setScale(glm::vec3(gizmosScale));
	transformationXGizmoEntity->transform.setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
	transformationXGizmoEntity->setIsPostprocessApplied(false);

	// transformationYGizmo
	transformationYGizmoEntity = SCENE.addEntity(RESOURCE_MANAGER.getPrefabByName("TransformationYGizmoGM")[0], "transformationYGizmoEntity");
	transformationYGizmoEntity->setCastShadows(false);
	transformationYGizmoEntity->transform.setScale(glm::vec3(gizmosScale));
	transformationYGizmoEntity->transform.setRotation(glm::vec3(0.0f));
	transformationYGizmoEntity->setIsPostprocessApplied(false);

	// transformationZGizmo
	transformationZGizmoEntity = SCENE.addEntity(RESOURCE_MANAGER.getPrefabByName("TransformationZGizmoGM")[0], "transformationZGizmoEntity");
	transformationZGizmoEntity->setCastShadows(false);
	transformationZGizmoEntity->transform.setScale(glm::vec3(gizmosScale));
	transformationZGizmoEntity->transform.setRotation(glm::vec3(90.0f, 0.0f, 90.0f));
	transformationZGizmoEntity->setIsPostprocessApplied(false);

	// plane gizmos
	transformationXYGizmoEntity = SCENE.addEntity(RESOURCE_MANAGER.getPrefabByName("TransformationXYGizmoGM")[0], "transformationXYGizmoEntity");
	transformationXYGizmoEntity->setCastShadows(false);
	transformationXYGizmoEntity->transform.setScale(glm::vec3(gizmosScale, gizmosScale, gizmosScale * 0.02f));
	transformationXYGizmoEntity->transform.setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
	transformationXYGizmoEntity->setIsPostprocessApplied(false);

	
	transformationYZGizmoEntity = SCENE.addEntity(RESOURCE_MANAGER.getPrefabByName("TransformationYZGizmoGM")[0], "transformationYZGizmoEntity");
	transformationYZGizmoEntity->setCastShadows(false);
	transformationYZGizmoEntity->transform.setScale(glm::vec3(gizmosScale * 0.02f, gizmosScale, gizmosScale));
	transformationYZGizmoEntity->transform.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	transformationYZGizmoEntity->setIsPostprocessApplied(false);

	transformationXZGizmoEntity = SCENE.addEntity(RESOURCE_MANAGER.getPrefabByName("TransformationXZGizmoGM")[0], "transformationXZGizmoEntity");
	transformationXZGizmoEntity->setCastShadows(false);
	transformationXZGizmoEntity->transform.setScale(glm::vec3(gizmosScale, gizmosScale * 0.02f, gizmosScale));
	transformationXZGizmoEntity->transform.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	transformationXZGizmoEntity->setIsPostprocessApplied(false);

	// scaleXGizmo
	scaleXGizmoEntity = SCENE.addEntity(RESOURCE_MANAGER.getPrefabByName("scaleXGizmoGM")[0], "scaleXGizmoEntity");
	scaleXGizmoEntity->setCastShadows(false);
	scaleXGizmoEntity->transform.setScale(glm::vec3(gizmosScale));
	scaleXGizmoEntity->transform.setRotation(glm::vec3(0.0f, 0.0f, -90.0f));
	scaleXGizmoEntity->setIsPostprocessApplied(false);

	// scaleYGizmo
	scaleYGizmoEntity = SCENE.addEntity(RESOURCE_MANAGER.getPrefabByName("scaleYGizmoGM")[0], "scaleYGizmoEntity");
	scaleYGizmoEntity->setCastShadows(false);
	scaleYGizmoEntity->transform.setScale(glm::vec3(gizmosScale));
	scaleYGizmoEntity->transform.setRotation(glm::vec3(0.0f));
	scaleYGizmoEntity->setIsPostprocessApplied(false);

	// scaleZGizmo
	scaleZGizmoEntity = SCENE.addEntity(RESOURCE_MANAGER.getPrefabByName("scaleZGizmoGM")[0], "scaleZGizmoEntity");
	scaleZGizmoEntity->setCastShadows(false);
	scaleZGizmoEntity->transform.setScale(glm::vec3(gizmosScale));
	scaleZGizmoEntity->transform.setRotation(glm::vec3(90.0f, 0.0f, 90.0f));
	scaleZGizmoEntity->setIsPostprocessApplied(false);

	// rotateXGizmo
	rotateXGizmoEntity = SCENE.addEntity(RESOURCE_MANAGER.getPrefabByName("rotateXGizmoGM")[0], "rotateXGizmoEntity");
	rotateXGizmoEntity->setCastShadows(false);
	rotateXGizmoEntity->transform.setScale(glm::vec3(gizmosScale * 2.0f));
	rotateXGizmoEntity->transform.setRotation(rotateXStandardRotation);
	rotateXGizmoEntity->setIsPostprocessApplied(false);

	// rotateYGizmo
	rotateYGizmoEntity = SCENE.addEntity(RESOURCE_MANAGER.getPrefabByName("rotateYGizmoGM")[0], "rotateYGizmoEntity");
	rotateYGizmoEntity->setCastShadows(false);
	rotateYGizmoEntity->transform.setScale(glm::vec3(gizmosScale * 2.0f));
	rotateYGizmoEntity->transform.setRotation(rotateYStandardRotation);
	rotateYGizmoEntity->setIsPostprocessApplied(false);

	// rotateZGizmo
	rotateZGizmoEntity = SCENE.addEntity(RESOURCE_MANAGER.getPrefabByName("rotateZGizmoGM")[0], "rotateZGizmoEntity");
	rotateZGizmoEntity->setCastShadows(false);
	rotateZGizmoEntity->transform.setScale(glm::vec3(gizmosScale * 2.0f));
	rotateZGizmoEntity->transform.setRotation(rotateZStandardRotation);
	rotateZGizmoEntity->setIsPostprocessApplied(false);
}