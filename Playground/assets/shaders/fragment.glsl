#version 400 core

in vec2 v_TexCoord;

uniform sampler2D u_Texture;



void main()
{
	gl_FragColor = texture(u_Texture, v_TexCoord);
}

