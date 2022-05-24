
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <App.h>
#include <Log.h>
#include <Shader.h>
#include <Camera.h>
#include <Texture.h>

using namespace Core;
using namespace Debug;
using namespace Resources;
using namespace LowRenderer;



void framebuffer_size_callback(GLFWwindow* window, int width, int height);



void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1200;

int main()
{
	AppInitializer initializer = { SCR_WIDTH , SCR_HEIGHT, 4, 5, "ChatChien", framebuffer_size_callback, glDebugOutput };

	App app;
	app.Init(initializer);

	ResourceManager manager;
	Model* model = manager.Create<Model>("Resources/Obj/cube.obj", "cube");
	Model* model2 = manager.Create<Model>("Resources/Obj/khazix.obj", "khazix");
	Model* model3 = manager.Create<Model>("Resources/Obj/Garen.obj", "garen");
	Model* model4 = manager.Create<Model>("Resources/Obj/Azir.obj", "azir");

	if (model == nullptr)
	{
		cout << "resource not found" << endl;
	}

	// build and compile our shader program
	// ------------------------------------
	
	Shader shader("Resources/Shaders/VertexShader.glsl", "Resources/Shaders/FragmentShader.glsl");

	Texture texture("sample.png");
	Texture texture2("khaz.png");
	Texture texture3("Azir.png");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	app.directLights.push_back(new DirectionnalLight(Vec3(5, -10, 0), Vec3(1, 1, 1)));
	app.pointLights.push_back(new PointLight(Vec3(0,10,0), Vec3(1,1,1), 1, 0.022f, 0.0019f));
	app.spotLights.push_back(new SpotLight(Vec3(0, -10, 0), Vec3(0, 0, 0), Vec3(1,1,1), 1, 0.022f, 0.0019f, M_PI/3.15));

	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(0, 0, 0), Vec3(), Vec3(0.05f, 0.05f, 0.05f)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(0, -3, 0), Vec3(), Vec3(1.f, 1.f, 1.f)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(0, 3, 0), Vec3(), Vec3(1.f, 1.f, 1.f)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(3, -3, 0), Vec3(), Vec3(1.f, 1.f, 1.f)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(-3, -3, 0), Vec3(), Vec3(1.f, 1.f, 1.f)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(0, -3, 3), Vec3(), Vec3(1.f, 1.f, 1.f)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(0, -3, -3), Vec3(), Vec3(1.f, 1.f, 1.f)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(0, -8, 0), Vec3(), Vec3(1.f, 1.f, 1.f)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(0, -20, 0), Vec3(), Vec3(1.f, 1.f, 1.f)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(10, 5, -4), Vec3(), Vec3(1, 1, 1)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(-7, -2, 5), Vec3(), Vec3(1, 1, 1)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(2, -5, 0), Vec3(), Vec3(1, 1, 1)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(-6, -8, -3), Vec3(), Vec3(1, 1, 1)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(12, 3, 8), Vec3(), Vec3(1, 1, 1)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(3, -9, -5), Vec3(), Vec3(1, 1, 1)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(-1, 4, 1), Vec3(), Vec3(1, 1, 1)), &texture));
	app.meshes.push_back(new Mesh(model, CreateTransformMatrix(Vec3(20, 10, -1), Vec3(), Vec3(2, 1, 1)), &texture));
	app.meshes.push_back(new Mesh(model2, CreateTransformMatrix(Vec3(20, 10, -1), Vec3(), Vec3(0.05f, 0.05f, 0.05f)), &texture2));
	app.meshes.push_back(new Mesh(model3, CreateTransformMatrix(Vec3(0, 10, -1), Vec3(), Vec3(0.05f, 0.05f, 0.05f)), &texture));
	app.meshes.push_back(new Mesh(model4, CreateTransformMatrix(Vec3(-20, 10, -1), Vec3(), Vec3(0.05f, 0.05f, 0.05f)), &texture3));
	

	// create a sampler and parameterize it
	// ------------------------------------
	GLuint sampler = 0;
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);

	GLint max = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);

	
	glBindTextureUnit(0, texture.texture);
	glBindSampler(0, sampler);

	glBindTextureUnit(1, texture2.texture);
	glBindSampler(1, sampler);
	

	// render loop
	// -----------
	while (!glfwWindowShouldClose(app.window))
	{
		app.Update(shader.shaderProgram);
	}



	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//glBindBuffer(GL_ARRAY_BUFFER, 0);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	app.meshes.clear();

	glDeleteTextures(1, &texture.texture);

	glDeleteSamplers(1, &sampler);

	return 0;
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
