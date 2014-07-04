uniform float timer;

vec4 Process(vec4 color)
{
    float red = sin(timer) * 0.25;
    float green = (sin(timer) * 0.5) * (cos(timer) * 0.25);
    float blue = cos(timer) * 0.25;
    
    vec4 input = getTexel(gl_TexCoord[0].st);
    
    input.r += red;
    input.g += green;
    input.b += blue;
    
    return color * input;
}
