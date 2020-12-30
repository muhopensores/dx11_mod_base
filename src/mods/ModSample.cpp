#include "ModSample.hpp"


// clang-format off
// clang-format on

std::optional<std::string> ModSample::on_initialize() {
  // uintptr_t base = g_framework->get_module().as<uintptr_t>();

  if (!install_hook(0xBADF00D, m_function_hook, &detour, &jmp_ret, 5)) {
    // return a error string in case something goes wrong
    // spdlog::error("[{}] failed to initialize", get_name());
    return "Failed to initialize ModSample";
  }
  return Mod::on_initialize();
}

// during load
//void ModSample::on_config_load(const utility::Config &cfg) {}
// during save
//void ModSample::on_config_save(utility::Config &cfg) {}
// do something every frame
//void ModSample::on_frame() {}
// will show up in debug window, dump ImGui widgets you want here
//void ModSample::on_draw_debug_ui() {}
// will show up in main window, dump ImGui widgets you want here
//void ModSample::on_draw_ui() {}