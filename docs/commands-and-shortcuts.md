# 4coder (4ed) — Commands & Shortcuts (Checklist)

This document is meant to be a **living checklist**: it captures the **default keybindings** (Windows/Linux “default mapping” + macOS “mac-default”), and a **commands list** you can extend.

> Note: In 4coder, a **command** is a function-like action (e.g. `save`, `search`, `build_in_build_panel`). A **shortcut** is a keybinding that triggers a command (e.g. `Ctrl+S -> save`).  
> Default mappings live in:
> - `code/custom/4coder_default_map.cpp` (Windows/Linux)
> - `code/custom/4coder_mac_map.cpp` (macOS)
> Essential input hooks live in:
> - `code/custom/4coder_default_framework.cpp`

---

## Legend

- [ ] = not verified / to be expanded
- [x] = verified (present in default mappings)
- `Global` / `File` / `Code` = 4coder “maps” in the mapping system

Modifier naming:
- Win/Linux: `Ctrl`, `Alt`, `Shift`
- macOS: `Cmd`, `Ctrl`, `Shift`, `Opt` (Option = Alt)

---

# 1) Default shortcuts — Windows/Linux (`setup_default_mapping`)

## 1.1 Global map (Win/Linux)

- [x] `Ctrl+U` → `keyboard_macro_start_recording`
- [x] `Ctrl+Shift+U` → `keyboard_macro_finish_recording`
- [x] `Alt+U` → `keyboard_macro_replay`

- [x] `Ctrl+,` → `change_active_panel`
- [x] `Ctrl+Shift+,` → `change_active_panel_backwards`

- [x] `Ctrl+N` → `interactive_new`
- [x] `Ctrl+O` → `interactive_open_or_new`
- [x] `Alt+O` → `open_in_other`
- [x] `Ctrl+K` → `interactive_kill_buffer`
- [x] `Ctrl+I` → `interactive_switch_buffer`

- [x] `Ctrl+H` → `project_go_to_root_directory`

- [x] `Ctrl+Shift+S` → `save_all_dirty_buffers`

- [x] `Alt+.` → `change_to_build_panel`
- [x] `Alt+,` → `close_build_panel`

- [x] `Alt+N` → `goto_next_jump`
- [x] `Alt+Shift+N` → `goto_prev_jump`
- [x] `Alt+M` → `build_in_build_panel`
- [x] `Alt+Shift+M` → `goto_first_jump`

- [x] `Alt+B` → `toggle_filebar`

- [x] `Alt+Z` → `execute_any_cli`
- [x] `Alt+Shift+Z` → `execute_previous_cli`

- [x] `Alt+X` → `command_lister`
- [x] `Alt+Shift+X` → `project_command_lister`

