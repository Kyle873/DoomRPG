uniform float timer;

vec4 Process(vec4 color)
{
    float red = sin(timer) * 0.25;
    float green = (sin(timer) * 0.5) * (cos(timer) * 0.25);
    float blue = cos(timer) * 0.25;

    vec4 inputTexel = getTexel(gl_TexCoord[0].st);

    inputTexel.r += red;
    inputTexel.g += green;
    inputTexel.b += blue;

    return color * inputTexel;
}
