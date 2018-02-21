#version 430

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 uv;

layout(location = 10) uniform mat4 modelView;
layout(location = 11) uniform mat4 projection;
layout(location = 12) uniform mat4 transformation;

out vec3 lightToPoint;
out vec3 modelView_Normal;
out vec3 eyeToPoint;

void main()
{
    mat4 mvt = modelView * transformation;

    vec4 mvt_Position = (mvt * vec4(vPosition, 1.0));
    eyeToPoint = mvt_Position.xyz; //Actually mvt_Position - (0, 0, 0)
    modelView_Normal = (mvt * vec4(vNormal, 0.0)).xyz; //using 0 as w component prevents applying translation from modelView matrix
    lightToPoint =  -mvt_Position.xyz; //Actually LightPosition - mvt_Position, but lightPosition is currently the same as eye position

    gl_Position = projection * mvt_Position;
}