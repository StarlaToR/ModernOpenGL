#include <App.h>;

using namespace Core;
using namespace Resources;

App::~App()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void App::Update(unsigned int shaderProgram)
{
	// input
		// -----
	glfwPollEvents();
	processInput();


	if (mouseOn)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// render
	// ------
	glClearColor(0.f, 0.f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	//glBindTexture(GL_TEXTURE_2D, texture);

	cam.Update();
	Mat4 projView = cam.GetProjectionMatrix() * cam.GetViewMatrix();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	glUseProgram(shaderProgram);

	ASSERT(directLights.size() + pointLights.size() + spotLights.size() > 8, "There are too many lights in the scene");

	ImGui::Begin("Control Panel");
	ImGui::Checkbox("Draw models", &drawOn);

	if (ImGui::Button("Add Cube"))
	{
		meshes.push_back(new LowRenderer::Mesh(manager->Get<Model>("cube"), Vec3(), Vec3(), Vec3(1, 1, 1), manager->Get<Texture>("catText")));
	}

	if (ImGui::Button("Add Point Light"))
	{
		pointLights.push_back(new LowRenderer::PointLight(Vec3(0, 0, 0), Vec3(1, 1, 1), 1, 0.022f, 0.0019f));
	}

	/*
	if (ImGui::Button("Add Directionnal Light"))
	{
		directLights.push_back(new LowRenderer::DirectionnalLight(Vec3(0, -1, 0), Vec3(1, 1, 1)));
	}
	*/
	if (ImGui::Button("Add Spot Light"))
	{
		spotLights.push_back(new LowRenderer::SpotLight(Vec3(0, -10, 0), Vec3(0, 0, 0), Vec3(1, 1, 1), 1, 0.022f, 0.0019f, M_PI / 4));
	}

	PointLightsToShaders(shaderProgram);
	DirectLightsToShaders(shaderProgram);
	SpotLightsToShaders(shaderProgram);

	if (drawOn)
	{
		stringstream mesh;
		stringstream rotationString;
		stringstream positionString;
		stringstream scaleString;

		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i]->Update(projView, shaderProgram);

			mesh << "Mesh " << i + 1;
			rotationString << "rotation" << i;
			positionString << "position " << i;
			scaleString << "scale " << i;

			if (ImGui::TreeNode(mesh.str().c_str()))
			{
				ImGui::SliderFloat3(rotationString.str().c_str(), meshes[i]->rotation, -2 * M_PI, 2 * M_PI);
				meshes[i]->SetRotation(Vec3(meshes[i]->rotation[0], meshes[i]->rotation[1], meshes[i]->rotation[2]));
				ImGui::SliderFloat3(positionString.str().c_str(), meshes[i]->position, -100, 100);
				meshes[i]->SetPosition(Vec3(meshes[i]->position[0], meshes[i]->position[1], meshes[i]->position[2]));
				ImGui::SliderFloat3(scaleString.str().c_str(), meshes[i]->scale, 0.0, 1);
				meshes[i]->SetScale(Vec3(meshes[i]->scale[0], meshes[i]->scale[1], meshes[i]->scale[2]));

				ImGui::TreePop();
				ImGui::Separator();
			}
				
			rotationString.str("");
			positionString.str("");
			scaleString.str("");
			mesh.str("");
		}
	}

	ImGui::Text("light");
	static float color[4] = { 1.0f,1.0f,1.0f,1.0f };
	ImGui::ColorEdit3("color", color);

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(window);
	
}

