#ifndef __ScorePopup_H__
#define __ScorePopup_H__

#include "../olcPixelGameEngine.h"

#include <vector>
#include <functional>

#include "../spaceobj.h"


class ScorePopup : public SpaceObj {
public:

    static void cleanup();
    static ScorePopup* spawn(short score, float x, float y);

    /** \brief deletes all dead instances from the memeory */
    static void refreshInstanceList();

    ScorePopup(short score, float x, float y);
    virtual~ScorePopup();

    std::vector<SpaceObj*>* onUpdate(float deltaTime) override;
    void onDraw(olc::PixelGameEngine*) override;

    void kill() override;

protected:
    short score;        // Keeps track of what score is displayed
    short lifetime;      // for how many ticks this popup will stay 

private:
    static std::vector<ScorePopup*> _instances;

    static bool bDirty;

};

#endif
