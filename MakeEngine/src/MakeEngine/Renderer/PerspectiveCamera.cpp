#include "mkpch.h"
#include "PerspectiveCamera.h"

namespace MK {
    PerspectiveCamera::PerspectiveCamera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch)
        : Position(position), Front(glm::vec3(0.0f, 0.0f, 0.0f)), WorldUp(worldUp), Yaw(yaw), Pitch(pitch),
        MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(Fov), 1280.f / 780.f, 0.1f, 100.0f);
        updateCameraVectors();
    }

    PerspectiveCamera::PerspectiveCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        m_ProjectionMatrix = glm::perspective(glm::radians(Fov), 1280.f / 780.f, 0.1f, 100.0f);
        updateCameraVectors();
    }

    void PerspectiveCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        switch (direction)
        {
        case Camera_Movement::FORWARD:
            Position += Front * velocity;
            break;
        case Camera_Movement::BACKWARD:
            Position -= Front * velocity;
            break;
        case Camera_Movement::LEFT:
            Position -= Right * velocity;
            break;
        case Camera_Movement::RIGHT:
            Position += Right * velocity;
            break;
        case Camera_Movement::UP:
            Position += glm::vec3(0.f, 1.f, 0.f) * velocity;
            break;
        case Camera_Movement::DOWN:
            Position -= glm::vec3(0.f, 1.f, 0.f) * velocity;
            break;
        default:
            break;
        }
        m_ViewMatrix = glm::lookAt(Position, Position + Front, Up);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void PerspectiveCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > MAX_PITCH)
                Pitch = MAX_PITCH;
            if (Pitch < -MAX_PITCH)
                Pitch = -MAX_PITCH;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    void PerspectiveCamera::ProcessMouseScroll(float yoffset)
    {
        Fov -= (float)yoffset;
        if (Fov < MinFov)
            Fov = MinFov;
        if (Fov > MaxFov)
            Fov = MaxFov;
        m_ProjectionMatrix = glm::perspective(glm::radians(Fov), 1280.f / 780.f, 0.1f, 100.0f);
    }

    void PerspectiveCamera::updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));

        m_ViewMatrix = glm::lookAt(Position, Position + Front, Up);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}
