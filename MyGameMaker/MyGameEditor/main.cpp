#include <iostream>

//assimp
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h>

//imgui
#include "MyGUI.h"

//opengl
#include "MyGameEngine/Renderer.h"

//engine
#include "MyGameEngine/Engine.h"

//modules
#include "MyGameEngine/MyWindow.h"
#include "MyGameEngine/Input.h"

//utils
#include "MyGameEngine/Camera.h"
#include "MyGameEngine/Texture.h"
#include "MyGameEngine/Shader.h"

//panels
#include "Panel.h"
#include "PanelConsole.h"

using namespace std;

static Camera camera;

struct BakerHouse {
	Transform transform;

	vector<vector<vec3>> vertex_positions;
	vector<vector<vec2>> vertex_texCoords;
	vector<vector<unsigned int>> index_data;

	std::unique_ptr<Shader> m_Shader;
	vector<unsigned int> vBPosID, vBTCoordsID, iBID, vA;
	std::unique_ptr<Texture> m_Texture;

	unsigned int numM = 0;

	void LoadFBX(const std::string& pFile) {
		// Create an instance of the Importer class
		Assimp::Importer importer;

		// And have it read the given file with some example postprocessing
		// Usually - if speed is not the most important aspect for you - you'll
		// probably to request more postprocessing than we do in this example.
		const aiScene* scene = importer.ReadFile(pFile,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		// If the import failed, report it
		if (nullptr == scene) {
			cout << importer.GetErrorString() << endl;
		}
		else {

			numM = scene->mNumMeshes;
			vertex_positions.resize(numM);
			vertex_texCoords.resize(numM);
			index_data.resize(numM);

			for (unsigned int i = 0; i < numM; i++) {
				aiMesh* mesh = scene->mMeshes[i];
				std::cout << "Malla " << i << ": " << mesh->mName.C_Str() << std::endl;

				for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
					aiVector3D vertex = mesh->mVertices[j];
					vec3 aux = vec3(vertex.x, vertex.y, vertex.z);	
					vertex_positions[i].push_back(aux);

					// Coordenadas UV (si existen)
					if (mesh->mTextureCoords[0]) {  // Comprueba si hay UVs
						aiVector3D uv = mesh->mTextureCoords[0][j];
						aux.x = uv.x;  // Solo X y Y
						aux.y = 1.0f - uv.y;
					}
					vertex_texCoords[i].push_back(aux);
				}

				for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
					aiFace face = mesh->mFaces[j];
					for (unsigned int k = 0; k < face.mNumIndices; k++) {
						index_data[i].push_back(face.mIndices[k]);
					}
				}

				unsigned int auxVBPosID, auxVBTCoordsID, auxIBID, auxVA;

				glGenVertexArrays(1, &auxVA);
				glBindVertexArray(auxVA);

				//buffer de positions
				glGenBuffers(1, &auxVBPosID);
				glBindBuffer(GL_ARRAY_BUFFER, auxVBPosID);
				glBufferData(GL_ARRAY_BUFFER, vertex_positions[i].size() * sizeof(vec3), vertex_positions[i].data(), GL_STATIC_DRAW);

				//position layout
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(vec3), (const void*)0);

				//buffer de coordenades de textura
				glGenBuffers(1, &auxVBTCoordsID);
				glBindBuffer(GL_ARRAY_BUFFER, auxVBTCoordsID);
				glBufferData(GL_ARRAY_BUFFER, vertex_texCoords[i].size() * sizeof(vec3), vertex_texCoords[i].data(), GL_STATIC_DRAW);

				//tex coord layout
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, sizeof(vec2), (const void*)0);

				glCreateBuffers(1, &auxIBID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, auxIBID);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data[i].size() * sizeof(unsigned int), index_data[i].data(), GL_STATIC_DRAW);

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				vBPosID.push_back(auxVBPosID);			//buffer de posicions
				vBTCoordsID.push_back(auxVBTCoordsID);  //buffer de coordenades de textura
				iBID.push_back(auxIBID);			    //buffer d'indexs
				vA.push_back(auxVA);					//vertex array
			}

			m_Shader = std::make_unique<Shader>("../MyGameEngine/Basic.shader");

		}
	}

	void draw() const {

		for (unsigned int i = 0; i < numM; i++) {
			glBindVertexArray(vA[i]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBID[i]);

			m_Texture->Bind();

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", (glm::mat4)camera.projection() * (glm::mat4)camera.view() * (glm::mat4)transform.mat());
			m_Shader->SetUniform1i("u_Texture", 0);

			glDrawElements(GL_TRIANGLES, index_data[i].size(), GL_UNSIGNED_INT, nullptr);

			m_Shader->UnBind();
			m_Texture->Unbind();

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
	}

};

