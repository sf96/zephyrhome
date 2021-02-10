all:
	cmake -B build -GNinja -DBOARD=nucleo_f103rb
	ninja -C build

emulator:
	renode --execute "s @scripts/renode_emulator.resc"

documentation:
	make -C documentation html

.PHONY: all renode doc
