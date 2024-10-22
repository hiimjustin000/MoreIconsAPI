#include <random>
#include <MoreIconsAPI.hpp>

using namespace geode::prelude;

#include <Geode/modify/GJGarageLayer.hpp>
class $modify(MIAGarageLayer, GJGarageLayer) {
    bool init() {
        if (!GJGarageLayer::init()) return false;

        auto menu = getChildByID("shards-menu");
        auto myButton = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
            this,
            menu_selector(MIAGarageLayer::onMyButton)
        );
        myButton->setID("my-button"_spr);
        menu->addChild(myButton);
        menu->updateLayout();

        return true;
    }

    int randomNumber(int min, int max) {
        static std::mt19937 mt(std::random_device{}());
        return std::uniform_int_distribution<int>(min, max)(mt);
    }

    void onMyButton(CCObject*) {
        // Get the first loaded icon
        auto iconType = std::vector<IconType> {
            IconType::Cube, IconType::Ship, IconType::Ball, IconType::Ufo, IconType::Wave,
            IconType::Robot, IconType::Spider, IconType::Swing, IconType::Jetpack
        }[randomNumber(0, 8)];
        auto icons = MoreIconsAPI::vectorForType(iconType);
        if (icons.empty()) return;

        // Get a random player
        auto icon = icons[randomNumber(0, icons.size() - 1)];
        m_playerObject->updatePlayerFrame(1, iconType);
        MoreIconsAPI::updateSimplePlayer(m_playerObject, icon, iconType);
    }
};
