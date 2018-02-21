#version 430

layout (location = 0) uniform vec3 materialAmbient;
layout (location = 1) uniform vec3 materialDiffuse;
layout (location = 2) uniform vec3 materialSpecular;
layout (location = 3) uniform vec3 materialEmission;
layout (location = 4) uniform float materialShininess;

in vec3 lightToPoint;
in vec3 modelView_Normal;
in vec3 eyeToPoint;

out vec4 FragColor;

void main()
{
    vec3 lightToPoint1 = normalize(lightToPoint);
    vec3 modelView_Normal1 = normalize(modelView_Normal);
    vec3 eyeToPoint1 = normalize(eyeToPoint);

    vec3 H = normalize(lightToPoint1 + eyeToPoint1);
    float Kd=max(dot(lightToPoint1, modelView_Normal1), 0.0);
    float Ks = pow(max(dot(modelView_Normal1, H), 0.0), materialShininess);
    vec3 ambient = vec3(0.5, 0.5, 0.5) * materialAmbient;
    vec3 diffuse = Kd * vec3(0.5, 0.5, 0.5) * materialDiffuse;
    vec3 specular;
    if( dot(lightToPoint1, modelView_Normal1) < 0.0 ) {
        specular = vec3(0.0, 0.0, 0.0);
    } else	specular = Ks * vec3(0.5, 0.5, 0.5) * materialSpecular;


    FragColor = vec4(ambient + diffuse + specular, 1.0);

}