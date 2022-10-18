#if defined(cl_khr_fp64)
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#define DOUBLE_SUPPORT_AVAILABLE
#elif defined(cl_amd_fp64)
#pragma OPENCL EXTENSION cl_amd_fp64 : enable
#define DOUBLE_SUPPORT_AVAILABLE
#endif

#if defined(DOUBLE_SUPPORT_AVAILABLE)

// double
typedef double real_t;
typedef double2 real2_t;
typedef double3 real3_t;
typedef double4 real4_t;
typedef double8 real8_t;
typedef double16 real16_t;
#define PI 3.14159265358979323846

#else

// float
typedef float real_t;
typedef float2 real2_t;
typedef float3 real3_t;
typedef float4 real4_t;
typedef float8 real8_t;
typedef float16 real16_t;
#define PI 3.14159265359f

#endif

float modulo(float a, float b)
{
	return a - b * floor(a / b);
}

real_t modulus_2(real2_t z)
{
	return z.x * z.x + z.y * z.y;
}

real_t modulus(real2_t z)
{
	return sqrt(z.x * z.x + z.y * z.y);
}

real_t argument_from_modulus(real2_t z, real_t mod)
{
	if (mod == 0.)
		return 0.;

	if (z.y >= 0.)
		return acos(z.x / mod);

	else
		return 2. * PI - acos(z.x / mod);
}

real_t argument(real2_t z)
{
	return argument_from_modulus(z, modulus(z));
}

real2_t add(real2_t z_1, real2_t z_2)
{
	return (real2_t)(z_1.x + z_2.x, z_1.y + z_2.y);
}

real2_t add_3(real2_t z_1, real2_t z_2, real2_t z_3)
{
	return add(add(z_1, z_2), z_3);
}

real2_t subtract(real2_t z_1, real2_t z_2)
{
	return (real2_t)(z_1.x - z_2.x, z_1.y - z_2.y);
}

real2_t multiply(real2_t z_1, real2_t z_2)
{
	return (real2_t)(z_1.x * z_2.x - z_1.y * z_2.y, z_1.x * z_2.y + z_1.y * z_2.x);
}

real2_t real_multiply(real2_t z, real_t n)
{
	return (real2_t)(z.x * n, z.y * n);
}

real2_t multiply_3(real2_t z_1, real2_t z_2, real2_t z_3)
{
	return multiply(multiply(z_1, z_2), z_3);
}

real2_t divide(real2_t z_1, real2_t z_2)
{
	real_t mod_2 = modulus_2(z_2);

	if (mod_2 == 0.)
		return (real2_t)(0., 0.);

	return (real2_t)((z_1.x * z_2.x + z_1.y * z_2.y) / mod_2, (z_1.y * z_2.x - z_1.x * z_2.y) / mod_2);
}

real2_t real_divide(real2_t z, real_t n)
{
	return (real2_t)(z.x / n, z.y / n);
}

real2_t square(real2_t z)
{
	return multiply(z, z);
}

float4 get_color(float iterations, float max_iterations, float4* pallet, int colors_nb)
{
	float value = iterations / max_iterations;
	float4 color = (float4)(1.f, 1.f, 1.f, 1.f);

	float min_value;
	float max_value;

	for (int i = 0; i < (int)colors_nb; i++)
	{
		min_value = (float)i / colors_nb;
		max_value = (float)(i + 1) / colors_nb;

		if (value >= min_value && value <= max_value)
		{
			color = mix(pallet[i], pallet[i + 1], (value - min_value) * colors_nb);
			break;
		}
	}

	return color;
}

