//#pragma once
//
//#include "sre/Camera.hpp"
//#include "glm/glm.hpp"
//#include "Component.hpp"
//
//class VerticalCamera : public MyEngine::Component {
//public:
//    explicit VerticalCamera(GameObject *gameObject);
//
//    void update(float deltaTime) override;
//
//    void setFollowObject(std::shared_ptr<GameObject> followObject, glm::vec2 offset);
//
//    void setZoomMode(bool zoomEnabled);
//    bool isZoomMode();
//
//    sre::Camera& getCamera();
//private:
//    sre::Camera camera;
//    std::shared_ptr<GameObject> followObject;
//    glm::vec2 offset;
//    bool zoom = false;
//};
//