void App::PointLightsToShaders(unsigned int shaderProgram)
{
	stringstream pointLight;
	stringstream diffuseColor;
	stringstream ambientColor;
	stringstream specularColor;
	stringstream constant;
	stringstream linear;
	stringstream quadratic;
	stringstream lightPos;

	for (int i = 0; i < pointLights.size(); i++)
	{
		pointLight << "Point Light " << i;
		diffuseColor << "pointLights[" << i << "].diffuseColor";
		ambientColor << "pointLights[" << i << "].ambientColor";
		specularColor << "pointLights[" << i << "].specularColor";
		constant << "pointLights[" << i << "].constant";
		linear << "pointLights[" << i << "].linear";
		quadratic << "pointLights[" << i << "].quadratic";
		lightPos << "pointLights[" << i << "].position";

		if (ImGui::TreeNode(pointLight.str().c_str()))
		{
			ImGui::SliderFloat3(diffuseColor.str().c_str(), pointLights[i]->diffuseCol, 0, 1);
			pointLights[i]->diffuseColor = Vec3(pointLights[i]->diffuseCol[0], pointLights[i]->diffuseCol[1], pointLights[i]->diffuseCol[2]);
			ImGui::SliderFloat3(ambientColor.str().c_str(), pointLights[i]->ambientCol, 0, 1);
			pointLights[i]->ambientColor = Vec3(pointLights[i]->ambientCol[0], pointLights[i]->ambientCol[1], pointLights[i]->ambientCol[2]);
			ImGui::SliderFloat3(specularColor.str().c_str(), pointLights[i]->specularCol, 0.0, 1);
			pointLights[i]->specularColor = Vec3(pointLights[i]->specularCol[0], pointLights[i]->specularCol[1], pointLights[i]->specularCol[2]);
			ImGui::SliderFloat3(lightPos.str().c_str(), pointLights[i]->posit, 0.0, 100);
			pointLights[i]->position = Vec3(pointLights[i]->posit[0], pointLights[i]->posit[1], pointLights[i]->posit[2]);

			ImGui::TreePop();
			ImGui::Separator();
		}

		glUniform3f(glGetUniformLocation(shaderProgram, diffuseColor.str().c_str()), pointLights[i]->diffuseColor.x, pointLights[i]->diffuseColor.y, pointLights[i]->diffuseColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, ambientColor.str().c_str()), pointLights[i]->ambientColor.x, pointLights[i]->ambientColor.y, pointLights[i]->ambientColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, specularColor.str().c_str()), pointLights[i]->specularColor.x, pointLights[i]->specularColor.y, pointLights[i]->specularColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, lightPos.str().c_str()), pointLights[i]->position.x, pointLights[i]->position.y, pointLights[i]->position.z);

		glUniform1f(glGetUniformLocation(shaderProgram, constant.str().c_str()), pointLights[i]->constant);
		glUniform1f(glGetUniformLocation(shaderProgram, linear.str().c_str()), pointLights[i]->linear);
		glUniform1f(glGetUniformLocation(shaderProgram, quadratic.str().c_str()), pointLights[i]->quadratic);

		pointLight.str("");
		diffuseColor.str("");
		ambientColor.str("");
		specularColor.str("");
		lightPos.str("");
		constant.str("");
		linear.str("");
		quadratic.str("");
	}

	glUniform1i(glGetUniformLocation(shaderProgram, "pointLightCount"), pointLights.size());

}

void App::DirectLightsToShaders(unsigned int shaderProgram)
{
	stringstream directLight;
	stringstream diffuseColor;
	stringstream ambientColor;
	stringstream specularColor;
	stringstream lightDir;

	for (int i = 0; i < directLights.size(); i++)
	{
		directLight << "Direct Light " << i;
		diffuseColor << "directLights[" << i << "].diffuseColor";
		ambientColor << "directLights[" << i << "].ambientColor";
		specularColor << "directLights[" << i << "].specularColor";
		lightDir << "directLights[" << i << "].direction";

		/*
		if (ImGui::TreeNode(directLight.str().c_str()))
		{
			ImGui::SliderFloat3(diffuseColor.str().c_str(), directLights[i]->diffuseCol, -2 * M_PI, 2 * M_PI);
			directLights[i]->diffuseColor = Vec3(directLights[i]->diffuseCol[0], directLights[i]->diffuseCol[1], directLights[i]->diffuseCol[2]);
			ImGui::SliderFloat3(ambientColor.str().c_str(), directLights[i]->ambientCol, -100, 100);
			directLights[i]->ambientColor = Vec3(directLights[i]->ambientCol[0], directLights[i]->ambientCol[1], directLights[i]->ambientCol[2]);
			ImGui::SliderFloat3(specularColor.str().c_str(), directLights[i]->specularCol, 0.0, 1);
			directLights[i]->specularColor = Vec3(directLights[i]->specularCol[0], directLights[i]->specularCol[1], directLights[i]->specularCol[2]);
			ImGui::SliderFloat3(lightDir.str().c_str(), directLights[i]->direct, 0.0, 1);
			directLights[i]->direction = Vec3(directLights[i]->direct[0], directLights[i]->direct[1], directLights[i]->direct[2]);

			ImGui::TreePop();
			ImGui::Separator();
		}
		*/
		glUniform3f(glGetUniformLocation(shaderProgram, diffuseColor.str().c_str()), directLights[i]->diffuseColor.x, directLights[i]->diffuseColor.y, directLights[i]->diffuseColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, ambientColor.str().c_str()), directLights[i]->ambientColor.x, directLights[i]->ambientColor.y, directLights[i]->ambientColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, specularColor.str().c_str()), directLights[i]->specularColor.x, directLights[i]->specularColor.y, directLights[i]->specularColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, lightDir.str().c_str()), directLights[i]->direction.x, directLights[i]->direction.y, directLights[i]->direction.z);

		directLight.str("");
		diffuseColor.str("");
		ambientColor.str("");
		specularColor.str("");
		lightDir.str("");
	}

	glUniform1i(glGetUniformLocation(shaderProgram, "directLightCount"), directLights.size());

}

