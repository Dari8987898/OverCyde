#include "RendererComponent.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Texture.h"
#include "../Rendering/Texture2D.h"
#include "../Rendering/Shape.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <glm/glm.hpp>

RendererComponent::RendererComponent(GameObj *gameObj,
                                     Shape *shape,
                                     Shader *shader,
                                     GLshort updateOrder) : Component(gameObj, updateOrder),
                                                            texture(nullptr),
                                                            shape(shape),
                                                            shader(shader),
                                                            model(glm::mat4(1)) {}

RendererComponent::~RendererComponent() {}

void RendererComponent::Draw(GLFWwindow *window, glm::mat4 projection, glm::mat4 view) {
    GameObjData *data = this->gameObj->GetGameObjData();

    this->model = glm::translate(this->model, data->GetPosition());
    this->model = glm::rotate(this->model, glm::radians(data->GetRotation()), data->GetRotationVec());
    this->model = glm::scale(this->model, data->GetScale());

    // this->shader->setMatrix4("projection", projection);
    // this->shader->setMatrix4("model", model);
    // this->shader->setMatrix4("view", view);
    if(this->texture) {
        this->shader->use();
        this->texture->Bind();
        this->shape->Draw();
    }
}