#version 430

layout (location = 0) uniform vec3 materialAmbient;
layout (location = 1) uniform vec3 materialDiffuse;
layout (location = 2) uniform vec3 materialSpecular;
layout (location = 3) uniform vec3 materialEmission;
layout (location = 4) uniform float materialShininess;

in vec3 fPosition;
in vec3 fNormal;

out vec4 FragColor;

void main()
{
    //ambient
    vec3 ambient = vec3(0.3, 0.3, 0.3) * materialAmbient;

    //diffuse
    vec3 norm = normalize(fNormal);
    vec3 lightDir = normalize(-fPosition); //Actually lightpos - fPos
    float Kd = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = Kd * vec3(1., 1., 1.) * materialDiffuse;

    //specular
    vec3 viewDir = normalize(-fPosition);
    vec3 halfWayDir = normalize(lightDir + viewDir); //Blinn-phong
    float Ks = pow(max(dot(fNormal, halfWayDir), 0.0), materialShininess);
    //vec3 reflectDir = reflect(-lightDir, norm); //Regular phong shading
    //float Ks = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
    vec3 specular = Ks * vec3(0.5, 0.5, 0.5) * materialSpecular;

    FragColor = vec4(ambient + diffuse + specular, 1.0);

    /*vec3 lightToPoint1 = normalize(lightToPoint);
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
    } else	specular = Ks * vec3(0.5, 0.5, 0.5) * materialSpecular;*/

}