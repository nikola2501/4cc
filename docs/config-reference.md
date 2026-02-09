# 4cc `config.4coder` Reference (Custom Layer)

This document lists **configuration keys that are actually read/used by the 4cc custom layer** (under `4cc/code/custom/`).

It is intended as a practical reference:
- what key to set
- what it does
- where it’s used in the code
- typical/default value
- allowed values (when they’re constrained)

> Notes
>
> - A key only has an effect if it is **read** by the custom layer (typically via `def_get_config_b32`, `def_get_config_u64`, `def_get_config_string`).
> - Keys are loaded from `config.4coder` using the normal config search path (project dir, user dir, binary dir). In 4cc’s boot log you’ll see `def_config: "config.4coder"` and a dump of loaded values.
> - Many values are “free-form strings” (e.g. a font filename). When options are constrained, this doc calls it out.

---

## Summary Table

| Key | Type | Typical default | Purpose |
|---|---:|---|---|
| `mapping` | string | `""` | Selects built-in mapping fallback / binding file name choice. |
| `mode` | string | `"4coder"` | Selects interaction mode (e.g. 4coder vs notepad-like). |
| `bind_by_physical_key` | bool | `false` | Use physical or language-arranged key mode. |
| `lalt_lctrl_is_altgr` | bool | `false` | Treat LAlt+LCtrl as AltGr (layout behavior). |
| `default_theme_name` | string | `"4coder"` | Select theme by name. |
| `default_font_name` | string | `"liberation-mono.ttf"` | Global font file name. |
| `default_font_size` | u64 | `12` (fallback), ship often `16` | Global font point size. |
| `default_font_hinting` | bool | `false` | Enable font hinting. |
| `default_font_aa_mode` | string | `"8bit"` | Font AA mode (`8bit` or `1bit`). |
| `automatically_load_project` | bool | `false`/ship varies | Auto-load project on startup. |
| `treat_as_code` | string | e.g. `".cpp.c.h..."` | Extension list treated as code. |
| `enable_code_wrapping` | bool | `true`/ship varies | Wrap mode for code buffers. |
| `enable_output_wrapping` | bool | `false`/ship varies | Wrap mode for output buffers like `*compilation*`. |
| `enable_virtual_whitespace` | bool | `true`/ship varies | Enables “virtual whitespace” layouts. |
| `virtual_whitespace_regular_indent` | u64 | `4` | Indent width used by virtual whitespace layout. |
| `automatically_indent_text_on_save` | bool | `true`/ship varies | Auto-indent on save (code w/ virtual whitespace). |
| `automatically_save_changes_on_build` | bool | `true`/ship varies | Save dirty buffers before build. |
| `indent_width` | u64 | `4` | Indentation width for indent commands. |
| `default_tab_width` | u64 | `4` | Tab width used for layout/indent calculations. |
| `indent_with_tabs` | bool | `false` | Use tabs for indentation. |
| `indent_clear_blank_lines` | bool | `false` | Indenter clears indentation on blank lines. |
| `show_line_number_margins` | bool | `false` | Show line number margin. |
| `cursor_roundness` | u64 | `45` (ship varies) | Cursor roundness (0–50, percent). |
| `mark_thickness` | u64 | `2` (ship varies) | Mark outline thickness (pixels). |
| `use_file_bars` | bool | `true` | Show file bar per view. |
| `hide_file_bar_in_ui` | bool | `true` | Hide file bar in UI rendering integration. |
| `use_scope_highlight` | bool | `true` | Scope highlight on/off. |
| `use_paren_helper` | bool | `true` | Paren highlight helper on/off. |
| `use_error_highlight` | bool | `true` | Error highlight on/off. |
| `use_jump_highlight` | bool | `true` | Jump highlight on/off. |
| `use_comment_keyword` | bool | `true` | Highlight NOTE/TODO in comments. |
| `highlight_line_at_cursor` | bool | `true` | Highlight the active cursor line. |
| `enable_undo_fade_out` | bool | `true` | Fade/flash effect on undo. |
| `lister_whole_word_backspace_when_modified` | bool | `true` | Lister path field backspace behavior. |
| `lister_roundness` | u64 | `20` (ship varies) | Lister item rounding (0–50). |
| `user_name` | string | `"not-set"` | Used for comment-writing helpers and project overrides. |
| `default_compiler_bat` | string | `"cl"` | Default compiler when generating project scripts (Windows). |
| `default_flags_bat` | string | (ship value) | Default flags when generating project scripts (Windows). |
| `default_compiler_sh` | string | `"g++"` | Default compiler when generating project scripts (Unix). |
| `default_flags_sh` | string | `"-g"` | Default flags when generating project scripts (Unix). |

