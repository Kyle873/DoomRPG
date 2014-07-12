uniform float timer;

vec4 Process(vec4 color)
{
    float red = color.x * (sin(timer) * 0.1);
    float green = color.y * (sin(timer) * 0.1);
    float blue = color.z * (sin(timer) * 0.1);
    vec4 inputTexel = getTexel(gl_TexCoord[0].st);

    inputTexel.r += red;
    inputTexel.g += green;
    inputTexel.b += blue;

    return color * inputTexel;
}
