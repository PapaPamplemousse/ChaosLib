# ChaosLib 🛠️💥🌀

![Made with C](https://img.shields.io/badge/Made%20with-C-blue.svg?style=for-the-badge\&logo=c)
![Rocket-Proof](https://img.shields.io/badge/Rocket-Tested-FF4136.svg?style=for-the-badge)
![Embedded Safe](https://img.shields.io/badge/Embedded-Safe-brightgreen.svg?style=for-the-badge)
![Chaos Guaranteed](https://img.shields.io/badge/Chaos-Guaranteed-FF851B.svg?style=for-the-badge)
![Humans Optional](https://img.shields.io/badge/Humans-Optional-9B59B6.svg?style=for-the-badge)
![Undefined-Behavior-Free](https://img.shields.io/badge/UB-Free-2ECC40.svg?style=for-the-badge)
![Radiation-Tested](https://img.shields.io/badge/Radiation-Tested-F39C12.svg?style=for-the-badge)

**ChaosLib** is a **work-in-progress C library** designed to **replace libc for critical embedded systems**.
Safe memory, sane strings, predictable math — **all the chaos you want, none of the crashes**.

> 🚀 Built for satellites, rockets, microwaves… and humans who can handle it.

---

## 🔧 What is ChaosLib?

Think of it as **libc on steroids**, designed for when **satellites, rockets, or your sanity are at stake**:

* Core **types, status codes, and configurable assertions**
* **Memory ops** (`memcpy`, `memcmp`, `memset`)
* **Strings & stdlib replacements** (`atoi`, `strtol`, …)
* Low-level **math utilities**
* Optional “SAFE” **dynamic allocation**

All functions are **MISRA-friendly**, **single-return**, and just chaotic enough to keep you entertained.

> 💀 Undefined behavior? Not on my watch.

---

## 🏗️ Current Architecture

```
CHAOSLIB/
├── chaos_core/      # Core foundations (mandatory)
├── chaos_types/     # CHAOS types (no stdint.h)
├── chaos_alloc/     # Safe dynamic allocation
├── chaos_memory/    # memcpy / memset / memcmp
├── chaos_string/    # Safe string operations
├── chaos_math/      # Low-level math
├── chaos_stdlib/    # Safe atoi/strtol/etc.
├── tests/           # Unit tests (host)
├── config.mk        # Compile-time options
├── makefile
├── README.md
└── LICENSE
```

> ⚡ Warning: Contents may be **too chaotic for normal humans**.

---

## ⚡ Build & Test

1. **Configure** your options in `config.mk`
2. **Build the library**

```bash
make all
```

3. **Run the tests**

```bash
cd tests
make all
```

> Other test options exist but aren’t documented yet… explore at your own risk 🕵️‍♂️💥

---

## 🧙 Developer Motto

ChaosLib: **predictable enough to survive launch, chaotic enough to keep you awake**.

> **Code hard. Crash never. Humans optional. 🌀**

