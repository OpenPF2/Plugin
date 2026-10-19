# Contributing to OpenPF2

This repository enforces strict, opinionated conventions for C++ formatting. For matters not specified here, match the nearest equivalent file. Resolve competing conventions using the process below. This document captures the conventions used repeatedly across the plugin's runtime, editor, Blueprint-node, and test modules.

The shared Unreal guidance and skill installation instructions are maintained in the [Unreal Best Practices repository](https://github.com/GuyPaddock/skill-unreal-best-practices). This guide documents the conventions specific to OpenPF2.

## Scope

This guide is focused on:

- C++ headers and sources under `Source/`
- Automation specs under `Source/OpenPF2Tests`
- Contributor expectations for code reviews and pull requests

For high-level project context, installation, and licensing background, see [README.md](README.md).

## Quick Start

If you only read one section, follow these rules:

- Match Unreal Engine idioms first, then match the nearest equivalent OpenPF2 file.
- Preserve the correct license header on every C++ file.
- Keep headers lightweight and prefer forward declarations where possible.
- Keep `Public/` for API surface and `Private/` for implementation details.
- Preserve section banners, documentation style, and local formatting in edited files.
- Use `this->` consistently in member functions, as the codebase already does.
- Treat GAS, replication, and authority flow as architectural concerns, not local implementation details.
- Add or update automation specs for gameplay logic, reusable math, attribute calculations, and library behavior.
- Avoid unrelated reformatting or include churn.

## When Editing Existing Code

### Bumping Copyrights

If you are editing a file for the first time in a new year (e.g., the last edit was in 2025 and you are now editing the file in 2026), be sure to update the copyright in the file header accordingly.

If this is the first time you have contributed to the file, you may reference yourself via an additional line in the copyright portion of the file header, as follows:
```
// Portions Copyright YEAR, YOUR NAME.
```

Your contributions must be licensed under the same license as the existing file (e.g., MPL or OGL).


### Maintaining Consistency

Most contributions will modify existing files. Preserve unrelated code and follow the resolved conventions for the work in scope.

- Follow established local conventions for matters not specified by this guide.
- Ask the user about unresolved conflicts with project instructions, the [Unreal Best Practices skill](https://github.com/GuyPaddock/skill-unreal-best-practices/blob/43183ae96dbb15276cd7be1413fc41af8b387c37/SKILL.md), formatter
  behavior, or established local conventions before making the affected edit. Continue independent work when possible.
- Honor prior resolutions for the same conflict and scope. Preserve public APIs, framework-required contracts, and
  supported engine/compiler constraints rather than breaking them to satisfy a style preference.
- Do not reformat unrelated code.
- Preserve section banners and comment structure.
- Preserve public API shape unless the change explicitly requires an API break.
- Avoid include churn unless it improves correctness or dependency hygiene.
- Keep existing ReSharper suppressions if they still apply.
- Prefer narrow `disable once` suppressions over broad file-level suppression.

When touching gameplay code:

- Preserve server/client initialization behavior.
- Be explicit about authority checks.
- Keep replication declarations and `OnRep_...` behavior synchronized.
- Use existing ability-system wrappers and interfaces instead of bypassing them.
- Treat passive gameplay effects, dynamic tags, and attribute sets as project-level architecture.

### What "Architectural Concerns" Means Here

In OpenPF2, GAS, replication, and authority flow are part of the gameplay architecture, not just implementation details hidden inside a class.

That means a small local change can still have system-wide effects if it changes:

- when abilities initialize
- who is allowed to mutate gameplay state
- what must replicate
- what clients can infer locally
- how passive gameplay effects, tags, and queued commands stay in sync
- how Blueprint-facing events and interfaces behave in multiplayer

In practice:

- Do not "simplify" authority checks unless you have verified the client/server behavior.
- Do not move ASC initialization, refresh, or passive-effect activation casually.
- Do not update replicated gameplay state in whatever layer is convenient, and do not treat replicated gameplay fields as ordinary local state.
- Do not bypass existing interfaces or wrappers for one-off convenience.
- When changing gameplay code, think in terms of lifecycle, ownership, replication, and server/client behavior first.
- When a change affects ownership, replication timing, ability initialization, or multiplayer event flow, treat it as a design-level change and test it accordingly.

Examples from the current codebase:

- `APF2CharacterBase` ability initialization: `InitializeOrRefreshAbilities()` is triggered from both possession-time and controller-replication paths. Removing one because it looks redundant would change whether the server, the client, or both reinitialize the ASC actor info at the right time.
- `APF2CharacterBase::CharacterLevel`: this is replicated gameplay state, not just a local field. Treating level as ordinary local state would risk desynchronizing level-dependent abilities, effects, and UI.
- Lazy interface events objects in `APF2CharacterBase` and `UPF2CommandQueueComponent`: these are created on demand because constructor-time creation caused multiplayer bugs through shared CDO state. A seemingly cleaner refactor back to constructor allocation would break network behavior.
- `UPF2CommandQueueComponent` queue mutations: the replicated queue and its event broadcasts are part of one behavior. Bypassing the component to manipulate the underlying array directly could change what remote clients observe and when they observe it.

If a change feels local in code but alters who owns the truth, when clients learn it, or how GAS state is applied, it is architectural in this project.

## When Adding New Code

### Repository Layout

The plugin is organized into separate modules with distinct roles:

- `Source/OpenPF2GameFramework`: runtime gameplay code, GAS integrations, interfaces, utilities, and Blueprint libraries
- `Source/OpenPF2BlueprintNodes`: custom K2 nodes and Blueprint-node utilities
- `Source/OpenPF2EditorSupport`: editor-only customizations and authoring helpers
- `Source/OpenPF2Tests`: automation specs and test scaffolding

Follow the module's existing structure:

- Public API goes in `Public/`
- Internal implementation goes in `Private/`
- Related subsystems stay grouped in subfolders such as `Abilities/`, `CharacterStats/`, `Commands/`, `Items/`, `ModesOfPlay/`, or `Utilities/`
- File names use the `PF2` prefix consistently for project-owned types

### File Headers and Licensing

Every C++ file in this repository starts with a license header. Do not omit it in new files.

There are two common header variants in the current codebase:

- MPL 2.0 headers for engine/framework code
- OGL headers for files that contain Pathfinder 2E rules text, mechanics text, or other Open Game Content

If you are unsure which header applies:

- Check nearby files in the same subsystem.
- Consult `LICENSE.txt`.
- Preserve the existing header when editing a file.

The first line of the new file must state:
```
// OpenPF2 Game Framework for Unreal Engine, Copyright YEAR, Guy Elsmore-Paddock. All Rights Reserved.
```

You may then reference yourself in the second line of the file, as follows:
```
// Portions Copyright YEAR, YOUR NAME.
```

Your contributions must be licensed under either the MPL or OGL.

### File Structure

Most headers follow this order:

1. License header
2. `#pragma once`
3. Engine and project includes
4. generated-header include last
5. section banner comments
6. forward declarations
7. delegate/type declarations
8. class/struct/interface declarations

Many files use large section banners like this:

```cpp
// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
```

Use these banners when a file is large enough to benefit from them. They are common in public headers and complex source files.

### Naming Conventions

Follow Unreal naming conventions and the project's existing prefixes:

- `U`, `A`, `F`, `E`, `I`, and `T` prefixes for Unreal-reflected and UObject-style types
- `UPF2...`, `APF2...`, `FPF2...`, `EPF2...`, `IPF2...`, `TPF2...` for project types
- `b` prefix for booleans such as `bAreAbilitiesInitialized`
- Descriptive PascalCase names for constants, pin names, and similar identifiers
- Method names that describe actions and type names that describe responsibilities
- Descriptive Boolean predicate names, retaining Unreal's `b` prefix and the project's established prefixes
- `FPF2...Spec` for automation spec classes
- `.spec.cpp` for spec file suffixes

Prefer descriptive names over abbreviations unless the abbreviation is already established in the codebase, such as `ASC`, `GE`, `GA`, `MMC`, or `DC`.

### Formatting

Apply the resolved rules below. Use surrounding code for matters these rules leave unspecified.

- Use tabs for indentation in C++ files, displayed at width four.
- Prefer lines of 120 characters or fewer. Allow longer lines when materially clearer or when a literal cannot be wrapped cleanly.
- Put opening braces on the next line for functions, classes, structs, namespaces, control-flow statements, and lambdas.
- Allow readable short lambdas on one line when they fit the 120-character soft limit. Keep longer lambdas multiline.
- Give every control-statement body braces, including single-statement `if`, `else`, `for`, `while`, and `do` bodies.
- Keep pointer and reference symbols attached to the type: `UObject* Object`, `const FString& Name`.
- Use spaces inside control-flow parentheses only as already shown in nearby code.
- Match established constructor-initializer alignment, subject to the conflict-resolution process above.
- For consecutive same-type variables declared together, write the type once and put each variable on its own aligned line.
- Start a new declaration when the type changes. Keep separate declarations when long or complex initializers make grouping harder to read.
- Preserve each variable's actual type and qualification; pointer/reference declarators may need a symbol on each variable.
- Use explicit `nullptr` comparisons for object-pointer checks.
- Group related assignments and calls into short logical paragraphs. Prefer a blank line between setup assignments and calls unless they form one tight responsibility.
- Align assignment operators when doing so improves scanning without awkward wrapping.
- Keep short, simple value-choice ternaries on one line. Wrap them when aligning branches makes differences easier to compare, such as mirrored coordinates, visibility, or alignment choices.

#### Wrapping

- Break at higher syntactic boundaries before splitting nested expressions: assignments, argument lists, conditional headers, or chained calls.
- In compound conditions, parenthesize operands containing binary expressions when this clarifies grouping. Avoid redundant parentheses around standalone comparisons, unary expressions, or calls.
- Keep a wrapped declaration's return type and function name on the first line where practical. Put each parameter on its own following line, indented one additional level, and vertically align parameter names.
- Put the closing parenthesis on its own line aligned with the declaration start. For a wrapped standalone call, put arguments on following lines and the closing parenthesis on its own line aligned with the call's start.
- Wrap long Unreal annotations across lines. Omit spaces around `=` within metadata: `meta=(...)`, `Category="..."`, and `DisplayName="..."`.
- Prefer an `if` initializer when its variable is used only by that conditional. Keep the header on one line when it fits.
- If the header must wrap, put the initializer on its own line inside the parentheses and the condition on the next line with four additional spaces of leading indent.
- Hoist initialization when the value is reused afterward or the wrapped header reads awkwardly, preserving supported compiler and engine constraints.

Examples from the codebase:

```cpp
void APF2CharacterBase::OnRep_Controller()
{
	Super::OnRep_Controller();

	this->InitializeOrRefreshAbilities();
}
```

```cpp
explicit FPF2CharacterAbilityBoostSelection(
	const TSubclassOf<UPF2AbilityBoostBase>    BoostGameplayAbility,
	const TSet<EPF2CharacterAbilityScoreType>& SelectedAbilities
) :
		BoostGameplayAbility(BoostGameplayAbility),
		SelectedAbilities(SelectedAbilities)
{
}
```

### Class and Method Organization

- Declare nested types before fields, then fields before methods. Within each field or method group, use `public`, `protected`, `private` order.
- Within each visibility level's methods, put overrides before other methods. Group overrides by parent type in header-only subsections and order them according to the parent hierarchy.
- Implement methods in header declaration order. Put a true getter before its setter in both declarations and definitions.
- Use dedicated `Forward Declarations (to minimize header dependencies)` and `Delegates` sections when applicable.
- In C++ source sections, put content directly after the heading without a blank line. Keep section headings in headers rather than mirroring them in implementation files; this does not change Markdown heading spacing.

### Local Initialization and Method Shape

- Prefer local declarations near the top of their block, with the scoped `if` initializer exception above.
- Initialize at declaration unless initialization is materially expensive or the correct value depends on intervening work.
- Prefer `const` for unchanged locals and parameters. Top-level `const` on by-value parameters may be omitted in header declarations; prefer it in definitions unless intentionally moving from the parameter.
- Name significant behavioral, layout, and policy constants. Document what the value means and why it matters. Obvious literals such as zero, one, and straightforward geometry fractions need no extraction unless a name improves clarity.
- Prefer short methods with one or two responsibilities. Extract smaller units when this improves readability, isolation, or testability without obscuring control flow.
- Prefer one entry and one exit when readable. Use early returns for exceptional validation, clear guards, and cheap no-op cases when they avoid less readable nesting.

### Includes and Forward Declarations

Header hygiene is a strong convention in this repository.

- Prefer forward declarations in headers whenever a full definition is not required.
- Include generated headers last in the include list.
- Group includes by directory, separated by blank lines. Order engine groups before project groups and keep generated headers last.
- Use angle brackets for engine headers and quotes for project headers.
- Do not include large headers transitively "just in case."

Common pattern:

- Engine base includes first.
- Project headers next.
- Generated header last in headers.
- Implementation-only includes stay in `.cpp`.

### Class Design and Unreal API Style

The project favors explicit API surfaces and interface-based composition.

- Prefer interfaces for system boundaries and replaceable gameplay components.
- Prefer a minimal reflected interface wrapper using `UINTERFACE(MinimalAPI, ...)` when sufficient, and put the module API macro on the native `I...` interface exposing callable methods. Retain stronger exports where the API contract requires them.
- Keep reflected fields annotated with meaningful `UPROPERTY` and `UFUNCTION` metadata.
- Use `BlueprintCallable`, `BlueprintAssignable`, `BlueprintReadOnly`, and category metadata consistently when exposing behavior to Blueprint.
- Use `Transient`, replication, clamp, and editor metadata when the property semantics require it.
- Mark constructors `explicit` where appropriate.
- Use `mutable` only when there is a clear reason, such as lazily created event objects.

When adding public headers:

- Separate forward declarations, delegates, helper types, and class declarations with banner comments when the file is nontrivial.
- Keep comments focused on gameplay semantics and API contracts.

When writing reflected types:

- Use `USTRUCT(BlueprintType)` and `UCLASS(...)` only where reflection is required.
- Keep Blueprint categories consistent with the subsystem, for example `OpenPF2|Characters`.
- Prefer explicit event objects and multicast delegates for Blueprint bindings when following existing interface-event patterns.
- Use `meta=(CannotImplementInterfaceInBlueprint)` on interfaces when the existing design expects native implementations only.

For custom Blueprint nodes and editor code:

- Use `LOCTEXT_NAMESPACE` in `.cpp` files that define localized editor text.
- `#undef LOCTEXT_NAMESPACE` at the end of the file.
- Keep node titles, tooltips, and menu categories localized through `LOCTEXT`.

### Why OpenPF2 Uses `this->`

OpenPF2 uses `this->` heavily and consistently in non-static member functions. Follow that convention in edited files and new code.

Reasons this style works well in this codebase:

- It makes member access visually obvious in large classes with many reflected fields and helper methods.
- It distinguishes member state from locals and parameters.
- It keeps style uniform across regular classes and template-heavy code, where `this->` can also matter for dependent-name lookup.
- It makes accidental shadowing easier to notice during review because `this->Member` and `Member` read differently.

`this->` does not prevent shadowing by itself, and it does not silence compiler shadowing warnings. A shadowing warning still depends on compiler settings and on whether a local or parameter reuses a member name. What `this->` does provide is a clear way to say "use the member here" when a name is ambiguous to the reader.

## Comments, Logging, and Utilities

### Comments and Documentation

This codebase is thoroughly documented. New public APIs should be too.

- Use Doxygen-style block comments for classes, structs, delegates, methods, template parameters, and all member fields, including private state and nested-type fields.
- Document every enum value, not just its enum type.
- Do not duplicate inherited override documentation unless behavior differs meaningfully or project-specific context is needed.
- Lead each documented type, field, method, event, and enum value with one or two sentences explaining what it
  represents or why a caller uses it. Establish its role before describing execution order, storage, restrictions,
  or side effects. Apply the same rule to Blueprint descriptions and tooltips.
- Include `@param`, `@return`, and `@tparam` sections when applicable to explain the callable or template contract.
- Use inline comments sparingly and only when they explain non-obvious behavior, engine quirks, multiplayer caveats, or design constraints.
- Preserve helpful comments such as `BUGBUG:` notes when they still apply.

Good fits for comments in this repository include:

- Explaining multiplayer or replication edge cases
- Explaining why a type propagation rule exists in a K2 node
- Explaining Pathfinder rules assumptions behind an attribute or calculation

### Logging and Diagnostics

Logging is expected to be structured and contextual.

- Use the module's existing log category.
- Include enough context to identify the object or world involved.
- Prefer `GetIdForLogs()` and helper utilities such as `PF2LogUtilities` when available.
- Match existing severity usage: `VeryVerbose` for routine lifecycle tracing and `Warning` for recoverable issues.

Avoid adding noisy logs without context or logs that duplicate existing lifecycle messages.

### Utilities and Generic Code

Utility code in this repository is intentionally straightforward.

- Keep template utilities small and readable.
- Favor immutable-style helper functions that return new values rather than mutating inputs unless mutation is the natural Unreal pattern.
- Reserve containers before filling them when the size is known.
- Prefer descriptive lambda parameter names such as `PreviousValue` and `CurrentValue` when implementing reducer-style helpers.

## Blueprint Authoring

- When authoring Blueprint graphs, use Blueprint Assist if installed for the project's engine and available in the editor.
- Select and format only nodes added or changed by the task. Do not format the entire graph or expand formatting
  to unrelated connected nodes. Preserve unrelated node positions, comments, and authored comment groups.
- If selection-scoped formatting cannot be guaranteed, or Blueprint Assist is unavailable, arrange affected nodes
  manually. This guidance does not authorize installing the plugin or making unrelated asset changes.
- Preserve pin defaults and logical terminal connections during layout-only changes. Compile affected Blueprints,
  inspect their layout, and exercise the relevant behavior before accepting the result.

## Tests

Tests are first-class code in this repository.

- Place new automation specs under `Source/OpenPF2Tests/Private/Tests`.
- Use the existing shared base in `PF2SpecBase`.
- Prefer the `BEGIN_DEFINE_PF_SPEC` and `END_DEFINE_PF_SPEC` macros for specs.
- Structure specs with `BeforeEach`, `AfterEach`, `Describe`, and `It`.
- Write assertions with clear labels using `TestEqual`, `TestTrue`, and similar helpers.
- Reuse the provided test pawn, test character, and world setup helpers instead of rebuilding test scaffolding ad hoc.

Match current naming patterns:

- Pretty test name strings are namespaced like `"OpenPF2.CharacterAttributeSet"`.
- File names mirror the tested type or behavior, for example `PF2CharacterAttributeSet.spec.cpp`.

When adding tests for Blueprint-backed gameplay assets, follow existing helpers for loading blueprints synchronously from content paths.

## Pull Request Checklist

Before opening a change, confirm that you:

- Added the correct file header to any new source file.
- Matched the module's existing naming and formatting.
- Kept headers lean and moved implementation-only includes into `.cpp`.
- Updated or added automation specs for new gameplay logic.
- Verified Blueprint-facing names, categories, and metadata.
- Considered replication and GAS side effects for gameplay changes.
- Avoided unrelated formatting-only edits.

## A Note on Lists and Punctuation

This guide uses a simple punctuation rule for readability:

- Bullets that are sentence fragments usually do not end with periods.
- Bullets that are full sentences do end with periods.

That keeps short scan-friendly lists compact while still letting explanatory bullets read like normal prose. If a future edit changes a bullet from a fragment into a sentence, update the punctuation to match.

## When in Doubt

- Use the nearest equivalent file for unspecified matters; ask about unresolved conflicts and honor prior resolutions as described above.
- Prefer explicitness over cleverness.
- Prefer stable gameplay behavior over micro-optimizations.
- Ask in review whether a new pattern should become a project-wide convention before spreading it.
