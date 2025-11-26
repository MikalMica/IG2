#version 330 core 
uniform sampler2D textura1;
uniform float flipping;
in vec2 vUv0;
in vec3 vNormal;
in vec3 vLightDirection;
in vec3 vLightAmbient;
in vec3 vLightDiffuse;
in vec3 vMaterialDiffuse;
out vec4 fFragColor;

void main(){ 

    bool front;
    if(flipping > -1) front = gl_FrontFacing;
    else front = !gl_FrontFacing;
    
    vec3 color = vec3(texture(textura1, vUv0));

    if(color.r > 0.6){
        discard;
    }

    vec3 ambient = vLightAmbient*vMaterialDiffuse;
    vec3 diffuse;
    
    if(!front){ 
        color = -vNormal;
        diffuse = max(0, dot(-vNormal, -vLightDirection))*vLightDiffuse*vMaterialDiffuse;
    }
    else diffuse = max(0, dot(vNormal, -vLightDirection))*vLightDiffuse*vMaterialDiffuse;

    color = color * (ambient + diffuse);

    fFragColor = vec4(color,1.0);
}