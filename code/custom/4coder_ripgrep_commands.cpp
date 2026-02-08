/*
4coder_ripgrep_commands.cpp

Interactive ripgrep helpers (vimgrep format) for "IDE-like" navigation without LSP.

Goals:
- Shortcut -> prompt for pattern -> run `rg --vimgrep` -> output to *compilation*
- Results are jumpable (file:line:col:match)

This file is intended to be compiled as part of the default custom layer include
aggregator (it is included from `4coder_default_include.cpp` in this repo).
Therefore:
- DO NOT include `4coder_default_include.cpp` here (that would recurse).
- Rely on symbols/types already provided by the default include aggregator.

Requires:
- `rg` (ripgrep) available in PATH.
*/

#if !defined(FCODER_RIPGREP_COMMANDS_CPP)
#define FCODER_RIPGREP_COMMANDS_CPP

// ------------------------------
// Helpers

function String_Const_u8
rg_prompt_pattern(Application_Links *app, Arena *arena, String_Const_u8 prompt){
    Query_Bar_Group group(app);

    local_persist u8 pattern_space[4096];

    Query_Bar bar = {};
    bar.prompt = prompt;
    bar.string = SCu8(pattern_space, (u64)0);
    bar.string_capacity = sizeof(pattern_space);

    if (!query_user_string(app, &bar)){
        return SCu8();
    }

    bar.string.size = clamp_top(bar.string.size, sizeof(pattern_space) - 1);
    pattern_space[bar.string.size] = 0;

    return push_string_copy(arena, bar.string);
}

function String_Const_u8
rg_quote_for_shell(Arena *arena, String_Const_u8 s){
    // Best-effort escaping using 4coder's helper.
    // We still wrap in double quotes.
    String_Const_u8 escaped = string_escape(arena, s);
    return push_u8_stringf(arena, "\"%.*s\"", string_expand(escaped));
}

function String8
rg_project_root(Application_Links *app, Arena *arena){
    Variable_Handle prj_var = vars_read_key(vars_get_root(), vars_save_string_lit("prj_config"));
    String8 prj_dir = prj_path_from_project(arena, prj_var);
    return prj_dir;
}

function void
rg_exec_to_compilation(Application_Links *app, View_ID view, String_Const_u8 working_dir, String_Const_u8 cmd){
    Buffer_Identifier out = buffer_identifier(string_u8_litexpr("*compilation*"));

    // Match behavior of other CLI-based commands.
    u32 flags = CLI_OverlapWithConflict | CLI_SendEndSignal;

    exec_system_command(app, view, out, working_dir, cmd, flags);

    block_zero_struct(&prev_location);
    lock_jump_buffer(app, string_u8_litexpr("*compilation*"));
}

function String_Const_u8
rg_make_cmd_basic(Arena *arena, String_Const_u8 pattern_quoted, String_Const_u8 target_path){
    // --vimgrep => file:line:col:match (best for jump-to-result)
    // --smart-case => nice default behavior
    // --hidden + ignore .git
    return push_u8_stringf(
        arena,
        "rg --vimgrep --smart-case -n --hidden --glob \"!**/.git/*\" %.*s %.*s",
        string_expand(pattern_quoted),
        string_expand(target_path)
    );
}

function String_Const_u8
rg_make_cmd_no_vendor(Arena *arena, String_Const_u8 pattern_quoted, String_Const_u8 target_path){
    // Same as basic, but exclude vendor/**.
    return push_u8_stringf(
        arena,
        "rg --vimgrep --smart-case -n --hidden --glob \"!**/.git/*\" --glob \"!vendor/**\" %.*s %.*s",
        string_expand(pattern_quoted),
        string_expand(target_path)
    );
}

function void
rg_search_prompt_common(Application_Links *app,
                        String_Const_u8 prompt,
                        String_Const_u8 target_path,
                        b32 exclude_vendor){
    Scratch_Block scratch(app);

    String_Const_u8 pattern = rg_prompt_pattern(app, scratch, prompt);
    if (pattern.size == 0){
        return;
    }

    String8 prj_dir = rg_project_root(app, scratch);
    if (prj_dir.size == 0){
        print_message(app, string_u8_litexpr("ripgrep: no project loaded (load a project.4coder first)\n"));
        return;
    }

    String_Const_u8 quoted = rg_quote_for_shell(scratch, pattern);

    String_Const_u8 cmd = {};
    if (exclude_vendor){
        cmd = rg_make_cmd_no_vendor(scratch, quoted, target_path);
    }
    else{
        cmd = rg_make_cmd_basic(scratch, quoted, target_path);
    }

    // Use the active view. (We intentionally avoid `get_or_open_build_panel` here because
    // it is a `static` helper inside `4coder_build_commands.cpp` and is not visible here.)
    //
    // Output still goes to *compilation*, and jump navigation works the same.
    View_ID view = get_active_view(app, Access_Always);
    rg_exec_to_compilation(app, view, prj_dir, cmd);
}

// ------------------------------
// Commands

CUSTOM_COMMAND_SIG(rg_search_repo_prompt)
CUSTOM_DOC("Prompt for a pattern and run `rg --vimgrep` in the project root (includes vendor). Output goes to *compilation* for jump navigation.")
{
    rg_search_prompt_common(app, string_u8_litexpr("rg (repo, incl vendor) pattern: "),
                            string_u8_litexpr("."), false);
}

CUSTOM_COMMAND_SIG(rg_search_repo_no_vendor_prompt)
CUSTOM_DOC("Prompt for a pattern and run `rg --vimgrep` in the project root (excludes vendor/**). Output goes to *compilation* for jump navigation.")
{
    rg_search_prompt_common(app, string_u8_litexpr("rg (repo, no vendor) pattern: "),
                            string_u8_litexpr("."), true);
}

CUSTOM_COMMAND_SIG(rg_search_vendor_prompt)
CUSTOM_DOC("Prompt for a pattern and run `rg --vimgrep` in vendor/. Output goes to *compilation* for jump navigation.")
{
    rg_search_prompt_common(app, string_u8_litexpr("rg (vendor) pattern: "),
                            string_u8_litexpr("vendor"), false);
}

#endif // FCODER_RIPGREP_COMMANDS_CPP