- [x] `Alt+\` → `quick_swap_buffer`

- [x] `Ctrl+P` → `jump_to_last_point`

- [x] `Ctrl+Shift+I` → `list_all_functions_current_buffer_lister`

- [x] `Alt+F4` → `exit_4coder`

- [x] `F1..F16` → `project_fkey_command` (each F-key triggers the same dispatcher)

## 1.2 File map (Win/Linux)

- [x] `Delete` → `delete_char`
- [x] `Backspace` → `backspace_char`

- [x] `Up` → `move_up`
- [x] `Down` → `move_down`
- [x] `Left` → `move_left`
- [x] `Right` → `move_right`

- [x] `End` → `seek_end_of_line`
- [x] `Home` → `seek_beginning_of_line`

- [x] `PageUp` → `page_up`
- [x] `PageDown` → `page_down`

- [x] `Ctrl+PageUp` → `goto_beginning_of_file`
- [x] `Ctrl+PageDown` → `goto_end_of_file`

- [x] `Ctrl+Up` → `move_up_to_blank_line_end`
- [x] `Ctrl+Down` → `move_down_to_blank_line_end`

- [x] `Ctrl+Left` → `move_left_whitespace_boundary`
- [x] `Ctrl+Right` → `move_right_whitespace_boundary`

- [x] `Alt+Up` → `move_line_up`
- [x] `Alt+Down` → `move_line_down`

- [x] `Ctrl+Backspace` → `backspace_alpha_numeric_boundary`
- [x] `Ctrl+Delete` → `delete_alpha_numeric_boundary`

- [x] `Alt+Backspace` → `snipe_backward_whitespace_or_token_boundary`
- [x] `Alt+Delete` → `snipe_forward_whitespace_or_token_boundary`

- [x] `Ctrl+Space` → `set_mark`

- [x] `Ctrl+A` → `replace_in_range`

- [x] `Ctrl+C` → `copy`
- [x] `Ctrl+X` → `cut`
- [x] `Ctrl+V` → `paste_and_indent`
- [x] `Ctrl+Shift+V` → `paste_next_and_indent`

- [x] `Ctrl+D` → `delete_range`
- [x] `Ctrl+Shift+D` → `delete_line`

- [x] `Ctrl+E` → `center_view`
- [x] `Ctrl+Shift+E` → `left_adjust_view`

- [x] `Ctrl+F` → `search`
- [x] `Ctrl+Shift+F` → `list_all_locations`
- [x] `Alt+F` → `list_all_substring_locations_case_insensitive`

- [x] `Ctrl+G` → `goto_line`
- [x] `Ctrl+Shift+G` → `list_all_locations_of_selection`

- [x] `Ctrl+J` → `snippet_lister`

- [x] `Ctrl+Shift+K` → `kill_buffer`

- [x] `Ctrl+L` → `duplicate_line`

- [x] `Ctrl+M` → `cursor_mark_swap`

- [x] `Ctrl+Shift+O` → `reopen`

- [x] `Ctrl+Q` → `query_replace`
- [x] `Ctrl+Shift+Q` → `query_replace_identifier`
- [x] `Alt+Q` → `query_replace_selection`

- [x] `Ctrl+R` → `reverse_search`

- [x] `Ctrl+S` → `save`
- [x] `Ctrl+Shift+S` → `save_all_dirty_buffers`

- [x] `Ctrl+T` → `search_identifier`
- [x] `Ctrl+Shift+T` → `list_all_locations_of_identifier`

- [x] `Ctrl+Y` → `redo`
- [x] `Ctrl+Z` → `undo`

- [x] `Ctrl+1` → `view_buffer_other_panel`
- [x] `Ctrl+2` → `swap_panels`

- [x] `Enter` → `if_read_only_goto_position`
- [x] `Shift+Enter` → `if_read_only_goto_position_same_panel`

- [x] `Ctrl+Shift+.` → `view_jump_list_with_lister`

## 1.3 Code map (Win/Linux)

> `Code` inherits from `File`, so all `File` shortcuts apply in code buffers too.

- [x] `Ctrl+Left` → `move_left_alpha_numeric_boundary`
- [x] `Ctrl+Right` → `move_right_alpha_numeric_boundary`

- [x] `Alt+Left` → `move_left_alpha_numeric_or_camel_boundary`
- [x] `Alt+Right` → `move_right_alpha_numeric_or_camel_boundary`

- [x] `Ctrl+;` → `comment_line_toggle`

- [x] `Tab` → `word_complete`
- [x] `Shift+Tab` → `word_complete_prev`
- [x] `Ctrl+Shift+Tab` → `word_complete_drop_down`
- [x] `Ctrl+Tab` → `auto_indent_range`

- [x] `Alt+R` → `write_block`
- [x] `Alt+T` → `write_todo`
- [x] `Alt+Y` → `write_note`

- [x] `Alt+D` → `list_all_locations_of_type_definition`
- [x] `Alt+Shift+T` → `list_all_locations_of_type_definition_of_identifier`

- [x] `Ctrl+[` → `open_long_braces`
- [x] `Ctrl+Shift+[` → `open_long_braces_semicolon`
- [x] `Ctrl+Shift+]` → `open_long_braces_break`

- [x] `Alt+[` → `select_surrounding_scope`
- [x] `Alt+Shift+[` → `select_surrounding_scope_maximal`

- [x] `Alt+]` → `select_prev_scope_absolute`
- [x] `Alt+Shift+]` → `select_prev_top_most_scope`

- [x] `Alt+'` → `select_next_scope_absolute`
- [x] `Alt+Shift+'` → `select_next_scope_after_current`

- [x] `Alt+/` → `place_in_scope`
- [x] `Alt+-` → `delete_current_scope`

- [x] `Alt+I` → `if0_off`

- [x] `Alt+1` → `open_file_in_quotes`
- [x] `Alt+2` → `open_matching_file_cpp`

- [x] `Ctrl+0` → `write_zero_struct`

- [x] `Ctrl+W` → `jump_to_definition_at_cursor`

---

# 2) Default shortcuts — macOS (`setup_mac_mapping`)

> Differences are mainly: `Cmd` is used where Win/Linux uses `Ctrl`, plus a few Ctrl/Opt swaps.

## 2.1 Global map (macOS)

- [x] `Cmd+U` → `keyboard_macro_start_recording`
- [x] `Cmd+Shift+U` → `keyboard_macro_finish_recording`
- [x] `Ctrl+U` → `keyboard_macro_replay`

- [x] `Cmd+,` → `change_active_panel`
- [x] `Cmd+Shift+,` → `change_active_panel_backwards`

- [x] `Cmd+N` → `interactive_new`
- [x] `Cmd+O` → `interactive_open_or_new`
- [x] `Ctrl+O` → `open_in_other`
- [x] `Cmd+K` → `interactive_kill_buffer`
- [x] `Cmd+I` → `interactive_switch_buffer`

- [x] `Cmd+H` → `project_go_to_root_directory`

- [x] `Cmd+Shift+S` → `save_all_dirty_buffers`

- [x] `Ctrl+.` → `change_to_build_panel`
- [x] `Ctrl+,` → `close_build_panel`

- [x] `Ctrl+N` → `goto_next_jump`
- [x] `Ctrl+Shift+N` → `goto_prev_jump`
- [x] `Ctrl+M` → `build_in_build_panel`
- [x] `Ctrl+Shift+M` → `goto_first_jump`

- [x] `Ctrl+B` → `toggle_filebar`

- [x] `Ctrl+Z` → `execute_any_cli`
- [x] `Ctrl+Shift+Z` → `execute_previous_cli`

- [x] `Ctrl+X` → `command_lister`
- [x] `Ctrl+Shift+X` → `project_command_lister`

- [x] `Cmd+\` → `quick_swap_buffer`

- [x] `Cmd+P` → `jump_to_last_point`

- [x] `Cmd+Shift+I` → `list_all_functions_current_buffer` (mac mapping uses the non-`*_lister` variant)

- [x] `F1..F16` → `project_fkey_command`
- [x] `Alt+F4` → `exit_4coder`

## 2.2 File map (macOS)

- [x] `Cmd+PageUp` → `goto_beginning_of_file`
- [x] `Cmd+PageDown` → `goto_end_of_file`

- [x] `Cmd+Up` → `move_up_to_blank_line_end`
- [x] `Cmd+Down` → `move_down_to_blank_line_end`

- [x] `Cmd+Left` → `move_left_whitespace_boundary`
- [x] `Cmd+Right` → `move_right_whitespace_boundary`

- [x] `Cmd+Backspace` → `backspace_alpha_numeric_boundary`
- [x] `Cmd+Delete` → `delete_alpha_numeric_boundary`

- [x] `Ctrl+Backspace` → `snipe_backward_whitespace_or_token_boundary`
- [x] `Ctrl+Delete` → `snipe_forward_whitespace_or_token_boundary`

- [x] `Ctrl+Space` → `set_mark`
- [x] `Cmd+/` → `set_mark` (an additional mark shortcut on mac)

- [x] `Cmd+A` → `replace_in_range`
- [x] `Cmd+C` → `copy`
- [x] `Cmd+X` → `cut`
- [x] `Cmd+V` → `paste_and_indent`
- [x] `Cmd+Shift+V` → `paste_next_and_indent`

- [x] `Cmd+D` → `delete_range`
- [x] `Cmd+Shift+D` → `delete_line`

- [x] `Cmd+E` → `center_view`
- [x] `Cmd+Shift+E` → `left_adjust_view`

- [x] `Cmd+F` → `search`
- [x] `Cmd+Shift+F` → `list_all_locations`
- [x] `Ctrl+F` → `list_all_substring_locations_case_insensitive`

- [x] `Cmd+G` → `goto_line`
- [x] `Cmd+Shift+G` → `list_all_locations_of_selection`

- [x] `Cmd+J` → `snippet_lister`

- [x] `Cmd+Shift+K` → `kill_buffer`

- [x] `Cmd+L` → `duplicate_line`

- [x] `Cmd+M` → `cursor_mark_swap`

- [x] `Cmd+Shift+O` → `reopen`

- [x] `Cmd+Q` → `query_replace`
- [x] `Cmd+Shift+Q` → `query_replace_identifier`
- [x] `Ctrl+Q` → `query_replace_selection`

- [x] `Cmd+R` → `reverse_search`

- [x] `Cmd+S` → `save`
- [x] `Cmd+Shift+S` → `save_all_dirty_buffers`

- [x] `Cmd+T` → `search_identifier`
- [x] `Cmd+Shift+T` → `list_all_locations_of_identifier`

- [x] `Cmd+Y` → `redo`
- [x] `Cmd+Z` → `undo`

- [x] `Cmd+1` → `view_buffer_other_panel`
- [x] `Cmd+2` → `swap_panels`

- [x] `Cmd+Shift+.` → `view_jump_list_with_lister`

## 2.3 Code map (macOS)

- [x] `Cmd+Left` → `move_left_alpha_numeric_boundary`
- [x] `Cmd+Right` → `move_right_alpha_numeric_boundary`

- [x] `Ctrl+Left` → `move_left_alpha_numeric_or_camel_boundary`
- [x] `Ctrl+Right` → `move_right_alpha_numeric_or_camel_boundary`

- [x] `Cmd+;` → `comment_line_toggle`

- [x] `Tab` → `word_complete`
- [x] `Cmd+Tab` → `auto_indent_range`
- [x] `Shift+Tab` → `auto_indent_line_at_cursor`
- [x] `Cmd+Shift+Tab` → `word_complete_drop_down`

- [x] `Ctrl+R` → `write_block`
- [x] `Ctrl+T` → `write_todo`
- [x] `Ctrl+Y` → `write_note`

- [x] `Ctrl+D` → `list_all_locations_of_type_definition`
- [x] `Ctrl+Shift+T` → `list_all_locations_of_type_definition_of_identifier`

- [x] `Cmd+[` → `open_long_braces`
- [x] `Cmd+Shift+[` → `open_long_braces_semicolon`
- [x] `Cmd+Shift+]` → `open_long_braces_break`

- [x] `Ctrl+[` → `select_surrounding_scope`
- [x] `Ctrl+Shift+[` → `select_surrounding_scope_maximal`

- [x] `Ctrl+]` → `select_prev_scope_absolute`
- [x] `Ctrl+Shift+]` → `select_prev_top_most_scope`

- [x] `Ctrl+'` → `select_next_scope_absolute`
- [x] `Ctrl+Shift+'` → `select_next_scope_after_current`

- [x] `Ctrl+/` → `place_in_scope`
- [x] `Ctrl+-` → `delete_current_scope`

- [x] `Ctrl+I` → `if0_off`

- [x] `Ctrl+1` → `open_file_in_quotes`
- [x] `Ctrl+2` → `open_matching_file_cpp`

- [x] `Cmd+0` → `write_zero_struct`

- [x] `Cmd+W` → `jump_to_definition_at_cursor`

---

# 3) Commands list (to be completed)

This is a starter list of commands referenced by the default mappings and some common custom-layer commands.  
If you want a *complete* list, the next step would be to extract every `CUSTOM_COMMAND_SIG(...)` from `code/custom/` and copy their `CUSTOM_DOC("...")` strings here.

## 3.1 Editing / Text input

- [ ] `write_text_input`
- [ ] `delete_char`
- [ ] `backspace_char`
- [ ] `delete_range`
- [ ] `delete_line`
- [ ] `duplicate_line`
- [ ] `move_line_up`
- [ ] `move_line_down`

## 3.2 Cursor / movement

- [ ] `set_mark`
- [ ] `cursor_mark_swap`
- [ ] `move_up`, `move_down`, `move_left`, `move_right`
- [ ] `page_up`, `page_down`
- [ ] `seek_beginning_of_line`, `seek_end_of_line`
- [ ] `goto_beginning_of_file`, `goto_end_of_file`
- [ ] `goto_line`

## 3.3 Clipboard

- [ ] `copy`
- [ ] `cut`
- [ ] `paste`
- [ ] `paste_next`
- [ ] `paste_and_indent`
- [ ] `paste_next_and_indent`

## 3.4 Search / replace

- [ ] `search`
- [ ] `reverse_search`
- [ ] `search_identifier`
- [ ] `query_replace`
- [ ] `query_replace_identifier`
- [ ] `query_replace_selection`

## 3.5 Undo / redo

- [ ] `undo`
- [ ] `redo`

## 3.6 Files / buffers / panels

- [ ] `interactive_new`
- [ ] `interactive_open_or_new`
- [ ] `interactive_switch_buffer`
- [ ] `interactive_kill_buffer`
- [ ] `open_in_other`
- [ ] `kill_buffer`
- [ ] `quick_swap_buffer`
- [ ] `save`
- [ ] `save_all_dirty_buffers`
- [ ] `reopen`
- [ ] `swap_panels`
- [ ] `view_buffer_other_panel`

## 3.7 Build / CLI / project

- [ ] `build_search`
- [ ] `build_in_build_panel`
- [ ] `change_to_build_panel`
- [ ] `close_build_panel`
- [ ] `execute_any_cli`
- [ ] `execute_previous_cli`
- [ ] `project_command_lister`
- [ ] `project_fkey_command`
- [ ] `project_go_to_root_directory`

## 3.8 Code helpers

- [ ] `comment_line_toggle`
- [ ] `auto_indent_range`
- [ ] `word_complete`
- [ ] `word_complete_prev`
- [ ] `word_complete_drop_down`

---

# 4) Next steps (if you want this to be “complete”)

- [ ] Extract all `CUSTOM_COMMAND_SIG(...)` from `code/custom/` and list them here.
- [ ] Include each command’s `CUSTOM_DOC("...")` description.
- [ ] (Optional) Add a table: `Command -> Default shortcut (Win/Linux, macOS)` when a binding exists.