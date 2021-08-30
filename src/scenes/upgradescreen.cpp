#include <functional>
#include <stdio.h>

#include "./upgradescreen.h"

#include "../engine/olcPixelGameEngine.h"
#include "../engine/Global.h"
#include "../engine/Assets.h"

#include "../gameobjects/ship/shipupgrade_shieldgenerator.h"
#include "../gameobjects/ship/Upgrade_BulletHell.h"
#include "../gameobjects/bullets/SnipeShot.h"

#include "./maingame.h"

using namespace RGNDS;

#define ERROR_PRICE_TO_HIGH "You don't have enough points"

#define NUM_TOTAL_UPGRADES 5

struct Upgrade {
	int price;
	const char* title;
	const char* descriptionFile;
	int influence;
	std::string description;
};

static Upgrade upgradeList[] = {
	{   0, "none"                 , "upgrades/none.txt"      , 0   },
	{ 700, "+1 Shield use"        , "upgrades/shield.txt"    , 80  },
	{2050, "Generator capacity up", "upgrades/gencap.txt"    , 30  },
	{3500, "Generator speed + 50%", "upgrades/genreg.txt"    , 30  },
	{2080, "Snipe Shot"           , "upgrades/snipeshot.txt" , 100 },

	{ 400, "Bullet Hell"          , "upgrades/bullethell.txt", 20  },
};

#ifdef DEBUG_BUILD
std::vector<std::vector<int>> categorielist = {
	{ 1 }, { 5 },    /* Acitvateables */
	{ 2 }, { 3 },    /* Ship Control */
	{ 4 }        /* Weapons */
};
#else
std::vector<std::vector<int>> categorielist = {
	{ 1, 5 },    /* Acitvateables */
	{ 2, 3 },    /* Ship Control */
	{ 4 }        /* Weapons */
};
#endif

/*=============================================================================
 * UpgradeScreen
 *===========================================================================*/
UpgradeScreen::UpgradeScreen(MainGameScreen* backscene) : Scene(), backscene(backscene)
{
	selection.transform.pos.y += 200;
	selection.transform.pos.x += 8;

	descriptionlocation.x += 8;
	descriptionlocation.y += 34;

	scorelocation.x += 8.0f;
	scorelocation.y += 8.0f;

	costlocation.x += 8;
	costlocation.y = 180;
}
UpgradeScreen::~UpgradeScreen() {}


void UpgradeScreen::onStart(olc::PixelGameEngine* pge) {

	// Unload previous loaded description
	for (auto upg : upgrade_data)
		upgradeList[upg].description = "";
	upgrade_data.clear();

	// Add one purchaseable from each Group
	for (auto grp : categorielist) {
		if (grp.size() > 1)
			//TODO: Implement weights for randomizer
			upgrade_data.push_back(grp.at(rand() % grp.size()));
		else
			upgrade_data.push_back(grp.at(0));
	}

	upgrade_data.push_back(0);

	for (auto upg : upgrade_data) {
		Upgrade* u = &upgradeList[upg];

		selection.addOption(u->title);
		u->description = Assets::loadText(u->descriptionFile);
	}

	showError = false;

}

void UpgradeScreen::onEnd() {
	upgrade_data.clear();
	selection.clearOptions();
}

bool UpgradeScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {

	if (Global::input->pressed & KEYPAD_DOWN)
		selection.selectNext();
	else if (Global::input->pressed & KEYPAD_UP)
		selection.selectPrev();
	else if (Global::input->pressed & (KEYPAD_A | KEYPAD_START))
	{
		int selected = upgrade_data.at(selection.selected());
		int cost = upgradeList[selected].price * (backscene->game_difficulty);

		if (Global::score >= cost) {
			Global::score -= cost;

			switch (selected) {

			case 0: // none 
				break;

			case 1: // shielduses 
				Global::shipStats->registerNewComponent(new ShipUpgrade_ShieldGenerator());
				break;

			case 2: // Generator capacity 
				Global::shipStats->generatorcapacity += 15;
				break;

			case 3: // Generator regen
				Global::shipStats->generatorrecovery *= 1.5f;
				break;

			case 4: // snipe upgrade
				Global::shipStats->shotenergyconsumption *= 1.2f;
				Global::shipStats->prototypeBullet->addModifier(new SnipeShot());
				break;

			case 5: // Bullet hell
				Global::shipStats->registerNewComponent(new UpgradeBulletHell());
				break;

			}
			return false;
		}
		else {
			showError = true;
		}
	}

	return true;
}


static void _printPGE(
	olc::PixelGameEngine* pge,
	const olc::vf2d pos,
	const char* buffer,
	olc::Pixel pixel,
	olc::vf2d scale = { 1.0f, 1.0f }
) {
	std::string s(buffer);
	pge->DrawStringDecal(
		pos, s,
		pixel,
		scale
	);
}

void UpgradeScreen::onDraw(olc::PixelGameEngine* pge) {

	pge->FillRect(
		22, 199 + (10 * selection.selected()),
		288, 10,
		pix_menubg
	);
	selection.draw(pge);

	if (showError)
		_printPGE(pge, { 16, 116 }, ERROR_PRICE_TO_HIGH, olc::RED);

	char buffer[17]{ 0 };
	std::sprintf(buffer, "Score: % 8d", Global::score);
	_printPGE(pge, scorelocation, buffer, olc::Pixel(0, 80, 255), { 2.0f, 2.0f });

	pge->DrawStringDecal(
		descriptionlocation,
		upgradeList[upgrade_data.at(selection.selected())].description,
		olc::WHITE
	);

	char str[32];
	std::sprintf(
		str,
		"cost: % 24d",
		(int)(upgradeList[upgrade_data.at(selection.selected())].price * (backscene->game_difficulty))
	);
	_printPGE(pge, costlocation, str, olc::WHITE);

}

Scene* UpgradeScreen::nextScene() { return backscene; }

