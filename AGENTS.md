# AGENTS.md — KILLA CITY (Master Game Design & Engineering Specification)

## 1. Project Identity & Repository Context
- **Game Title:** *Killa City*
- **Repository:** `https://github.com/josephdavis8484-sys/KIlla_City_DEMO.git`
- **Engine & Target Platforms:** Unreal Engine 5 (Windows 11, DirectX 12), targeting PC first with console-ready architecture for **PlayStation 5** and **Xbox Series X|S**.
- **Target Rating:** **ESRB M (17+) / PEGI 18** (Strictly compliant to avoid Adults Only 18+ console storefront bans).
- **Theme & Tone:** **Gritty Neo-Noir / Bio-Crime Thriller** (*Grand Theft Auto IV* meets *Resident Evil* with pitch-black Midwest satire). Heavy focus on desperation, the consequences of greed, exaggerated violence, and watching a vibrant Heartland city slowly rot from the inside out because of the player's own product.
- **Elevator Pitch:** Start with `$0` in Kansas City and build a criminal empire out of stolen copper, boosted cars, and a synthetic street drug that rots minds and mutates flesh. Across four dynamic seasons, every batch you cook lines your pockets while turning neighbors, street-walkers, and wildlife into bloodthirsty monsters—forcing you to survive the biological nightmare you profited from.

---

## 2. Codex Engineering Strategy & Rules
1. **C++ Core + Lightweight Blueprints:** Because Unreal Engine `.uasset` and `.umap` files are binary, **implement all core gameplay systems, state machines, economy logic, AI controllers, weather managers, and vehicle wrappers in C++ (`Source/KillaCity/`)** exposed via `UPROPERTY(EditAnywhere, BlueprintReadWrite)` and `UFUNCTION(BlueprintCallable)`.
2. **Console & Memory Discipline:** Use `TWeakObjectPtr` for dynamic NPC/AI references, avoid hard synchronous asset loads in `Tick`, and design around Unreal's **World Partition** and **Lumen Lite** so the prototype scales cleanly to `60 FPS` on PS5 and Xbox Series X|S.
3. **ESRB M (17+) Compliance Rules (Non-Negotiable):**
   - Street-walker / adult encounters must remain **implied** (camera pan/fade or exterior vehicle rock—never explicit on-screen nudity or interactive sexual mini-games).
   - Drug names and chemical recipes must remain **fictionalized** (e.g., *"Show-Me Blue"*, *"Heartland Dust"*) and must never resemble real-world instructional chemistry.

---

## 3. Core Gameplay Loop
1. **Zero-Dollar Start & Scavenging:** Player begins with `$0`, enters buildings seamlessly (houses, gas stations, coffee shops, strip clubs, casinos, auto shops, bars/nightclubs, skating rinks, pawn shops, stores), steals random items (copper pipes, TVs, jewelry, cash registers) and vehicles (cars, motorcycles, boats, helicopters, planes), and fences them for `DirtyCash`.
2. **Cook & Formulate:** Buy or steal precursor chemicals and lab equipment; cook batches of the synthetic zombie drug while balancing **Purity** (sale price) against **Volatility** (speed and severity of user mutation).
3. **Distribute & Launder:** Sell doses to street-walkers, clubgoers, and addicts; launder dirty cash through Missouri River casinos and front businesses (`CleanCash`) to avoid federal heat.
4. **Survive the Outbreak & Seasons:** Fight or evade escalating KCPD/SWAT/HAZMAT/National Guard wanted levels (1–5 stars) and mutated human/animal hordes across **Spring, Summer, Fall, and Winter** (including interactive snow-day activities), locking in **1 of 9 endings** that set up the **I-70 East: St. Louis expansion**.

---

## 4. Playable Characters & 9-Ending Matrix
Players select from **3 protagonists**, each starting in a distinct Kansas City district with `$0`, a unique passive perk, and a 2-axis morality/choice meter governing **3 distinct endings** (**9 endings total**):

