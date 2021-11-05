#include "Menu.hpp"
#include "Simulator.hpp"

bool			Menu::visible			= true;
bool			Menu::active			= false;
FractalType		Menu::fractal_type		= FractalType::Julia;

void Menu::check_events(const sf::Event& sf_event)
{
	if (sf_event.type == sf::Event::KeyReleased && sf_event.key.code == sf::Keyboard::Key::F1)
		visible = !visible;
}

void Menu::title(const std::string& text)
{
	float window_width = ImGui::GetWindowSize().x;
	float text_width = ImGui::CalcTextSize(text.data()).x;

	ImGui::NewLine();
	ImGui::SetCursorPosX((window_width - text_width) * 0.5f);
	ImGui::Text(text.data());
	ImGui::Separator();
}

std::vector<bool> Menu::centered_buttons(const std::vector<std::string> texts, float buttons_height, float spaces_size)
{
	float window_width = ImGui::GetWindowSize().x;
	float buttons_widths = (window_width - ((texts.size() + 2) * spaces_size)) / texts.size();
	std::vector<bool> result(texts.size());

	ImGui::NewLine();
	ImGui::NewLine();

	for (int i = 0; i < texts.size(); i++)
	{
		ImGui::SameLine();
		ImGui::SetCursorPosX(spaces_size + buttons_widths * i + spaces_size * i);
		ImGui::Text("");
		ImGui::SameLine();
		result[i] = ImGui::Button(texts[i].data(), ImVec2(buttons_widths, buttons_height));
	}

	return result;
}

void Menu::set_default_values()
{
	
}

void Menu::julia()
{
	
}

void Menu::mandelbrot()
{
	
}

void Menu::display()
{
	if (visible)
	{
		ImGui::Begin("Simulation settings (F1 to hide)");
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.9f);

		ImGui::NewLine();

		FractalType temp = fractal_type;

		ImGui::Text("The type of fractal");
		ImGui::Combo("##fractal_type", reinterpret_cast<int*>(&fractal_type), "Julia\0Mandelbrot");

		if (fractal_type != temp)
			set_default_values();

		active = ImGui::IsWindowFocused();

		ImGui::End();
	}
}
