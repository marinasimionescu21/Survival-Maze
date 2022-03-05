#include "lab_m1/Tema2/Tema2.h"
#include "lab_m1/Tema2/Transform2D.h"
#include "lab_m1/Tema2/object2D.h"


#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace m1;

#define MAX_TIME 100

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    renderCameraTarget = false;

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    {
        cout << "=====================================" << endl;
        cout << "Game Started!" << endl << "You have 3 lives" << endl;
        cout << "Have fun" << endl;
        cout << "=====================================" << endl << endl;
    }

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("wall");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("shotgun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("heart");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "heart.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("timeBar");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("consumeBar");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Shader *shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Shader* shader = new Shader("EnemyShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "EnemyVS.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "EnemyFS.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        lightPosition = glm::vec3(0, 3, 1);
        materialShininess = 50;
        materialKd = 1.0f;
        materialKs = 1.0f;
        switch_person = false;
        lifePlayer = 3;
    }

    {
        timeRem = MAX_TIME;
        translateX = 0;
        translateY = 0;
        translateZ = 0;
    }

    {
        translateEnemyX = 0;
        translateEnemyY = 1.25f;
        translateEnemyZ = 0;
    }

    {
        scaleX = 1;
        scaleY = 1;
        scaleZ = 1;
    }

    {
        rows = 0;
        cols = 0;
    }

    {
        ifstream infile;
        string filename;
        int choice;

        choice = (rand() % 4);

        switch (choice) {
            case 0:
                filename = "maze1.txt";
                break;

            case 1:
                filename = "maze2.txt";
                break;

            case 2:
                filename = "maze3.txt";
                break;

            case 3:
                filename = "maze4.txt";
                break;

            case 4:
                filename = "maze5.txt";
                break;


        }

        rows = 0;
        cols = 0;

        infile.open(filename);
        cout << "Maze: " << filename << endl;

        if (!infile.is_open()) {
            cout << "Error reading file" << endl;
            return;
        }

        infile >> rows;											//reads number of rows
        infile >> cols;											//reads number of columns

        for (int k = 0; k < rows; k++) {						//reads and stores rest of maze
            for (int i = 0; i < cols; i++) {
                infile >> maze[k][i];
            }
        }
    }

    {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (maze[i][j] == '1') {
                     wall.Tx = mazeX;
                     wall.Ty = mazeY;
                     wall.Tz = mazeZ;
                     walls.push_back(wall);
                }
                mazeX += 1;
            }
            mazeX = 0;
            mazeZ += 1;
        }

        

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (maze[i][j] == '2') {
                    translateEnemyX = i;
                    translateEnemyZ = j;
                }
            }
        }
    }
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::GenerateFastShotgun()
{
    for (int i = 0; i < fastShotgun.size(); i++) {
        glm::mat4 modelMatrix = glm::mat4(1);
        fastShotgun[i].x -= goShot * sin(fastShotgun[i].angle) * fastShotgun[i].speed;
        fastShotgun[i].z -= goShot * cos(fastShotgun[i].angle) * fastShotgun[i].speed;

        modelMatrix *= transform3D::Translate(fastShotgun[i].x, fastShotgun[i].y + 0.7f, fastShotgun[i].z);
        modelMatrix *= transform3D::Scale(0.1f, 0.1f, 0.1f);
        RenderSimpleMesh(meshes["shotgun"], shaders["LabShader"], modelMatrix, glm::vec3(0.541f, 0.169f, 0.88f));

        for (int i = 0; i < fastShotgun.size(); i++) {
            if (fastShotgun[i].z < (translateZ - 30.0f) || fastShotgun[i].x < (translateX - 30.0f) ||
                fastShotgun[i].z >(translateZ + 30.0f) || fastShotgun[i].x >(translateX + 30.0f)) {
                fastShotgun.erase(fastShotgun.begin() + i);
            }
        }
    }
}