| Character | Starting District | Core Passive Perk | Choice Axis | 3 Endings |
| :--- | :--- | :--- | :--- | :--- |
| **1. Dr. Julian Vance**<br>*(Disgraced Chemist)* | Hospital Hill / Troost Ave | **Master Formulator:** Cooks higher-purity batches for 2x profit or laces volatile strains for rapid weaponized mutations. | **Greed vs. Guilt** | **1. Kingpin of Ash:** Weaponizes horde to breach Broadway Bridge blockade and escapes to St. Louis with empire.<br>**2. The Cure:** Disperses aerosolized antidote from KC Power & Light HVAC during blizzard and surrenders.<br>**3. Patient Zero:** Cornered and broke, injects pure strain to survive SWAT breach and becomes KC's apex monster. |
| **2. Marcus "Mack" Kowalski**<br>*(Washed-Up Enforcer)* | West Bottoms / 12th St Bridge | **Heavy Handed:** `-30%` incoming melee/bullet damage, `2x` faster vehicle hotwiring, intimidates shopkeepers without firing. | **Loyalty vs. Brutality** | **1. Iron Fist:** Crushes National Guard at Union Station and rules frozen downtown KC as feudal warlord.<br>**2. State's Evidence:** Escorts FBI convoy across icy I-70 during whiteout to enter WitSec in St. Louis.<br>**3. Blaze of Glory:** Surrounded in West Bottoms warehouse, detonates fuel tanks to wipe out breach team and horde. |
| **3. Selena "Lux" Morales**<br>*(Nightlife Hustler)* | Westport | **Velvet Rope:** Bypasses VIP bouncers, `+25%` sale prices to wealthy clubgoers, recruits street-walkers/bartenders as lookouts. | **Self-Preservation vs. Syndicate Power** | **1. Untouchable:** Washes millions offshore, fights through icy I-70 to private airfield, flies to St. Louis.<br>**2. Queen of Ash:** Fortifies Power & Light with generators and mercenaries, ruling the warmest oasis in ruined KC.<br>**3. Betrayed:** Alienated bodyguards lock her Westport penthouse and lace her champagne with her own zombie drug. |

---

## 5. Full Seasonal Mission Trees (All 3 Characters)

### 5.1 Dr. Julian Vance (The Disgraced Chemist)
- **Act I (Spring — Broke to Starter Hustler):**
  1. *Copper & Cash (Tutorial):* Burglarize West Bottoms warehouses & Waldo house; fence copper/jewelry at Independence Ave pawn shop for lab capital.
  2. *Night Shift at Hospital Hill:* Infiltrate university lab for centrifuge & sedatives. **Choice:** Leave guard tied cleanly (`Guilt +1`) or frame him (`Greed +1`).
  3. *Street Testing:* Cook batch #1 and distribute free samples outside an 18th & Vine dive bar; witness first human mutation and police response.
- **Act II (Summer — Street Dealer to Kingpin):**
  4. *Neon & Nausea:* Push product inside a Power & Light nightclub & strip club; fend off rival dealers.
  5. *House Money:* Launder `$50,000` at Missouri River riverboat casinos via rigged blackjack tables.
  6. *Bad Batch in Brookside (Branch):* Contaminated batch mutates frat house and neighborhood dogs. **Path A (`Greed`):** Harvest mutated animal blood for deadlier strain. **Path B (`Guilt`):** Tranquilize infected before media arrives.
- **Act III (Fall — Empire to Quarantine):**
  7. *Swope Park Safari:* Hunt mutated coyotes and an escaped zoo bear near Swope Park.
  8. *Wheels Up at Wheeler:* Steal twin-engine plane from Charles B. Wheeler Downtown Airport to air-drop supply crates across the Missouri River.
  9. *The Antidote Dilemma (Story Lock):* Raid KCK pharmaceutical warehouse for **Stabilizer** (locks *Cure* path) or **Acoustic Weaponizer** (locks *Kingpin* path).
- **Act IV (Winter — Finales):** *Snowpiercer on the I-70* (Kingpin), *Ground Zero* (Cure), or *Cold Turkey* (Patient Zero).

