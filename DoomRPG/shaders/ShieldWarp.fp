uniform float timer;

vec4 Process(vec4 color)
{
	vec2 texCoord = gl_TexCoord[0].st;

	const float pi = 3.14159265358979323846;
    
    vec4 input = getTexel(gl_TexCoord[0].st);

	float offsetvalue = 0.125 * sin((pi * 2.0) * -timer + (sqrt (pow(0.5 - texCoord.y, 2) + pow(0.5 - texCoord.x, 2)) * 32.0));
	input.r += offsetvalue;
	input.g += offsetvalue;
	input.b += offsetvalue;

	return input * color;
}

