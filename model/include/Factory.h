/*
* ModelFactory is part of the ReBoot distribution (https://github.com/octopusprime314/ReBoot.git).
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
*  Factory namespace acts as a thin wrapper for creating objects that subscribe to events
*/

#pragma once
#include "AnimatedModel.h"
#include "Model.h"
#include "ViewManager.h"
#include "Light.h"

namespace Factory {
    
    //Static view event wrapper that allows subscription to game events
    static ViewManagerEvents* _viewEventWrapper = nullptr;

    //Templated class function to generate classes that subscribe to game events
    template<class T>
    T* make(std::string name) {
        return new T(name, _viewEventWrapper);
    }

    //Templated class function to generate classes that subscribe to game events
    template<class T>
    T* make(MVP mvp,
        LightType type,
        Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f }) {
        return new T(_viewEventWrapper, mvp, type, color);
    }

    //Sets the reference to the view model's event object
    static void setViewWrapper(ViewManager* viewManager) {
        _viewEventWrapper = viewManager->getEventWrapper();
    }
}
