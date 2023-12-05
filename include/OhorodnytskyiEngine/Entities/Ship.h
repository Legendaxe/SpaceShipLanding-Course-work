#pragma once
#include "OhorodnytskyiEngine/Entities/Entity.h"

namespace OhorodnytskyiEngine
{
    class Ship : public Entity
    {
    private:
        bool _engineStarted;

        void CheckEngine();

        bool DetectCollision();
    public:
        Ship(const std::string filePath = "Resources/Ship.png");

        void StartEngine();
        void StopEngine();

        void ProcessMove();

        void rotate(float angle);
    };

}