void Tema2::RenderPlayer() {

    float rotationangle = RADIANS(180);

    { //cap
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = transform3D::Translate(0, 1.09f, 0); // centru
        modelMatrix *= transform3D::Translate(translateX, 0, translateZ);
        modelMatrix *= transform3D::Scale(0.2f, 0.2f, 0.2f); // dimensiunea
        modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, -1, 0));
        modelMatrix = glm::rotate(modelMatrix, rotationangle, glm::vec3(0, -1, 0));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.824f, 0.706f, 0.549f));
    }
    { //corp
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = transform3D::Translate(0, 0.7f, 0); // centru
        modelMatrix *= transform3D::Translate(translateX, 0, translateZ);
        modelMatrix *= transform3D::Scale(0.4f, 0.5f, 0.4f);
        modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, -1, 0));
        modelMatrix = glm::rotate(modelMatrix, rotationangle, glm::vec3(0, -1, 0));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.0f, 0.5f, 0.5f));
    }
    { // brat stang
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = transform3D::Translate(-0.3f, 0.7f, 0); // centru
        modelMatrix *= transform3D::Translate(translateX, 0, translateZ);
        modelMatrix *= transform3D::Scale(0.1f, 0.5f, 0.1f);
        modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, -1, 0));
        modelMatrix = glm::rotate(modelMatrix, rotationangle, glm::vec3(0, -1, 0));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.0f, 0.5f, 0.5f));
    }
    { // brat drept
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = transform3D::Translate(0.3f, 0.7f, 0); // centru
        modelMatrix *= transform3D::Translate(translateX, 0, translateZ);
        modelMatrix *= transform3D::Scale(0.1f, 0.5f, 0.1f);
        modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, -1, 0));
        modelMatrix = glm::rotate(modelMatrix, rotationangle, glm::vec3(0, -1, 0));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.0f, 0.5f, 0.5f));
    }
    { // picior stang
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = transform3D::Translate(0.15f, 0.25f, 0); // centru
        modelMatrix *= transform3D::Translate(translateX, 0, translateZ);
        modelMatrix *= transform3D::Scale(0.2f, 0.5f, 0.1f);
        modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, -1, 0));
        modelMatrix = glm::rotate(modelMatrix, rotationangle, glm::vec3(0, -1, 0));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.255f, 0.412f, 0.882f));
    }
    { // picior drept
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = transform3D::Translate(-0.15f, 0.25f, 0); // centru
        modelMatrix *= transform3D::Translate(translateX, 0, translateZ);
        modelMatrix *= transform3D::Scale(0.2f, 0.5f, 0.1f);
        modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, -1, 0));
        modelMatrix = glm::rotate(modelMatrix, rotationangle, glm::vec3(0, -1, 0));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.255f, 0.412f, 0.882f));
    }
}

void Tema2::RenderLight() {

    float rotationangle = RADIANS(180);

    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = transform3D::Translate(0, 1.5f, 0);
    modelMatrix *= transform3D::Translate(translateX, 0, translateZ);
    modelMatrix *= transform3D::Scale(0.1f, 0.1f, 0.1f);
    modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, -1, 0));
    modelMatrix = glm::rotate(modelMatrix, rotationangle, glm::vec3(0, -1, 0));
    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, glm::vec3(0, 0.5, 0));
}

void Tema2::RenderGround() {
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Scale(1, 1, 1);
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0.941f, 0.961f));
    }
}

