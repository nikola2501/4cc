# 4coder (4ed) — Project setup & build scripts (Go-focused)

This guide explains how to set up a **per-project** workflow in 4coder using a `project.4coder` file, how to wire up **build/run/test** commands for a single Go repository, and which **default shortcuts** trigger those commands.

It’s based on how this repo’s default layer works:
- Project configuration lives in `project.4coder`.
- “Project commands” are defined in `project.4coder` and executed via:
  - a **project command lister**, or
  - **F-keys** mapped to project commands.
- There is also a “standard build search” path (searches for `build.bat` / `build.sh` / `Makefile` up the directory tree), but for a Go repo you’ll usually want explicit project commands.

---

## 1) Two ways to build: Project commands vs. Build search

### 1.1 Project commands (recommended)
You define named commands like:
- `build`
- `test`
- `run`
- `lint`
- `fmt`

Each command can specify:
- per-OS command string (`.win`, `.linux`, `.mac`)
- output buffer (`*compilation*` for build/test/lint; `*run*` for long-running program output)
- whether to open a footer panel
- whether to save dirty files first

Then you run them via the project command lister or function keys.

### 1.2 Standard build search (fallback / quick-and-dirty)
There are editor commands that search upward from the current file directory (and then from the “hot directory”) for:
- Windows: `build.bat`
- Linux/macOS: `build.sh` or `Makefile`

That’s handy if you want “just run the nearest build script”, but it’s less descriptive than a proper `project.4coder` command list.

---

## 2) Minimal `project.4coder` for a Go repository (copy/paste)

Create `project.4coder` in the **root of your Go repo**.

This example assumes:
- your main module is at repo root (has `go.mod`)
- you build/run using `go test`, `go run`, `go build`
- you may optionally use `golangci-lint` if installed

```/dev/null/project.4coder#L1-170
version(2);
project_name = "MyGoService";

patterns = {
  "*.go",
  "go.mod",
  "go.sum",
  "*.md",
  "*.txt",
  "Makefile",
  "*.sh",
  "*.bat",
  ".env",
  "*.yaml",
  "*.yml",
  "*.json",
  "*.toml",
};

blacklist_patterns = {
  ".*",          // hidden files/dirs
  "vendor/*",    // if you vendor deps
  "bin/*",
  "dist/*",
  "build/*",
  ".git/*",
};

load_paths = {
  .win = {
    { .path = ".", .recursive = true, .relative = true, },
  },
  .linux = {
    { .path = ".", .recursive = true, .relative = true, },
  },
  .mac = {
    { .path = ".", .recursive = true, .relative = true, },
  },
};

commands = {
  // Build the module (produces an executable in ./bin for convenience)
  .build = {
    .win   = "echo build & if not exist bin mkdir bin & go build -o bin\\mygoservice.exe ./cmd/mygoservice",
    .linux = "echo build && mkdir -p bin && go build -o bin/mygoservice ./cmd/mygoservice",
    .mac   = "echo build && mkdir -p bin && go build -o bin/mygoservice ./cmd/mygoservice",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },

  // Run unit tests
  .test = {
    .win   = "echo test & go test ./...",
    .linux = "echo test && go test ./...",
    .mac   = "echo test && go test ./...",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },

  // Run the app quickly via `go run` (good for iterating)
  .run = {
    .win   = "echo run & go run ./cmd/mygoservice",
    .linux = "echo run && go run ./cmd/mygoservice",
    .mac   = "echo run && go run ./cmd/mygoservice",
    .out = "*run*",
    .footer_panel = false,
    .save_dirty_files = true,
    .cursor_at_end = true,
  },

  // Format code (Go uses gofmt; gofmt modifies files)
  .fmt = {
    .win   = "echo fmt & gofmt -w .",
    .linux = "echo fmt && gofmt -w .",
    .mac   = "echo fmt && gofmt -w .",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },

  // Lint (optional: requires golangci-lint to be installed in PATH)
  .lint = {
    .win   = "echo lint & golangci-lint run",
    .linux = "echo lint && golangci-lint run",
    .mac   = "echo lint && golangci-lint run",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },
};

fkey_command = {
  .F1 = "build",
  .F2 = "test",
  .F4 = "run",
  .F5 = "fmt",
  .F6 = "lint",
};
```

### Notes on the Go example
- Adjust `./cmd/mygoservice` to your real main package. If your main is at repo root, use `./` instead.
- If you don’t have a `cmd/` layout, change build/run commands accordingly.
- If you use `vendor/`, keep it blacklisted; otherwise indexing can get noisy.
- If your repo is a monorepo with multiple modules, you can:
  - create a separate `project.4coder` per module root, or
  - define separate commands like `build_api`, `build_worker` that target different `./cmd/...` entries.

---

## 3) Build scripts per project (optional)

For Go, you *don’t need* build scripts. Putting the commands directly into `project.4coder` is enough.

But if you prefer a single entrypoint script (e.g. to set env vars), use:
- `build.bat` on Windows
- `build.sh` on Linux/macOS

Then call those scripts from `commands.build`.

### 3.1 Example `build.bat` (Go)
```/dev/null/build.bat#L1-60
@echo off
setlocal

REM Example setup (edit as needed):
REM set GOFLAGS=-trimpath
REM set CGO_ENABLED=0

if not exist bin mkdir bin

echo build
go build -o bin\mygoservice.exe .\cmd\mygoservice

endlocal
```

### 3.2 Example `build.sh` (Go)
```/dev/null/build.sh#L1-60
#!/usr/bin/env sh
set -eu

# Example setup (edit as needed):
# export GOFLAGS='-trimpath'
# export CGO_ENABLED=0

mkdir -p bin

echo build
go build -o bin/mygoservice ./cmd/mygoservice
```

If you use scripts, update `commands.build` like:
- Windows: `"echo build & build.bat"`
- Linux/macOS: `"echo build && ./build.sh"`

---

## 4) Default shortcuts to run project commands

The default keymap in this repo binds:

- **`F1..F16` → `project_fkey_command`**

Meaning: if your `project.4coder` sets:
- `fkey_command.F1 = "build"`
- `fkey_command.F2 = "test"`
- `fkey_command.F4 = "run"`

Then pressing `F1` runs the configured `"build"` command, etc.

### Project command lister (run any project command by name)
Default shortcuts:

- **Windows/Linux**: `Alt+Shift+X` → `project_command_lister`
- **macOS**: `Ctrl+Shift+X` → `project_command_lister`

Use this when you don’t want to memorize F-key slots.

### Jump to project root directory (hot directory)
Useful when you rely on relative paths and want builds to run from the repo root:

- **Windows/Linux**: `Ctrl+H` → `project_go_to_root_directory`
- **macOS**: `Cmd+H` → `project_go_to_root_directory`

---

## 5) Output buffers: `*compilation*` vs `*run*`

Typical convention:
- `*compilation*`: build/test/lint output (so you can jump through errors)
- `*run*`: application output (server logs, etc.)

In `project.4coder` you control this with `.out`.
You also control whether the command opens in a footer panel with `.footer_panel`.

---
