#ifdef GEODE_IS_WINDOWS
    #ifdef MORE_ICONS_API_EXPORTING
        #define MORE_ICONS_API_DLL __declspec(dllexport)
    #else
        #define MORE_ICONS_API_DLL __declspec(dllimport)
    #endif
#else
    #define MORE_ICONS_API_DLL __attribute__((visibility("default")))
#endif

/**
 * An API for interacting with the More Icons mod.
 */
class MORE_ICONS_API_DLL MoreIconsAPI {
private:
    // Gets a saved value from the More Icons mod.
    template<class T>
    static T getMIValue(const std::string& key, const T& defaultValue) {
        if (auto moreIcons = geode::Loader::get()->getLoadedMod("hiimjustin000.more_icons")) return moreIcons->getSavedValue<T>(key, defaultValue);
        return defaultValue;
    }

    // Checks if a sprite frame exists.
    static bool doesExist(cocos2d::CCSpriteFrame* frame) {
        return frame && frame->getTag() != 105871529;
    }
public:
    /**
     * Gets the vector of custom icons for a specific type.
     * @param type The type of icon.
     * @returns The custom icons for the type, or an empty vector if none exist.
     */
    static std::vector<std::string> vectorForType(IconType type);

    /**
     * Gets the save key for a specific icon type.
     * @param type The type of icon.
     * @param dual Whether the icon is a separate dual icon.
     * @returns The save key for the icon type, or an empty string if none exists.
     */
    static std::string savedForType(IconType type, bool dual);

    /**
     * Gets the active custom icon for a specific type.
     * @param type The type of icon.
     * @param dual Whether the icon is a separate dual icon.
     * @returns The active custom icon, or an empty string if none is active.
     */
    static std::string activeForType(IconType type, bool dual);

    /**
     * Checks if a custom icon exists for a specific type.
     * @param icon The custom icon to check.
     * @param type The type of icon.
     * @returns Whether the icon exists.
     */
    static bool hasIcon(const std::string& icon, IconType type);

    /**
     * Updates a SimplePlayer with a custom icon.
     * @param player The SimplePlayer to update.
     * @param icon The custom icon to use.
     * @param type The type of icon.
     */
    static void updateSimplePlayer(SimplePlayer* player, const std::string& icon, IconType type);

    /**
     * Updates a GJRobotSprite with a custom icon.
     * @param sprite The GJRobotSprite to update.
     * @param icon The custom icon to use.
     * @param type The type of icon.
     */
    static void updateRobotSprite(GJRobotSprite* sprite, const std::string& icon, IconType type);
};
