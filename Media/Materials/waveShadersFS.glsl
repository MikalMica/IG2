#version 330 core 
uniform sampler2D textura1; 
in vec2 vUv0;
out vec4 fFragColor;

void main(){  
    vec3 color = vec3(texture(textura1, vUv0));       
    fFragColor = vec4(color,1.0);
}