__kernel void julia(__global float4* pixels, float c_r, float c_i, int max_iterations, real_t position_x, real_t position_y,
	real_t width, real_t height, __global float4* pallet, int colors_nb, float color_range, float color_shift, int smooth)
{
	real2_t number = (real2_t)(0., 0.);
	real2_t c = (real2_t)(c_r, c_i);
	real2_t temp = (real2_t)(0., 0.);
	int i = 0;
	float4 color = (float4)(0.f, 0.f, 0.f, 0.f);
	float color_mod = (float)max_iterations * 0.01f * color_range;

	number.x = ((real_t)get_global_id(0) / (real_t)get_global_size(0)) * width + position_x - width / 2.;
	number.y = ((real_t)(get_global_size(1) - 1 - get_global_id(1)) / (real_t)get_global_size(1)) * height + position_y - height / 2.;
	real_t smooth_value = exp(-length(number));

	float max_modulus;

	if (smooth == 1)
		max_modulus = 1000.f;
	else
		max_modulus = 4.f;

	while (modulus_2(number) < max_modulus && i < max_iterations)
	{
		temp = number;
		number.x = temp.x * temp.x - temp.y * temp.y + c.x;
		number.y = 2. * temp.x * temp.y + c.y;
		i++;
		smooth_value += exp(-length(number));
	}

	int shifted_i = (int)(i + color_shift * (int)((float)max_iterations / color_mod)) % max_iterations;
	real_t shifted_smooth_value = (int)(floor(smooth_value) + color_shift * (int)((float)max_iterations / color_mod)) % max_iterations + (smooth_value - floor(smooth_value));

	if (i == max_iterations)
		color = (float4)(0.f, 0.f, 0.f, 1.f);
	else if (colors_nb == -1)
		color = get_color(i % 6, 6, pallet, 6);
	else if (colors_nb == -2)
		color = get_color(i % 2, 2, pallet, 2);
	else if (smooth == 1)
		color = get_color(modulo((float)shifted_smooth_value, (float)max_iterations / color_mod), (float)max_iterations / color_mod, pallet, colors_nb);
	else
		color = get_color(shifted_i % (max_iterations / (int)color_mod), max_iterations / (int)color_mod, pallet, colors_nb);

	pixels[get_global_id(1) * get_global_size(0) + get_global_id(0)] = color;
}

__kernel void mandelbrot(__global float4* pixels, int max_iterations, real_t position_x, real_t position_y,
	real_t width, real_t height, __global float4* pallet, int colors_nb, float color_range, float color_shift, int smooth)
{
	real2_t number = (real2_t)(0., 0.);
	real2_t c = (real2_t)(0., 0.);
	real2_t temp = (real2_t)(0., 0.);
	int i = 0;
	float4 color = (float4)(0.f, 0.f, 0.f, 0.f);
	real_t mod = (real_t)(0.);
	real_t arg = (real_t)(0.);
	float color_mod = (float)max_iterations * 0.01f * color_range;

	c.x = ((real_t)get_global_id(0) / (real_t)get_global_size(0)) * width + position_x - width / 2.;
	c.y = ((real_t)(get_global_size(1) - 1 - get_global_id(1)) / (real_t)get_global_size(1)) * height + position_y - height / 2.;

	float max_modulus;

	if (smooth == 1)
		max_modulus = 1000.f;
	else
		max_modulus = 4.f;

	while (modulus_2(number) < max_modulus && i < max_iterations)
	{
		temp = number;
		number.x = temp.x * temp.x - temp.y * temp.y + c.x;
		number.y = 2. * temp.x * temp.y + c.y;
		i++;
	}

	float smooth_value = (float)i + 1. - log(log(length(number))) / log(2.);
	int shifted_i = (int)(i + color_shift * (int)((float)max_iterations / color_mod)) % max_iterations;
	real_t shifted_smooth_value = (int)(floor(smooth_value) + color_shift * (int)((float)max_iterations / color_mod)) % max_iterations + (smooth_value - floor(smooth_value));

	if (i == max_iterations)
		color = (float4)(0.f, 0.f, 0.f, 1.f);
	else if (colors_nb == -1)
		color = get_color(i % 6, 6, pallet, 6);
	else if (colors_nb == -2)
		color = get_color(i % 2, 2, pallet, 2);
	else if (smooth == 1)
		color = get_color(modulo(shifted_smooth_value, (float)max_iterations / color_mod), (float)max_iterations / color_mod, pallet, colors_nb);
	else
		color = get_color(shifted_i % (max_iterations / (int)color_mod), max_iterations / (int)color_mod, pallet, colors_nb);

	pixels[get_global_id(1) * get_global_size(0) + get_global_id(0)] = color;
}

