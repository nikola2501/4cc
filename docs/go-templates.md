# Go Templates for 4coder (no LSP) — vendor + stdlib workflows

This repo is the 4coder Community codebase. This document describes **template `project.4coder` files** you can copy into *your own* Go repos (or use as a starting point) to get a solid “IDE-like” workflow without LSP:

- fast `go build` / `go test` / `go run` / `gofmt`
- a clean default project (no vendor indexed)
- an alternate project (vendor indexed)
- a separate “project” to browse/search Go’s **standard library source** as if it were a normal codebase
- a multi-`cmd/` layout template

You said you’re on Linux and you’re fine opening each template in a **separate 4coder window**. That’s a great workflow: keep your app in one instance, stdlib in another, and (optionally) vendor in a third.

---

## Principles

### 1) Two project files: with and without vendor indexing
Indexing `vendor/` can be heavy. The best practice is:

- **default project**: exclude `vendor/` from indexing (clean, fast)
- **vendor project**: include `vendor/` in `load_paths` only when you need deep code reading/searching there

### 2) Stdlib source
Go stdlib source lives at:

- `$(go env GOROOT)/src`

You can treat that directory as its own “project” by creating a `project.4coder` next to it (or in a separate folder that points `load_paths` into it).

Then you can open it in a separate 4coder instance and use all the usual navigation/search tools.

---

## Requirements (recommended)
These templates assume:

- `go` is installed and in `PATH`
- optionally `rg` (ripgrep) is installed for fast repo/vendor/stdlib searching via CLI
  - install on Ubuntu: `sudo apt install ripgrep`

Even without `rg`, your `go test` outputs and editor search will still work, but `rg` makes it much nicer.

---

## Folder layout for templates in this repository

This repo contains a place to store templates:

- `4cc/go-templates/`

Recommend you keep these as **reference examples** and copy them into your actual repos.

Templates described below:

- `4cc/go-templates/single-main/project.4coder`
- `4cc/go-templates/single-main-with-vendor/project.4coder`
- `4cc/go-templates/go-stdlib/project.4coder`
- `4cc/go-templates/multi-cmd/project.4coder`

> Note: These are templates. Paths like `.` mean “the folder containing this project file”.

---

## How to open each in a separate 4coder instance (Linux)

Typical workflow:

1) Open your application repo:
   - start 4coder with its hot directory set to repo root
   - open/click `project.4coder` for the template you want in that repo
2) In another terminal, open stdlib project:
   - start another 4coder instance with hot directory set to the stdlib project folder

If you want, you can create shell aliases, e.g.:

- `4coder -d /path/to/repo` for your app
- `4coder -d /path/to/go-stdlib-project` for stdlib browsing

(Exact CLI flags depend on how your 4coder build is packaged; if you don’t have a `-d` option, just `cd` into the directory and start it.)

---

# Template 1: Single-module, single `main` at repo root (no vendor indexing)

Use when:
- one `go.mod` at repo root
- one `package main` at repo root (i.e. `go run .` works)
- you want fast indexing and you rarely need to read vendor code

Create/copy:

```/dev/null/project.4coder#L1-170
version(2);
project_name = "go-single-main (no vendor)";

patterns = {
  "*.go",
  "go.mod",
  "go.sum",
  "*.md",
  "*.txt",
  "Makefile",
  "*.sh",
  "*.json",
  "*.yaml",
  "*.yml",
  "*.toml",
};

blacklist_patterns = {
  ".*",
  ".git/*",
  "vendor/*",
  "bin/*",
  "dist/*",
  "build/*",
};

load_paths = {
  .linux = {
    { .path = ".", .recursive = true, .relative = true, },
  },
};

commands = {
  .build = {
    .linux = "echo build && mkdir -p bin && go build -o bin/app .",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },

  .test = {
    .linux = "echo test && go test ./...",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },

  .run = {
    .linux = "echo run && go run .",
    .out = "*run*",
    .footer_panel = false,
    .save_dirty_files = true,
    .cursor_at_end = true,
  },

  .fmt = {
    .linux = "echo fmt && gofmt -w .",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },

  // Optional fast grep (requires ripgrep):
  .search_repo = {
    .linux = "echo 'rg (repo): edit this command to include your pattern' && rg -n --hidden --glob '!**/.git/*' --glob '!vendor/**' TODO .",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = false,
    .cursor_at_end = false,
  },
};

fkey_command = {
  .F1 = "build",
  .F2 = "test",
  .F4 = "run",
  .F5 = "fmt",
};
```

