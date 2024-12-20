////
//// Created by Morten Nobel-Jørgensen on 10/10/2017.
////
//
//#include "VerticalCamera.h"
//#include "PlatformerGame.hpp"
//
//using namespace glm;
//
//VerticalCamera::VerticalCamera(GameObject *gameObject)
//        : Component(gameObject)
//{
//    setZoomMode(false);
//}
//
//sre::Camera &VerticalCamera::getCamera() {
//    return camera;
//}
//
//void VerticalCamera::update(float deltaTime) {
//    if (followObject != nullptr){
//        auto position = followObject->getPosition();
//
//        position.x = offset.x;
//        position.y += offset.y;
//        if (zoom){
//            position.x = offset.x/2;
//            position.y -= offset.y/2;
//        }
//        gameObject->setPosition(position);
//        vec3 eye (position, 0);
//        vec3 at (position, -1);
//        vec3 up (0, 1, 0);
//        camera.lookAt(eye, at, up);
//    }
//}
//
//void VerticalCamera::setFollowObject(std::shared_ptr<GameObject> followObject, glm::vec2 offset) {
//    this->followObject = followObject;
//    this->offset = offset;
//}
//
//void VerticalCamera::setZoomMode(bool zoomEnabled) {
//    this->zoom = zoomEnabled;
//    if (zoomEnabled){
//        camera.setOrthographicProjection(PlatformerGame::windowSize.y/4,-1,1);
//    } else {
//        camera.setOrthographicProjection(PlatformerGame::windowSize.y/2,-1,1);
//    }
//}
//
//bool VerticalCamera::isZoomMode() {
//    return zoom;
//}
