#include "./Collision.h"
#include <math.h>


namespace RGNDS::Physics {
/*==============================================================================
 * Collision
 *============================================================================*/
    static bool _collectOverlapData(
            Collision* overlapdata,
            float dx, float dy,
            float radius1, float radius2
        ) {
        
        float dstP = (dx * dx) + (dy * dy);
        float dstR = radius1 + radius2;
        dstR *= dstR;

        if(dstP < dstR){
            if(overlapdata != nullptr) {
                overlapdata->C2COverlapDist = std::sqrt(dstR);
                overlapdata->C2COverlapImpact = std::sqrt(dstR-dstP);
                overlapdata->overlapDir.x = dx / overlapdata->C2COverlapDist;
                overlapdata->overlapDir.y = dy / overlapdata->C2COverlapDist;
            }
            return true;
        }

        return false;
    }

    bool Collision::checkCircleOnCircle(
            float x1, float y1, float radius1,
            float x2, float y2, float radius2,
            Collision* overlapdata )
    {
        return _collectOverlapData(
                overlapdata, 
                x1 - x2, y1 - y2,
                radius1, radius2
        );
    }

    bool Collision::checkCircleOnCircle(
            olc::vf2d* const pos1, float radius1, 
            olc::vf2d* const pos2, float radius2, 
            Collision* overlapdata
    ){
        return _collectOverlapData(
                overlapdata,
                pos1->x-pos2->x, pos1->y-pos2->y,
                radius1, radius2
        );
    }

    bool Collision::checkCircleOnCircle(
            Collision::Circle* c1, 
            Collision::Circle* c2,
            Collision* overlapdata
    ) {

        return _collectOverlapData (
                overlapdata,
                c1->x - c2->x, c1->y - c2->y,
                c1->radius, c2->radius
        );
    }

    bool Collision::checkCircleOnCircle(
            Collision::Circle c1, 
            std::vector<Collision::Circle> ca,
            Collision* overlapdata
    ) {
        bool r = false;
        for(auto c2 : ca) {
            r = _collectOverlapData (
                overlapdata,
                c1.x - c2.x, c1.y - c2.y,
                c1.radius, c2.radius
            );

            if(r) break;
        }
        return r;
    }

    Collision::Collision() {}
    Collision::~Collision() {}
}
