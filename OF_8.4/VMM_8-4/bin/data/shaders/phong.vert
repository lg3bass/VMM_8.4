varying vec3 normal;
varying vec3 v; // view

void main(void) {
    v = vec3(gl_ModelViewMatrix * gl_Vertex);
 	normal = normalize(gl_NormalMatrix * gl_Normal);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}