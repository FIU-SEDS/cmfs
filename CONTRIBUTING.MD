# Contributing to Cosmic Messenger Flight Software (CMFS)

Thanks for contributing to **Cosmic Messenger Flight Software (CMFS)**, the FIU SEDS flight software project.

CMFS is being developed in C++ for the Teensy 4.1. The current PlatformIO prototype uses FreeRTOS to blink the onboard LED, with sensor integration planned. We are learning and validating parts of the stack as we go, so **small changes, clear documentation, and reproducible tests** are more important than large, complicated pull requests.

Before making changes, read the repository [README](README.md) and any setup documentation in `docs/`. Use [GitHub Issues](https://github.com/FIU-SEDS/cmfs/issues) for tasks and bugs. Keep design discussions tied to an issue or pull request so decisions are easy to find later.

## 1) Branching rules

- **Do not push directly to `main`.**
- Create a topic branch for every change.
- Name branches using `type/short-description`:
  - `feature`: new functionality or meaningful behavior expansion
  - `fix`: bug fixes and regressions
  - `docs`: documentation-only changes
  - `chore`: tooling, dependencies, CI, and cleanup
  - `spike`: time-boxed research or experiments
  - `test`: tests and test infrastructure
- Examples:
  - `feature/bmp390-driver`
  - `feature/flight-state-machine`
  - `spike/freertos-startup`
  - `fix/uart-buffer-overflow`
  - `docs/sensor-interface`

A `spike` should answer a specific technical question and document what was learned, even if the approach does not work.

## 2) Commits and history

- Keep commits small, focused, and easy to review.
- Write descriptive commit messages, preferably in the form `type: summary`:
  - `feat: add barometer readout`
  - `fix: handle invalid sensor sample`
  - `docs: explain FreeRTOS task priorities`
- Do not commit secrets, machine-specific configuration, generated build artifacts, or temporary debug files.
- Avoid rewriting commits after a branch has been shared.
- **Never force-push shared branch history** without coordinating with its contributors.

## 3) Keep your branch current

Regularly merge the latest `main` into your topic branch:

```bash
git fetch origin
git merge origin/main
```

Resolve conflicts carefully and rerun the applicable local checks afterward.

## 4) Pull request expectations

- Open a pull request when the change is ready for review; use a draft PR if you want early feedback.
- Keep each PR focused on one logical change.
- Link the related GitHub Issue when applicable (for example, `Closes #12`).
- Request **at least one reviewer** other than the author.
- Do not merge while required CI checks are failing, once those checks are configured.
- Prefer **Squash and merge** to keep `main` readable.

Every PR should answer:

1. **What changed?** Summarize the implementation.
2. **Why?** State the issue, requirement, or design decision.
3. **How was it verified?** Include commands, tests, or serial logs.
4. **Any limitations?** Identify hardware not tested, remaining risks, or follow-up work.

For hardware-dependent changes, include the **board, sensor breakout, interface (I2C/SPI/UART), and test outcome**. A short terminal log or photo is helpful when it provides evidence.

## 5) Local checks before requesting review

For firmware changes, run `just fmt` and review the formatting diff, then run `just build` for Teensy 4.1. Run applicable host tests as they become available. Use `just --list` to discover recipes and see the [setup guide](docs/SETUP.md) for tool requirements.

In the PR, include the checks you ran and any limits on verification. Documentation-only changes do not require flashing firmware.

## 6) Embedded software and review guidelines

Follow the [C++ naming conventions](docs/CODING_STYLE.md) for project-owned firmware. Check names during review when adding or renaming files or identifiers.

- **Safety and correctness:** Flight-state transitions, recovery-related logic, sensor validation, and error handling need explicit review and tests. Do not present a bench prototype as flight-qualified software.
- **C++:** Make resource ownership and lifetimes explicit. Document callback, linkage, and ownership assumptions at C and FreeRTOS boundaries.
- **FreeRTOS:** Explain task priorities, timing assumptions, stack sizes, and ownership of shared resources when adding or modifying tasks.
- **Interrupts and concurrency:** Keep interrupt handlers short; use appropriate task notifications, queues, or synchronization primitives. Do not add blocking operations inside an ISR.
- **Drivers:** Keep device-specific drivers separate from application logic. Handle initialization failures, invalid readings, and communication timeouts explicitly.
- **Testing:** Add host-side tests for pure logic (such as flight-state transitions) where possible. Record hardware-in-the-loop results for sensor, peripheral, interrupt, or scheduling changes.
- **Scope:** Avoid unrelated refactors in feature PRs. Call out interface changes and behavior changes clearly.

## 7) Issues, sprints, and design decisions

CMFS uses short development sprints to make incremental progress toward a working prototype.

- Prefer **one actionable GitHub Issue per deliverable**, with an owner and acceptance criteria.
- Associate issues with a sprint or milestone when those are configured.
- Use issue comments or GitHub Discussions for questions that need a decision; summarize the result in the issue, PR, or relevant Markdown documentation.
- Close an issue only when its acceptance criteria are met or clearly explain what remains.
- Update documentation when an implementation decision changes the architecture, developer setup, or hardware interface.

An issue is ready to implement when it explains **what to build, how to know it works, and any dependencies**.

## 8) After merge

- Confirm the PR was merged successfully.
- Delete the remote topic branch.
- Delete your local topic branch and update `main`:

```bash
git checkout main
git pull origin main
git branch -d your-branch-name
```

- Close or update related issues and document follow-up tasks as needed.

## 9) Licensing and source headers

Contributions must follow the licensing terms adopted by the CMFS repository. Check for a root `LICENSE` file and confirm the project license with maintainers before adding SPDX identifiers or copyright notices.

---

**Keep contributions small, reviewable, and testable.** The goal is steady progress toward reliable flight software, not perfect tooling on day one.
