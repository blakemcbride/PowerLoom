# Running PowerLoom under SBCL — Step-by-Step

All paths in this document are relative to this directory (the PowerLoom project root — the directory containing this file, `load-powerloom.lisp`, `sources/`, `native/`, etc.).

Prerequisites:
- **SBCL** installed and on `PATH` (tested with 2.6.3, any recent version should work).
- Pre-translated Lisp sources (`.slisp`) ship in `native/lisp/`, so **no C++/Java toolchain is required** — SBCL compiles them on first load and caches the fasls.
- This project bundles its own copy of STELLA under `sources/stella/` and `native/lisp/stella/`. You do **not** need the sibling `Stella/` tree.

---

## 1. Verify SBCL
```bash
sbcl --version        # any recent SBCL; 2.6.x confirmed working
```

## 2. Change to this directory
The loader uses `*load-truename*` to resolve its own pathnames, so start SBCL from the project root (or pass a full path to `load`).
```bash
cd <path-to>/PowerLoom
```

## 3. Launch SBCL and load PowerLoom
```bash
sbcl --load load-powerloom.lisp
```

What happens on first load:
- `load-powerloom.lisp` sets `*load-cl-struct-stella?* = t` (faster struct-based STELLA) and applies SBCL-specific optimization settings (`speed 3 safety 1`).
- It `load`s `native/lisp/stella/load-stella.slisp`, which boots STELLA.
- It then `make-system`s the `powerloom` system, which compiles every `.slisp` under `native/lisp/{stella,logic,powerloom,utilities}/` into fasls. **First run takes several minutes; subsequent runs load the cached fasls in seconds.**
- Fasls land under `native/lisp/bin/<sbcl-version>/…` so multiple SBCL versions can coexist.

When loading finishes you will see:
```
PowerLoom <version> loaded.
Type `(powerloom)' to get started.
```

## 4. Start the PowerLoom listener
```lisp
(powerloom)
```
You are now at the `PL-USER |= ` prompt. Try:
```lisp
(help)           ; list commands
(demo)           ; pick from the bundled demos
```

## 5. Exit the listener (and SBCL)
From the `PL-USER |=` prompt:
```lisp
(stop)           ; returns you to the SBCL `*` prompt
```
Ctrl-D at the `PL-USER |=` prompt does the same thing. Once you're back at the SBCL `*` prompt:
```lisp
(sb-ext:exit)    ; or Ctrl-D again
```
Tip: staying at the SBCL prompt after `(stop)` keeps PowerLoom loaded in memory, so you can re-enter with `(powerloom)` instantly instead of paying the load cost again.

## 6. (Optional) Run PowerLoom commands directly from the Lisp prompt
Instead of `(powerloom)`, you can skip the listener entirely and drive PowerLoom from the SBCL REPL:
```lisp
(in-package "STELLA")
```
Note: the `STELLA` package does **not** inherit from `COMMON-LISP`; prefix CL symbols with `CL:` (e.g. `CL:*` for the previous result). Exit SBCL with `(CL:exit)` or Ctrl-D.

## 7. (Optional) Save a pre-loaded image for instant startup
After step 3, from the SBCL prompt:
```lisp
(sb-ext:save-lisp-and-die "powerloom.core" :toplevel (lambda () (powerloom)) :executable nil)
```
Re-launch later (from this same directory) with:
```bash
sbcl --core powerloom.core
```

## 8. (Optional) Load extension systems (RDBMS, webtools, etc.)
Before loading, edit `load-powerloom.lisp` and set:
```lisp
(defvar *load-all-extensions?* t)
```
Or, from the prompt, call `(stella::make-system "<name>" :common-lisp ...)` individually.

---

## Troubleshooting

| Symptom | Fix |
|---|---|
| `File not found: …native/lisp/stella/load-stella.slisp` | You launched SBCL from the wrong directory. `cd` into this project directory first (the loader resolves paths from `*load-truename*`). |
| Compile warnings / style-warnings during first load | Expected — the translated code is aggressive. Non-fatal; loading continues. |
| `(powerloom)` undefined | Loading failed partway. Re-run after `rm -rf native/lisp/bin/` to force a clean recompile. |
| Slow startup every time | You are recompiling. Confirm `native/lisp/bin/<sbcl-version>/` is being populated and is writable. |
| Class redefinition errors after editing `.ste` files | Set `*load-cl-struct-stella?*` to `nil` in `load-powerloom.lisp` to use the CLOS backend (slower but tolerant of redefinition). |
| Want verbose compile output | Remove or comment out the `(setq *compile-verbose* nil *compile-print* nil)` block in `load-powerloom.lisp`. |

---

## Quick reference — minimal cold-start

```bash
cd <path-to>/PowerLoom
sbcl --load load-powerloom.lisp
```
then at the `*` prompt:
```lisp
(powerloom)
(demo)
```
