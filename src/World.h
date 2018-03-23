//
// Created by Engin Manap on 13.02.2016.
//

#ifndef LIMONENGINE_WORLD_H
#define LIMONENGINE_WORLD_H

#include<vector>
#include <tinyxml2.h>
#include <unordered_map>
#include "PhysicalRenderable.h"
#include "GLHelper.h"
#include "glm/glm.hpp"
#include "InputHandler.h"
#include "FontManager.h"
#include "AI/Actor.h"

class btGhostPairCallback;
class Camera;
class Model;
class SkyBox;
class BulletDebugDrawer;
class Light;
class AIMovementGrid;

class GUILayer;
class GUIText;
class GUIFPSCounter;
class GUITextDynamic;

class GameObject;
class Player;
class PhysicalPlayer;
class FreeMovingPlayer;
class FreeCursorPlayer;
class ImGuiHelper;
class AssetManager;

class World {
    friend class WorldLoader;
    AssetManager* assetManager;
    Options* options;
    uint32_t totalObjectCount = 1;
    std::unordered_map<uint32_t, PhysicalRenderable *> objects;
    std::vector<Light *> lights;
    std::vector<GUILayer *> guiLayers;
    std::vector<Actor*> actors;
    AIMovementGrid *grid = nullptr;
    SkyBox *sky = nullptr;
    GLHelper *glHelper;
    long gameTime = 0;
    GUITextDynamic* trd;
    glm::vec3 worldAABBMin= glm::vec3(std::numeric_limits<float>::max());
    glm::vec3 worldAABBMax = glm::vec3(std::numeric_limits<float>::min());

    GLSLProgram *shadowMapProgramDirectional, *shadowMapProgramPoint;
    FontManager fontManager;
    PhysicalPlayer* physicalPlayer;
    FreeCursorPlayer* editorPlayer = nullptr;
    FreeMovingPlayer* debugPlayer = nullptr;
    Player* currentPlayer;
    Camera* camera;
    BulletDebugDrawer *debugDrawer;
    GUIText *cursor;
    btGhostPairCallback *ghostPairCallback;
    btDiscreteDynamicsWorld *dynamicsWorld;
    std::vector<btRigidBody *> rigidBodies;


    btBroadphaseInterface *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;
    bool inEditorMode = false;
    ImGuiHelper *imgGuiHelper;
    GameObject* pickedObject = nullptr;
    bool availableAssetsLoaded = false;

    void handlePlayerInput(InputHandler &inputHandler);

    bool checkPlayerVisibility(const glm::vec3 &from, const std::string &fromName);

    ActorInformation fillActorInformation(int j);

    void updateWorldAABB(glm::vec3 aabbMin, glm::vec3 aabbMax);

    void addModelToWorld(Model *xmlModel);

    GameObject * getPointedObject() const;


    void addActor(Actor *actor);

    void createGridFrom(const glm::vec3 &aiGridStartPoint);

    void setSky(SkyBox *skyBox);

    void addLight(Light *light);

    World(AssetManager *assetManager, GLHelper *, Options *options);

    void ImGuiFrameSetup();
public:
    ~World();

    void play(Uint32, InputHandler &);

    void render();

    uint32_t getNextObjectID() {
        return totalObjectCount++;
    }


};

#endif //LIMONENGINE_WORLD_H
