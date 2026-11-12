# pkgscan

A lightweight AUR package security scanner that parses PKGBUILDs for malicious patterns before installation.

![demo](demo.gif)

## Features
- **PKGBUILD Static Analysis**: Parses PKGBUILDs against known malicious patterns, base64 payload heuristics, and IP address sources.
- **AUR Metadata Checks**: Inspects votes, package age, maintainer status, and out-of-date flags via AUR RPC API.
- **Native ALPM Pacman Hook**: Hooks directly into pacman pre-transactions (`PreTransaction`) to scan packages before installation/upgrade.
- **Process Tree Search**: Inspects parent process (`paru`/`yay`) working directories via `/proc` to scan local PKGBUILDs in-place without disk duplication.
- **Verification Database & Caching**: Tracks package verification status in `/var/lib/pkgscan/database.json` and logs transactions to `/var/log/pkgscan.log` to prevent duplicate scans.
- **PGP Signature Verification**: Bypasses hashing for signed packages verified by GPG key signatures.
- **Official Package Skipping**: Automatically checks package repositories and skips non-AUR official repository packages.
- **Suspicion Flag System**: Scopes anomalous package behaviour with warning levels and colored terminal danger scoring.

## Dependencies
- `git`
- `base-devel`
- `curl`
- `cjson`

## Installation
```bash
git clone https://github.com/Vikyek/pkgscan
cd pkgscan
make && sudo make install
```
Or via AUR:

```bash
paru -S pkgscan
```

## Usage

Scan a package directly:
```bash
pkgscan <package>
pkgscan pkg1 pkg2 pkg3
```

Scan a local PKGBUILD directory:
```bash
pkgscan --test /path/to/pkgbuild_dir
```

Enable native ALPM pacman hook:
```bash
sudo pkgscan --hook enable
```

Check hook status:
```bash
pkgscan --hook status
```

Disable hook:
```bash
sudo pkgscan --hook disable
```

### Command-Line Flags
| Flag | Description |
|------|-------------|
| `--hook enable` | Installs ALPM pacman hook to `/etc/pacman.d/hooks/pkgscan.hook` |
| `--hook disable` | Removes ALPM pacman hook and cleans legacy shell hooks |
| `--hook status` | Shows current ALPM and shell hook installation status |
| `--hook-mode` | Runs pkgscan in pacman hook mode (reads packages from `stdin`) |
| `--test <path>` | Scans a local PKGBUILD directory without cloning |
| `--scan-all` | Forces scanning of packages regardless of database cache |
| `--force-hash` | Always verifies SHA256 hashes even if PGP signature matches |
| `--database <path>` | Specifies custom database JSON path (default: `/var/lib/pkgscan/database.json`) |
| `--log <path>` | Specifies custom transaction log path (default: `/var/log/pkgscan.log`) |
| `--help` | Displays help message and CLI usage |

## How It Works
When scanning an AUR package, `pkgscan`:
1. Checks whether the target is an official Arch repository package (via `pacman -Si`) and skips scanning if it is not an AUR package.
2. Checks the local JSON database (`/var/lib/pkgscan/database.json`) and GPG signatures/SHA256 hashes to skip already verified packages.
3. Locates local PKGBUILD sources in parent process (`paru`/`yay`) working directories via `/proc` or local caches to inspect in-place, falling back to cloning from AUR to `/tmp` if necessary.
4. Scores PKGBUILD contents against weighted pattern keywords in `keywords.h`, checks for obfuscated base64 payloads, and detects IP addresses in source URLs.
5. Queries the AUR RPC v5 API for package metadata and flags suspicious conditions (e.g. low vote count, newly submitted packages, or recent edits after long inactivity).
6. Prompts for user confirmation before proceeding with installation and logs the result to `/var/log/pkgscan.log`.

Keywords are defined in `keywords.h` and can be customized before compiling.

## Danger Levels
| Level    | Score | Description                          |
|----------|-------|--------------------------------------|
| Low      | 0     | No suspicious patterns found         |
| Medium   | 1-15  | Some patterns detected               |
| High     | 16-35 | Suspicious patterns, review advised  |
| Critical | 35+   | Multiple serious patterns detected   |

## Limitations
- Static analysis only, so obfuscated or encoded payloads may bypass detection
- Keyword list is open source and can be studied by malicious package authors
- Metadata flags are heuristics, not guarantees
- Not a substitute for manual PKGBUILD review on high risk packages
- Sophisticated attacks are outside the scope of this tool

## Contributing
Pull requests are welcome to help improve detection patterns or features. To adjust detection rules, edit `keywords.h` and recompile.

---

## Support & Sponsorship

`pkgscan` is authored and maintained by **[Vikyek](https://github.com/Vikyek)** as an independent open-source project. Everything is 100% open-source, telemetry-free, and public.

<div align="center">


[![Sponsor Vikyek](https://img.shields.io/badge/Sponsor-%E2%9D%A4-ea4aaa?logo=github&style=for-the-badge)](https://github.com/sponsors/Vikyek)
[![Donate on Liberapay](https://img.shields.io/badge/Donate-Liberapay-f6c915?style=for-the-badge&logo=liberapay&logoColor=black)](https://liberapay.com/Vikyek)
[![Donate with Stripe](https://img.shields.io/badge/Donate-Stripe-635BFF?style=for-the-badge&logo=stripe&logoColor=white)](https://profile.stripe.com/@vikyek)

</div>

> ### 🎯 Active Sponsorship Goal: Monthly Living Essentials
> **Target:** **2,710 PLN / ~$680 USD per month** (`630 PLN / week`) — Rent & Essential Utilities  
> Covering basic living essentials directly unlocks dedicated, sustainable full-time independent open-source engineering across Arch Linux utilities, developer tools, and AI middleware free from corporate telemetry, ads, or paywalls.

If this project saves you time, optimizes your setup, or accelerates your workflow, consider supporting ongoing work:

- **GitHub Sponsors**: [github.com/sponsors/Vikyek](https://github.com/sponsors/Vikyek) *(Monthly tiers and one-time tips)*
- **Liberapay**: [liberapay.com/Vikyek](https://liberapay.com/Vikyek) *(0% platform fee recurrent patronage in EUR/USD/PLN)*
- **Direct Stripe Profile**: [profile.stripe.com/@vikyek](https://profile.stripe.com/@vikyek) *(Direct one-time tips & sponsorship)*

Every contribution—monthly or one-time—directly supports active maintenance, hardware testbeds, and new feature development!
