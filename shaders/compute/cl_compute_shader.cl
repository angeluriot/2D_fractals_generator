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

real_t modulus_2(real2_t x)
{
	return x.x * x.x + x.y * x.y;
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
	real_t width, real_t height, __global float4* pallet, int colors_nb, int smooth)
{
	real2_t number = (real2_t)(0.f, 0.f);
	real2_t c = (real2_t)(c_r, c_i);
	real2_t temp = (real2_t)(0.f, 0.f);
	int i = 0;
	float4 color = (float4)(0.f, 0.f, 0.f, 0.f);

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
		number.y = 2.f * temp.x * temp.y + c.y;
		i++;
		smooth_value += exp(-length(number));
	}

	if (i == max_iterations)
		color = (float4)(0.f, 0.f, 0.f, 1.f);
	else if (colors_nb == -1)
		color = get_color(i % 6, 6, pallet, 6);
	else if (colors_nb == -2)
		color = get_color(i % 2, 2, pallet, 2);
	else if (smooth == 1)
		color = get_color(modulo((float)smooth_value, (float)max_iterations / 10.f), (float)max_iterations / 10.f, pallet, colors_nb);
	else
		color = get_color(i % (max_iterations / 10), max_iterations / 10, pallet, colors_nb);

	pixels[get_global_id(1) * get_global_size(0) + get_global_id(0)] = color;
}

__kernel void mandelbrot(__global float4* pixels, int max_iterations, real_t position_x, real_t position_y,
	real_t width, real_t height, __global float4* pallet, int colors_nb, int smooth)
{
	real2_t number = (real2_t)(0.f, 0.f);
	real2_t c = (real2_t)(0.f, 0.f);
	real2_t temp = (real2_t)(0.f, 0.f);
	int i = 0;
	float4 color = (float4)(0.f, 0.f, 0.f, 0.f);

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
		number.y = 2.f * temp.x * temp.y + c.y;
		i++;
	}

	float smooth_value = (float)i + 1. - log(log(length(number))) / log(2.);

	if (i == max_iterations)
		color = (float4)(0.f, 0.f, 0.f, 1.f);
	else if (colors_nb == -1)
		color = get_color(i % 6, 6, pallet, 6);
	else if (colors_nb == -2)
		color = get_color(i % 2, 2, pallet, 2);
	else if (smooth == 1)
		color = get_color(modulo(smooth_value, (float)max_iterations / 10.f), (float)max_iterations / 10.f, pallet, colors_nb);
	else
		color = get_color(i % (max_iterations / 10), max_iterations / 10, pallet, colors_nb);

	pixels[get_global_id(1) * get_global_size(0) + get_global_id(0)] = color;
}

__kernel void burning_ship(__global float4* pixels, int max_iterations, real_t position_x, real_t position_y,
	real_t width, real_t height, __global float4* pallet, int colors_nb, int smooth)
{
	real2_t number = (real2_t)(0.f, 0.f);
	real2_t c = (real2_t)(0.f, 0.f);
	real2_t temp = (real2_t)(0.f, 0.f);
	int i = 0;
	float4 color = (float4)(0.f, 0.f, 0.f, 0.f);

	c.x = ((real_t)get_global_id(0) / (real_t)get_global_size(0)) * width + position_x - width / 2.;
	c.y = ((real_t)(get_global_size(1) - 1 - get_global_id(1)) / (real_t)get_global_size(1)) * height + position_y - height / 2.;

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
		number.y = 2.f * temp.x * temp.y + c.y;
		i++;
	}

	float smooth_value = (float)i + 1. - log(log(length(number))) / log(2.);

	if (i == max_iterations)
		color = (float4)(0.f, 0.f, 0.f, 1.f);
	else if (colors_nb == -1)
		color = get_color(i % 6, 6, pallet, 6);
	else if (colors_nb == -2)
		color = get_color(i % 2, 2, pallet, 2);
	else if (smooth == 1)
		color = get_color(modulo(smooth_value, (float)max_iterations / 10.f), (float)max_iterations / 10.f, pallet, colors_nb);
	else
		color = get_color(i % (max_iterations / 10), max_iterations / 10, pallet, colors_nb);

	pixels[get_global_id(1) * get_global_size(0) + get_global_id(0)] = color;
}

void set_pixel(float4* pixels, int2 pos, int2 screen_size, int i, int max_iterations)
{
	if (pos.x >= 0 && pos.x < screen_size.x && pos.y >= 0 && pos.y < screen_size.y && i > 1)
	{
		if (i < max_iterations / 25)
			pixels[pos.y * screen_size.x + pos.x].x += 1.f / ((float)(max_iterations) / 10.f);
		else if (i < max_iterations / 5)
			pixels[pos.y * screen_size.x + pos.x].y += 1.f / ((float)(max_iterations) / 10.f);
		else
			pixels[pos.y * screen_size.x + pos.x].z += 1.f / ((float)(max_iterations) / 10.f);
	}
}

__kernel void buddhabrot(__global float4* pixels, __global real2_t* points, int max_iterations,
	real_t position_x, real_t position_y, real_t width, real_t height, int2 screen_size)
{
	real2_t number = (real2_t)(0.f, 0.f);
	real2_t c = points[get_global_id(0)];
	real2_t temp = (real2_t)(0.f, 0.f);
	int i = 0;
	float4 result = 0.f;
	int2 pos = (int2)(0, 0);

	while (modulus_2(number) < 4.f && i < max_iterations)
	{
		temp = number;
		number.x = temp.x * temp.x - temp.y * temp.y + c.x;
		number.y = 2.f * temp.x * temp.y + c.y;
		i++;

		pos.x = (int)(((number.x + width / 2. - position_x) / width) * (real_t)screen_size.x);
		pos.y = screen_size.y - 1 - (int)(((number.y + height / 2. - position_y) / height) * (real_t)screen_size.y);
		set_pixel(pixels, pos, screen_size, i, max_iterations);

		pos.y = screen_size.y - 1 - (int)(((-number.y + height / 2. - position_y) / height) * (real_t)screen_size.y);
		set_pixel(pixels, pos, screen_size, i, max_iterations);
	}
}
