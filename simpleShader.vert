#version 330

in vec3 vertex;			 // Each vertex supplied by glDrawArrays, etc.

uniform mat4 model;		 // Model and World transformation matrix
uniform mat4 view;		 // View/Camera transformation matrix
uniform mat4 projection; // Projection transformation matrix

void main(){
	// The vertex is first transformed by the model and world, then 
	// the view/camera and finally the projection matrix
	// The order in which transformation matrices affect the vertex
	// is in the order from right to left
	vec4 transformedVert = projection * view * model * vec4(vertex.xyz, 1.0); 

	//Pass the transformed vertex to the fragment shader
	gl_Position = transformedVert; 
}