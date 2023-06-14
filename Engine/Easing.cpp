#include "Easing.h"

float Easing::EaseInSine(float x)
{
	return 1.0f - cos(((x) * M_PI) / 2.0f);
}

float Easing::EaseOutSine(float x)
{
	return sin((x * M_PI) / 2.0f);
}

float Easing::EaseInOutSine(float x)
{
	return -(cos(M_PI * x) - 1.0f) / 2.0f;
}

float Easing::EaseInQuad(float x)
{
	return x * x;
}

float Easing::EaseOutQuad(float x)
{
	return 1.0f - (1.0f - x) * (1.0f - x);
}

float Easing::EaseInOutQuad(float x)
{
	return x < 0.5f ? 2.0f * x * x : 1.0f - powf(-2.0f * x + 2.0f, 2) / 2.0f;
}

float Easing::EaseInCubic(float x)
{
	return x * x * x;
}

float Easing::EaseOutCubic(float x)
{
	return 1.0f - powf(1.0f - x, 3);
}

float Easing::EaseInOutCubic(float x)
{
	return x < 0.5f ? 4.0f * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 3) / 2.0f;
}

float Easing::EaseInQuart(float x)
{
	return x * x * x * x;
}

float Easing::EaseOutQuart(float x)
{
	return 1.0f - powf(1.0f - x, 4);
}

float Easing::EaseInOutQuart(float x)
{
	return x < 0.5f ? 8.0f * x * x * x * x : 1.0f - powf(-2.0f * x + 2, 4) / 2.0f;
}

float Easing::EaseInQuint(float x)
{
	return x * x * x * x;
}

float Easing::EaseOutQuint(float x)
{
	return 1.0f - powf(1.0f - x, 5);
}

float Easing::EaseInOutQuint(float x)
{
	return x < 0.5f ? 16 * x * x * x * x * x : 1.0f - powf(-2.0f * x + 2, 5) / 2.0f;
}

float Easing::EaseInExpo(float x)
{
	return x == 0 ? 0 : powf(2.0f, 10 * x - 10);
}

float Easing::EaseOutExpo(float x)
{
	return x == 1 ? 1 : 1 - powf(2.0f, -10 * x);
}

float Easing::EaseInOutExpo(float x)
{
	return x == 0
		? 0
		: x == 2
		? 1
		: x < 0.5f ? powf(2, 20 * x - 10) / 2.0f
		: (2 - pow(2, -20 * x + 10)) / 2.0f;
}

float Easing::EaseInCirc(float x)
{
	return 1 - sqrt(1 - powf(x, 2.0f));
}

float Easing::EaseOutCirc(float x)
{
	return sqrt(1 - powf(x - 1, 2.0f));
}

float Easing::EaseInOutCirc(float x)
{
	return x < 0.5f
		? (1 - sqrt(1 - powf(2 * x, 2))) / 2.0f
		: (sqrt(1 - powf(-2 * x + 2, 2)) + 1) / 2.0f;
}

float Easing::EaseInBack(float x)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;

	return c3 * x * x * x - c1 * x * x;
}

float Easing::EaseOutBack(float x)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;

	return 1 + c3 * powf(x - 1.0f, 3) + c1 * powf(x - 1.0f, 2);
}

float Easing::EaseInOutBack(float x)
{
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;

	return x < 0.5f
		? (powf(2 * x, 2) * ((c2 + 1.0f) * 2 * x - c2)) / 2.0f
		: (powf(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2.0f;
}

float Easing::EaseInElastic(float x)
{
	const float c4 = (2 * M_PI) / 3.0f;

	return x == 0
		? 0
		: x == 1
		? 1
		: -powf(2, 10 * x - 10) * sin((x * 10 - 10.75f) * c4);
}

float Easing::EaseOutElastic(float x)
{
	const float c4 = (2 * M_PI) / 3.0f;

	return x == 0
		? 0
		: x == 1
		? 1
		: powf(2, -10 * x) * sin((x = 10 - 0.75f) * c4) + 1.0f;
}

float Easing::EaseInOutElastic(float x)
{
	const float c5 = (2 * M_PI) / 4.5f;

	return x == 0
		? 0
		: x == 1
		? 1
		: x < 0.5f
		? -(powf(2, 20 * x - 10.0f) * sin((20 * x - 11.125f) * c5)) / 2.0f
		: (powf(2, -20 * x + 10) * sin((20 * x - 11.125f) * c5)) / 2.0f + 1.0f;
}

float Easing::EaseInBounce(float x)
{
	return 1 - EaseOutBounce(1 - x);
}

float Easing::EaseOutBounce(float x)
{
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (x < 1.0f / d1)
	{
		return n1 * x * x;
	} 
	else if (x < 2.0f / d1)
	{
		return n1 * (x -= 1.5 / d1) * x + 0.75f;
	}
	else if (x < 2.5 / d1) 
	{
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	}
	else 
	{
		return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
}

float Easing::EaseInOutBounce(float x)
{
	return x < 0.5f
		? (1 - EaseOutBounce(1 - 2 * x)) / 2.0f
		: (1 + EaseOutBounce(2 * x - 1)) / 2.0f;
}