void App::SpotLightsToShaders(unsigned int shaderProgram)
{
	stringstream spotLight;
	stringstream diffuseColor;
	stringstream ambientColor;
	stringstream specularColor;
	stringstream constant;
	stringstream linear;
	stringstream quadratic;
	stringstream lightPos;
	stringstream lightDir;
	stringstream lightAng;

	for (int i = 0; i < spotLights.size(); i++)
	{
		spotLight << "Spot Light " << i;
		ambientColor << "spotLights[" << i << "].ambientColor";
		diffuseColor << "spotLights[" << i << "].diffuseColor";
		specularColor << "spotLights[" << i << "].specularColor";
		constant << "spotLights[" << i << "].constant";
		linear << "spotLights[" << i << "].linear";
		quadratic << "spotLights[" << i << "].quadratic";
		lightPos << "spotLights[" << i << "].position";
		lightDir << "spotLights[" << i << "].direction";
		lightAng << "spotLights[" << i << "].angle";

		if (ImGui::TreeNode(spotLight.str().c_str()))
		{
			ImGui::SliderFloat3(diffuseColor.str().c_str(), spotLights[i]->diffuseCol, 0, 1);
			spotLights[i]->diffuseColor = Vec3(spotLights[i]->diffuseCol[0], spotLights[i]->diffuseCol[1], spotLights[i]->diffuseCol[2]);
			ImGui::SliderFloat3(ambientColor.str().c_str(), spotLights[i]->ambientCol, 0, 1);
			spotLights[i]->ambientColor = Vec3(spotLights[i]->ambientCol[0], spotLights[i]->ambientCol[1], spotLights[i]->ambientCol[2]);
			ImGui::SliderFloat3(specularColor.str().c_str(), spotLights[i]->specularCol, 0.0, 1);
			spotLights[i]->specularColor = Vec3(spotLights[i]->specularCol[0], spotLights[i]->specularCol[1], spotLights[i]->specularCol[2]);
			ImGui::SliderFloat3(lightDir.str().c_str(), spotLights[i]->direct, 0.0, 360);
			spotLights[i]->direction = Vec3(spotLights[i]->direct[0], spotLights[i]->direct[1], spotLights[i]->direct[2]);
			ImGui::SliderFloat3(lightPos.str().c_str(), spotLights[i]->posit, 0.0, 100);
			spotLights[i]->position = Vec3(spotLights[i]->posit[0], spotLights[i]->posit[1], spotLights[i]->posit[2]);
			ImGui::SliderAngle(lightAng.str().c_str(), &spotLights[i]->angl, 0, 60);
			spotLights[i]->angle = DegToRad(spotLights[i]->angl);

			ImGui::TreePop();
			ImGui::Separator();
		}

		glUniform3f(glGetUniformLocation(shaderProgram, diffuseColor.str().c_str()), spotLights[i]->diffuseColor.x, spotLights[i]->diffuseColor.y, spotLights[i]->diffuseColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, ambientColor.str().c_str()), spotLights[i]->ambientColor.x, spotLights[i]->ambientColor.y, spotLights[i]->ambientColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, specularColor.str().c_str()), spotLights[i]->specularColor.x, spotLights[i]->specularColor.y, spotLights[i]->specularColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, lightPos.str().c_str()), spotLights[i]->position.x, spotLights[i]->position.y, spotLights[i]->position.z);
		glUniform3f(glGetUniformLocation(shaderProgram, lightDir.str().c_str()), spotLights[i]->direction.x, spotLights[i]->direction.y, spotLights[i]->direction.z);

		glUniform1f(glGetUniformLocation(shaderProgram, constant.str().c_str()), spotLights[i]->constant);
		glUniform1f(glGetUniformLocation(shaderProgram, linear.str().c_str()), spotLights[i]->linear);
		glUniform1f(glGetUniformLocation(shaderProgram, quadratic.str().c_str()), spotLights[i]->quadratic);
		glUniform1f(glGetUniformLocation(shaderProgram, lightAng.str().c_str()), spotLights[i]->angle);

		diffuseColor.str("");
		ambientColor.str("");
		specularColor.str("");
		lightPos.str("");
		lightDir.str(""); 
		constant.str("");
		linear.str("");
		quadratic.str("");
		lightAng.str("");
		spotLight.str("");
	}

	glUniform1i(glGetUniformLocation(shaderProgram, "spotLightCount"), spotLights.size());
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

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		mouseOn = true;
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		cam.MouseDirection(xpos, ypos);
	}
	else
	{
		mouseOn = false;
		cam.camForward = cam.oldDirection;
		cam.firstMouse = true;
	}
}