Notes:
- Replace `TODO` in `search_repo` with your actual query; without LSP, this is a handy pattern.
- Keep `vendor/*` blacklisted here so your day-to-day project remains snappy.

---

# Template 2: Single-module, single `main` at repo root (vendor indexed)

Use when:
- you *actively* need to read/search into `vendor/` and want it indexed like normal code

Key difference:
- `vendor/*` is **not** blacklisted
- `vendor/` is included in `load_paths`

```/dev/null/project.4coder#L1-190
version(2);
project_name = "go-single-main (WITH vendor indexed)";

patterns = {
  "*.go",
  "go.mod",
  "go.sum",
  "*.md",
  "*.txt",
  "*.sh",
  "*.json",
  "*.yaml",
  "*.yml",
};

blacklist_patterns = {
  ".*",
  ".git/*",
  "bin/*",
  "dist/*",
  "build/*",
};

load_paths = {
  .linux = {
    // repo source
    { .path = ".", .recursive = true, .relative = true, },

    // vendor (explicit; yes this duplicates '.', but it documents intent)
    { .path = "vendor", .recursive = true, .relative = true, },
  },
};

commands = {
  .build = {
    .linux = "echo build && mkdir -p bin && go build -o bin/app .",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },

  .test = {
    .linux = "echo test && go test ./...",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },

  .run = {
    .linux = "echo run && go run .",
    .out = "*run*",
    .footer_panel = false,
    .save_dirty_files = true,
    .cursor_at_end = true,
  },

  .fmt = {
    .linux = "echo fmt && gofmt -w .",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },

  // Search vendor quickly (requires ripgrep):
  .search_vendor = {
    .linux = "echo 'rg (vendor): edit this command to include your pattern' && rg -n TODO vendor",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = false,
    .cursor_at_end = false,
  },
};

fkey_command = {
  .F1 = "build",
  .F2 = "test",
  .F4 = "run",
  .F5 = "fmt",
  .F6 = "search_vendor",
};
```

Notes:
- Indexing vendor can be noisy/heavy. That’s why I strongly recommend using this template only when needed (separate window).

---

# Template 3: Go standard library source as its own “project”

Goal:
- open Go’s stdlib source (`GOROOT/src`) in a separate 4coder window
- use the same navigation/search workflow as any other project

## Option A (simple): put the project file inside `$(go env GOROOT)/src`
If you don’t want to modify your Go installation directory, skip this.

If you *do* allow it, create `project.4coder` at:

- `$(go env GOROOT)/src/project.4coder`

Example:

```/dev/null/project.4coder#L1-170
version(2);
project_name = "go-stdlib";

patterns = {
  "*.go",
  "*.s",
  "*.c",
  "*.h",
  "*.md",
  "*.txt",
};

blacklist_patterns = {
  ".*",
  ".git/*",
  "testdata/*",
};

load_paths = {
  .linux = {
    { .path = ".", .recursive = true, .relative = true, },
  },
};

commands = {
  // Optional: run stdlib tests (can be heavy):
  .test_std = {
    .linux = "echo 'stdlib tests (can take a while)' && go test ./...",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = false,
    .cursor_at_end = false,
  },

  // Optional `rg` search inside stdlib (requires ripgrep):
  .search_std = {
    .linux = "echo 'rg (stdlib): edit this command to include your pattern' && rg -n TODO .",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = false,
    .cursor_at_end = false,
  },
};

fkey_command = {
  .F2 = "test_std",
  .F6 = "search_std",
};
```

