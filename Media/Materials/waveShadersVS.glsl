#version 330 core
uniform mat4 modelViewProjMat;
uniform float time;
in vec4 vertex;
in vec2 uv0;
out vec2 vUv0;

void main() {
    vUv0 = uv0;

    vec4 center = vec4(0,0,0,0);
    float a = 1.5;
    float b = 1;
    vec4 vertexCoord = vertex;
    float distanceCenter = distance(vertex, center);

    vertexCoord.y += sin(vertexCoord.x + (time*a)) * b + sin(vertexCoord.z + (distanceCenter) + (time*a)) * b; 


    gl_Position = modelViewProjMat * vertexCoord;
}