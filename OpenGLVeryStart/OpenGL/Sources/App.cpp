#include <App.h>;

using namespace Core;
using namespace Resources;

App::~App()
{
	// glfw: terminate, clearing all previously allocated GLFW resources.
// ------------------------------------------------------------------
	glfwTerminate();
}

void App::Init(AppInitializer initializer)
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, initializer.major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, initializer.minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);


	// glfw window creation
	// --------------------
	/*GLFWwindow* */ window = glfwCreateWindow(initializer.width, initializer.height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, initializer.framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return ;
	}


	GLint flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(initializer.glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void App::Update(int shaderProgram)
{
	// input
		// -----
	glfwPollEvents();
	processInput();

	// render
	// ------
	glClearColor(0.f, 0.f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	//glBindTexture(GL_TEXTURE_2D, texture);

	cam.Update();
	Mat4 projView = cam.GetProjectionMatrix() * cam.GetViewMatrix();
	
	glUniform3f(glGetUniformLocation(shaderProgram, "ambientColor"), lights[0]->ambientColor.x, lights[0]->ambientColor.y, lights[0]->ambientColor.z);
	glUniform3f(glGetUniformLocation(shaderProgram, "diffuseColor"), lights[0]->diffuseColor.x, lights[0]->diffuseColor.y, lights[0]->diffuseColor.z);
	glUniform3f(glGetUniformLocation(shaderProgram, "specularColor"), lights[0]->specularColor.x, lights[0]->specularColor.y, lights[0]->specularColor.z);
	glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), lights[0]->position.x, lights[0]->position.y, lights[0]->position.z);
	//glUniform1i(glGetUniformLocation(shaderProgram, "lightType"), lights[0]->type);
	glUniform3f(glGetUniformLocation(shaderProgram, "viewPos"), cam.position.x, cam.position.y, cam.position.z);

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Update(projView, shaderProgram);
	}

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(window);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void App::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.position -= cam.speed * cam.camForward;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.position += cam.speed * cam.camForward;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.position -= cam.camRight * cam.speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.position += cam.camRight * cam.speed;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cam.position += cam.camUp * cam.speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		cam.position -= cam.camUp * cam.speed;

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	cam.MouseDirection(xpos, ypos);
	//cout << "xpos : " << xpos << ", ypos : " << ypos << endl;
}