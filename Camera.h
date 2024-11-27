#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};
/*
* Camera class implementation
Implementation from LearnOpenGL website:https://github.com/JoeyDeVries/LearnOpenGL
*/
// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    //Attributes of camera
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    //attributes for changing 
    float Yaw;
    float Pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    //Constructors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    //View matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    //Process keyboard input
    void ProcessKeyBoard(Camera_Movement direction, float deltaTime)
    {
        const float cameraSpeed = movementSpeed * deltaTime;
        if (direction == FORWARD)
        {
            Position += cameraSpeed * Front;
        }
        if (direction == BACKWARD)
        {
            Position -= cameraSpeed * Front;
        }
        if (direction == LEFT)
        {
            Position -= Right * cameraSpeed;
        }
        if (direction == RIGHT)
        {
            Position += Right * cameraSpeed;
        }
    }

    //Process mouse movement
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        //modify x and y offset
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        //Modify the yaw and pitch
        Yaw += xoffset;
        Pitch -= yoffset;

        //Put limit on the pitch
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;

        updateCameraVectors();
    }

    //Zoom in or out
    void ProcessMouseScroll(float yoffset)
    {
        zoom -= (float)yoffset;
        if (zoom < 1.0f)
            zoom = 1.0f;
        if (zoom > 45.0f)
            zoom = 45.0f;

        updateCameraVectors();
    }

private:
    void updateCameraVectors()
    {
        glm::vec3 front;

        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

        Front = glm::normalize(front);

        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
#endif

