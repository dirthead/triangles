QMAKE  	   ?= qmake
CMD 		= $(QMAKE) -o Makefile ../triangles.pro -spec linux-g++
DEBUG  		= CONFIG+=debug CONFIG+=qml_debug
RELEASE		= CONFIG+=release CONFIG+=qml_release
DEBUG_DIR 	= build_debug
RELEASE_DIR	= build_release

debug:
	mkdir -p $(DEBUG_DIR)
	[ ! -f $(DEBUG_DIR)/Makefile ] && ( cd $(DEBUG_DIR) && $(CMD) $(DEBUG) ) || true
	cd $(DEBUG_DIR) && make

release:
	mkdir -p $(RELEASE_DIR)
	[ ! -f $(RELEASE_DIR)/Makefile ] && ( cd $(RELEASE_DIR) && $(CMD) $(RELEASE) ) || true
	cd $(RELEASE_DIR) && make

both: debug release

clean: clean-debug clean-release

clean-debug:
	rm -rf $(DEBUG_DIR)

clean-release:
	rm -rf $(RELEASE_DIR)

