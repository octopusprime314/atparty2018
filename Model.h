/*
* Model is part of the ReBoot distribution (https://github.com/octopusprime314/ReBoot.git).
* Copyright (c) 2017 Peter Morley.
*
* ReBoot is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* ReBoot is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/**
*  Model class. Contains vertex and normal data which will get populated in opengl
*  buffers to be rendered to the screen
*/

#pragma once
#include "Matrix.h"
#include "Texture2.h"
#include "StateVector.h"
#include <vector>
#include "UpdateInterface.h"
#include "GLIncludes.h"
#include "Shader.h"
#include "DebugShader.h"
#include <iostream>
#include "FbxLoader.h"
#include "MasterClock.h"
#include "TextureBroker.h"

class SimpleContext;

enum class ModelClass {
    ModelType = 0,
    AnimatedModelType
};

class Model : public UpdateInterface {

public:

    Model();
    //Default model to type to base class
    Model(std::string name, ViewManagerEvents* eventWrapper, ModelClass classId = ModelClass::ModelType);
    virtual ~Model();
    Matrix                      getNormal();
    float*                      getModelBuffer();
    float*                      getViewBuffer();
    float*                      getProjectionBuffer();
    float*                      getNormalBuffer();
    GLuint                      getVertexContext();
    GLuint                      getNormalContext();
    GLuint                      getTextureContext();
    GLuint                      getNormalDebugContext();
    GLuint                      getBufferedVertexContext();
    GLuint                      getBufferedNormalContext();
    GLuint                      getBufferedNormalDebugContext();
    void                        setVertexContext(GLuint context);
    void                        setNormalContext(GLuint context);
    void                        setTextureContext(GLuint context);
    void                        setNormalDebugContext(GLuint context);
    std::vector<Vector4>*       getVertices();
    std::vector<Vector4>*       getNormals();
    std::vector<Texture2>*      getTextures();
    std::vector<int>*		    getIndices();
    void                        addVertex(Vector4 vertex);
    void                        addNormal(Vector4 normal);
    void                        addTexture(Texture2 texture);
    void                        addDebugNormal(Vector4 normal);
    void						setVertexIndices(std::vector<int> indices);
    ModelClass                  getClassType();
    size_t                      getArrayCount();
    void                        addTexture(Texture* texture);
    Texture*                    getTexture(int index);

protected:
    Matrix                      _model; //Object and World Space Matrix i.e. how the model is centered around the origin and 
                                 //where it is placed in the context of the game World
    Matrix                      _view;  //View matrix updates from ViewManager/Camera 
    Matrix                      _projection; //Projection matrix based on ViewManager/Camera
    Matrix                      _normal; //Normal matrix based on inverse transpose matrix of the ViewManager/Camera matrix
    StateVector                 _state; //Kinematics
    std::vector<Vector4>        _vertices; //Vertices that make up the triangles of the model
    std::vector<Vector4>        _normals; //Normals that implement how light is shaded onto a model
    std::vector<Texture2>       _textures; //Texture coordinates that places texture data and maps it onto a vertex
    std::vector<int>            _indices; //Used to map vertices
    GLuint                      _vertexBufferContext[2]; //Used as the vertex attribute vbo context, double buffered
    GLuint                      _normalBufferContext[2]; //Used as the normal attribute vbo context, double buffered
    GLuint                      _textureBufferContext; //Used as the texture coordinate attribute vbo context, single buffered
    GLuint                      _debugNormalBufferContext[2]; //Used as the debug normal line attribute vbo context, double buffered
    Shader*                     _shaderProgram; //Container object of the Model's shader
    DebugShader*                _debugShaderProgram; //Container object of the normal line shader
    bool                        _debugMode; //Runs an extra shader with debug information include normals
    std::vector<Vector4>        _debugNormals; //Vertex storage for normal line visualization
    FbxLoader*                  _fbxLoader; //Used to load fbx data and parse it into engine format
    ModelClass                  _classId; //Used to identify which class is being used
    MasterClock*                _clock; //Used to coordinate time with the world
    bool                        _doubleBufferIndex; //Used to switch between gpu contexts for buffering purposes
    TextureBroker               _textureManager; //Used to coordinate between textures of the model
    
    void                        _updateKeyboard(unsigned char key, int x, int y); //Do stuff based on keyboard upate
    void                        _updateMouse(int button, int state, int x, int y); //Do stuff based on mouse update
    void                        _updateDraw(); //Do draw stuff
    void                        _updateView(Matrix view); //Get view matrix updates
    void                        _updateProjection(Matrix projection); //Get projection matrix updates
    void                        _updateKinematics(int milliSeconds);

};