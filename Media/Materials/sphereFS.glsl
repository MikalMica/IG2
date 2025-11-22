#version 330 core 
uniform sampler2D textura1;
uniform float flipping;
in vec2 vUv0;
in vec4 vVertex;
out vec4 fFragColor;

void main(){ 

    bool front;
    if(flipping > -1) front = gl_FrontFacing;
    else front = !gl_FrontFacing;
    
    vec3 color = vec3(texture(textura1, vUv0));

    if(color.r > 0.6){
        discard;
    }

    if(front) fFragColor = vec4(color,1.0);
    else fFragColor = vec4(vVertex.x/100, vVertex.y/100, -vVertex.z/100, 1.0);
}