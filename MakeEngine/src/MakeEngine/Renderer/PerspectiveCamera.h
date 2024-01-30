#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// Default camera values
#define YAW -90.0f
#define PITCH 0.0f
#define SPEED 5.5f
#define SENSITIVITY 0.1f
#define FOV 45.0f
#define MAX_PITCH 89.f

namespace MK {
    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    enum class Camera_Movement : unsigned char {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NO_DIRECTION
    };

    


    // An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
    class PerspectiveCamera
    {
    public:
        // camera Attributes
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        float MinFov = 1.0f;
        float MaxFov = 90.f;
        float Fov = FOV;
        // camera world attributes
        glm::vec3 Position;
        glm::vec3 WorldUp;
        // euler Angles
        float Yaw;
        float Pitch;
        // camera options
        float MovementSpeed;
        float MouseSensitivity;

        // constructor with vectors
        PerspectiveCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
        // constructor with scalar values
        PerspectiveCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
           
        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix;}

        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

        void ProcessKeyboard(Camera_Movement direction, float deltaTime);

        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

        void ProcessMouseScroll(float yoffset);

    private:
        // calculates the front vector from the Camera's (updated) Euler Angles
        void updateCameraVectors();
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
    };

}