uniform float timer;

vec4 Process(vec4 color)
{
    float red = 0.5 + (sin(timer) * 0.5);
    float green = 0.5 + ((sin(timer) * 0.5) * (cos(timer) * 0.5));
    float blue = 0.5 + (cos(timer) * 0.5);

    vec4 inputTexel = getTexel(gl_TexCoord[0].st);

    inputTexel.r += red;
    inputTexel.g += green;
    inputTexel.b += blue;

    return color * inputTexel;
}
