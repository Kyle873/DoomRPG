uniform float timer;

vec4 Process(vec4 color)
{
    float red = color * (sin(timer) * 0.05);
    float green = color * (sin(timer) * 0.05);
    float blue = color * (sin(timer) * 0.05);
    vec4 inputTexel = getTexel(gl_TexCoord[0].st);

    inputTexel.r += red;
    inputTexel.g += green;
    inputTexel.b += blue;

    return color * inputTexel;
}
