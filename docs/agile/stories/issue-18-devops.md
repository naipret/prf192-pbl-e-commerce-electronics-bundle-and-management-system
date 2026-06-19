# GitHub Project Card: Story 10.1 - DevOps build release & Container Package

## 📋 Description

Setup repository compilation validation pipeline. Configure the multi-stage Docker build and create the GitHub Action workflow to cross-compile the production binary for Windows automatically.

## 🛠️ Files to Modify/Create

* **Modify**: [Dockerfile](../../../Dockerfile)
* **Modify**: [.github/workflows/build-and-release.yml](../../../.github/workflows/build-and-release.yml)

## 📖 Global References

* Refer to compiler flags in [CONTRIBUTING.md](../../../CONTRIBUTING.md#5-development-build-commands).
* Refer to directory structures in [docs/readme.md](../../../docs/readme.md).

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] The `Dockerfile` successfully builds a static C binary in the build stage and runs it in a minimal runtime container.
* [ ] GitHub workflow config `.github/workflows/build-and-release.yml` triggers on push to `main` and Pull Requests.
* [ ] CI sets up MSYS2 with UCRT64 environment on `windows-latest` runner.
* [ ] CI compiles the codebase for Windows using:
  `gcc -std=c17 -m64 -O2 -Iinclude src/*.c -o bin/prf192-pbl-e-commerce-electronics-bundle-and-management-system.exe`
* [ ] CI uploads and drafts a GitHub release containing the resulting Windows `.exe` executable artifact successfully.