__kernel void burning_ship(__global float4* pixels, int max_iterations, real_t position_x, real_t position_y,
	real_t width, real_t height, __global float4* pallet, int colors_nb, float color_range, float color_shift, int smooth)
{
	real2_t number = (real2_t)(0., 0.);
	real2_t c = (real2_t)(0., 0.);
	real2_t temp = (real2_t)(0., 0.);
	int i = 0;
	float4 color = (float4)(0.f, 0.f, 0.f, 0.f);
	float color_mod = (float)max_iterations * 0.01f * color_range;

	c.x = ((real_t)get_global_id(0) / (real_t)get_global_size(0)) * width + position_x - width / 2.;
	c.y = -(((real_t)(get_global_size(1) - 1 - get_global_id(1)) / (real_t)get_global_size(1)) * height + position_y - height / 2.);

	float max_modulus;

	if (smooth == 1)
		max_modulus = 1000.f;
	else
		max_modulus = 4.f;

	while (modulus_2(number) < max_modulus && i < max_iterations)
	{
		number.x = fabs(number.x);
		number.y = fabs(number.y);
		temp = number;
		number.x = temp.x * temp.x - temp.y * temp.y + c.x;
		number.y = 2. * temp.x * temp.y + c.y;
		i++;
	}

	float smooth_value = (float)i + 1. - log(log(length(number))) / log(2.);
	int shifted_i = (int)(i + color_shift * (int)((float)max_iterations / color_mod)) % max_iterations;
	real_t shifted_smooth_value = (int)(floor(smooth_value) + color_shift * (int)((float)max_iterations / color_mod)) % max_iterations + (smooth_value - floor(smooth_value));

	if (i == max_iterations)
		color = (float4)(0.f, 0.f, 0.f, 1.f);
	else if (colors_nb == -1)
		color = get_color(i % 6, 6, pallet, 6);
	else if (colors_nb == -2)
		color = get_color(i % 2, 2, pallet, 2);
	else if (smooth == 1)
		color = get_color(modulo(shifted_smooth_value, (float)max_iterations / color_mod), (float)max_iterations / color_mod, pallet, colors_nb);
	else
		color = get_color(shifted_i % (max_iterations / (int)color_mod), max_iterations / (int)color_mod, pallet, colors_nb);

	pixels[get_global_id(1) * get_global_size(0) + get_global_id(0)] = color;
}

void set_pixel(float4* pixels, int2 pos, int2 screen_size, int i, int max_iterations, int nb_points, float brightness)
{
	if (pos.x >= 0 && pos.x < screen_size.x && pos.y >= 0 && pos.y < screen_size.y)
	{
		if (i <= max_iterations / 100)
			pixels[pos.y * screen_size.x + pos.x].z += (brightness * 55000.f) / nb_points;
		else if (i <= max_iterations / 10)
			pixels[pos.y * screen_size.x + pos.x].y += (brightness * 50000.f) / nb_points;
		else
			pixels[pos.y * screen_size.x + pos.x].x += (brightness * 70000.f) / nb_points;
	}
}

__kernel void buddhabrot(__global float4* pixels, __global real2_t* points, int max_iterations, int nb_points, real_t position_x,
	real_t position_y, real_t width, real_t height, int color_id, int2 screen_size, float brightness)
{
	real2_t number = (real2_t)(0., 0.);
	real2_t c = points[get_global_id(0)];
	real2_t temp = (real2_t)(0., 0.);
	int i = 0;
	float4 result = 0.f;
	int2 pos = (int2)(0, 0);

	while (modulus_2(number) < 4. && i < max_iterations)
	{
		temp = number;
		number.x = temp.x * temp.x - temp.y * temp.y + c.x;
		number.y = 2. * temp.x * temp.y + c.y;
		i++;
	}

	number = (real2_t)(0., 0.);
	c = points[get_global_id(0)];
	temp = (real2_t)(0., 0.);

	if (i < max_iterations - 3)
	{
		i = 0;

		while (modulus_2(number) < 4. && i < max_iterations)
		{
			temp = number;
			number.x = temp.x * temp.x - temp.y * temp.y + c.x;
			number.y = 2. * temp.x * temp.y + c.y;
			i++;

			if (i > 3)
			{
				pos.x = (int)(((number.x + width / 2. - position_x) / width) * (real_t)screen_size.x);
				pos.y = screen_size.y - 1 - (int)(((number.y + height / 2. + position_y) / height) * (real_t)screen_size.y);
				set_pixel(pixels, pos, screen_size, i, max_iterations, nb_points, brightness);

				pos.y = screen_size.y - 1 - (int)(((-number.y + height / 2. + position_y) / height) * (real_t)screen_size.y);
				set_pixel(pixels, pos, screen_size, i, max_iterations, nb_points, brightness);
			}
		}
	}
}

