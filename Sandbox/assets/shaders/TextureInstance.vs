#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in mat4 a_InstanceMatrix;

uniform mat4 u_ViewProjection;

out vec2 v_TexCoord;


void main()
{
    v_TexCoord = a_TexCoord;
    gl_Position = u_ViewProjection * a_InstanceMatrix * vec4(a_Position, 1.0);
    //gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}
