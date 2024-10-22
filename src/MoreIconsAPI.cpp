#include <MoreIconsAPI.hpp>

using namespace geode::prelude;

std::vector<std::string> MoreIconsAPI::vectorForType(IconType type) {
    switch (type) {
        case IconType::Cube: return getMIValue<std::vector<std::string>>("icons", {});
        case IconType::Ship: return getMIValue<std::vector<std::string>>("ships", {});
        case IconType::Ball: return getMIValue<std::vector<std::string>>("balls", {});
        case IconType::Ufo: return getMIValue<std::vector<std::string>>("ufos", {});
        case IconType::Wave: return getMIValue<std::vector<std::string>>("waves", {});
        case IconType::Robot: return getMIValue<std::vector<std::string>>("robots", {});
        case IconType::Spider: return getMIValue<std::vector<std::string>>("spiders", {});
        case IconType::Swing: return getMIValue<std::vector<std::string>>("swings", {});
        case IconType::Jetpack: return getMIValue<std::vector<std::string>>("jetpacks", {});
        case IconType::Special: return getMIValue<std::vector<std::string>>("trails", {});
        default: return {};
    }
}

std::string MoreIconsAPI::savedForType(IconType type, bool dual) {
    auto isDual = Loader::get()->isModLoaded("weebify.separate_dual_icons") && dual;
    switch (type) {
        case IconType::Cube: return isDual ? "icon-dual" : "icon";
        case IconType::Ship: return isDual ? "ship-dual" : "ship";
        case IconType::Ball: return isDual ? "ball-dual" : "ball";
        case IconType::Ufo: return isDual ? "ufo-dual" : "ufo";
        case IconType::Wave: return isDual ? "wave-dual" : "wave";
        case IconType::Robot: return isDual ? "robot-dual" : "robot";
        case IconType::Spider: return isDual ? "spider-dual" : "spider";
        case IconType::Swing: return isDual ? "swing-dual" : "swing";
        case IconType::Jetpack: return isDual ? "jetpack-dual" : "jetpack";
        case IconType::Special: return isDual ? "trail-dual" : "trail";
        default: return "";
    }
}

std::string MoreIconsAPI::activeForType(IconType type, bool dual) {
    auto savedType = savedForType(type, dual);
    return !savedType.empty() ? getMIValue<std::string>(savedType, "") : "";
}

bool MoreIconsAPI::hasIcon(const std::string& icon, IconType type) {
    auto vec = vectorForType(type);
    return !vec.empty() && std::find(vec.begin(), vec.end(), icon) != vec.end();
}

void MoreIconsAPI::updateSimplePlayer(SimplePlayer* player, const std::string& icon, IconType type) {
    if (!player || icon.empty() || !hasIcon(icon, type)) return;

    if (type == IconType::Robot) {
        updateRobotSprite(player->m_robotSprite, icon, type);
        return;
    }
    else if (type == IconType::Spider) {
        updateRobotSprite(player->m_spiderSprite, icon, type);
        return;
    }

    auto sfc = CCSpriteFrameCache::get();
    auto iconFrame = fmt::format("hiimjustin000.more_icons/{}_001.png", icon);
    auto iconFrame2 = fmt::format("hiimjustin000.more_icons/{}_2_001.png", icon);
    auto iconFrame3 = fmt::format("hiimjustin000.more_icons/{}_3_001.png", icon);
    auto iconFrameExtra = fmt::format("hiimjustin000.more_icons/{}_extra_001.png", icon);
    auto iconFrameGlow = fmt::format("hiimjustin000.more_icons/{}_glow_001.png", icon);

    player->m_firstLayer->setDisplayFrame(sfc->spriteFrameByName(iconFrame.c_str()));
    player->m_secondLayer->setDisplayFrame(sfc->spriteFrameByName(iconFrame2.c_str()));
    auto firstCenter = player->m_firstLayer->getContentSize() / 2;
    player->m_secondLayer->setPosition(firstCenter);
    player->m_outlineSprite->setDisplayFrame(sfc->spriteFrameByName(iconFrameGlow.c_str()));
    player->m_outlineSprite->setPosition(firstCenter);
    if (type == IconType::Ufo) {
        player->m_birdDome->setDisplayFrame(sfc->spriteFrameByName(iconFrame3.c_str()));
        player->m_birdDome->setPosition(firstCenter);
    }
    auto extraFrame = sfc->spriteFrameByName(iconFrameExtra.c_str());
    auto extraVisible = doesExist(extraFrame);
    player->m_detailSprite->setVisible(extraVisible);
    if (extraVisible) {
        player->m_detailSprite->setDisplayFrame(extraFrame);
        player->m_detailSprite->setPosition(firstCenter);
    }
}

void MoreIconsAPI::updateRobotSprite(GJRobotSprite* sprite, const std::string& icon, IconType type) {
    if (!sprite || icon.empty() || !hasIcon(icon, type)) return;

    sprite->setBatchNode(nullptr);
    sprite->m_paSprite->setBatchNode(nullptr);

    auto spriteParts = sprite->m_paSprite->m_spriteParts;
    auto spriteFrameCache = CCSpriteFrameCache::get();
    for (int i = 0; i < spriteParts->count(); i++) {
        auto spritePart = static_cast<CCSpritePart*>(spriteParts->objectAtIndex(i));
        auto tag = spritePart->getTag();

        auto spriteFrame = fmt::format("hiimjustin000.more_icons/{}_{:02}_001.png", icon, tag);
        auto spriteFrame2 = fmt::format("hiimjustin000.more_icons/{}_{:02}_2_001.png", icon, tag);
        auto spriteFrameExtra = fmt::format("hiimjustin000.more_icons/{}_{:02}_extra_001.png", icon, tag);
        auto spriteFrameGlow = fmt::format("hiimjustin000.more_icons/{}_{:02}_glow_001.png", icon, tag);

        spritePart->setBatchNode(nullptr);
        spritePart->setDisplayFrame(spriteFrameCache->spriteFrameByName(spriteFrame.c_str()));
        if (auto secondSprite = static_cast<CCSprite*>(sprite->m_secondArray->objectAtIndex(i))) {
            secondSprite->setBatchNode(nullptr);
            secondSprite->setDisplayFrame(spriteFrameCache->spriteFrameByName(spriteFrame2.c_str()));
            secondSprite->setPosition(spritePart->getContentSize() / 2);
        }

        auto glowChild = static_cast<CCSprite*>(sprite->m_glowSprite->getChildren()->objectAtIndex(i));
        glowChild->setBatchNode(nullptr);
        glowChild->setDisplayFrame(spriteFrameCache->spriteFrameByName(spriteFrameGlow.c_str()));

        if (spritePart == sprite->m_headSprite) {
            auto extraFrame = spriteFrameCache->spriteFrameByName(spriteFrameExtra.c_str());
            auto hasExtra = doesExist(extraFrame);
            if (hasExtra) {
                if (sprite->m_extraSprite) {
                    sprite->m_extraSprite->setBatchNode(nullptr);
                    sprite->m_extraSprite->setDisplayFrame(extraFrame);
                }
                else {
                    sprite->m_extraSprite = CCSprite::createWithSpriteFrame(extraFrame);
                    sprite->m_headSprite->addChild(sprite->m_extraSprite, 2);
                }
                sprite->m_extraSprite->setPosition(spritePart->getContentSize() / 2);
            }
            sprite->m_extraSprite->setVisible(hasExtra);
        }
    }
}
