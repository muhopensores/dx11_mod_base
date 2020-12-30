#include "ModSample.hpp"

// Initialize our static variables like this:
// variable_type class_name::variable_name
// do this for variables you want to share to other modules/mods.
uintptr_t ModSample::variable{NULL};
// pointers to return from assembly detour can be defined as global static
// uintptr_ts, no need to define it in hpp file. static has a bunch of
// differrent meanings in c++
static uintptr_t jmp_ret{NULL};
// our naked _asm function, pretty much copy of the cheat engine script
// man, clang-format really destroys formatting in asm blocks.
// Disable it for naked functions
// clang-format off
static naked void detour() {
	__asm {
		mov qword ptr [ModSample::variable], rbx
		mov rax, 0xDEADBEEF
		jmp qword ptr [jmp_ret]
	}
}
// Enable clang-format back on
// clang-format on
// called on initialize you want to return either Mod::on_initialize(); or an
// error string
std::optional<std::string> ModSample::on_initialize() {
  // get module base
  // uintptr_t base = g_framework->get_module().as<uintptr_t>();
  // install_hook takes care of installing and creating jmp hooks.
  // because i always forget to call hook->create().
  // 1st arg is an offset
  // most of the things from cheat table were converted to a header file
  // with offsets namespace.
  // 2nd arg is a FunctionHook instance
  // 3rd arg is a pointer to your naked function, dont forget & operator
  // 4th arg is a pointer to return address, dont forget & operator
  // 5th argument is a next instruction offset, from the place where you
  // hooking. If you want you can skip last argument and get it from minhook,
  // but be aware that it copies the stolen bytes, so your naked function does
  // not have to. But it's an additional jump so i dunno less performance maybe

  // EXAMPLE change to your offsets from offsets namespace (utils/Offsets.hpp)
  if (!install_hook(0xBADF00D, m_function_hook, &detour, &jmp_ret, 5)) {
    // return a error string in case something goes wrong
    // spdlog::error("[{}] failed to initialize", get_name());
    return "Failed to initialize ModSample";
  }
  // spdlog::info("[{}] init success\n", get_name());
  // return Mod::on_initialize() if everything went fine
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
//void on_update_player_ptr(uintptr_t manual_player) {}