# GitHub Project Card: Story 9.1 - CLI Dashboard Menu Navigation

## 📋 Description

Build the core CLI navigation structure. Establish the customer menu loop, role switches, and admin dashboards. Implement consistent cancel/exit handlers.

## 🛠️ Files to Modify/Create

* **Modify**: [include/menu.h](../../../include/menu.h)
* **Modify**: [src/menu.c](../../../src/menu.c)
* **Modify**: [src/program.c](../../../src/program.c)

## 📖 Global References

* Consult the main program flowchart in [architecture.md](../../../docs/architecture.md#3-dependency-graph) and [PRD.md](../../../docs/requirements.md#2-user-roles--access-control).

## 🚀 Acceptance Criteria & Technical Requirements

* [ ] Program startup initiates the First-Run Setup (Story 2.1) if needed, then loads the Customer Menu.
* [ ] Customer Menu loops: Browse Products, Search/Sort, Place Order, Admin Login, Exit.
* [ ] Admin Menu loops: Manage Products, Manage Bundles, Sales Reports, Save Changes, Logout.
* [ ] Selection actions route correctly to sub-modules.
* [ ] Pressing `0` or selecting exit routes moves back up the menu level cleanly.