void Tema2::Update(float deltaTimeSeconds)
{

    while (lifePlayer != 0)
    {
        float timeScale = timeRem / MAX_TIME;
        timeMat = glm::mat4(1);
        timeMat *= transform3D::Translate(-1.5f, 2.7f, 0);
        timeMat *= transform3D::Translate(translateX, translateY, translateZ);
        timeMat *= transform3D::Scale(timeScale, 0.15f, 0);
        RenderSimpleMesh(meshes["timeBar"], shaders["LabShader"], timeMat, glm::vec3(0, 1, 0));
        timeMat = glm::mat4(1);
        timeMat *= transform3D::Translate(-1, 2.7f, 0);
        timeMat *= transform3D::Translate(translateX, translateY, translateZ);
        timeMat *= transform3D::Scale(1.0f - timeScale, 0.15f, 0);
        RenderSimpleMesh(meshes["consumeBar"], shaders["LabShader"], timeMat, glm::vec3(1, 0.271f, 0));

        {
            timeRem -= deltaTimeSeconds;
        }
        break;
    }

    {
        if (lifePlayer == 3) {
            timeMat = glm::mat4(1);
            timeMat *= transform3D::Translate(1.5f, 2.5f, 0);
            timeMat *= transform3D::Translate(translateX, translateY, translateZ);
            timeMat *= transform3D::Scale(0.02f, 0.02f, 0.02f);
            timeMat *= transform3D::RotateOX(93);
            RenderSimpleMesh(meshes["heart"], shaders["LabShader"], timeMat, glm::vec3(0, 1, 0));
        }
        else if (lifePlayer == 2) {
            timeMat = glm::mat4(1);
            timeMat *= transform3D::Translate(1.5f, 2.5f, 0);
            timeMat *= transform3D::Translate(translateX, translateY, translateZ);
            timeMat *= transform3D::Scale(0.02f, 0.02f, 0.02f);
            timeMat *= transform3D::RotateOX(93);
            RenderSimpleMesh(meshes["heart"], shaders["LabShader"], timeMat, glm::vec3(1, 0.549f, 0));
        }
        else if (lifePlayer == 1) {
            timeMat = glm::mat4(1);
            timeMat *= transform3D::Translate(1.5f, 2.5f, 0);
            timeMat *= transform3D::Translate(translateX, translateY, translateZ);
            timeMat *= transform3D::Scale(0.02f, 0.02f, 0.02f);
            timeMat *= transform3D::RotateOX(93);
            RenderSimpleMesh(meshes["heart"], shaders["LabShader"], timeMat, glm::vec3(0.863f, 0.078f, 0.235f));
        }
    }


    RenderLight();
    RenderPlayer();
    RenderGround();

    if (((translateEnemyZ + translateZ) <= 0.3f && (translateEnemyX - translateX <= 3.5f)) && lifePlayer > 0) {
        _sleep(1000);
        lifePlayer--;
        cout << "Ai pierdut o viata! Ti-au mai ramas " << lifePlayer << " vieti" << endl;
    }

    if (lifePlayer == 0 && gameOver == 0 || (int)timeRem == 0) {
        gameOver = 1;
        cout << "\t\t\t=======================" << endl;
        cout << endl;
        cout << "\t\t\t=      GAME OVER      =" << endl;
        cout << endl;
        cout << "\t\t\t=======================" << endl;
    }

    if (!gameOver) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (maze[i][j] == '1') {
                    for (int k = 0; k < walls.size(); k++) {
                        glm::mat4 modelMatrix = glm::mat4(1);
                        modelMatrix *= transform3D::Translate(0, 0, 0);
                        modelMatrix *= transform3D::Translate(walls[k].Tx - 3.5f, walls[k].Ty, -walls[k].Tz - 1);
                        modelMatrix *= transform3D::Scale(1, 1, 1);
                        RenderSimpleMesh(meshes["wall"], shaders["LabShader"], modelMatrix, glm::vec3(0.753f, 0.753f, 0.753f));

                    }
                }
                if (maze[i][j] == '2') {
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix *= transform3D::Translate(-0.4f, 0, 0.4f);
                    modelMatrix *= transform3D::Translate(translateEnemyX - 3.4f, translateEnemyY - 0.5f, -translateEnemyZ - 1);

                    modelMatrix *= transform3D::Scale(0.2f, 0.2f, 0.2f);
                    RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, glm::vec3(0.545f, 0.271f, 0.075f));

                    if (translateEnemyZ == j && (translateEnemyX >= i && translateEnemyX <= i + 0.65f)) {
                        translateEnemyX += 0.05f;
                    }
                    else if (translateEnemyX >= (i + 0.65f) && ((translateEnemyZ >= j && translateEnemyZ <= j + 0.65f))) {
                        translateEnemyZ += 0.05f;
                    }
                    else if (translateEnemyZ >= (j + 0.65f) && (translateEnemyX >= i && translateEnemyX <= i + 1.65f)) {
                        translateEnemyX -= 0.05f;
                    }
                    else if (translateEnemyX >= (i - 0.1f) && (translateEnemyZ >= j && translateEnemyZ <= j + 1.65f)) {
                        translateEnemyZ -= 0.05f;
                    }
                    else {
                        translateEnemyX = i;
                        translateEnemyZ = j;
                    }

                    for (int i = 0; i < fastShotgun.size(); i++) {
                        if (translateEnemyX - fastShotgun[i].x < 3.74f && translateZ - (-fastShotgun[i].z) < 0.74f) {
                            RenderSimpleMesh(meshes["sphere"], shaders["EnemyShader"], modelMatrix, glm::vec3(0.545f, 0, 0));
                            translateEnemyY = -10;
                        }
                    }

                }
            }
        }


    }

        if (renderFastShotgun == true) {
            GenerateFastShotgun();
        }
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniforms for light & material properties
    // TODO(student): Set light position uniform
    GLint light_pos = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(light_pos, 1, glm::value_ptr(lightPosition));

    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    // TODO(student): Set eye position (camera position) uniform
    GLint eye_pos = glGetUniformLocation(shader->program, "eye_position");
    glUniform3fv(eye_pos, 1, glm::value_ptr(eyePosition));

    // TODO(student): Set material property uniforms (shininess, kd, ks, object color)
    GLint shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(shininess, materialShininess);

    GLint kd_pos = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(kd_pos, materialKd);

    GLint ks_pos = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(ks_pos, materialKs);

    GLint colorObj = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(colorObj, 1, glm::value_ptr(color));

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    if (switch_person)
        viewMatrix = glm::lookAt(glm::vec3(translateX, translateY + 1, translateZ - 0.1f), glm::vec3(0, 0, -100), glm::vec3(0, 2, 0));
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
    float cameraSpeed = 2.0f;

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(1, 1, 1);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

        if (window->KeyHold(GLFW_KEY_W) ) {
                    // TODO(student): Translate the camera forward
            lightPosition -= forward * deltaTime * cameraSpeed;
            translateZ -= deltaTime * cameraSpeed * cos(angle);
            translateX -= deltaTime * cameraSpeed * sin(angle);
            camera->TranslateForward(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_A) && collisionWall == false) {
                // TODO(student): Translate the camera to the left
            lightPosition -= right * deltaTime * cameraSpeed;
            translateX -= deltaTime * cameraSpeed * cos(angle);
            translateZ += deltaTime * cameraSpeed * sin(angle);
            camera->TranslateRight(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_S) && collisionWall == false) {
                // TODO(student): Translate the camera backward
            lightPosition += forward * deltaTime * cameraSpeed;
            translateZ += deltaTime * cameraSpeed * cos(angle);
            translateX += deltaTime * cameraSpeed * sin(angle);
            camera->TranslateForward(-deltaTime * cameraSpeed);
        }
        if (window->KeyHold(GLFW_KEY_D) && collisionWall == false) {
                // TODO(student): Translate the camera to the right
            lightPosition += right * deltaTime * cameraSpeed;
            translateX += deltaTime * cameraSpeed * cos(angle);
            translateZ -= deltaTime * cameraSpeed * sin(angle);
            camera->TranslateRight(deltaTime * cameraSpeed);
        }
       

    }
    // TODO(student): Change projection parameters. Declare any extra
    // variables you might need in the class header. Inspect this file
    // for any hardcoded projection arguments (can you find any?) and
    // replace them with those extra variables.
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections

    if (key == GLFW_KEY_2) {
        var = false;
        fastShotgunON = true;
    }

    if (key == GLFW_KEY_C) {
        if (switch_person) {
            camera->Set(glm::vec3(0, 1, -0.5f), glm::vec3(0, 1, -1), glm::vec3(0, 1, 0));
            
        }
        else {
            camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
        }

        switch_person = !switch_person;
    }
}

void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;
       
        camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
        camera->RotateFirstPerson_OY(-sensivityOY * deltaX);
        angle = sensivityOX * deltaX;
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        if (fastShotgunON == true && switch_person == true) {
            fastGun fastGunObject;
            fastGunObject.angle = angle;
            fastGunObject.x = translateX;
            fastGunObject.y = translateY;
            fastGunObject.z = translateZ;
            fastShotgun.push_back(fastGunObject);
        }
    }
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
