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
}

void App::Update(int shaderProgram, unsigned int VAO)
{
	cam.Update();

	Mat4 modelMatrix = GetIdentityMat4();

	modelMatrix.Scale(Vec3(0.5f, 0.5f, 0.5f));
	modelMatrix.Translate(Vec3(0, 0, 0));
	modelMatrix.Rotate(Vec3(0, (float)glfwGetTime(), (float)glfwGetTime()));

	Mat4 transformMatrix = cam.GetProjectionMatrix() * cam.GetViewMatrix() * modelMatrix;

	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, *transformMatrix.tab);

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

	// draw our first triangle
	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0); // set it manually
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1); // set it manually

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	// glBindVertexArray(0); // no need to unbind it every time

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
		cam.position -= cam.speed * cam.direction;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.position += cam.speed * cam.direction;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.position += GetCrossProduct(cam.direction, cam.camUp).GetNormalizedVector() * cam.speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.position -= GetCrossProduct(cam.direction, cam.camUp).GetNormalizedVector() * cam.speed;
}