uniform float timer;

// TODO: This doesn't actually work yet, should scroll the texture vertically and properly wrap the texture
vec4 Process(vec4 color)
{
    vec4 texCoord = gl_TexCoord[0].st;
    float yoff = 0.0;
    
    yoff += timer;
    texCoord.y += offset;
    
    return GetTexel(texCoord) * color;
}
