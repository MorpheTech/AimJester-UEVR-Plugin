// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "uevr/Plugin.hpp"

#include <sstream>
#include <memory>


using namespace uevr;
using namespace std;

/*
  TODO:
    - hook up a symbolic link so my plugin can reload/hotswap while the game is running
mklink "C:\Users\jakem\AppData\Roaming\UnrealVRMod\HogwartsLegacy\plugins\AimJester.dll" "C:\Users\jakem\Documents\GitHub\AimJester-UEVR-Plugin\x64\Release\AimJester.dll"
    - get cursor to move in  Non-VR
SetCursorPos(0, 0);
    - get rotation/direction VRdata from tracked device
    - get cursor to move in that on_pre_engine_tick callback (VR)
    - see if we can manipulate wand aiming at all with VRData
*/

#define PLUGIN_LOG_ONCE(...) \
    static bool _logged_ = false; \
    if (!_logged_) { \
        _logged_ = true; \
        API::get()->log_info(__VA_ARGS__); \
    }

class AimJester : public uevr::Plugin {
public:
    AimJester() = default;
    int a = 0;
    UEVR_PluginInitializeParam uevr_plugin;
    UEVR_TrackedDeviceIndex hmd_index;
    UEVR_TrackedDeviceIndex rc_index;
    UEVR_TrackedDeviceIndex lc_index;
    UEVR_Vector3f pos;
    UEVR_Quaternionf rot;

    void on_dllmain() override {}

    void on_initialize() override {
        API::get()->log_error("%s %s", "INITIALZING AIM JESTER PLUGIN", "error");
        API::get()->log_warn("%s %s", "INITIALZING AIM JESTER PLUGIN", "warning");
        API::get()->log_info("%s %s", "INITIALZING AIM JESTER PLUGIN", "info");
        SetCursorPos(-500, 0);

        for (int i = 0; i < 200; i++) {
            SetCursorPos(a, a);
            a += 10;
        }
        API::get()->log_info("Finished moving cursor | a = %i pos for cursor", a);

        uevr_plugin = UEVR_PluginInitializeParam();
    }

    void on_pre_engine_tick(UEVR_UGameEngineHandle engine, float delta) override {
        PLUGIN_LOG_ONCE("Pre Engine Tick: %f", delta);
        API::get()->log_info("MADE IT 1");
        hmd_index = uevr_plugin.vr->get_hmd_index();
        API::get()->log_info("MADE IT 2");
        rc_index = uevr_plugin.vr->get_right_controller_index();
        lc_index = uevr_plugin.vr->get_left_controller_index();
        uevr_plugin.vr->get_pose(rc_index, &pos, &rot);
        API::get()->log_info("MADE IT 4");
        SetCursorPos(rot.x, rot.y);
        API::get()->log_info("on_pre_engine_tick JESTER (%f, %f)", rot.x, rot.y);
    }

    void on_post_engine_tick(UEVR_UGameEngineHandle engine, float delta) override {
        PLUGIN_LOG_ONCE("Post Engine Tick: %f", delta);
    }

};

// // Actually creates the plugin. Very important that this global is created.
// // The fact that it's using std::unique_ptr is not important, as long as the constructor is called in some way.
std::unique_ptr<AimJester> g_plugin{ new AimJester() };