static BakerHouse bakerHouse;

static void drawFloorGrid(int size, double step) {
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	for (double i = -size; i <= size; i += step) {
		glVertex3d(i, 0, -size);
		glVertex3d(i, 0, size);
		glVertex3d(-size, 0, i);
		glVertex3d(size, 0, i);
	}
	glEnd();
}

static void display_func() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw floor grid
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(&camera.view()[0][0]);

	drawFloorGrid(16, 0.25);

	//draw house
	bakerHouse.draw();
}

static void init_opengl() {
	glewInit();
	if (!GLEW_VERSION_3_0) throw exception("OpenGL 3.0 API is not available.");
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 0.5, 1.0);
}

static void reshape_func(int width, int height) {
	glViewport(0, 0, width, height);
	camera.aspect = static_cast<double>(width) / height;
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(&camera.projection()[0][0]);
}

bool rightMouse = false;
int lastMouseX = -1;
int lastMouseY = -1;
int mouseX = 0;
int mouseY = 0;
float yaw = 0.0f;
float pitch = 0.0f;

int main(int argc, char* argv[]) {
	//start engine
	Engine& engine = Engine::Instance();
	engine.Awake();
	engine.Start();

	//start opengl
	init_opengl();

	//start imgui
	MyGUI gui(engine.window->windowPtr(), engine.window->contextPtr());
	engine.input->SetEventProcessor(&gui);

	//Panels
	PanelConsole console(PanelType::CONSOLE, "Console");
	

	// Init camera
	camera.transform().pos() = vec3(0, 1, 4);
	camera.transform().rotate(glm::radians(180.0), vec3(0, 1, 0));

	// Load house
	bakerHouse.m_Texture = std::make_unique<Texture>("../MyGameEngine/Baker_house.png");
	bakerHouse.LoadFBX("../MyGameEngine/BakerHouse.fbx");
	bakerHouse.transform.pos() = vec3(0, 0, 0);

	while (engine.input->GetWindowEvent(WE_QUIT) != true) {

		display_func();
		reshape_func(engine.window->width(), engine.window->height());

		engine.input->PreUpdate();

		//camera movement
		if (engine.input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			camera.transform().translate(vec3(0, 0, 0.05)); 
		}
		if (engine.input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			camera.transform().translate(vec3(0.05, 0, 0));
		}
		if (engine.input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			camera.transform().translate(vec3(0, 0, -0.05));
		}
		if (engine.input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			camera.transform().translate(vec3(-0.05, 0, 0));
		}

		//camera rotation
		if (engine.input->GetMouseButtonDown(3) == KEY_DOWN) {
			rightMouse = true;
			engine.input->GetMousePosition(lastMouseX, lastMouseY);
		}
		else if (engine.input->GetMouseButtonDown(3) == KEY_UP) {
			rightMouse = false;
		}

		if (rightMouse) {
			engine.input->GetMousePosition(mouseX, mouseY);

			float dx = (float)(mouseX - lastMouseX);
			float dy = (float)(mouseY - lastMouseY);

			// Ajusta la sensibilidad
			float sensitivity = 0.5f;
			dx *= sensitivity;
			dy *= sensitivity;

			yaw = glm::degrees(atan2(camera.transform().fwd().z, camera.transform().fwd().x));
			pitch = glm::degrees(atan2(camera.transform().fwd().y, glm::sqrt(camera.transform().fwd().x * camera.transform().fwd().x + camera.transform().fwd().z * camera.transform().fwd().z)));

			yaw += dx;
			pitch -= dy;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

			//actualizo el vector forward de la camera
			camera.transform().setFwd(glm::normalize(direction));
			//uso vec3(0,1,0) porque busco el vector up en coordenadas world!!! igualmente acutalizo el vector up(local) de la camera
			camera.transform().setRigth(glm::normalize(glm::cross(vec3(0, 1, 0), camera.transform().fwd())));
			camera.transform().setUp(glm::normalize(glm::cross(camera.transform().fwd(), camera.transform().right())));

			engine.input->GetMousePosition(lastMouseX, lastMouseY);
		}

		gui.render();

		engine.window->swapBuffers();

	}

	return 0;
}