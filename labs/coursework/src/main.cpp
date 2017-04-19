#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;
effect eff;
texture tex;
texture tex2;
texture tex3;
texture tex4;
free_camera cam;
point_light light;

bool load_content() {
	// Create plane mesh
	meshes["floor_plane"] = mesh(geometry_builder::create_plane());

	// Create sphere mesh
	meshes["sphere"] = mesh(geometry_builder::create_sphere(unsigned int(20), unsigned int(20)));

	// Create table mesh - 4 legs and the top
	meshes["table_leg1"] = mesh(geometry_builder::create_cylinder(unsigned int(20), unsigned int(20)));
	meshes["table_leg2"] = mesh(geometry_builder::create_cylinder(unsigned int(20), unsigned int(20)));
	meshes["table_leg3"] = mesh(geometry_builder::create_cylinder(unsigned int(20), unsigned int(20)));
	meshes["table_leg4"] = mesh(geometry_builder::create_cylinder(unsigned int(20), unsigned int(20)));
	meshes["table_top"] = mesh(geometry_builder::create_box());

	// Create chair mesh
	meshes["chair"] = mesh(geometry("models/chair.obj"));

	// Set transforms for meshes and emissive, diffuse, specular and shininess values

	// plane
	meshes["floor_plane"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);

	// sphere
	meshes["sphere"].get_transform().scale = vec3(2.50f, 2.50f, 2.50f);
	meshes["sphere"].get_transform().position = vec3(-12.5f, 21.0f, 2.5f);
	meshes["sphere"].get_material().set_emissive(vec4(1.0f, 1.0f, 0.0f, 1.0f));
	meshes["sphere"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["sphere"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["sphere"].get_material().set_shininess(25.0f);

	// table
	meshes["table_leg1"].get_transform().scale = vec3(2.5f, 18.0f, 2.5f);
	meshes["table_leg1"].get_transform().position = vec3(-25.0f, 9.0f, -15.0f);
	meshes["table_leg1"].get_material().set_emissive(vec4(0.25f, 0.25f, 0.25f, 1.0f));
	meshes["table_leg1"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["table_leg1"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["table_leg1"].get_material().set_shininess(25.0f);

	meshes["table_leg2"].get_transform().scale = vec3(2.5f, 18.0f, 2.5f);
	meshes["table_leg2"].get_transform().position = vec3(0.0f, 9.0f, -15.0f);
	meshes["table_leg2"].get_material().set_emissive(vec4(0.25f, 0.25f, 0.25f, 1.0f));
	meshes["table_leg2"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["table_leg2"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["table_leg2"].get_material().set_shininess(25.0f);

	meshes["table_leg3"].get_transform().scale = vec3(2.5f, 18.0f, 2.5f);
	meshes["table_leg3"].get_transform().position = vec3(-25.0f, 9.0f, 20.0f);
	meshes["table_leg3"].get_material().set_emissive(vec4(0.25f, 0.25f, 0.25f, 1.0f));
	meshes["table_leg3"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["table_leg3"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["table_leg3"].get_material().set_shininess(25.0f);

	meshes["table_leg4"].get_transform().scale = vec3(2.5f, 18.0f, 2.5f);
	meshes["table_leg4"].get_transform().position = vec3(0.0f, 9.0f, 20.0f);
	meshes["table_leg4"].get_material().set_emissive(vec4(0.25f, 0.25f, 0.25f, 1.0f));
	meshes["table_leg4"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["table_leg4"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["table_leg4"].get_material().set_shininess(25.0f);

	meshes["table_top"].get_transform().scale = vec3(29.5f, 2.5f, 40.0f);
	meshes["table_top"].get_transform().position = vec3(-12.5f, 17.0f, 2.5f);
	meshes["table_top"].get_material().set_emissive(vec4(0.25f, 0.25f, 0.25f, 1.0f));
	meshes["table_top"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["table_top"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["table_top"].get_material().set_shininess(25.0f);

	// chair
	meshes["chair"].get_transform().position = vec3(-8.0f, 10.5f, -30.0f);
	meshes["chair"].get_material().set_emissive(vec4(0.25f, 0.25f, 0.25f, 1.0f));
	meshes["chair"].get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["chair"].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes["chair"].get_material().set_shininess(25.0f);

	// Load textures
	tex = texture("textures/seamless_24_pvqcu.jpg");
	tex2 = texture("textures/wood_plain_210_251_Small.jpg");
	tex3 = texture("textures/wood_plain_211_252_Small.jpg");
	tex4 = texture("textures/morning_sun_texture_by_xjillvalentinex-d5v1668.jpg");

	// Set lighting values

	// Position
	light.set_position(vec3(-12.5, 24.5, 2.5));
	// Light colour white
	light.set_light_colour(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	// Set range 
	light.set_range(500);

	// Load in shaders
	eff.add_shader("shaders/coursework.vert", GL_VERTEX_SHADER);
	eff.add_shader("shaders/coursework.frag", GL_FRAGMENT_SHADER);
	// Build effect
	eff.build();

	// Set camera properties
	cam.set_position(vec3(10.0f, 10.0f, 10.0f));
	cam.set_target(vec3(-100.0f, 0.0f, -100.0f));
	auto aspect = static_cast<float>(renderer::get_screen_width()) / static_cast<float>(renderer::get_screen_height());
	cam.set_projection(quarter_pi<float>(), aspect, 2.414f, 1000.0f);
	glfwSetInputMode(renderer::get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return true;
}


bool update(float delta_time) {
	// Set free cam details

	// The ratio of pixels to rotation - remember the fov
	static double ratio_width = quarter_pi<float>() / static_cast<float>(renderer::get_screen_width());
	static double ratio_height =
		(quarter_pi<float>() * renderer::get_screen_aspect()) / static_cast<float>(renderer::get_screen_height());
	static double cursor_x = 0.0;
	static double cursor_y = 0.0;
	double current_x;
	double current_y;
	// Get the current cursor position
	glfwGetCursorPos(renderer::get_window(), &current_x, &current_y);
	// Calculate delta of cursor positions from last frame
	double delta_x = current_x - cursor_x;
	double delta_y = current_y - cursor_y;
	// Multiply deltas by ratios - gets actual change in orientation
	delta_x *= ratio_width;
	delta_y *= ratio_height;
	// Rotate cameras by delta
	cam.rotate(delta_x, -delta_y);
	// Use keyboard to move the camera - WASD
	vec3 translation(0.0f, 0.0f, 0.0f);
	if (glfwGetKey(renderer::get_window(), 'W')) {
		translation.z += 50.0f * delta_time;
	}
	if (glfwGetKey(renderer::get_window(), 'S')) {
		translation.z -= 50.0f * delta_time;
	}
	if (glfwGetKey(renderer::get_window(), 'A')) {
		translation.x -= 50.0f * delta_time;
	}
	if (glfwGetKey(renderer::get_window(), 'D')) {
		translation.x += 50.0f * delta_time;
	}
	// Move camera
	cam.move(translation);
	// Update the camera
	cam.update(delta_time);
	// Update cursor pos
	cursor_x = current_x;
	cursor_y = current_y;
	return true;
}

bool render() {
	// Render meshes
	for (auto &e : meshes) {
		auto m = e.second;
		// Bind effect
		renderer::bind(eff);
		// Create MVP matrix
		auto M = m.get_transform().get_transform_matrix();
		auto V = cam.get_view();
		auto P = cam.get_projection();
		auto MVP = P * V * M;
		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));
		// Set M matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("M"), 1, GL_FALSE, value_ptr(M));
		// Set N matrix uniform 
		glUniformMatrix3fv(eff.get_uniform_location("N"), 1, GL_FALSE, value_ptr(m.get_transform().get_normal_matrix()));
		// Bind material
		renderer::bind(m.get_material(), "mat");
		// Bind light
		renderer::bind(light, "point");

		// Bind textures to renderer
		if (e.first == "floor_plane")
		{
			renderer::bind(tex, 0);
		}
		else
		{
			renderer::bind(tex2, 0);
		}
		if (e.first == "chair")
		{
			renderer::bind(tex3, 0);
		}
		if (e.first == "sphere")
		{
			renderer::bind(tex4, 0);
		}

		// Set texture values for shader
		glUniform1i(eff.get_uniform_location("tex"), 0);
		glUniform1i(eff.get_uniform_location("tex2"), 1);
		glUniform1i(eff.get_uniform_location("tex3"), 2);
		glUniform1i(eff.get_uniform_location("tex4"), 3);

		// Render mesh
		renderer::render(m);
	}
	return true;
}

void main() {
  // Create application
  app application("Graphics Coursework");
  // Set load content, update and render methods
  application.set_load_content(load_content);
  application.set_update(update);
  application.set_render(render);
  // Run application
  application.run();
}