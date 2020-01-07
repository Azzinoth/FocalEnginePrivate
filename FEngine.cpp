#include "FEngine.h"
using namespace FocalEngine;

FEngine* FEngine::_instance = nullptr;
#define RENDERER_OBJ FERenderer::getInstance()
#define RESOURCE_MANAGER_OBJ FEResourceManager::getInstance()
#define ENGINE_OBJ FEngine::getInstance()
#define SCENE_OBJ FocalEngine::FEScene::getInstance()
#define TIME_OBJ FocalEngine::FETime::getInstance()

FEngine::FEngine()
{
	FEInput::getInstance().mouseButtonCallbackImpl = &FEngine::mouseButtonCallback;
	FEInput::getInstance().mouseMoveCallbackImpl = &FEngine::mouseMoveCallback;
	FEInput::getInstance().keyButtonCallbackImpl = &FEngine::keyButtonCallback;
}

FEngine::~FEngine()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool FEngine::isWindowOpened()
{
	return !glfwWindowShouldClose(window);
}

void FEngine::beginFrame(bool internalCall)
{
	if (!internalCall) TIME_OBJ.beginTimeStamp();

	FE_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	ImGui::GetIO().DeltaTime = 1.0f / 60.0f;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void FEngine::render(bool internalCall)
{
	ENGINE_OBJ.currentCamera->move(cpuTime + gpuTime);
	RENDERER_OBJ.render(currentCamera);

	if (!internalCall) cpuTime = TIME_OBJ.endTimeStamp();
}

void FEngine::endFrame(bool internalCall)
{
	if (!internalCall) TIME_OBJ.beginTimeStamp();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(window);
	glfwPollEvents();
	if (!internalCall) gpuTime = TIME_OBJ.endTimeStamp();
}

void FEngine::createWindow(int width, int height, std::string WindowTitle)
{
	windowW = width;
	windowH = height;
	windowTitle = WindowTitle;

	glfwInit();
	//if (!glfwInit())
		//return -1;

	window = glfwCreateWindow(windowW, windowH, windowTitle.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		//return -1;
	}

	glfwMakeContextCurrent(window);
	glewInit();
   
	glfwSetMouseButtonCallback(window, &FEInput::mouseButtonCallback);
	glfwSetCursorPosCallback(window, &FEInput::mouseMoveCallback);
	glfwSetKeyCallback(window, &FEInput::keyButtonCallback);

	glClearColor(0.7f, 0.0f, 0.7f, 1.0f);

	// turn off v-sync
	glfwSwapInterval(0);

	currentCamera = new FEFreeCamera(window);
	currentCamera->setAspectRatio(float(width) / float(height));

	FE_GL_ERROR(glEnable(GL_DEPTH_TEST));
	FE_GL_ERROR(glEnable(GL_CULL_FACE));
	FE_GL_ERROR(glCullFace(GL_BACK));

	RENDERER_OBJ.standardFBInit(windowW, windowH);
	RENDERER_OBJ.addPostProcess(new FEBlurEffect(RESOURCE_MANAGER_OBJ.getSimpleMesh("plane"), windowW, windowH));
	RENDERER_OBJ.addPostProcess(new FEGammaAndHDRCorrection(RESOURCE_MANAGER_OBJ.getSimpleMesh("plane"), windowW, windowH));

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	unsigned char* tex_pixels = NULL;
	int tex_w, tex_h;
	io.Fonts->GetTexDataAsRGBA32(&tex_pixels, &tex_w, &tex_h);

	io.DisplaySize = ImVec2(float(windowW), float(windowH));
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

void FEngine::setWindowCaption(const char* text)
{
	glfwSetWindowTitle(window, text);
}

void FEngine::setKeyCallback(void(*func)(int, int, int, int))
{
	clientKeyButtonCallbackImpl = func;
}

void FEngine::setMouseButtonCallback(void(*func)(int, int, int))
{
	clientMouseButtonCallbackImpl = func;
}

void FEngine::setMouseMoveCallback(void(*func)(double, double))
{
	clientMouseMoveCallbackImpl = func;
}

void FEngine::mouseButtonCallback(int button, int action, int mods)
{
	FEngine& engineObj = getInstance();
	if (engineObj.clientMouseButtonCallbackImpl != nullptr)
		engineObj.clientMouseButtonCallbackImpl(button, action, mods);
}

void FEngine::mouseMoveCallback(double xpos, double ypos)
{
	FEngine& engineObj = getInstance();
	if (engineObj.clientMouseMoveCallbackImpl != nullptr)
		engineObj.clientMouseMoveCallbackImpl(xpos, ypos);

	engineObj.currentCamera->mouseMoveInput(xpos, ypos);
}

void FEngine::keyButtonCallback(int key, int scancode, int action, int mods)
{
	FEngine& engineObj = getInstance();
	if (engineObj.clientKeyButtonCallbackImpl != nullptr)
		engineObj.clientKeyButtonCallbackImpl(key, scancode, action, mods);

	engineObj.currentCamera->keyboardInput(key, scancode, action, mods);
}

void FEngine::setCamera(FEBasicCamera* newCamera)
{
	currentCamera = newCamera;
}

FEBasicCamera* FEngine::getCamera()
{
	return currentCamera;
}

int FEngine::getWindowWidth()
{
	return windowW;
}

int FEngine::getWindowHeight()
{
	return windowH;
}

void FEngine::renderTo(FEFramebuffer* renderTo)
{
	renderTo->bind();
	beginFrame(true);
	render(true);
	renderTo->unBind();
}

float FEngine::getCpuTime()
{
	return cpuTime;
}

float FEngine::getGpuTime()
{
	return gpuTime;
}

FEPostProcess* FEngine::createPostProcess(int ScreenWidth, int ScreenHeight)
{
	if (ScreenWidth < 2 || ScreenHeight < 2)
	{
		ScreenWidth = windowW;
		ScreenHeight = windowH;
	}

	return RESOURCE_MANAGER_OBJ.createPostProcess(ScreenWidth, ScreenHeight);
}
