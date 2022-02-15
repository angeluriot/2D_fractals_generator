#include "Simulator.hpp"

std::vector<std::vector<dim::Color>> ColorPallet::pallets =
{
	// Original
	{
		dim::Color(  0.f / 255.f,   7.f / 255.f, 100.f / 255.f, 1.f),
		dim::Color( 32.f / 255.f, 107.f / 255.f, 203.f / 255.f, 1.f),
		dim::Color(237.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.f),
		dim::Color(255.f / 255.f, 170.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(  0.f / 255.f,   2.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(  0.f / 255.f,   7.f / 255.f, 100.f / 255.f, 1.f)
	},

	// Fire
	{
		dim::Color( 20.f / 255.f,   0.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(255.f / 255.f,  20.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(255.f / 255.f, 200.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(255.f / 255.f,  20.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color( 20.f / 255.f,   0.f / 255.f,   0.f / 255.f, 1.f)
	},

	// Electric
	{
		dim::Color(  0.f / 255.f,   0.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(  0.f / 255.f,   0.f / 255.f, 200.f / 255.f, 1.f),
		dim::Color(255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.f),
		dim::Color(  0.f / 255.f,   0.f / 255.f, 200.f / 255.f, 1.f),
		dim::Color(  0.f / 255.f,   0.f / 255.f,   0.f / 255.f, 1.f)
	},

	// Gold
	{
		dim::Color( 85.f / 255.f,  47.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(255.f / 255.f, 171.f / 255.f,  12.f / 255.f, 1.f),
		dim::Color(255.f / 255.f, 247.f / 255.f, 127.f / 255.f, 1.f),
		dim::Color(255.f / 255.f, 171.f / 255.f,  12.f / 255.f, 1.f),
		dim::Color( 85.f / 255.f,  47.f / 255.f,   0.f / 255.f, 1.f)
	},

	// RGB gradient
	{
		dim::Color(255.f / 255.f,   0.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(255.f / 255.f, 255.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(  0.f / 255.f, 255.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(  0.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.f),
		dim::Color(  0.f / 255.f,   0.f / 255.f, 255.f / 255.f, 1.f),
		dim::Color(255.f / 255.f,   0.f / 255.f, 255.f / 255.f, 1.f),
		dim::Color(255.f / 255.f,   0.f / 255.f,   0.f / 255.f, 1.f)
	},

	// RGB
	{
		dim::Color(255.f / 255.f,   0.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(255.f / 255.f, 255.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(  0.f / 255.f, 255.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(  0.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.f),
		dim::Color(  0.f / 255.f,   0.f / 255.f, 255.f / 255.f, 1.f),
		dim::Color(255.f / 255.f,   0.f / 255.f, 255.f / 255.f, 1.f),
		dim::Color(255.f / 255.f,   0.f / 255.f,   0.f / 255.f, 1.f)
	},

	// Black and white gradient
	{
		dim::Color(  0.f / 255.f,   0.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.f),
		dim::Color(  0.f / 255.f,   0.f / 255.f,   0.f / 255.f, 1.f)
	},

	// Black or white
	{
		dim::Color(  0.f / 255.f,   0.f / 255.f,   0.f / 255.f, 1.f),
		dim::Color(255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.f),
		dim::Color(  0.f / 255.f,   0.f / 255.f,   0.f / 255.f, 1.f)
	},

	// Set only
	{
		dim::Color(255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.f),
		dim::Color(255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.f)
	}
};

bool ColorPallet::menu(int& index)
{
	ImGui::NewLine();
	ImGui::Text("The color pallet:");
	return ImGui::Combo("##color_pallet", &index, "Original\0Fire\0Electric\0Gold\0RGB gradient\0RGB\0Black and white gradient\0Black or white\0Set only", 9);
}
