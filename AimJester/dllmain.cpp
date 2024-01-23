// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "uevr/Plugin.hpp"

#include <memory>


using namespace uevr;

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
    UEVR_Vector3f *prev_pos = new UEVR_Vector3f();
    UEVR_Quaternionf *prev_rot = new UEVR_Quaternionf();

    void on_dllmain() override {}

    void on_initialize() override {
        API::get()->log_info("%s %s", "INITIALZING AIM JESTER PLUGIN", "info");
        uevr_plugin = *API::get()->param();
        send_mouse_input(100, 100);
        prev_pos->x = 0.0f; prev_pos->y = 0.0f; prev_pos->z = 0.0f;
        prev_rot->w = 0.0f; prev_rot->x = 0.0f; prev_rot->y = 0.0f; prev_rot->z = 0.0f;
    }

    void on_pre_engine_tick(UEVR_UGameEngineHandle engine, float delta) override {
        PLUGIN_LOG_ONCE("Pre Engine Tick: %f", delta);
        hmd_index = uevr_plugin.vr->get_hmd_index();
        rc_index = uevr_plugin.vr->get_right_controller_index();
        lc_index = uevr_plugin.vr->get_left_controller_index();
        uevr_plugin.vr->get_pose(hmd_index, &pos, &rot);
        API::get()->log_info("on_pre_engine_tick get_pose (%f, %f)", rot.x, rot.y);
        // API::get()->log_info("on_pre_engine_tick get_pose (%i, %i)", static_cast<int>(rot.x), static_cast<int>(rot.y));
        // send_mouse_input(static_cast<int>(rot.x * 20), static_cast<int>(rot.y * 20));
        prev_rot->x = rot.x; prev_rot->y = rot.y;
    }

    void on_post_engine_tick(UEVR_UGameEngineHandle engine, float delta) override {
        PLUGIN_LOG_ONCE("Post Engine Tick: %f", delta);
    }

    static void send_mouse_input(int x, int y) {
        INPUT inputs[1] = {};
        ZeroMemory(inputs, sizeof(inputs));
        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dx = x;
        inputs[0].mi.dy = y;
        inputs[0].mi.dwFlags = MOUSEEVENTF_MOVE;
        // API::get()->log_info("on_pre_engine_tick send_mouse_input (%i, %i)", inputs[0].mi.dx, inputs[0].mi.dy);
        SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    }

};

// // Actually creates the plugin. Very important that this global is created.
// // The fact that it's using std::unique_ptr is not important, as long as the constructor is called in some way.
std::unique_ptr<AimJester> g_plugin{ new AimJester() };