__kernel void newton_1(__global float4* pixels, int max_iterations, real_t position_x, real_t position_y,
	real_t width, real_t height, float2 point_1, float2 point_2, float2 point_3, int smooth)
{
	real2_t x = (real2_t)(0., 0.);
	real2_t p_1 = (real2_t)(point_1.x, point_1.y);
	real2_t p_2 = (real2_t)(point_2.x, point_2.y);
	real2_t p_3 = (real2_t)(point_3.x, point_3.y);
	real2_t num = (real2_t)(0., 0.);
	real2_t denom = (real2_t)(0., 0.);
	real_t d_1 = (real_t)(length(p_1));
	real_t d_2 = (real_t)(length(p_2));
	real_t d_3 = (real_t)(length(p_3));
	real_t d_min = (real_t)(min(min(d_1, d_2), d_3));
	real_t threshold = 0.001;
	int i = 0;
	float4 color = (float4)(0.f, 0.f, 0.f, 0.f);

	x.x = ((real_t)get_global_id(0) / (real_t)get_global_size(0)) * width + position_x - width / 2.;
	x.y = ((real_t)(get_global_size(1) - 1 - get_global_id(1)) / (real_t)get_global_size(1)) * height + position_y - height / 2.;

	while (d_min > threshold && i < max_iterations)
	{
		num = multiply_3(subtract(x, p_1), subtract(x, p_2), subtract(x, p_3));
		denom = add_3(multiply(subtract(x, p_2), subtract(x, p_3)), multiply(subtract(x, p_1), subtract(x, p_3)), multiply(subtract(x, p_1), subtract(x, p_2)));
		x = subtract(x, divide(num, denom));
		d_1 = length(subtract(x, p_1));
		d_2 = length(subtract(x, p_2));
		d_3 = length(subtract(x, p_3));
		d_min = min(min(d_1, d_2), d_3);
		i++;
	}

	float color_value;

	if (smooth == 1)
		color_value = 0.6 + 0.4 * cos(0.25 * ((float)i - log2(log(d_min) / log(threshold))));
	else
		color_value = 0.6 + 0.4 * cos(0.25 * (float)i);

	if (i == max_iterations)
		color = (float4)(0.f, 0.f, 0.f, 1.f);
	else if (d_1 < d_2 && d_1 < d_3)
		color = (float4)(1.f * color_value, 0.f, 0.3f * color_value, 1.f);
	else if (d_2 < d_1 && d_2 < d_3)
		color = (float4)(0.f, 1.f * color_value, 0.3f * color_value, 1.f);
	else
		color = (float4)(0.f, 0.3f * color_value, 1.f * color_value, 1.f);

	pixels[get_global_id(1) * get_global_size(0) + get_global_id(0)] = color;
}

__kernel void newton_2(__global float4* pixels, int max_iterations, real_t position_x, real_t position_y,
	real_t width, real_t height, int smooth)
{
	real2_t x = (real2_t)(0., 0.);
	real2_t p_1 = (real2_t)(-1., 0.);
	real2_t p_2 = (real2_t)(1., 0.);
	real2_t p_3 = (real2_t)(0., 0.);
	real2_t num = (real2_t)(0., 0.);
	real2_t denom = (real2_t)(0., 0.);
	real_t threshold = 0.001;
	int i = 0;
	float4 color = (float4)(0.f, 0.f, 0.f, 0.f);

	p_3.x = ((real_t)get_global_id(0) / (real_t)get_global_size(0)) * width + position_x - width / 2.;
	p_3.y = ((real_t)(get_global_size(1) - 1 - get_global_id(1)) / (real_t)get_global_size(1)) * height + position_y - height / 2.;

	real_t d_1 = (real_t)(length(p_1));
	real_t d_2 = (real_t)(length(p_2));
	real_t d_3 = (real_t)(length(p_3));
	real_t d_min = (real_t)(min(min(d_1, d_2), d_3));

	x = real_divide(add(add(p_1, p_2), p_3), 3.);

	while (d_min > threshold && i < max_iterations)
	{
		num = multiply_3(subtract(x, p_1), subtract(x, p_2), subtract(x, p_3));
		denom = add_3(multiply(subtract(x, p_2), subtract(x, p_3)), multiply(subtract(x, p_1), subtract(x, p_3)), multiply(subtract(x, p_1), subtract(x, p_2)));
		x = subtract(x, divide(num, denom));
		d_1 = length(subtract(x, p_1));
		d_2 = length(subtract(x, p_2));
		d_3 = length(subtract(x, p_3));
		d_min = min(min(d_1, d_2), d_3);
		i++;
	}

	float color_value;

	if (smooth == 1)
		color_value = 0.6 + 0.4 * cos(0.25 * ((float)i - log2(log(d_min) / log(threshold))));
	else
		color_value = 0.6 + 0.4 * cos(0.25 * (float)i);

	if (i == max_iterations)
		color = (float4)(0.f, 0.f, 0.f, 1.f);
	else if (d_1 < d_2 && d_1 < d_3)
		color = (float4)(1.f * color_value, 0.f, 0.3f * color_value, 1.f);
	else if (d_2 < d_1 && d_2 < d_3)
		color = (float4)(0.f, 1.f * color_value, 0.3f * color_value, 1.f);
	else
		color = (float4)(0.f, 0.3f * color_value, 1.f * color_value, 1.f);

	pixels[get_global_id(1) * get_global_size(0) + get_global_id(0)] = color;
}
