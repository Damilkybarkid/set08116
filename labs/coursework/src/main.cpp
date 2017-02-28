#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;
effect eff;
texture tex;
texture tex2;
//target_camera cam;
free_camera cam2;

bool initialise() {
	// Set input mode - hide the cursor
	glfwSetInputMode(renderer::get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return true;
}
bool load_content() {
	// Create plane mesh
	meshes["plane"] = mesh(geometry_builder::create_plane());

	// Sphere
	meshes["sphere"] = mesh(geometry_builder::create_sphere(unsigned int(20), unsigned int(20)));

	// Table
	meshes["table"] = mesh(geometry("models/Table.obj"));

	// Chair
	meshes["chair"] = mesh(geometry("models/chair.obj"));

	// Set the transforms for your meshes here

	// plane
	meshes["plane"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);

	// Sphere
	meshes["sphere"].get_transform().scale = vec3(2.50f, 2.50f, 2.50f);
	meshes["sphere"].get_transform().position = vec3(-50.0f, 5.0f, -25.0f);

	// Table
	//meshes["table"].get_transform().position = vec3(-50.0f, 50.0f, -25.0f);
	//meshes["table"].get_transform().scale = vec3(1.0f, 1.0f, 1.0f);
	//meshes["table"].get_transform().rotate(vec3(135.0f, 5.0f, 0.0f));

	// Load texture
	tex = texture("textures/CGRright_202_color.jpg");
	tex2 = texture("textures/Wooden_Table_1_default.png");

	// Load in shaders
	eff.add_shader("shaders/coursework.vert", GL_VERTEX_SHADER);
	eff.add_shader("shaders/coursework.frag", GL_FRAGMENT_SHADER);
	// Build effect
	eff.build();

	// Set camera properties
	cam2.set_position(vec3(10.0f, 10.0f, 10.0f));
	cam2.set_target(vec3(-100.0f, 0.0f, -100.0f));
	auto aspect = static_cast<float>(renderer::get_screen_width()) / static_cast<float>(renderer::get_screen_height());
	cam2.set_projection(quarter_pi<float>(), aspect, 2.414f, 1000.0f);
	return true;
}


bool update(float delta_time) {
	//if (glfwGetKey(renderer::get_window(), '1')) {
		//cam.set_position(vec3(10.0f, 10.0f, 10.0f));
	//}
	//if (glfwGetKey(renderer::get_window(), '2')) {
		//cam.set_position(vec3(-10.0f, 10.0f, 10.0f));
	//}
	//if (glfwGetKey(renderer::get_window(), '3')) {
		//cam.set_position(vec3(-50, 10, -50));
	//}
	//if (glfwGetKey(renderer::get_window(), '4')) {
		//cam.set_position(vec3(50, 10, -50));
	//}
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
	cam2.rotate(delta_x, -delta_y);
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
	cam2.move(translation);
	// Update the camera
	cam2.update(delta_time);
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
		auto V = cam2.get_view();
		auto P = cam2.get_projection();
		auto MVP = P * V * M;
		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));
		// Set material colour 
		glUniform4fv(eff.get_uniform_location("material_colour"), 1, value_ptr(vec4(1.0f, 1.0f, 1.0f, 1.0f)));
		// Set ambient intensity - (0.3, 0.3, 0.3, 1.0)
		glUniform4fv(eff.get_uniform_location("ambient_intensity"), 1, value_ptr(vec4(0.1f, 0.1f, 0.1f, 0.1f)));
		// *********************************
		// Bind texture to renderer
		if (e.first == "plane")
		{
			renderer::bind(tex, 0);
		}
		else
		{
			renderer::bind(tex2, 0);
		}
		
		// Set the texture value for the shader here
		glUniform1i(eff.get_uniform_location("tex"), 0);
		glUniform1i(eff.get_uniform_location("tex2"), 1 );
		// *********************************
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
  application.set_initialise(initialise);
  application.set_update(update);
  application.set_render(render);
  // Run application
  application.run();
}