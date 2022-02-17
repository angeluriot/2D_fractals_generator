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
	changed = ImGui::SliderInt("##max_iteration", &max_iterations, 1, 10000, NULL, ImGuiSliderFlags_Logarithmic) || changed;

	ImGui::NewLine();

	ImGui::Text("The number of points:");
	changed = ImGui::SliderInt("##nb_points", &nb_points, 1, 10000000, NULL, ImGuiSliderFlags_Logarithmic) || changed;

	if (changed)
		Simulator::image_done = false;
}

void Buddhabrot::reset()
{
	max_iterations = 1000;
	nb_points = 10000;
	image.reset(dim::Window::get_size().x, dim::Window::get_size().y);
}

void Buddhabrot::compute()
{
	image.fill(dim::Color(0.f, 0.f, 0.f, 1.f));

	ComputeShader::choose_function("buddhabrot");
	ComputeShader::add_argument(image.buffer);

	std::vector<std::array<double, 2>> points(nb_points);

	for (auto& p : points)
		p = { dim::random_float(-2.f, 0.5f), dim::random_float(-1.3f, 1.3f) };

	cl::Buffer points_buffer = ComputeShader::Buffer(points, Permissions::Read);

	ComputeShader::add_argument(points_buffer);
	ComputeShader::add_argument(max_iterations);
	ComputeShader::add_argument(Simulator::position[0]);
	ComputeShader::add_argument(Simulator::position[1]);
	ComputeShader::add_argument(Simulator::area_width);

	double area_height = Simulator::area_width * ((double)dim::Window::get_size().y / (double)dim::Window::get_size().x);

	ComputeShader::add_argument(area_height);

	std::array<int, 2> screen_size = { dim::Window::get_size().x, dim::Window::get_size().y };

	ComputeShader::add_argument(screen_size);

	ComputeShader::launch(cl::NDRange(nb_points));

	image.update(dim::Window::get_size().x, dim::Window::get_size().y);
}