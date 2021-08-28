#pragma once

class ShipEngine
{
    public:
        float acceleration;

        void accelerate(float deltaTime);
        void decerlerate(float deltaTime);
};
