# CMFS Development Workflow

**Cosmic Messenger Flight Software (CMFS)** · FIU SEDS  
**Audience:** New contributors, current team members, and maintainers  
**Project:** [FIU-SEDS/cmfs](https://github.com/FIU-SEDS/cmfs)  
**Prototype milestone:** December 18, 2026 (bench-top demonstration)

This guide explains **how we collaborate**, from choosing a sprint task to merging a pull request (PR). You do **not** need to be an expert in C++ or FreeRTOS before contributing. Start with a small, testable change, ask questions in its GitHub Issue, and document what you learn.

> **One-line workflow:** **Onboard → select an issue → create a branch → implement → validate → open a PR → review → squash merge → close/verify the issue.**
>
> The December prototype is **not flight-qualified software**. Do not connect or actuate recovery/pyrotechnic outputs during ordinary bench bring-up.

---

## 1. Start here: onboarding checklist

Before claiming your first issue:

- [ ] Read the root [`README.md`](../README.md) for the project overview.
- [ ] Read [`CONTRIBUTING.MD`](../CONTRIBUTING.MD) for branch and review rules. (Follow the filename actually used by the repository if its case differs.)
- [ ] Read [`AGENTS.md`](../AGENTS.md) for repository-specific coding conventions and tool usage.
- [ ] Read [the setup guide](SETUP.md) for the current tooling status.
- [ ] Review the [architecture guide](ARCHITECTURE.md) and its bench milestones.
- [ ] Ask a maintainer which **GitHub Project** tracks the current sprint and which issue is suitable for your first contribution.
- [ ] Check available commands with `just --list` rather than assuming a command exists.

Clone the project and inspect it:

```bash
git clone https://github.com/FIU-SEDS/cmfs.git
cd cmfs
```

Run `just --list` if `just` is installed. If you don't have physical hardware, you can still contribute to documentation, host-side tests, the flight-state machine, and some reusable libraries.

See the [architecture guide](ARCHITECTURE.md) for the planned locations of board startup, sensor drivers, portable logic, and host tools.

---

## 2. How we manage work in GitHub

Use **GitHub Issues** for actionable deliverables and **one GitHub Project** to track weekly sprints. Avoid tracking work exclusively in chats or personal notes: the issue should remain the source of truth.

### Choose an issue template

| Template | Use it for | Example |
| --- | --- | --- |
| **Task / Feature** (`01-task.yml`) | A deliverable with acceptance criteria | Read an IMU over SPI |
| **Bug Report** (`02-bug.yml`) | Something that behaves incorrectly | Sensor init fails intermittently |
| **Technical Spike** (`03-spike.yml`) | A short experiment to answer an uncertainty | Validate FreeRTOS scheduler startup with the selected Teensy board support |

Create issues using **GitHub → Issues → New issue**. Write a clear objective, observable acceptance criteria, and a verification plan. Link related work and blockers.

**Issue example**

- **Title:** `[Task]: Read barometer pressure over I2C`
- **Objective:** Initialize a breakout board and publish pressure readings.
- **Acceptance criteria:** Sensor initializes; readings are plausible; errors/timeouts are reported; procedure is documented.
- **Validation:** Build firmware; flash to the test board; capture a timestamped serial log.
- **Dependencies:** I²C pins and sensor model confirmed in hardware documentation.

### GitHub Project fields and statuses

The recommended board is:

```text
Backlog → Ready → In Progress → Review → Done
```

- **Backlog:** Proposed work, not yet refined.
- **Ready:** Scoped, acceptance criteria clear, dependencies resolved, available for assignment.
- **In Progress:** An owner is actively implementing it.
- **Review:** A PR is open and awaiting review/validation.
- **Done:** Merged and verified against the issue's acceptance criteria.

Use Project fields **Iteration/Sprint**, **Priority**, and **Area/Subsystem** if configured. Assign the issue to an owner. These fields and columns are **configured in GitHub Projects**; committing YAML issue templates alone does not create them.

### Weekly sprint rhythm

| When | Team action | Expected result |
| --- | --- | --- |
| **Start of sprint** | Pick a small set of Ready issues, assign owners, agree on acceptance criteria | A sprint that can realistically be completed |
| **Mid-sprint** | Comment on blockers, share test evidence, revise scope if needed | Risks identified early |
| **End of sprint** | Demo what works, review/merge PRs, record unfinished tasks | Observable progress and a clean handoff |

**Rule:** A sprint is successful when we can *demonstrate verified progress*, not merely when issues are moved to Done. If a task is blocked, document the blocker and either carry it forward or split it into a smaller deliverable.

---

## 3. The contribution workflow: issue to merged PR

### Step 1 — Claim and understand the issue

1. Choose a **Ready** issue from the current sprint.
2. Assign yourself (or ask a maintainer to assign you).
3. Read the acceptance criteria, related issues, and hardware requirements.
4. Move it to **In Progress**.
5. Ask questions **on the issue**, so answers remain visible to other contributors.

Do not silently expand the scope of an issue. If you discover additional work, discuss it with the maintainer and create or link a follow-up task as appropriate.

### Step 2 — Create a topic branch

Never push directly to `main`. Start from an updated local `main`:

```bash
git switch main
git pull origin main
git switch -c feature/barometer-driver
```

Choose a descriptive branch prefix:

| Prefix | Meaning | Example |
| --- | --- | --- |
| `feature/` | New functionality | `feature/flight-state-machine` |
| `fix/` | Bug fix | `fix/i2c-timeout` |
| `docs/` | Documentation | `docs/setup-guide` |
| `chore/` | Tooling or maintenance | `chore/ci-workflow` |
| `spike/` | Time-boxed experiment | `spike/freertos-startup` |
| `test/` | Test coverage or infrastructure | `test/fsm-transitions` |

### Step 3 — Implement a focused change

- Keep changes limited to the issue's objective.
- Use clear C++ types, explicit resource ownership, and small modules.
- Keep portable logic independent of Teensy and FreeRTOS APIs. Put board startup, pin ownership, and task coordination under `fw-flight-computer/`.
- Do not place flight-state decisions inside sensor drivers. Drivers measure; flight logic evaluates; application tasks orchestrate.
- Record assumptions about pinouts, sensor addresses, interrupt ownership, task priorities, stacks, synchronization, and failure behavior when relevant.
- When calling C or FreeRTOS APIs from C++, document linkage, ownership, and callback lifetimes. Confirm which component owns each exception handler.

Commit small, reviewable steps:

```bash
git add <files-you-changed>
git commit -m "feat: add barometer initialization"
git push -u origin feature/barometer-driver
```

Replace `<files-you-changed>` with actual paths. Avoid committing generated firmware and build directories, secrets, or machine-specific configuration.

### Step 4 — Validate your work

For firmware changes, apply the project's formatting with `just fmt`, review the diff, and compile the Teensy target with `just build`. Run the [host tests](SETUP.md#run-host-tests) for portable code. For documentation changes, check links and verify that the described commands and paths match the checkout. See the [setup guide](SETUP.md) for tool requirements.

**Report verification accurately:**

- **Host-tested:** Unit tests or tools ran on a development computer.
- **Target-built:** Firmware compiled for Teensy 4.1.
- **Hardware-tested:** Firmware was flashed onto a real test board and the behavior was observed.

These are **not interchangeable**. If you cannot test on hardware, say so in the PR. Never treat a successful build as proof of sensor readings, FreeRTOS scheduling, or safe flight behavior.

For bench tests, record board revision, sensor breakout model, wiring/pins, test procedure, observed output, and known failures. Keep recovery/pyrotechnic circuits disconnected during routine bring-up.

### Step 5 — Open a pull request

On GitHub, open a PR from your topic branch into `main`. The repository's [PR template](../.github/PULL_REQUEST_TEMPLATE.md) should guide your description:

1. **Summary:** What changed and why?
2. **Related Issue:** Use `Closes #123` when merging this PR will complete the issue.
3. **Validation:** Check only the commands actually run; include logs/results or explain limitations.
4. **Hardware/Embedded Impact:** List changes to pins, interfaces, RTOS scheduling, interrupts, or recovery behavior; use `N/A` if irrelevant.
5. **Review Checklist:** Tests, documentation, breaking changes, requested reviewer.

For work still in progress but ready for feedback, open a **Draft PR**. Move the issue to **Review** when the PR is ready for review.

### Step 6 — Review and update

- Request **at least one reviewer** other than the author.
- Reply to feedback and push follow-up commits to the same branch.
- Keep your branch current by merging `main` if necessary:

```bash
git fetch origin
git merge origin/main
```

- Rerun applicable checks after resolving conflicts.
- Do **not** merge with failing required checks. Do not force-push shared branch history.
- When the change is approved and required checks pass, use **Squash and merge** (per `CONTRIBUTING.MD`).

### Step 7 — Finish and clean up

After merge:

1. Confirm that the issue's acceptance criteria were met and any follow-up tasks are documented.
2. Let `Closes #123` close the linked issue automatically, or update it manually if it is not fully complete.
3. Move the issue to **Done** only when its criteria are satisfied.
4. Delete the remote topic branch and clean up your local branch:

```bash
git switch main
git pull origin main
git branch -d feature/barometer-driver
```

---

## 4. Definition of Done (DoD)

Before declaring an issue complete, confirm the applicable items:

- [ ] Acceptance criteria have been met and demonstrated.
- [ ] Code or documentation is focused, readable, and reviewed.
- [ ] Applicable formatting, linting, and tests have passed (or limitations are explained).
- [ ] Firmware builds for the target if firmware code changed and the required toolchain is available.
- [ ] Hardware behavior was verified **if required**, with board/setup and results recorded.
- [ ] New configuration, wiring, interfaces, or design decisions are documented.
- [ ] PR is approved, merged into `main`, and linked to the issue.
- [ ] Remaining risks or follow-up work are captured clearly.

A **technical spike** is done when it produces a reproducible experiment, results, and a decision—not necessarily production code. A **documentation-only** task does not need hardware testing.

---

## 5. Recommended first contributions

If you're new to C++, FreeRTOS, or the codebase, start with a small issue:

1. **Documentation:** Verify the setup guide on your computer and fix missing steps.
2. **Host C++ test:** Add unit tests for a `FlightState` transition or invalid sensor sample.
3. **Hardware bring-up:** Once the C++ build is available, verify board startup in an approved bench setup and record the result.
4. **Driver experiment:** Read one sensor ID/register and report success/error codes; do not build an entire sensor stack at once.
5. **FreeRTOS spike:** Create a narrowly scoped experiment proving kernel startup and two task executions; document startup/interrupt ownership.

For the December 18 milestone, prioritize a **working, reproducible bench prototype** over additional abstractions or large untested features.

---

## 6. When something goes wrong

- **Blocked on tooling?** Comment on the issue with the command, exact error, OS/toolchain, and what you already tried.
- **Missing GitHub labels/iteration?** Ask a maintainer to configure the Project; don't invent an alternative sprint tracker.
- **Hardware not available?** Test the portable portion on the host and mark hardware verification as outstanding.
- **Disagreement about design?** Discuss options on the issue or GitHub Discussions, then document the decision and reasoning.
- **CI fails?** Fix the failure or explain why the check is unrelated; do not merge with a failing required check.
- **Safety-critical behavior touched?** Escalate for careful review. Bench demonstration does not establish flight readiness.

## 7. Quick reference

```text
GitHub Project:  Backlog → Ready → In Progress → Review → Done
Issue types:     Task / Feature | Bug Report | Technical Spike
Branch format:   type/short-description
PR requirements: Related issue + summary + validation + reviewer
Merge strategy:  Squash and merge
Recipe discovery: just --list
```

**Related documents:** [Setup](SETUP.md) · [Contribution rules](../CONTRIBUTING.MD) · [Agent guide](../AGENTS.md) · [Architecture](ARCHITECTURE.md) · [Repository](https://github.com/FIU-SEDS/cmfs)
