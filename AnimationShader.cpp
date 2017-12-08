#include "AnimationShader.h"
#include "AnimatedModel.h"

AnimationShader::AnimationShader() {

}

AnimationShader::~AnimationShader() {

}

void AnimationShader::build(std::string shaderName) {
    
    //Call main build
    Shader::build(shaderName);

    //BONE UNIFORMS!!!!
    //glUniform mat4 
    _bonesLocation = glGetUniformLocation(_shaderContext, "bones");

}

void AnimationShader::runShader(Model* modelIn) {


    AnimatedModel* model = static_cast<AnimatedModel*>(modelIn);

    //LOAD IN SHADER
    glUseProgram(_shaderContext); //use context for loaded shader

    //LOAD IN VBO BUFFERS 
    //Bind vertex buff context to current buffer
    glBindBuffer(GL_ARRAY_BUFFER, model->getVertexContext());

    //Say that the vertex data is associated with attribute 0 in the context of a shader program
    //Each vertex contains 3 floats per vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Now enable vertex buffer at location 0
    glEnableVertexAttribArray(0);

    //Bind normal buff context to current buffer
    glBindBuffer(GL_ARRAY_BUFFER, model->getNormalContext());

    //Say that the normal data is associated with attribute 1 in the context of a shader program
    //Each normal contains 3 floats per normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Now enable normal buffer at location 1
    glEnableVertexAttribArray(1);

    //Bind texture coordinate buff context to current buffer
    glBindBuffer(GL_ARRAY_BUFFER, model->getTextureContext());

    //Say that the texture coordinate data is associated with attribute 2 in the context of a shader program
    //Each texture coordinate contains 2 floats per texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

    //Now enable texture buffer at location 2
    glEnableVertexAttribArray(2);

    //Bind bone index buff context to current buffer
    glBindBuffer(GL_ARRAY_BUFFER, model->getIndexContext());

    //Say that the bone index data is associated with attribute 3 in the context of a shader program
    //Each bone index contains 4 floats per index
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, 0);

    //Now enable bone index buffer at location 3
    glEnableVertexAttribArray(3);

    //Bind weight buff context to current buffer
    glBindBuffer(GL_ARRAY_BUFFER, model->getWeightContext());

    //Say that the weight data is associated with attribute 4 in the context of a shader program
    //Each weight contains 4 floats per index
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, 0);

    //Now enable weight buffer at location 4
    glEnableVertexAttribArray(4);

    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model->getTexture()->getContext()); //grab first texture of model and return context
    //glUniform texture 
    //The second parameter has to be equal to GL_TEXTURE(X) so X must be 0 because we activated texture GL_TEXTURE0 two calls before
    glUniform1iARB(_textureLocation, 0); 

    //glUniform mat4 combined model and world matrix, GL_TRUE is telling GL we are passing in the matrix as row major
    glUniformMatrix4fv(_modelLocation, 1, GL_TRUE, model->getModelBuffer());

    //glUniform mat4 view matrix, GL_TRUE is telling GL we are passing in the matrix as row major
    glUniformMatrix4fv(_viewLocation, 1, GL_TRUE, model->getViewBuffer());

    //glUniform mat4 projection matrix, GL_TRUE is telling GL we are passing in the matrix as row major
    glUniformMatrix4fv(_projectionLocation, 1, GL_TRUE, model->getProjectionBuffer());

    //glUniform mat4 normal matrix, GL_TRUE is telling GL we are passing in the matrix as row major
    glUniformMatrix4fv(_normalLocation, 1, GL_TRUE, model->getNormalBuffer());

    //Add bone uniforms here!!!!!!!!!!!!!!!!!!!!!!!!!

    auto bones = model->getBones();
    float* bonesArray = new float[ 16 * bones->size() ]; //4x4 times number of bones
    int bonesArrayIndex = 0;
    for(auto bone : *bones){
        for(int i = 0; i < 16; i++){
            float* buff = bone.getFlatBuffer();
            bonesArray[bonesArrayIndex++] = buff[i];
        }
    }
    glUniformMatrix4fv(_bonesLocation, static_cast<GLsizei>(bones->size()), GL_TRUE, bonesArray);
    delete [] bonesArray;

    //Draw triangles using the bound buffer vertices at starting index 0 and number of triangles
    glDrawArraysEXT(GL_TRIANGLES, 0, (GLsizei)model->getArrayCount());

    glDisableVertexAttribArray(0); //Disable vertex attribute
    glDisableVertexAttribArray(1); //Disable normal attribute
    glDisableVertexAttribArray(2); //Disable texture attribute
    glDisableVertexAttribArray(3); //Disable indexes attribute
    glDisableVertexAttribArray(4); //Disable weight attribute
    glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind buffer
    glUseProgram(0);//end using this shader
}