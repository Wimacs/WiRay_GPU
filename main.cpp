#include <GL/glew.h>

#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#include "Application.h"
#include "Core/TriangleList.h"
#include "Utils/GLFWWindow.h"

int main(int argc, char* argv[])
{
	constexpr int width = 1280;
	constexpr int height = 720;

	using namespace utils;
	using namespace core;
	using namespace glm;

	auto window = GLFWWindow("WiRay_GPU", 1280, 720, false, false);
	window.setVsync(false);
	auto triangleList = TriangleList();

	const std::string sky = "Models/envmaps/grass.jpg";
	//Conferenceroom();
	//scenes define
	const auto mat = triangleList.addMaterial(Material::light(vec3(50)));
	std::string nanosuit = "Models/nanosuit/nanosuit.obj";
	std::string sponza = "Models/sponza/sponza.obj";
	std::string sphere = "Models/sphere1.obj";
	std::string dragon = "Models/dragon.obj";
	std::string cbox = "Models/cornellbox/CornellBox-Original.obj";
	std::string countryKitch = "Models/assets/country_kitchen/Country-Kitchen.obj";
	std::string cat = "Models/assets/egyptcat/egyptcat.obj";
	std::string luxball = "Models/assets/luxball/luxball.obj";
	std::string conference = "Models/conference/conference.obj";
	std::string teapot = "Models/teapot.obj";
	std::string waterCbox = "Models/cbox/CornellBox-Sphere.obj";
	std::string breakfast = "Models/breakfast_room/breakfast_room.obj";
	std::string san = "Models/san/san-miguel.obj";
	std::string light = "Models/light.obj";
	std::string living = "Models/living/living_room.obj";
	triangleList.loadModel(light, 2.0f, glm::translate(mat4(1.0f), vec3(0.0f, 3.5f, 0.0f)), mat);


	const auto fMat = triangleList.addMaterial(Material::fresnel(vec3(0.9), 1.0f));
	auto tempMat = Material::lambertian(vec3(1.f, .8f, .8f));
	const auto mMat = triangleList.addMaterial(tempMat);

	triangleList.loadModel(conference, 15.0f, glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f)));

	Material fuck = Material::specular(vec3(0.1, 0.2, 0.2), 0.2);
	Material m = Material::lambertian(vec3(0.8, 0.2, 0.2));
	const auto dragMat = triangleList.addMaterial(m);
	auto application = Application(&window, &triangleList);

	application.loadSkybox(sky);
	application.run();
}
