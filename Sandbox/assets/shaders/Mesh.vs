#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in mat4 a_InstanceMatrix;

out vec3 v_FragPos;
out vec3 v_Normal;
out vec2 v_TexCoord;

uniform mat4 u_ViewProjection;

void main()
{
    v_FragPos = vec3(a_InstanceMatrix * vec4(a_Position, 1.0));
    v_Normal = mat3(transpose(inverse(a_InstanceMatrix))) * a_Normal;
    v_TexCoord = a_TexCoord;
    gl_Position = u_ViewProjection * a_InstanceMatrix * vec4(a_Position, 1.0);
    
}