## Option B (recommended): keep a separate folder with a project file pointing into stdlib
Create a folder anywhere you like, e.g.:

- `~/4coder-projects/go-stdlib/`

Inside it, create `project.4coder` that uses an **absolute** load path to `GOROOT/src`.

Because `project.4coder` doesn’t have a built-in `$(...)` expansion, you’ll hardcode the path once.
You can discover it via:

- `go env GOROOT`

Then set `load_paths` to that.

Example (edit `/usr/local/go` to your actual GOROOT):

```/dev/null/project.4coder#L1-120
version(2);
project_name = "go-stdlib (external project)";

patterns = { "*.go", "*.s", "*.c", "*.h", "*.md", "*.txt", };

blacklist_patterns = { ".*", ".git/*", "testdata/*", };

load_paths = {
  .linux = {
    { .path = "/usr/local/go/src", .recursive = true, .relative = false, },
  },
};

commands = {
  .search_std = {
    .linux = "echo 'rg (stdlib): edit this command to include your pattern' && rg -n TODO /usr/local/go/src",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = false,
    .cursor_at_end = false,
  },
};

fkey_command = {
  .F6 = "search_std",
};
```

This makes stdlib feel like a “normal project” in its own window.

---

# Template 4: Multiple binaries under `cmd/` (multi-cmd)

Use when:
- one `go.mod`
- multiple entry points: `./cmd/api`, `./cmd/worker`, etc.

```/dev/null/project.4coder#L1-220
version(2);
project_name = "go-multi-cmd";

patterns = {
  "*.go",
  "go.mod",
  "go.sum",
  "*.md",
  "*.txt",
  "*.sh",
  "*.json",
  "*.yaml",
  "*.yml",
};

blacklist_patterns = {
  ".*",
  ".git/*",
  "vendor/*",
  "bin/*",
  "dist/*",
  "build/*",
};

load_paths = {
  .linux = {
    { .path = ".", .recursive = true, .relative = true, },
  },
};

commands = {
  .build_all = {
    .linux = "echo build_all && mkdir -p bin && go build ./...",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },

  .test = {
    .linux = "echo test && go test ./...",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },

  .build_api = {
    .linux = "echo build_api && mkdir -p bin && go build -o bin/api ./cmd/api",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },

  .run_api = {
    .linux = "echo run_api && go run ./cmd/api",
    .out = "*run*",
    .footer_panel = false,
    .save_dirty_files = true,
    .cursor_at_end = true,
  },

  .build_worker = {
    .linux = "echo build_worker && mkdir -p bin && go build -o bin/worker ./cmd/worker",
    .out = "*compilation*",
    .footer_panel = true,
    .save_dirty_files = true,
    .cursor_at_end = false,
  },

  .run_worker = {
    .linux = "echo run_worker && go run ./cmd/worker",
    .out = "*run*",
    .footer_panel = false,
    .save_dirty_files = true,
    .cursor_at_end = true,
  },
};

fkey_command = {
  .F1 = "build_all",
  .F2 = "test",
  .F4 = "run_api",
  .F8 = "run_worker",
};
```

---

## Recommended “multi-window” setup (Linux)

- Window 1: your app project (no vendor indexing)
- Window 2: your app project (vendor indexed) — open only when debugging vendored code
- Window 3: go stdlib project

Why:
- keeps daily work fast
- still gives you full access when you need it

---

## Next step (if you want it): better parameterized searching
These templates include `rg` examples with a hardcoded `TODO` pattern.
If you want a nicer workflow (type a query in 4coder and run `rg` with it), we can add a small custom command that:
- prompts for a search string
- runs `rg` in a chosen folder (repo/vendor/stdlib)
- routes output to `*compilation*` so you can jump through results

That still avoids LSP but feels much more “IDE”.