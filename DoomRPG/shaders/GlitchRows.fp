// Kate's glitch image warper

uniform float timer;

vec4 Process(vec4 color)
{
	vec2 texCoord = gl_TexCoord[0].st;
    vec2 offset = vec2(0.0,0.0);
    float rndx = 0.0;
    float index = mod(texCoord.y + (floor (timer*64.0) / 64.0), 1.0);
    
    if (index < 0.015625)
        rndx = 0.0008804895238978983;
    else if (index < 0.03125)
        rndx = 0.01456665209191117;
    else if (index < 0.046875)
        rndx = 0.08307525211038626;
    else if (index < 0.0625)
        rndx = 0.09899622447968814;
    else if (index < 0.078125)
        rndx = 0.035273120559882125;
    else if (index < 0.09375)
        rndx = 0.0897017221534248;
    else if (index < 0.109375)
        rndx = 0.07900133492897433;
    else if (index < 0.125)
        rndx = 0.02834640839818028;
    else if (index < 0.140625)
        rndx = 0.026795568282054805;
    else if (index < 0.15625)
        rndx = 0.03510779647594631;
    else if (index < 0.171875)
        rndx = 0.012031077713812522;
    else if (index < 0.1875)
        rndx = 0.08506712768769084;
    else if (index < 0.203125)
        rndx = 0.017617298402977623;
    else if (index < 0.21875)
        rndx = 0.09987147882972866;
    else if (index < 0.234375)
        rndx = 0.007718089588670996;
    else if (index < 0.25)
        rndx = 0.0973066229109813;
    else if (index < 0.265625)
        rndx = 0.08003653409620037;
    else if (index < 0.28125)
        rndx = 0.03840463625318035;
    else if (index < 0.296875)
        rndx = 0.029561431073627742;
    else if (index < 0.3125)
        rndx = 0.03024060520494285;
    else if (index < 0.328125)
        rndx = 0.039269411528435584;
    else if (index < 0.34375)
        rndx = 0.07259667429955252;
    else if (index < 0.359375)
        rndx = 0.06754657447281937;
    else if (index < 0.375)
        rndx = 0.042781088794093605;
    else if (index < 0.390625)
        rndx = 0.08462873380445592;
    else if (index < 0.40625)
        rndx = 0.08783684943659406;
    else if (index < 0.421875)
        rndx = 0.09380862047128523;
    else if (index < 0.4375)
        rndx = 0.09389479987305405;
    else if (index < 0.453125)
        rndx = 0.09199649500175694;
    else if (index < 0.46875)
        rndx = 0.08333828616894386;
    else if (index < 0.484375)
        rndx = 0.050118098301886585;
    else if (index < 0.5)
        rndx = 0.05351779778641859;
    else if (index < 0.515625)
        rndx = 0.056703753870968626;
    else if (index < 0.53125)
        rndx = 0.00683605932820055;
    else if (index < 0.546875)
        rndx = 0.0814777429361;
    else if (index < 0.5625)
        rndx = 0.0661213452215469;
    else if (index < 0.578125)
        rndx = 0.07864903152007345;
    else if (index < 0.59375)
        rndx = 0.07711187512816398;
    else if (index < 0.609375)
        rndx = 0.08573783364796748;
    else if (index < 0.625)
        rndx = 0.07467691128884081;
    else if (index < 0.640625)
        rndx = 0.07345847152632944;
    else if (index < 0.65625)
        rndx = 0.027300546748990108;
    else if (index < 0.671875)
        rndx = 0.017887524032555956;
    else if (index < 0.6875)
        rndx = 0.03703370500161651;
    else if (index < 0.703125)
        rndx = 0.005580244336476636;
    else if (index < 0.71875)
        rndx = 0.09237749101040849;
    else if (index < 0.734375)
        rndx = 0.06789580937135063;
    else if (index < 0.75)
        rndx = 0.009328996923951893;
    else if (index < 0.765625)
        rndx = 0.08592209828677527;
    else if (index < 0.78125)
        rndx = 0.09191682511063265;
    else if (index < 0.796875)
        rndx = 0.05499816730019483;
    else if (index < 0.8125)
        rndx = 0.0682051741934234;
    else if (index < 0.828125)
        rndx = 0.021572038693785413;
    else if (index < 0.84375)
        rndx = 0.009913478974028568;
    else if (index < 0.859375)
        rndx = 0.06423204462900586;
    else if (index < 0.875)
        rndx = 0.028220656502524734;
    else if (index < 0.890625)
        rndx = 0.09138013700196501;
    else if (index < 0.90625)
        rndx = 0.001730051327489446;
    else if (index < 0.921875)
        rndx = 0.005442497044022021;
    else if (index < 0.9375)
        rndx = 0.047694843414814225;
    else if (index < 0.953125)
        rndx = 0.007422754013178235;
    else if (index < 0.96875)
        rndx = 0.09580827179406583;
    else if (index < 0.984375)
        rndx = 0.05527700033114996;
    else if (index < 1.0)
        rndx = 0.0507897485932538;
    
    offset.x = -0.05 + rndx;

	texCoord += offset;

	return (getTexel(texCoord) * (1.0 - ((0.05 - abs (offset.x)) * 5.0))) * color;
}
