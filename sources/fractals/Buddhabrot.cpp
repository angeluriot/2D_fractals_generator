#include "Simulator.hpp"

Buddhabrot::Buddhabrot()
{
	reset();
}

Fractal::Type Buddhabrot::get_type() const
{
	return Type::Buddhabrot;
}

void Buddhabrot::menu()
{
	bool changed = false;

	ImGui::NewLine();

	ImGui::Text("The max iterations number:");
	changed = ImGui::SliderInt("##max_iteration", &max_iterations, 100, 10000, NULL, ImGuiSliderFlags_Logarithmic) || changed;

	ImGui::NewLine();

	ImGui::Text("The number of points:");
	changed = ImGui::SliderInt("##nb_points", &nb_points, 1000, 100000000, NULL, ImGuiSliderFlags_Logarithmic) || changed;

	ImGui::NewLine();

	ImGui::Text("The brightness of the points:");
	changed = ImGui::SliderFloat("##brightness", &brightness, 0.1f, 10.f, "%.2f", ImGuiSliderFlags_Logarithmic) || changed;

	if (changed)
		Simulator::image_done = false;
}

void Buddhabrot::reset()
{
	Simulator::position = { -0.25, 0. };
	max_iterations = 5000;
	nb_points = 300000;
	brightness = 1.f;
	image.reset(dim::Window::get_size().x, dim::Window::get_size().y);
}

void Buddhabrot::compute_color(const cl::Buffer& points_buffer, int color_id, int current_max_iterations)
{
	ComputeShader::choose_function("buddhabrot");
	ComputeShader::add_argument(image.buffer);
	ComputeShader::add_argument(points_buffer);
	ComputeShader::add_argument(current_max_iterations);
	ComputeShader::add_argument(nb_points);
	ComputeShader::add_argument(Simulator::position[0]);
	ComputeShader::add_argument(Simulator::position[1]);
	ComputeShader::add_argument(Simulator::area_width);

	double area_height = Simulator::area_width * ((double)dim::Window::get_size().y / (double)dim::Window::get_size().x);

	ComputeShader::add_argument(area_height);
	ComputeShader::add_argument(color_id);

	std::array<int, 2> screen_size = { dim::Window::get_size().x, dim::Window::get_size().y };

	ComputeShader::add_argument(screen_size);
	ComputeShader::add_argument(brightness);

	ComputeShader::launch(cl::NDRange(nb_points));
}

void Buddhabrot::compute()
{
	image.fill(dim::Color(0.f, 0.f, 0.f, 1.f));

	std::vector<std::array<double, 2>> points(nb_points);

	for (auto& p : points)
		p = { dim::random_float(-2.f, 0.5f), dim::random_float(-1.3f, 1.3f) };

	cl::Buffer points_buffer = ComputeShader::Buffer(points, Permissions::Read);

	Buddhabrot::compute_color(points_buffer, 0, max_iterations);

	image.update();
}
