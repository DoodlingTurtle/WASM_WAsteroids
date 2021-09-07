#include <functional>
#include <stdio.h>

#include "./upgradescreen.h"

#include "../engine/olcPixelGameEngine.h"
#include "../engine/Global.h"
#include "../engine/Assets.h"

#include "../gameobjects/ship/shipupgrade_shieldgenerator.h"
#include "../gameobjects/ship/Upgrade_BulletHell.h"
#include "../gameobjects/bullets/SnipeShot.h"
#include "../gameobjects/ship/cannons/DualCannon.h"

#include "./maingame.h"

using namespace RGNDS;

#define ERROR_PRICE_TO_HIGH "You don't have enough points"
#define NUM_TOTAL_UPGRADES 5

struct Upgrade {
	int price;
	const char* title;
	const char* descriptionFile;
	int influence;
	bool singleuse;

	std::function<void()> fnc;

	std::string description;
};


static Upgrade upgradeList[] = {
	{   0, "none"                 , "upgrades/none.txt"      , 0 , false, []() {} },

	{ 700, "+1 Shield use"        , "upgrades/shield.txt"    , 80, false, []() {
		Global::shipStats->registerNewComponent(new ShipUpgrade_ShieldGenerator());
	} },

	{2050, "Generator capacity up", "upgrades/gencap.txt"    , 30, false, []() {
		Global::shipStats->generatorcapacity += 15;
	} },

	{3500, "Generator speed + 50%", "upgrades/genreg.txt"    , 30, false, []() {
		Global::shipStats->generatorrecovery *= 1.5f;
	} },

	{2080, "Snipe Shot"           , "upgrades/snipeshot.txt" , 20, true , []() {
		Global::shipStats->shotenergyconsumption += 6.0f;
		Global::shipStats->prototypeBullet->addModifier(new SnipeShot());
	} },

	{ 400, "Bullet Hell"          , "upgrades/bullethell.txt", 20, false, []() {
		Global::shipStats->registerNewComponent(new UpgradeBulletHell());
	} },

	{1200, "Dual Shot"            , "upgrades/dualshot.txt"  , 80, true , []() {
		delete Global::shipStats->shipCannon;
		Global::shipStats->shipCannon = new DualCannon();
		Global::shipStats->shotenergyconsumption += 10;
	} }
};

#ifdef DEBUG_BUILD
static const std::vector<std::vector<int>> categorielist = {
	{ 1 }, { 5 },    /* Acitvateables */
	{ 2 }, { 3 },    /* Ship Control */
	{ 4 }, { 6 }     /* Weapons */
};
#else
static const std::vector<std::vector<int>> categorielist = {
	{ 1, 5 },    /* Acitvateables */
	{ 2, 3 },    /* Ship Control */
	{ 4, 6 }     /* Weapons */
};
#endif

/*=============================================================================
 * UpgradeScreen
 *===========================================================================*/

std::vector<std::vector<int>> UpgradeScreen::upgrade_pool = {};

UpgradeScreen::UpgradeScreen(MainGameScreen* backscene) :
	Scene(), backscene(backscene), showError(false)
	, descriptionlocation(8, 34)
	, scorelocation(8, 8)
	, costlocation(8, 180)
	, upgrade_slotdata(std::vector<UpgradeScreen::UpgradeSlot>())
{
	selection.transform.pos.y += 200;
	selection.transform.pos.x += 8;
}
UpgradeScreen::~UpgradeScreen() {}

void UpgradeScreen::onStart(olc::PixelGameEngine* pge) {

	// Unload previous loaded description
	for (auto upg : upgrade_data)
		upgradeList[upg].description = "";
	upgrade_data.clear();

	// Add one purchaseable from each Group
	for (int a = 0; a < upgrade_pool.size(); a++) {
		auto grp = upgrade_pool.at(a);

		int grpIndex = 0;
		if (grp.size() > 1)
			grpIndex = rand() % grp.size(); //TODO: Implement weights for randomizer

		upgrade_data.push_back(grp.at(grpIndex));
		upgrade_slotdata.push_back({ a, grpIndex, grp.at(grpIndex) });
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

	backscene->updateBGM();

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

			upgradeList[selected].fnc();
			if (upgradeList[selected].singleuse) {
				auto slot_data = upgrade_slotdata.at(selection.selected());

				upgrade_pool.at(slot_data.grp).erase(upgrade_pool.at(slot_data.grp).begin() + slot_data.grpIndex);
				if (upgrade_pool.at(slot_data.grp).size() == 0) 
					upgrade_pool.erase(upgrade_pool.begin() + slot_data.grp);
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

void UpgradeScreen::resetPool() { upgrade_pool = categorielist; }