---

## Detailed Reference

Each entry has:
- **Type**: `bool` / `u64` / `string`
- **Where used**: file + approximate responsibility
- **Default**: either ship config default or code fallback if visible
- **Values**: allowed values and notes

### `mapping`
- **Type:** string
- **Where used:** `4cc/code/custom/4coder_default_framework.cpp` (`default_4coder_initialize`)
- **Purpose:** Determines which binding file to load (`bindings.4coder` vs `mac-bindings.4coder`) and what built-in mapping to fall back to when bindings file fails to load.
- **Default:** empty string in ship config often means “leave unaltered / use binding file if present”.
- **Values:** `""`, `"default"`, `"mac-default"`, `"choose"` (per ship config comments).

### `mode`
- **Type:** string
- **Where used:** `4cc/code/custom/4coder_config.cpp` (`load_config_and_apply`)
- **Purpose:** Selects UI/interaction “mode”.
- **Default:** `"4coder"` in ship
- **Values:** `"4coder"`, `"notepad-like"` (per ship config comments). Other values may be accepted if implemented by `change_mode(...)`.

### `bind_by_physical_key`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_config.cpp` (`load_config_and_apply`)
- **Purpose:** Chooses between physical key mode and language-arranged key mode.
- **Default:** `false`
- **Values:** `true`/`false`

### `lalt_lctrl_is_altgr`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_config.cpp` (`load_config_and_apply`)
- **Purpose:** If `true`, treats `LAlt+LCtrl` as AltGr for keyboard layout handling.
- **Default:** `false`
- **Values:** `true`/`false`

---

## Theme & Font

### `default_theme_name`
- **Type:** string
- **Where used:** `4cc/code/custom/4coder_config.cpp` (`load_config_and_apply`)
- **Purpose:** Picks a theme by name from the “live set” of loaded themes.
- **Default:** `"4coder"` in ship
- **Values:** Theme name string (usually derived from `.4coder` theme filenames).

### `default_font_name`
- **Type:** string
- **Where used:** `4cc/code/custom/4coder_config.cpp` (`load_config_and_apply`)
- **Purpose:** Font file name to load (first tries as-is, then tries `fonts/<name>` via search path).
- **Default:** Code fallback to `liberation-mono.ttf` if empty.
- **Values:** Any font file path/name in search path.

### `default_font_size`
- **Type:** u64
- **Where used:** `4cc/code/custom/4coder_config.cpp` (`load_config_and_apply`)
- **Purpose:** Global font size (pt).
- **Default:** If set to 0, falls back to `12` in code.
- **Values:** Positive integer (u64).

### `default_font_hinting`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_config.cpp` (`load_config_and_apply`)
- **Purpose:** Controls whether font hinting is enabled.
- **Default:** `false` in ship
- **Values:** `true`/`false`

### `default_font_aa_mode`
- **Type:** string
- **Where used:** `4cc/code/custom/4coder_config.cpp` (`load_config_and_apply`)
- **Purpose:** Selects font antialiasing mode.
- **Default:** `"8bit"`
- **Values:**
  - `"8bit"` → `FaceAntialiasingMode_8BitMono`
  - `"1bit"` → `FaceAntialiasingMode_1BitMono`

---

## Project Loading

### `automatically_load_project`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_default_hooks.cpp` (startup hook)
- **Purpose:** Calls `load_project(app)` at startup if enabled.
- **Default:** ship varies
- **Values:** `true`/`false`

---

## Code vs Text Classification

### `treat_as_code`
- **Type:** string
- **Where used:**
  - `4cc/code/custom/4coder_default_hooks.cpp` (`default_begin_buffer`)
  - `4cc/code/custom/4coder_project_commands.cpp` (open/close “code” files helpers)
