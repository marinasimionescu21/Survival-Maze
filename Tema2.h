#pragma once

#include <string>
#include <unordered_map>

#include "components/simple_scene.h"
#include "components/transform.h"
#include "lab_m1/Tema2/lab_camera.h"
#include "lab_m1/Tema2/transform3D.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        void Init() override;

        struct fastGun
        {
            fastGun() : x(0), y(0), z(0), length(0.1f), speed(2.0f), angle(0) {}
            fastGun(float x, float y, float z, float length, float speed, float angle)
                : x(x), y(x), z(z), length(length), speed(speed), angle(angle) {}
            float x;
            float y;
            float z;
            float length;
            float speed;
            float angle;
        };

        typedef struct wall
        {
            float Tx;
            float Ty;
            float Tz;
        } Wall;


     private:
        void FrameStart() override;
        void RenderPlayer();
        void RenderGround();
        void RenderLight();
        void Update(float deltaTimeSeconds) override;
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;

        void GenerateFastShotgun();

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        implemented::Camera *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        float fov = 3.14f / 4;
        float left = 0.1; 
        float right = 5;
        float bottom = 0.1;
        float top = 5;
        float zNear = 0.1, zFar = 300;
        bool var;

        bool fastShotgunON = false;
        bool renderFastShotgun = true;
        float goShot = 0.1f;

        glm::mat4 modelMatrix;
        float translateX, translateY, translateZ;
        float translateEnemyX, translateEnemyY, translateEnemyZ;

        float mazeX = 0, mazeY = 1, mazeZ = 0;
        float scaleX, scaleY, scaleZ;
        float angularStepOX, angularStepOY, angularStepOZ;

        float playerFixedPosition;

        char maze[100][100];
        int rows, cols;

        bool switch_person;
        bool gameOver = false;
        bool collisionWall = false;

        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        float angle;

        std::vector<fastGun> fastShotgun;
        std::vector<Wall> walls;
        Wall wall;

        int lifePlayer;
        float timeRem;
        glm::mat4 timeMat;
        glm::mat4 heartMat;

        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
