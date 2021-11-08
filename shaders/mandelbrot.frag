#version 430
precision highp float;

in vec2 v_texcoord;

out vec4 frag_color;

uniform int u_max_iterations;

vec4 get_color(int iterations, int max_iterations)
{
	float value = float(iterations) / float(max_iterations);
	vec4 color = vec4(1., 1., 1., 1.);

	vec4[7] colors =
	{
		vec4(0.25, 0., 0.5, 1.),
		vec4(0., 0., 1., 1.),
		vec4(0., 1., 1., 1.),
		vec4(1., 1., 1., 1.),
		vec4(1., 1., 0., 1.),
		vec4(1., 0., 0., 1.),
		vec4(0.25, 0., 0.5, 1.)
	};

	float min_value;
	float max_value;

	for (int i = 0; i < colors.length() - 1; i++)
	{
		min_value = float(i) / float(colors.length() - 1);
		max_value = float(i + 1) / float(colors.length() - 1);

		if (value >= min_value && value <= max_value)
		{
			color = mix(colors[i], colors[i + 1], (value - min_value) * float(colors.length() - 1));
			break;
		}
	}

	return color;
}

void main()
{
	vec2 number = vec2(0., 0.);
	vec2 c = v_texcoord;
	vec2 temp;
	int i = 0;

	while (length(number) < 2 && i < u_max_iterations)
	{
		temp = number;
		number.x = temp.x * temp.x - temp.y * temp.y + c.x;
		number.y = 2. * temp.x * temp.y + c.y;
		i++;
	}

	if (i == u_max_iterations)
		frag_color = vec4(0., 0., 0., 1.);
	else if (u_max_iterations <= 70)
		frag_color = get_color(i, u_max_iterations);
	else
		frag_color = get_color(i % (u_max_iterations / 10), u_max_iterations / 10);
}
