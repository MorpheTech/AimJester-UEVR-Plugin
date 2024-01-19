// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "uevr/Plugin.hpp"

#include <sstream>
#include <memory>
#include <iostream>


using namespace uevr;
using namespace std;

// TODO - Create a symbolic link
//      - Figure out how to run code on loop
//      - Figure out how to pull tracked device pose data

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

    void on_dllmain() override {}

    void on_initialize() override {
        API::get()->log_error("%s %s", "INITIALZING AIM JESTER PLUGIN", "error");
        API::get()->log_warn("%s %s", "INITIALZING AIM JESTER PLUGIN", "warning");
        API::get()->log_info("%s %s", "INITIALZING AIM JESTER PLUGIN", "info");
        SetCursorPos(0, 0);
 
        UEVR_PluginInitializeParam uevr_plugin = UEVR_PluginInitializeParam();
        // uevr.vr->get_pose();
    }

    void on_pre_engine_tick(UEVR_UGameEngineHandle engine, float delta) override {
        PLUGIN_LOG_ONCE("Pre Engine Tick: %f", delta);
    }

    void on_post_engine_tick(UEVR_UGameEngineHandle engine, float delta) override {
        PLUGIN_LOG_ONCE("Post Engine Tick: %f", delta);
    }

};

// // Actually creates the plugin. Very important that this global is created.
// // The fact that it's using std::unique_ptr is not important, as long as the constructor is called in some way.
std::unique_ptr<AimJester> g_plugin{ new AimJester() };
