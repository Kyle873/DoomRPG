uniform float timer;

vec4 Process(vec4 color)
{
    float red = color * (sin(timer) * 0.1);
    float green = color * (sin(timer) * 0.1);
    float blue = color * (sin(timer) * 0.1);
    vec4 input = getTexel(gl_TexCoord[0].st);
    
    input.r += red;
    input.g += green;
    input.b += blue;
    
    return color * input;
}
