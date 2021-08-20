#ifndef __SPACEOBJ_H__
#define __SPACEOBJ_H__

#include <functional>
#include "core/olcPixelGameEngine.h"
#include "core/transform.h"

#include "wraparoundrenderer.h"

class SpaceObj : public RGNDS::Transform {
public:

    SpaceObj();
    SpaceObj(float objectRadius);

    float moveVelocity;

    // Setters 
    
    /* sets the Angle that thie object will face */
    void setAngle(float radiants);

    /* defines the direction the object is moving in */ 
    void setDirection(olc::vf2d directionVector);

    /* define a new random direction for the object */
    void setRandomDirection();

    /* moves the object into its direction by its velocity per second
     * \param deltaTime  defines how much percent of a second has passed since the the last movement
     */
    void updatePosition(float deltaTime);


    /* moves the object into its direction by a fixed amount of pixels */
    void movePixelDistance(float px);

    // Getters
    float getAngle();

    /* normal vector for the direction the object is moving in */
    olc::vf2d getDirection();

    /* fills *pos and *radius with the collision sphere data */
    void getCollisionSphere(olc::vf2d *pos, float *radius);

    /* draws the object according to its "WrapAroundRenderer"
     * \param drawingLambda - is called 1-4 times (depending on the objects position)
     *                        the function is given a paramter that describes where
     *                        the object should be drawn
     */
    void draw(std::function<void(RGNDS::Transform*)> drawingLambda);

    // Virtual functionn

    /* called once per cycle 
     * \param deltaTime  defines how much percent of a second has passed since the the last update
     *
     * \return a list of new SpaceObj s, that will be spawned into the world, at the
     *         start of the next cycle
     *         (or nullptr) if no new object should be spawned
     */
    virtual std::vector<SpaceObj*>* onUpdate(float deltaTime) { return nullptr; };

    /* called once per cycle after everything has been updated */
    virtual void onDraw(olc::PixelGameEngine* pge ){};

protected:
    WrapAroundRenderer renderer;
    float objRadius;

private:
    float moveAngle;
    olc::vf2d moveDirection;

};

#endif
