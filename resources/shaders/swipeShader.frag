#ifdef GL_ES
precision lowp float;
#endif

varying vec2 v_texCoord;
uniform sampler2D CC_Texture0;

uniform vec3 u_innerCol;
uniform vec3 u_outerCol;

void main()
{
	vec4 origColor = texture2D(CC_Texture0, v_texCoord);
    vec4 outColor = vec4(0, 0, 0, 0);

    outColor += vec4(u_innerCol, 1) * origColor.b; // blue controls inner col
    outColor += vec4(u_outerCol, 1) * origColor.r; // red controls outer col

    gl_FragColor = outColor;
}