- **Purpose:** A dot-separated extension list used to decide whether a file is treated as code (used for wrapping/layout/lexer kickoff and various project commands).
- **Default:** ship example: `".cpp.c.hpp.h.cc..."` (your ship file includes `.go` too).
- **Values:** A string containing extensions separated by dots (e.g. `".cpp.c.h.go"`). Internally parsed by `parse_extension_line_to_extension_list(...)`.

### `enable_code_wrapping`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_default_hooks.cpp` (`default_begin_buffer`)
- **Purpose:** If a buffer is treated as code, this controls whether wrapping is enabled.
- **Default:** ship varies
- **Values:** `true`/`false`

### `enable_output_wrapping`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_default_hooks.cpp` (`default_begin_buffer`)
- **Purpose:** Controls wrapping for output buffers (buffers named like `*compilation*`, etc).
- **Default:** ship varies
- **Values:** `true`/`false`

---

## Virtual Whitespace & Layout

### `enable_virtual_whitespace`
- **Type:** bool
- **Where used:**
  - `4cc/code/custom/4coder_default_hooks.cpp` (tracks changes, clears layouts)
  - `4cc/code/custom/4coder_code_index.cpp` (layout decisions for index-based layout)
- **Purpose:** Enables “virtual whitespace” layouts.
- **Default:** ship varies
- **Values:** `true`/`false`

### `virtual_whitespace_regular_indent`
- **Type:** u64
- **Where used:** `4cc/code/custom/4coder_code_index.cpp`
- **Purpose:** Indentation value used for virtual whitespace regular indent spacing.
- **Default:** ship often `4`
- **Values:** integer (u64). Used as a multiplier of space advance.

---

## Save/Build Automation

### `automatically_indent_text_on_save`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_default_hooks.cpp` (`default_file_save`)
- **Purpose:** Auto-indent on save (only applied when virtual whitespace is enabled).
- **Default:** ship varies
- **Values:** `true`/`false`

### `automatically_save_changes_on_build`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_build_commands.cpp`
- **Purpose:** Saves all dirty buffers before building.
- **Default:** ship varies
- **Values:** `true`/`false`

---

## Indentation Behavior

### `indent_width`
- **Type:** u64
- **Where used:** `4cc/code/custom/4coder_auto_indent.cpp`
- **Purpose:** Indentation width used by auto-indent logic.
- **Default:** ship often `4`
- **Values:** integer (u64)

### `default_tab_width`
- **Type:** u64
- **Where used:**
  - `4cc/code/custom/4coder_auto_indent.cpp`
  - `4cc/code/custom/4coder_code_index.cpp`
  - `4cc/code/custom/4coder_layout_rule.cpp`
- **Purpose:** Tab width used for layout calculations and indentation logic.
- **Default:** ship often `4`
- **Values:** integer (u64), clamped to at least 1 in layout code.

### `indent_with_tabs`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_auto_indent.cpp`
- **Purpose:** If `true`, indenter uses tabs when indenting.
- **Default:** `false`
- **Values:** `true`/`false`

### `indent_clear_blank_lines`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_auto_indent.cpp`
- **Purpose:** Controls whether indentation is cleared on blank lines.
- **Default:** `false`
- **Values:** `true`/`false`

---

## UI & Rendering

### `show_line_number_margins`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_default_hooks.cpp` (`default_buffer_region`, `default_render_caller`)
- **Purpose:** Shows a line-number margin at the left.
- **Default:** ship varies
- **Values:** `true`/`false`

### `cursor_roundness`
- **Type:** u64
- **Where used:** `4cc/code/custom/4coder_default_hooks.cpp` (`default_render_buffer`)
- **Purpose:** Controls cursor roundness as a percentage of cursor width.
- **Default:** ship often `45`
- **Values:** 0–50 recommended (percent). Larger means more rounded.

### `mark_thickness`
- **Type:** u64
- **Where used:** `4cc/code/custom/4coder_default_hooks.cpp` (`default_render_buffer`)
- **Purpose:** Thickness of mark box outline (pixels).
- **Default:** ship often `2`
- **Values:** integer (u64)

### `use_file_bars`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_default_framework.cpp` (`new_view_settings`)
- **Purpose:** Toggles file bar visibility per view (ViewSetting_ShowFileBar).
- **Default:** `true`
- **Values:** `true`/`false`

### `hide_file_bar_in_ui`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_lister_base.cpp` (`lister_render`)
- **Purpose:** Prevents file bar from appearing in lister UI integration when set.
- **Default:** ship often `true`
- **Values:** `true`/`false`

