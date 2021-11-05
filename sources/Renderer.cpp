#include "Renderer.hpp"
#include "Simulator.hpp"

void Renderer::init()
{
	dim::Shader::add("julia", "julia.vert", "julia.frag");
}

void Renderer::change_type()
{
	
}

void Renderer::check_events(const sf::Event& sf_event)
{
	if (sf_event.type == sf::Event::Resized)
	{
		
	}
}

void Renderer::clear()
{
	
}

void Renderer::draw()
{

}
