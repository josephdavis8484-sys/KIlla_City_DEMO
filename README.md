# Killa City

This Unreal Engine 5.8 C++ project starts with **Copper & Cash**, Julian Vance's first tutorial. The warehouse, Waldo house, and pawn shop are greybox locations built at runtime.

## Open and play

1. Install the Windows C++ toolchain from [Epic's development setup guide](https://dev.epicgames.com/documentation/en-us/unreal-engine/setting-up-your-development-environment-for-cplusplus-in-unreal-engine).
2. Open `KillaCity.uproject` in Unreal Engine 5.8.4 and allow Unreal to build the project module.
3. Press **Play** in the editor. The greybox appears at runtime on the Entry map. Start from the default player start.
4. Use **WASD** to move, the **mouse** to aim, and **Space** to jump. Aim the crosshair at an item or the pawn shop counter and press **E**.

## Verify the tutorial

- Start as Julian Vance with $0 in dirty cash and $0 in stolen goods.
- Take the $60 copper pipe from the warehouse on the left and the $40 jewelry box from the house straight ahead.
- Fence them at the pawn shop on the right. Goods should return to $0, dirty cash should reach $100, and the HUD should show completion.
- You can fence the items in separate trips. Each item is collectible once per play session. The counter reports an empty inventory if you return without goods.
- Stop and restart Play to reset the prototype.

The prototype uses an engine primitive for the player and a compact greybox for the three locations. The full city and later missions are described in `AGENTS.md`.