### `use_scope_highlight`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_default_hooks.cpp` (`default_render_buffer`)
- **Purpose:** Highlights scopes (nested regions) based on cursor position.
- **Default:** ship often `true`
- **Values:** `true`/`false`

### `use_paren_helper`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_default_hooks.cpp` (`default_render_buffer`)
- **Purpose:** Highlights matching parentheses/brackets.
- **Default:** ship often `true`
- **Values:** `true`/`false`

### `use_error_highlight`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_default_hooks.cpp` (`default_render_buffer`)
- **Purpose:** Enables error highlighting overlay (typically based on `*compilation*` parsing).
- **Default:** ship often `true`
- **Values:** `true`/`false`

### `use_jump_highlight`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_default_hooks.cpp` (`default_render_buffer`)
- **Purpose:** Enables jump highlight overlay.
- **Default:** ship often `true`
- **Values:** `true`/`false`

### `use_comment_keyword`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_default_hooks.cpp` (`default_render_buffer`)
- **Purpose:** Highlights `NOTE`/`TODO` inside comments.
- **Default:** ship often `true`
- **Values:** `true`/`false`

### `highlight_line_at_cursor`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_default_hooks.cpp` (`default_render_buffer`)
- **Purpose:** Highlights the line where the cursor is.
- **Default:** ship often `true`
- **Values:** `true`/`false`

### `enable_undo_fade_out`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_base_commands.cpp` (undo fade effect)
- **Purpose:** Enables the visual fade/flash effect when undoing.
- **Default:** ship often `true`
- **Values:** `true`/`false`

---

## Lister Behavior

### `lister_whole_word_backspace_when_modified`
- **Type:** bool
- **Where used:** `4cc/code/custom/4coder_lists.cpp`
- **Purpose:** Controls whether backspace in certain lister text fields deletes “whole word” when a modifier is pressed.
- **Default:** ship often `true`
- **Values:** `true`/`false`
- **Notes:** The behavior depends on whether Control (or another modifier) is held; this key flips the interpretation.

### `lister_roundness`
- **Type:** u64
- **Where used:** `4cc/code/custom/4coder_lister_base.cpp`
- **Purpose:** Controls rounding of lister UI items.
- **Default:** ship often `20`
- **Values:** 0–50 recommended (percent).

---

## User Identity / Templates

### `user_name`
- **Type:** string
- **Where used:**
  - `4cc/code/custom/4coder_combined_write_commands.cpp` (comment-writing helpers)
  - `4cc/code/custom/4coder_project_commands.cpp` (user-specific overrides)
- **Purpose:** Used when generating comment templates and selecting per-user project overrides.
- **Default:** `"not-set"` (ship)
- **Values:** Any string.

---

## Project Script Generation Defaults

These are used when setting up scripts for a new project (generating `build.bat`/`build.sh` etc).

### `default_compiler_bat`
- **Type:** string
- **Where used:** `4cc/code/custom/4coder_project_commands.cpp` (`prj_setup_scripts`)
- **Default:** `"cl"` (ship)
- **Values:** compiler executable name/path.

### `default_flags_bat`
- **Type:** string
- **Where used:** `4cc/code/custom/4coder_project_commands.cpp` (`prj_setup_scripts`)
- **Default:** ship-defined flags string
- **Values:** shell string.

### `default_compiler_sh`
- **Type:** string
- **Where used:** `4cc/code/custom/4coder_project_commands.cpp` (`prj_setup_scripts`)
- **Default:** `"g++"` (ship)
- **Values:** compiler executable name/path (Unix).

### `default_flags_sh`
- **Type:** string
- **Where used:** `4cc/code/custom/4coder_project_commands.cpp` (`prj_setup_scripts`)
- **Default:** `"-g"` (ship)
- **Values:** shell string.

---

## Appendix: How config loading works (high-level)

- `config.4coder` is parsed and stored in the config variable table.
- The custom layer reads keys via `def_get_config_*`.
- Unknown/unused keys are harmless but have no effect unless you add code to read them.
- Some behavior (like keybindings) is not controlled by `config.4coder`, but by dynamic bindings files:
  - `bindings.4coder` (default)
  - `mac-bindings.4coder` (mac mapping selection)

---