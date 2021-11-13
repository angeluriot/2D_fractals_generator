#include "Simulator.hpp"

Mandelbrot::Mandelbrot()
{
	reset();
}

Fractal::Type Mandelbrot::get_type() const
{
	return Type::Mandelbrot;
}

void Mandelbrot::menu()
{
	bool changed = false;

	ImGui::NewLine();

	ImGui::Text("The maximum number of iterations :");
	changed = ImGui::SliderInt("##max_iteration", &max_iterations, 1, 10000, NULL, ImGuiSliderFlags_Logarithmic) || changed;

	changed = ColorPallet::menu(pallet_index) || changed;

	if (changed)
		Simulator::image_done = false;
}

void Mandelbrot::reset()
{
	max_iterations = 100;
	pallet_index = 0;
}

void Mandelbrot::compute()
{
	ComputeShader::choose_function("mandelbrot");
	ComputeShader::add_argument(image.buffer);
	ComputeShader::add_argument(max_iterations);
	ComputeShader::add_argument(Simulator::position[0]);
	ComputeShader::add_argument(Simulator::position[1]);
	ComputeShader::add_argument(Simulator::area_width);

	double area_height = Simulator::area_width * (static_cast<double>(dim::Window::get_size().y) / static_cast<double>(dim::Window::get_size().x));

	ComputeShader::add_argument(area_height);

	cl::Buffer pallet = ComputeShader::Buffer(ColorPallet::pallets[pallet_index], Permissions::Read);
	int size;

	if (pallet_index == ColorPallet::rgb)
		size = -1;

	else if (pallet_index == ColorPallet::black_or_white)
		size = -2;

	else
		size = ColorPallet::pallets[pallet_index].size() - 1;

	ComputeShader::add_argument(pallet);
	ComputeShader::add_argument(size);

	ComputeShader::launch(cl::NDRange(dim::Window::get_size().x, dim::Window::get_size().y));

	image.update(dim::Window::get_size().x, dim::Window::get_size().y);
}
