#ifndef __ShipComponent_H__
#define __ShipComponent_H__

#include <vector>
#include "spaceobj.h"
#include "olcPixelGameEngine.h"

class Ship;
class ShipStats;

class ShipComponent {
public:
    virtual ~ShipComponent(){};

    /* Called, once the component is attached to a ship 
     * \return  false = the component will be deleted */
    virtual bool initShipComponent(ShipStats*, Ship*) { return true; }

    /* Called, once the component is removed from the ship 
     * \return  false = the component will be deleted */
    virtual bool deinitShipComponent(ShipStats*) { return true; }

    /* Called by the ship once per cycle 
     * (tell the component, that a new cycle has begun))
     * \return  false = the component will be deleted */
    virtual bool updateShipComponent(float deltaTime) = 0;

    /* Called, when the player used the "KEYPAD_A" Key 
     * This is the point, where the component can spawn new items on the screen, or make changes to the ship
     * \return true = the component stays active
     *         false = the component will be deleted */
    virtual bool invokeShipComponent(ShipStats*, Ship*) = 0;

    /* Called by the ship one per cycle, after everything is updated 
     * \return defines if an icon has been drawn within the component list section of the screen 
     *         true = the component list renderer will advance to the next free drawable spot on the screen
     */
    virtual bool drawShipComponent(ShipStats* stats, Ship* ship, olc::PixelGameEngine* pge, olc::vf2d componentListIconCoordinates) = 0;
};

#endif
