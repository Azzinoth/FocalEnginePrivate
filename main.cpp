#include "../Editor/FEEditor.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ENGINE.createWindow();
	EDITOR.initializeResources();

	const int frameCountTillMeasure = 20;
	double cpuFrameDurations[frameCountTillMeasure] = { 0.0f };
	double gpuFrameDurations[frameCountTillMeasure] = { 0.0f };
	int frameCounter = 0;

	double avarageCpuFrameDuration = 0.0;
	double avarageGpuFrameDuration = 0.0;

	while (ENGINE.isWindowOpened())
	{
		ENGINE.beginFrame();
		ENGINE.render();

		if (RENDERER.CSM0 != nullptr)
		{
			/*ImGui::Image((void*)(intptr_t)RENDERER.CSM0->getTextureID(), ImVec2(256, 256), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
			ImGui::Image((void*)(intptr_t)RENDERER.CSM1->getTextureID(), ImVec2(256, 256), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
			ImGui::Image((void*)(intptr_t)RENDERER.CSM2->getTextureID(), ImVec2(256, 256), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
			ImGui::Image((void*)(intptr_t)RENDERER.CSM3->getTextureID(), ImVec2(256, 256), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));*/

			if (SELECTED.getTerrain() != nullptr)
			{
				if (SELECTED.getTerrain()->layerMaps[0] != nullptr && SELECTED.getTerrain()->layerMaps[1] != nullptr)
				{
					ImGui::Image((void*)(intptr_t)SELECTED.getTerrain()->layerMaps[0]->getTextureID(), ImVec2(256, 256), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
					ImGui::Image((void*)(intptr_t)SELECTED.getTerrain()->layerMaps[1]->getTextureID(), ImVec2(256, 256), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
				}
			}
			
#ifdef USE_DEFERRED_RENDERER
			//ImGui::Image((void*)(intptr_t)RENDERER.positionsGBufferLastFrame->getTextureID(), ImVec2(256 * 1, 256 * 1), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
			//ImGui::Image((void*)(intptr_t)RENDERER.SSAOLastFrame->getTextureID(), ImVec2(256 * 1, 256 * 1), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));

			ImGui::Image((void*)(intptr_t)RENDERER.GBuffer->positions->getTextureID(), ImVec2(256 * 1, 256 * 1), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
			ImGui::Image((void*)(intptr_t)RENDERER.GBuffer->normals->getTextureID(), ImVec2(256 * 1, 256 * 1), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
			ImGui::Image((void*)(intptr_t)RENDERER.GBuffer->albedo->getTextureID(), ImVec2(256 * 1, 256 * 1), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
			ImGui::Image((void*)(intptr_t)RENDERER.GBuffer->materialProperties->getTextureID(), ImVec2(256 * 1, 256 * 1), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
#endif

#ifdef EDITOR_SELECTION_DEBUG_MODE
			std::string objectsUnderMouse = "objectsUnderMouse: " + std::to_string(SELECTED.objectsUnderMouse.size());
			ImGui::Text(objectsUnderMouse.c_str());

			std::string colorIndex = "colorIndex: " + std::to_string(SELECTED.colorIndex);
			ImGui::Text(colorIndex.c_str());

			ImGui::Image((void*)(intptr_t)SELECTED.pixelAccurateSelectionFB->getColorAttachment()->getTextureID(), ImVec2(256 * 4, 256 * 4), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
#endif
		}

		//ImGui::ShowDemoWindow();
		EDITOR.render();
		ENGINE.endFrame();

		// CPU and GPU Time
		cpuFrameDurations[frameCounter++] = ENGINE.getCpuTime();
		gpuFrameDurations[frameCounter++] = ENGINE.getGpuTime();

		if (frameCounter > frameCountTillMeasure - 1)
		{
			avarageCpuFrameDuration = 0.0f;
			avarageGpuFrameDuration = 0.0f;
			for (size_t i = 0; i < frameCountTillMeasure; i++)
			{
				avarageCpuFrameDuration += cpuFrameDurations[i];
				avarageGpuFrameDuration += gpuFrameDurations[i];
			}
			avarageCpuFrameDuration /= frameCountTillMeasure;
			avarageGpuFrameDuration /= frameCountTillMeasure;
			
			frameCounter = 0;
		}

		std::string cpuMS = std::to_string(avarageCpuFrameDuration);
		cpuMS.erase(cpuMS.begin() + 4, cpuMS.end());

		std::string gpuMS = std::to_string(avarageGpuFrameDuration);
		gpuMS.erase(gpuMS.begin() + 4, gpuMS.end());

		std::string frameMS = std::to_string(avarageCpuFrameDuration + avarageGpuFrameDuration);
		frameMS.erase(frameMS.begin() + 4, frameMS.end());

		std::string caption = "CPU time : ";
		caption += cpuMS;
		caption += " ms";
		caption += "  GPU time : ";
		caption += gpuMS;
		caption += " ms";
		caption += "  Frame time : ";
		caption += frameMS;
		caption += " ms";

		ENGINE.setWindowCaption(caption.c_str());
	}
	
	return 0;
}