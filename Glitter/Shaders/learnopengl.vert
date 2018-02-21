#version 430

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 uv;

layout(location = 10) uniform mat4 modelView;
layout(location = 11) uniform mat4 projection;
layout(location = 12) uniform mat4 transformation;

out vec3 fPosition;
out vec3 fNormal;

void main()
{
    fPosition = (modelView * transformation * vec4(vPosition, 1.0)).xyz;
    //fNormal = mat3(transpose(inverse(modelView))) * vNormal;
    fNormal = (modelView * transformation * vec4(vNormal, 0.0)).xyz; //0 component gets rid of translation

    gl_Position = projection * modelView * transformation * vec4(vPosition, 1.0);
}