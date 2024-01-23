// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Rat.hpp"
#include "uevr/Plugin.hpp"

#include <memory>


using namespace uevr;
using namespace rat;

/*
  TODO:
    - mklink "C:\Users\jakem\AppData\Roaming\UnrealVRMod\HogwartsLegacy\plugins\AimJester.dll" "C:\Users\jakem\Documents\GitHub\AimJester-UEVR-Plugin\AimJester\x64\Release\AimJester.dll"
    - get cursor to move in that on_pre_engine_tick callback (Non-VR)
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
        API::get()->log_info("%s %s", "INITIALZING AIM JESTER PLUGIN", "info");
        uevr_plugin = *API::get()->param();
        Rat::send_mouse_input(150, 150);
    }

    void on_pre_engine_tick(UEVR_UGameEngineHandle engine, float delta) override {
        PLUGIN_LOG_ONCE("Pre Engine Tick: %f", delta);
        hmd_index = uevr_plugin.vr->get_hmd_index();
        rc_index = uevr_plugin.vr->get_right_controller_index();
        lc_index = uevr_plugin.vr->get_left_controller_index();
        uevr_plugin.vr->get_pose(hmd_index, &pos, &rot);
        API::get()->log_info("on_pre_engine_tick JESTER (%f, %f)", rot.x*10, rot.y*10);
        Rat::send_mouse_input(2, 2);
    }

    void on_post_engine_tick(UEVR_UGameEngineHandle engine, float delta) override {
        PLUGIN_LOG_ONCE("Post Engine Tick: %f", delta);
    }

};

// // Actually creates the plugin. Very important that this global is created.
// // The fact that it's using std::unique_ptr is not important, as long as the constructor is called in some way.
std::unique_ptr<AimJester> g_plugin{ new AimJester() };
