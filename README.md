# eden-seed-finder

Find a seed of The Binding of Isaac: Repentance that Eden starts with certain items and cards, and the Home floor has some specific pickups. It works for v1.7.9b.

## Usage

put this folder in `/path/to/tboi/mods` (the directory where Isaac stores your mods).

### For other versions of TBOI

Extract Isaac's resources with `/path/to/tboi/tools/ResourceExtractor/ResourceExtractor.exe`, and then execute the following command:

```bash
cp /path/to/tboi/resources-dlc3/items.xml \
   /path/to/tboi/resources-dlc3/items_metadata.xml \
   item_data/
```

Change the `ITEM_COUNT` and `STAGE_COUNT` constants in `constants.hpp` according to your Isaac version.

---

The current `generator.cpp` aims to find a Eden seed with the Glowing Hourglass, Sacred Heart or other powerful passive items~~Proptosis/Polyphemus/Brimstone/Mutant Spider, a Strength card/Huge Growth card~~, and the Home floor containing both Mom's Knife and a wild item in the rightmost small room. It is intended for the Beast Ending speedruns. You can easily modify it to search for other items or cards.

```bash
g++ generator.cpp -o generator -O2
./generator > seeds.txt
```

Copy the contents of `seeds.txt` to the `seeds_list` in `main.lua`. Launch TBOI, enable this mod (named `eden_seed_finder`), and start a run as regular Eden. Press <kbd>T</kbd>, and the mod will start to search for a seed that contains Mom's Knife in Mom's Chest. All the seeds it found will be printed to the Debug Console, with ID of the item in the rightmost small room. Hold <kbd>Y</kbd> if you want to cancel the search.
