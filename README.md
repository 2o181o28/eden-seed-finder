# eden-seed-finder

Find a seed of The Binding of Isaac: Repentance that Eden starts with certain items, cards, health, pickups or stats, and the Home floor has some specific pickups. It works for Repentace v1.7.9b and Repentance+.

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

Assume that the generator being used is named `generator.cpp`, and make sure the script being used is named `main.lua`. You can easily modify the existing generators and scripts to search for other items or cards.

```bash
g++ generator.cpp -o generator -O2 -std=c++20
./generator > seeds.txt
```

Copy the contents of `seeds.txt` to the `seeds_list` in `main.lua`. Launch TBOI, enable this mod (named `eden_seed_finder`), and start a run as regular Eden. If you use `main_tmtrainer.lua`, you need to give yourself TMTRAINER, execute `stage 13` manually, and then enter the corridor below Isaac's bedroom. If you use `main_greed.lua`, start in Greed Mode. Press <kbd>T</kbd>, and the mod will start to search for a seed that meets the corresponding given conditions. For scripts older than `main_dz_exp.lua`, all the seeds they found will be printed to the Debug Console, with some additional information. The newer scripts will save their output in JSON format after <kbd>Y</kbd> is pressed, to `/path/to/tboi/data/eden_seed_finder/saveX.dat`. Hold <kbd>Y</kbd> if you want to cancel the search.