### 5.2 Marcus "Mack" Kowalski (The Washed-Up Enforcer)
- **Act I (Spring):**
  1. *Dead Weight (Tutorial):* Grind off parole ankle monitor in West Bottoms auto shop; boost muscle car to East Bottoms chop shop.
  2. *Protection Racket:* Shake down gas station, pawn shop, and diner on Independence Ave (**Choice:** Skim cash `Brutality +1` vs. cut break for police tips `Loyalty +1`).
  3. *Hijacking the Cook:* Rob rival RV lab under I-35 overpass and sell stolen batch around 18th & Vine.
- **Act II (Summer):**
  4. *Skate or Die:* Raid rival gang's Raytown roller skating rink front during a packed Friday skate night.
  5. *High Roller Heist:* Rob Missouri River casino vault and escape via speedboat during thunderstorm.
  6. *Dog Eat Dog (Branch):* KCK stash shootout mutates stray pitbulls. **Path A (`Brutality`):** Cage mutated dogs as attack weapons. **Path B (`Loyalty`):** Put down animals and fortify block.
- **Act III (Fall):**
  7. *Chopper Down at Wheeler:* Hijack helicopter at Downtown Airport to shoot down rival cartel planes.
  8. *Penthouse Siege:* Storm Country Club Plaza luxury hotel occupied by corrupt officials and cartel bosses.
  9. *The Blockade Betrayal (Story Lock):* Heart of America Bridge sealed by National Guard. Turn informant for FBI immunity (*State's Evidence*) or assault Guard checkpoint (*Iron Fist* / *Blaze of Glory*).
- **Act IV (Winter — Finales):** *King of the Icebox* (Iron Fist), *One-Way Ticket East* (State's Evidence), or *Last Call in the West Bottoms* (Blaze of Glory).

### 5.3 Selena "Lux" Morales (The Nightlife Hustler)
- **Act I (Spring):**
  1. *Champagne & Pickpockets (Tutorial):* Talk past Westport bouncers, spike crooked contractors' drinks, lift watches/keys, fence on Broadway.
  2. *Backroom Ledger:* Crack Troost strip club safe for cash & politician blackmail ledger (**Choice:** Blackmail `Syndicate Power +1` vs. sell ledger `Self-Preservation +1`).
  3. *Designer High:* Rebrand wholesale pills as luxury club drug and push via street-walkers outside Power & Light.
- **Act II (Summer):**
  4. *Red Light District:* Team up with Independence Ave street-walkers for a motel honey-trap ambush against rival pimps/dealers.
  5. *High-Stakes Wash:* Rig high-roller poker aboard Missouri River casino boat to launder `$100,000`.
  6. *Disco Inferno (Branch):* Foam party outbreak at Crossroads warehouse club. **Path A (`Syndicate Power`):** Barricade exits and extort club deed. **Path B (`Self-Preservation`):** Pull fire alarms, rescue dancers, burn VIP evidence.
- **Act III (Fall):**
  7. *Midnight at the Rink:* Survive simultaneous SWAT/cartel raid and mutated stray dog breach at North KC skating rink.
  8. *Penthouse Airlift:* Steal/charter luxury helicopter at Downtown Airport to smuggle product over bridge checkpoints to Overland Park & Lee's Summit.
  9. *The Blackmail Summit (Story Lock):* Infiltrate Kaufman Center gala; steal offshore exit accounts (*Untouchable*) or execute cartel bosses (*Queen of Ash*).
- **Act IV (Winter — Finales):** *First Class Out of Hell* (Untouchable), *Last Dance at Power & Light* (Queen of Ash), or *Closing Time* (Betrayed).

---

## 6. Kansas City Geography & Map Architecture
- **Map Reference:** `SKM_C300i26112311460.pdf` in repo root[cite: 1]. Encloses the **I-435 / I-470 beltway** plus southern Johnson County / Lee's Summit corridors (~25x28 miles real-world compressed to **`6 km x 7 km`** in-game scale)[cite: 1].
- **Perimeter Quarantine Borders:** Outer loop highways (I-435 North/West, Hwy 150 South, I-435/I-470 East) use highway detours, police checkpoints, and National Guard concrete blockades instead of invisible walls[cite: 1]. **I-70 East** serves as the locked finale gate to the **St. Louis expansion**[cite: 1].
- **6 District Zones:**
  1. **Urban Core:** Downtown KC, Power & Light, Crossroads, Union Station, Charles B. Wheeler Downtown Airport[cite: 1].
  2. **Industrial Riverfront:** West Bottoms, KCK meatpacking/chemical plants, Sugar Creek, Missouri Riverboat Casinos[cite: 1].
  3. **Midtown / Culture:** Westport, Country Club Plaza, Hospital Hill, 18th & Vine[cite: 1].
  4. **East Side / Lakes:** Independence, Raytown, Lee's Summit, Longview Lake, I-70 East St. Louis Gate[cite: 1].
  5. **South Suburbs (JoCo):** Overland Park, Leawood, Olathe (high-value house burglaries & wealthy buyers)[cite: 1].
  6. **Northland & Parks:** Liberty, Gladstone, Swope Park / KC Zoo (mutated wildlife, sledding hills, hidden barn labs)[cite: 1].
- **Enterable Building Standard:** All modular doorways must clear **`140cm` wide x `240cm` tall** to accommodate third-person camera collision and sprinting/combat.

---

## 7. C++ Software Architecture (`Source/KillaCity/`)

Organize and implement all C++ classes under `Source/KillaCity/` (ensure `KillaCity.Build.cs` includes `Core`, `CoreUObject`, `Engine`, `InputCore`, `EnhancedInput`, `AIModule`, `NavigationSystem`, `ChaosVehicles`, and `UMG`):

```text
Source/KillaCity/
├── KillaCity.Build.cs
├── Core/
│   ├── KillaCityTypes.h            # Enums & Structs (ECharacterArchetype, EMutationStage, ESeasonType, FDrugBatch)
│   ├── KillaCityGameMode.h/.cpp    # Active protagonist, global outbreak tier, vertical slice loop controller
│   └── KillaCityGameState.h/.cpp   # City-wide infection count, active season/weather, global wanted state
├── Interfaces/
│   └── InteractableInterface.h/.cpp # IInteractableInterface (GetInteractPrompt, OnInteract)
├── Player/
│   ├── KillaCharacter.h/.cpp       # Enhanced Input, camera line-trace interaction, locational combat, snowball throw
│   └── EconomyComponent.h/.cpp     # DirtyCash, CleanCash, StolenLootValue, PrecursorChemicals, DrugInventory, Laundering
├── World/
│   ├── LootableActor.h/.cpp        # Stealable items (copper pipes, TVs, jewelry, cash registers)
│   ├── PawnShopActor.h/.cpp        # Fences StolenLootValue -> DirtyCash; sells weapons & precursors
│   ├── DrugLabActor.h/.cpp         # Cooking mini-game (Heat, Stir, Catalyst -> outputs FDrugBatch)
│   ├── CasinoLaundryActor.h/.cpp   # Converts DirtyCash -> CleanCash (85% rate) to reduce federal heat
│   ├── WeatherSeasonManager.h/.cpp # 4-season manager + MPC_SeasonWeather snow/wetness + vehicle ice friction
│   └── SnowActivityActors.h/.cpp   # ASnowballProjectile, ASledVehicle, ASnowmanActor (stash/bomb concealment)
├── AI/
│   ├── CitizenNPCCharacter.h/.cpp  # Pedestrian / Street-Walker / Animal base class with 4-stage Mutation State Machine
│   ├── CitizenAIController.h/.cpp  # Switches AI between Wander, OverdoseTwitch, FeralChase, and PackHunt
│   └── PoliceSpawnerManager.h/.cpp # 5-Star Wanted System (Patrol -> SWAT -> HAZMAT Bio-Unit -> National Guard)
├── Vehicles/
│   └── KillaVehiclePawn.h/.cpp     # ChaosVehicle wrapper implementing IInteractableInterface + winter ice grip multiplier
└── UI/
    └── KillaCityHUDWidget.h/.cpp   # UMG C++ base widget binding Cash, Drug Batches, Wanted Stars, Prompt, Cooking Bars