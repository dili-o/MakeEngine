#version 330 core
out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_DiffuseTexture;

void main()
{
	color = texture(u_DiffuseTexture, v_TexCoord);
	//color = vec4(v_TexCoord, 0.0, 1.0);
}